/*********************************************************************************
 Copyright 2017 GlobalPlatform, Inc.

 Licensed under the GlobalPlatform/Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

https://github.com/GlobalPlatform/SE-test-IP-connector/blob/master/Charter%20and%20Rules%20for%20the%20SE%20IP%20connector.docx

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*********************************************************************************/

#define _WIN32_WINNT 0x501
#define WIN32_LEAN_AND_MEAN

#define DEFAULT_BUFLEN 1024 * 64
#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT "66611"
#define DEFAULT_NAME "default_name"

#include <fstream>
#include <future>
#include <iostream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#include "nlohmann/json.hpp"
#include "plog/include/plog/Log.h"
#include "plog/include/plog/Appenders/ColorConsoleAppender.h"
#include "plog/include/plog/Appenders/RollingFileAppender.h"

#include "client/client_engine.h"
#include "config/config_wrapper.h"
#include "constants/request_code.h"
#include "constants/response_packet.h"
#include "terminal/flyweight_terminal_factory.h"
#include "terminal/terminals/terminal.h"
#include "terminal/terminals/utils/type_converter.h"

namespace client {

ClientEngine::~ClientEngine() {
	delete terminal;
}

ResponsePacket ClientEngine::initClient(std::string path, FlyweightTerminalFactory available_terminals, FlyweightRequests available_requests) {
	config.init(path);
	terminal = available_terminals.getFactory(config.getValue("terminal"))->create();
	requests = available_requests;

	// setup logger
	std::string log_path = config.getValue("log_path");
	std::string log_level = config.getValue("log_level", "info");
	static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;

	if (log_level.compare("debug") == 0) {;
		plog::init(plog::debug, log_path.c_str(), 1000, 5).addAppender(&consoleAppender);
	} else {
		plog::init(plog::info, log_path.c_str(), 1000, 5).addAppender(&consoleAppender);
	}

	LOG_INFO << "Client ready to be initialized";

	// launch terminal
	ResponsePacket response_packet;
	response_packet = terminal->init();
	if (response_packet.err_terminal_code != SUCCESS || response_packet.err_card_code != SUCCESS) {
		LOG_INFO << "Client unable to be initialized";
		return response_packet;
	}
	this->initialized = true;

	LOG_INFO << "Client initialized successfully";
	return response_packet;
}

ResponsePacket ClientEngine::loadAndListReaders() {
	ResponsePacket response;
	if (!initialized.load()) {
		ResponsePacket response_packet = { .response = "KO", .err_client_code = ERR_CLIENT_NOT_INITIALIZED, .err_client_description = "Client must be initialized correctly" };
		return response_packet;
	}
	return terminal->loadAndListReaders();
}

ResponsePacket ClientEngine::connectClient(const char* reader, const char* ip, const char* port) {
	ResponsePacket response;
	if (!initialized.load()) {
		ResponsePacket response_packet = { .response = "KO", .err_client_code = ERR_CLIENT_NOT_INITIALIZED, .err_client_description = "Client must be initialized correctly" };
		return response_packet;
	}

	if (connected.load()) {
		ResponsePacket response_packet = { .response = "KO", .err_client_code = ERR_CLIENT_NOT_INITIALIZED, .err_client_description = "Client is already connected" };
		return response_packet;
	}

	response = terminal->connect(reader);
	if (response.err_card_code < 0 || response.err_terminal_code < 0) {
		return response;
	}

	std::string name = config.getValue("name", DEFAULT_NAME);

	LOG_INFO << "Client trying to connect on IP " << ip << " port " << port;
	WSADATA wsaData;
	struct addrinfo *result = NULL, *ptr = NULL, hints;

	// initialises Winsock
	int retval = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (retval != 0) {
		ResponsePacket response_packet = { .response = "KO",  .err_client_code = ERR_NETWORK, .err_client_description = "WSAStartup failed" };
		return response_packet;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// resolves the server address and port
	retval = getaddrinfo(ip, port, &hints, &result);
	if (retval != 0) {
		WSACleanup();
		LOG_DEBUG << "Failed to call getaddrinfo() "
				  << "[ip:" << ip << "][port:" << port << "]";
		ResponsePacket response_packet = { .response = "KO",  .err_client_code = ERR_NETWORK, .err_client_description = "Can't resolve server address and port" };
		return response_packet;
	}

	// attempts to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
		this->client_socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		LOG_DEBUG << "Socket = " << this->client_socket;
		if (this->client_socket == INVALID_SOCKET) {
			LOG_DEBUG << "Failed to call socket() "
					  << "[ip:" << ip << "][port:" << port << "][WSAError:" << WSAGetLastError() << "]";
			ResponsePacket response_packet = { .response = "KO", .err_client_code = ERR_NETWORK, .err_client_description = "Socket creation failed" };
			return response_packet;
		}

		// connects to server
		retval = connect(this->client_socket, ptr->ai_addr, (int) ptr->ai_addrlen);
		if (retval == SOCKET_ERROR) {
			closesocket(this->client_socket);
			client_socket = INVALID_SOCKET;
			continue;
		}
		send(this->client_socket, name.c_str(), strlen(name.c_str()), 0);
		Sleep(1000);
		break;
	}

	freeaddrinfo(result);

	if (this->client_socket == INVALID_SOCKET) {
		WSACleanup();
		LOG_DEBUG << "Failed to connect to server "
				  << "[ip:" << ip << "][port:" << port << "]";
		ResponsePacket response_packet = { .response = "KO", .err_client_code = ERR_NETWORK, .err_client_description = "Can't connect to server" };
		return response_packet;
	}

	this->connected = true;
	LOG_INFO << "Client connected on IP " << ip << " port " << port;

	std::thread thr(&ClientEngine::waitingRequests, this);
	thr.detach();

	return response;
}

ResponsePacket ClientEngine::disconnectClient() {
	if (!connected.load()) {
		LOG_DEBUG << "Client unable to disconnect - Not connected yet";
		ResponsePacket response_packet = { .response = "KO", .err_client_code = ERR_CLIENT_NOT_INITIALIZED, .err_client_description = "Client must be initialized correctly." };
		return response_packet;
	}

	connected = false;
	closesocket(client_socket);
	client_socket = INVALID_SOCKET;
	WSACleanup();
	ResponsePacket response = terminal->disconnect();
	if (notifyConnectionLost != 0) notifyConnectionLost("End of connection");
	LOG_INFO << "Client disconnected successfully";
	return response;
}

ResponsePacket ClientEngine::waitingRequests() {
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	LOG_INFO << "Client ready to process incoming requests";

	// receives until the server closes the connection
	while (connected.load()) {
		int retval = recv(client_socket, recvbuf, recvbuflen, 0); // recv json request
		if (retval > 0) {
			recvbuf[retval] = '\0';
			if (notifyRequestReceived != 0) notifyRequestReceived(recvbuf);
			LOG_INFO << "Data received from server: " << recvbuf;
			std::async(std::launch::async, &ClientEngine::handleRequest, this, client_socket, recvbuf);
		} else if (retval < 0) {
			LOG_DEBUG << "Failed to receive data from server "
					  << "[socket:" << client_socket << "][recvbuf:" << recvbuf << "][size:" << recvbuflen << "][flags:" << NULL << "][WSAError:" << WSAGetLastError() << "]";
			this->disconnectClient();
		}
	}
	LOG_INFO << "Client not waiting for requests";

	ResponsePacket response_packet;
	return response_packet;
}

ResponsePacket ClientEngine::handleRequest(SOCKET socket, std::string request) {
	nlohmann::json response;
	ResponsePacket response_packet;

	nlohmann::json j = nlohmann::json::parse(request);
	IRequest* request_handler = requests.getRequest(j["request"]);
	unsigned long int length;
	unsigned char* command = utils::stringToUnsignedChar(j["data"].get<std::string>(), &length);
	std::future<ResponsePacket> future = std::async(std::launch::async, &IRequest::run, request_handler, terminal, this, command, length);

	// blocks until the timeout has elapsed or the result becomes available
	if (future.wait_for(std::chrono::milliseconds(j["timeout"])) == std::future_status::timeout) {
		LOG_DEBUG << "Response time from terminal has elapsed "
				  << "[request:" << request << "]";
		ResponsePacket response_packet = { .response = "KO", .err_client_code = ERR_TIMEOUT, .err_client_description = "Request terminal time elapsed" };
		response = response_packet;
	} else {
		response = future.get();
	}

	std::string to_send = response.dump();
	int retval = send(socket, to_send.c_str(), strlen(to_send.c_str()), 0);
	if (notifyResponseSent != 0) notifyResponseSent(to_send.c_str());
	if (retval == SOCKET_ERROR) {
		LOG_DEBUG << "Failed to send response to server "
				  << "[socket:" << socket << "][buffer:" << to_send.c_str() << "][size:" << strlen(to_send.c_str()) << "][flags:" << NULL << "]";
		ResponsePacket response_packet = { .response = "KO", .err_client_code = ERR_NETWORK, .err_client_description = "Network error on send response" };
		return response_packet;
	}
	LOG_INFO << "Data sent to server: " << to_send;

	return response_packet;
}

} /* namespace client */

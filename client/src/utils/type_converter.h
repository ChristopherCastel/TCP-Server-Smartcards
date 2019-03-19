/*
 * string_hex_converter.h
 *
 *  Created on: 05 Mar 2019
 *  Author: STMicroelectronics
 *  Purpose: Used to convert unsigned char* to string and vice versa.
 *  By example:
 *  unsigned char bytes[] = { 0x0F, 0xFF, 0x44, 0x4A } <===> std::string s = "0F FF 44 4A"
 */

#ifndef UTILS_TYPE_CONVERTER_H_
#define UTILS_TYPE_CONVERTER_H_

#include <sstream>
#include <string>
#include <vector>

namespace utils {

/**
 * stringToUnsignedChar - convert a string to unsigned char*
 * By example: unsigned char bytes[] = { 0x0F, 0xFF, 0x44, 0x4A } <===> std::string s = "0F FF 44 4A"
 * @param data to string to convert.
 * @param length to outputed length of the unsigned char* result.
 * @return the unsigned char* data.
 */
inline unsigned char* stringToUnsignedChar(std::string data, int* length) {
	std::istringstream hex_chars_stream(data);
	std::vector<unsigned char> bytes;
	unsigned int c;
	while (hex_chars_stream >> std::hex >> c) {
		bytes.push_back(c);
	}
	unsigned char* result = &bytes.front();
	*length = bytes.size();
	return result;
}

/**
 * unsignedCharToString - convert an unsigned char* to a string
 * By example: unsigned char bytes[] = { 0x0F, 0xFF, 0x44, 0x4A } <===> std::string s = "0F FF 44 4A"
 * @param hex the unsigned char* data to be converted.
 * @param length the length of the data to be converted.
 * @return the string data.
 */
inline std::string unsignedCharToString(unsigned char* hex, unsigned long int length) {
	std::string hexString;
	char buffer[length];
	for (unsigned long int i = 0; i < length; i++) {
		sprintf(buffer, "%02X ", hex[i]);
		hexString.append(buffer);
	}
	return hexString;
}

} // namespace utils

#endif /* UTILS_TYPE_CONVERTER_H_ */

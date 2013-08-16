#include "BaconBox/Helper/Parser.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace BaconBox;

const std::string FALSE_STRING = std::string("false");
const std::string TRUE_STRING = std::string("true");

int Parser::stringToInt(const std::string &str) {
	return atoi(str.c_str());
}

double Parser::stringToDouble(const std::string &str) {
	return atof(str.c_str());
}

bool Parser::isNumeric(const std::string &str) {
	for (std::string::const_iterator i = str.begin(); i != str.end(); i++) {
		if ((*i) != '-' && (*i) != '.'  && !std::isdigit(*i)) {
			return false;
		}
	}

	return true;
}
bool Parser::isInteger(const std::string &str) {
	for (std::string::const_iterator i = str.begin(); i != str.end(); i++) {
		if ((*i) != '-' && !std::isdigit(*i)) {
			return false;
		}
	}

	return true;
}


bool Parser::stringToBool(const std::string& str) {
	return !strcasecmp(str.c_str(), TRUE_STRING.c_str());
}


std::string Parser::intToString(const int anInt) {
	std::stringstream ss;
	ss << anInt;
	return ss.str();
}


std::string Parser::doubleToString(const double aDouble, int precision) {
	std::stringstream ss;

	//std::ostringstream oss;
	if (precision != BB_FULL_PRECISION) {
		ss << std::fixed << std::setprecision(precision) << aDouble;

	} else {
		ss << aDouble;

	}

	return ss.str();
}

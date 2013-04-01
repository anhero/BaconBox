#include "BaconBox/Helper/Parser.h"
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace BaconBox;

int Parser::stringToInt(const std::string& str){
	std::stringstream ss(str);
	int i;
	if((ss >> i).fail())
	{ 
		std::cout << "Impossible to parse " << str << " to integer." << std::endl;
	}
	return i;
}

double Parser::stringToDouble(const std::string& str){
	std::stringstream ss(str);
	double i;
	if((ss >> i).fail())
	{ 
		std::cout << "Impossible to parse " << str << " to double." << std::endl;
	}
	return i;
}

bool Parser::isNumeric(const std::string& str){
    for(std::string::const_iterator i = str.begin(); i != str.end(); i++){
	if((*i) != '-' && (*i) != '.'  && !std::isdigit(*i)){
	    return false;
	}
    }
    return true;
}
bool Parser::isInteger(const std::string& str){
    for(std::string::const_iterator i = str.begin(); i != str.end(); i++){
	if((*i) != '-' && !std::isdigit(*i)){
	    return false;
	}
    }
    return true;
}


std::string Parser::intToString(const int anInt){
	std::stringstream ss;
	ss << anInt;
	return ss.str();
}


std::string Parser::doubleToString(const double aDouble, int precision){
	std::stringstream ss;
	//std::ostringstream oss;
	if(precision != BB_FULL_PRECISION){
		ss << std::fixed <<std::setprecision(precision) << aDouble;
	}
	else {
		ss << aDouble;

	}
	return ss.str();
}

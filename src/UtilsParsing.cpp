#include <iostream>
#include <algorithm>	// <- for find()
#include <cstddef>		// <- for std::size_t
#include <typeinfo>		// <- for type conversions
#include <sstream>
#include "UtilsParsing.h"

std::string trim(const std::string &str, char c)
{
	if (str.length() > 0)
	{
		unsigned int first = 0;
		unsigned int last = str.length()-1;
		
		while (str.at(first) == c && first < str.length()-1)
		{
			first++;
		}
		while (str.at(last) == c && last >= first && last > 0)
		{
			last--;
		}
		if (first <= last) 
			return str.substr(first,last-first+1);
		else
			return "";
	}
	else
	{
		return "";
	}
}


std::string stripCarriageReturn(const std::string &line)
{
	if (line.length() > 0)
	{
		if ('\r' == line.at(line.length()-1))
		{
			return line.substr(0, line.length()-1);
		}
	}
	return line;
}


std::string getLine(std::ifstream &infile)
{
	std::string line;
	if (!std::getline(infile, line))
		return "";
	line = stripCarriageReturn(line);
	line = trim(line, ' ');		//remove whitespace
	line = trim(line, '\t');	//remove tabs
	return line;	
}


int toInt(const std::string &str)
{
	int num;
	if (!(std::stringstream(str) >> num))
		std::cerr << "Error: Failed to convert string '" << str << "' to integer." << std::endl;
	return num;
}


int getFirstInt(std::string &str, const char &delimeter)
{
	std::size_t delim_pos = str.find_first_of(delimeter);
	if (delim_pos == std::string::npos)
	{
		str = "";
		return 0; // not found
	}
	int num = toInt(str.substr(0, delim_pos));
	str = str.substr(delim_pos+1, str.length());
	return num;
}

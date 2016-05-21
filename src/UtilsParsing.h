#include <string>
#include <fstream>

std::string trim(const std::string &str, char c);
std::string stripCarriageReturn(const std::string &line);
std::string getLine(std::ifstream &infile);
int toInt(const std::string &str);
int getFirstInt(std::string &s, const char &separator);

//a future replacement for getFirstInt(), maybe?
/*std::vector<int> splitInts(const std::string &string, const char &separator)
{
	std::string temp = string + ",";
	std::vector<int> vec;
	while(temp.length() > 1)
	{
		int token = getFirstInt(temp, separator);
		vec.push_back(token);
	}
	return vec;
}*/

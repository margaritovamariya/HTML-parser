#include "strHelper.h"

bool isEmpty(const std::string& str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (!isspace(str[i]))
		{
			return false;
		}
	}
	return true;
}

std::vector<std::string> split(std::string& str)
{
	std::string helperString = str;
	std::string delimiter = " ";
	std::vector<std::string> token;

	size_t pos;
	while ((pos = helperString.find(delimiter)) != std::string::npos)
	{
		token.push_back(helperString.substr(0, pos));
		helperString.erase(0, pos + 1 /*delimiter.length()*/);
	}
	token.push_back(helperString.substr(0, helperString.length()));

	return token;
}

int fromString(const std::string& str)
{
	int number = 0;
	for (int i = 0; i < str.length(); i++) {

		number = number * 10 + (str[i] - '0');
	}
	return number;
}

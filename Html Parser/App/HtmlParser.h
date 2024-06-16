#pragma once
#include "../Models/HtmlElement.h"
#include "../Utils/strHelper.h"
#include "../Models/Text.h"
#include <string>
#include <iostream>
#include <fstream>

class HtmlParser {
public:
	HtmlElement* fromFile(const std::string& filename);

private:

	void fromFile(std::istream& in, HtmlElement* parent);

	void parseAtributes(HtmlElement* element, const std::vector<std::string>& attributes);
};
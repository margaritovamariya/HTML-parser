#include "HtmlParser.h"


HtmlElement* HtmlParser::fromFile(const std::string& filepath) {
	
	std::ifstream file(filepath);
	if (!file.is_open())
	{
		throw "Could not find file!";
	}
	HtmlElement* root = new HtmlElement("");

	fromFile(file, root);

	file.close();

	return root;
}

void HtmlParser::fromFile(std::istream& in, HtmlElement* parent)
{
	std::string content;
	while (!in.eof())
	{
		std::getline(in, content, '<');
		if (!isEmpty(content))
		{
			parent->addChildNode(new Text(content));
		}
		std::getline(in, content, '>');
		if (content[0] == '/' || isEmpty(content))
		{
			return;
		}
		std::vector<std::string> tokens = split(content);
		std::string tag = tokens[0];
		tokens.erase(tokens.begin());

		HtmlElement* el = new HtmlElement(tag);

		parseAtributes(el, tokens);

		parent->addChildNode(el);
		fromFile(in, el);
	}
}

void HtmlParser::parseAtributes(HtmlElement* element,const std::vector<std::string>& attributes)
{
	for (int i = 0; i < attributes.size(); i++)
	{
		std::string attr = attributes[i];
		int index = attr.find('=');
		std::string key = attr.substr(0,index);
		std::string value = attr.substr(index+2, attr.size() - (index + 3));

		element->addAttribute(new Attribute(key, value));
	}
}
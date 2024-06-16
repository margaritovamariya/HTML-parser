#pragma once
#include <iostream>
#include "../Utils/strHelper.h"
#include "../Models/HtmlElement.h"
#include "HtmlParser.h"

class App
{
private:
	HtmlElement* root;
	std::string filePath;
	HtmlElement* selectedElement;

	void loadHtml(const std::string& filePath);
	void newHtml();
	void save(const std::string& filePath);
	void selectId(const std::string& id);
	void selectList(const std::string& tag, const Attribute* attr);
	void selectOne(const std::string& tag, const Attribute* attr);


	HtmlElement* getElementById(const std::string& id);
	HtmlElement* getElementById(HtmlElement* element,const std::string& id);
	std::vector<HtmlElement*> getElementsByTag(const std::string& tag,const Attribute* attr = nullptr);
    void getElementsByTag(HtmlElement* element,std::vector<HtmlElement*>& matches,const std::string& tag, const Attribute* attr);
	void setElementText(HtmlElement* element, const std::string& text);
	void setElementAttribute(HtmlElement* element, const std::string& key, const std::string& value);
	void addElement(HtmlElement* element, const std::string& tag);

	
	void assertHasSelectedElement();
	void assertElementExist(HtmlElement* element);
	void assertIsHtmlLoaded();

public:
	void run();
};
#include "App.h"
#include <exception>
#include <stdexcept>

void App::run()
{
	std::cout << "      HTML PARSER----TRY IT NOW:" << std::endl;
	while (true)
	{
		try
		{
			std::cout << std::endl;
			std::cout << "Enter a command: "<<std::endl;
			std::string input;
			std::getline(std::cin, input);

			std::vector<std::string> args = split(input);
			std::string comand = args[0];

			if (comand == "load")
			{
				loadHtml(args[1]);
			}
			else if (comand == "new")
			{
				newHtml();
			}
			else if (comand == "save")
			{
				assertIsHtmlLoaded();
				save(args.size() == 3 ? args[2] : this->filePath);
			}
			else if (comand == "select")
			{
				assertIsHtmlLoaded();
				selectId(args[2]);
			}
			else if (comand == "select_list")
			{
				assertIsHtmlLoaded();
				Attribute attr;
				if (args.size() == 5)
				{
					attr = Attribute(args[3], args[4]);
				}
				selectList(args[2], attr.getKey() != "" ? &attr : nullptr);
			}
			else if (comand == "select_one")
			{
				assertIsHtmlLoaded();
				Attribute attr;
				if (args.size() == 5)
				{
					attr = Attribute(args[3], args[4]);
				}
				selectOne(args[2], attr.getKey() != "" ? &attr : nullptr);
			}
			else if (comand == "set")
			{

				assertIsHtmlLoaded();
				if (args.size() == 2)
				{
					assertHasSelectedElement();
					setElementText(selectedElement,args[1]);
				}
				else if (args.size() == 3)
				{
					HtmlElement* element = getElementById(args[2]);
					assertElementExist(element);
					setElementText(element, args[1]);
				}
				if (args.size() == 4)
				{
					assertHasSelectedElement();
					setElementAttribute(selectedElement,args[2],args[3]);
				}
				else if (args.size() == 5)
				{
					HtmlElement* element = getElementById(args[4]);
					assertElementExist(element);
					setElementAttribute(element,args[2],args[3]);
				}
				
			}
			else if (comand == "add")
			{
				assertIsHtmlLoaded();
				if (args.size() == 2)
				{
					assertHasSelectedElement();
					addElement(selectedElement,args[1]);
				}
				else if (args.size() == 3)
				{
					HtmlElement* element = getElementById(args[2]);
					assertElementExist(element);
					addElement(element, args[1]);
				}
				
			}
			
		
		}
		catch (const char* msg)
		{
			std::cout << msg<<std::endl;
		}
	}
}

void App::loadHtml(const std::string& filePath)
{
	delete root;
	HtmlParser htmlParser;
	this->root = htmlParser.fromFile(filePath);
	this->filePath = filePath;
	std::cout << "The file has been loaded!"<<std::endl;
}

void App::newHtml()
{
	delete root;
	root = new HtmlElement("html");
	HtmlElement* html = new HtmlElement("head");
	html->addChildNode(new HtmlElement("body"));
	root->addChildNode(html);
	root->write(std::cout);
}

void App::save(const std::string& filePath)
{
	std::ofstream out(filePath,std::ios::out|std::ios::trunc);
	std::vector<Node*> childNodes = root->getChildNodes();
	for (int i = 0; i < childNodes.size(); i++)
	{
		childNodes[i]->write(out);
	}

	out.close();
}

void App::selectId(const std::string& id)
{
	HtmlElement* element = getElementById(id);
	assertElementExist(element);
	element->write(std::cout);
	std::cout << std::endl;
}

void App::selectList(const std::string& tag, const Attribute* attr)
{
	std::vector<HtmlElement*> elements = getElementsByTag(tag,attr);
	if (elements.size() == 0)
	{
		std::cout << "No available elements" << std::endl;
		
		return;
	}
	for (int i = 0; i < elements.size(); i++)
	{
		elements[i]->write(std::cout);
		std::cout << std::endl;
	}
}

void App::selectOne(const std::string& tag, const Attribute* attr)
{
	std::vector<HtmlElement*> elements = getElementsByTag(tag, attr);
	if (elements.size() == 0)
	{
		std::cout << "No available elements" << std::endl;
		return;
	}

    elements[0]->write(std::cout);
	std::cout << std::endl;
	selectedElement = elements[0];
}

void App::setElementText(HtmlElement* element, const std::string& text)
{
	if (element->contains(selectedElement))
	{
		selectedElement = nullptr;
	}
	element->removeChildNodes();
	element->addChildNode(new Text(text));

}

void App::setElementAttribute(HtmlElement* element, const std::string& key, const std::string& value)
{
	element->setAttribute(key, value);
}

void App::addElement(HtmlElement* element, const std::string& tag)
{
	element->addChildNode(new HtmlElement(tag));
}

HtmlElement* App::getElementById(const std::string& id)
{
	return getElementById(this->root, id);
}

HtmlElement* App::getElementById( HtmlElement* element, const std::string& id)
{
	if (element->getId()==id)
	{
		return element;
	}
	std::vector<HtmlElement*> children = element->getChildren();
	for (int i = 0; i < children.size(); i++)
	{
		HtmlElement* match = getElementById(children[i], id);
		if (match != nullptr)
		{
			return match;
		}
	}
	return nullptr;
}

std::vector<HtmlElement*> App::getElementsByTag(const std::string& tag, const Attribute* attr)
{
	std::vector<HtmlElement*> matches;
    getElementsByTag(root,matches, tag, attr);
	return matches;
}

void App::getElementsByTag(HtmlElement* element, std::vector<HtmlElement*>& matches, const std::string& tag, const Attribute* attr = nullptr)
{
	if (element->getTag() ==tag)
	{
		if (attr == nullptr || (element->getAttrValue(attr->getKey())==attr->getValue()))
		{
			matches.push_back(element);
		}
		
	}
	std::vector<HtmlElement*> children = element->getChildren();
	for (int i = 0; i < children.size(); i++)
	{
		getElementsByTag(children[i], matches, tag, attr);
	}
	
}

void App::assertHasSelectedElement()
{
	if (selectedElement == nullptr)
	{
		throw "No element is selected!";
	}

}

void App::assertElementExist(HtmlElement* element)
{
	if (element == nullptr)
	{
		throw "Could not find element!";
	}
}

void App::assertIsHtmlLoaded()
{
	if (root == nullptr)
	{
		throw "There is no loaded html!";
	}
}


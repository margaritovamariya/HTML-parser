#include "HtmlElement.h";
#include <string>

HtmlElement::HtmlElement(std::string tag) : tag(tag), Node(NodeType::htmlElement)
{}

const std::string HtmlElement::getTag() const
{
	return this->tag;
}

const std::string HtmlElement::getId() const
{
	return getAttrValue("id");
}

const std::vector<Node*> HtmlElement::getChildNodes() const
{
	return this->childNodes;
}

const std::vector< HtmlElement*> HtmlElement::getChildren() const
{
	std::vector<HtmlElement*> children;
	for (int i = 0; i < childNodes.size(); i++)
	{
		if (childNodes[i]->getType() == NodeType::htmlElement)
		{
			children.push_back(dynamic_cast<HtmlElement*>(childNodes[i]));
		}
	}
	return children;
}

const std::vector< Attribute*> HtmlElement::getAttributes() const
{
	return attributes;
}

const std::string HtmlElement::getAttrValue(const std::string& key) const
{

	for (int i = 0; i < this->attributes.size(); i++)
	{
		if (attributes[i]->getKey() == key)
		{
			return attributes[i]->getValue();
		}
	}
	return "";
}

HtmlElement::~HtmlElement()
{
	for (int i = 0; i < attributes.size(); i++)
	{
		delete attributes[i];
	}

	removeChildNodes();
}

void HtmlElement::addAttribute(Attribute* attribute)
{
	attributes.push_back(attribute);
}

void HtmlElement::addChildNode(Node* node)
{
	childNodes.push_back(node);
}

void HtmlElement::removeChildNodes()
{
	for (int i = 0; i < childNodes.size(); i++)
	{
		delete childNodes[i];
	}
	childNodes.clear();
}

void HtmlElement::setAttribute(const std::string& key, const std::string& value)
{
	for (int i = 0; i < attributes.size(); i++)
	{
		if (attributes[i]->getKey()==key)
		{
			attributes[i]->setValue(value);
			return;
		}
	}
	addAttribute(new Attribute(key, value));
}

//I have received help for the implementation of few things connected with the recursion for the next functions
bool HtmlElement::contains(HtmlElement* parentElement,bool isRoot, HtmlElement* searchElement)
{
	if (!isRoot && parentElement==searchElement)
	{
		return true;
	}
	std::vector<HtmlElement*> children = parentElement->getChildren();
	for (int i = 0; i < children.size(); i++)
	{
		bool hasMatch = contains(children[i],false, searchElement);
		if (hasMatch)
		{
			return true;
		}
	}
	return false;
}

bool HtmlElement::contains(HtmlElement* element)
{
	return contains(this,true, element);
}

void HtmlElement::write(std::ostream& output, int depth) const
{
	for (int i = 0; i < depth; i++)
	{
		output << '\t';
	}
	output << '<' << this->tag;

	for (int i = 0; i < this->attributes.size(); i++)
	{
		output << ' ' << *this->attributes[i];
	}
	output << '>' << '\n';
	
	for (int i = 0; i < this->childNodes.size(); i++)
	{
		Node* node = this->childNodes[i];
		switch (node->getType())
		{
		case NodeType::htmlElement: 
			dynamic_cast<HtmlElement*>(node)->write(output, depth + 1);
			break;

		case NodeType::text:
			for (int i = 0; i < depth; i++)
			{
				output << '\t';
			}
			node->write(output);
			break;

		}
	}

	for (int i = 0; i < depth; i++)
	{
		output << '\t';
	}

	output << "</" << this->tag << '>' << '\n';
	
}

void HtmlElement::write(std::ostream& out) const
{
	write(out,0);
}
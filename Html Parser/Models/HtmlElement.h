#pragma once
#include "Node.h"
#include "attribute.h"
#include <string>
#include <vector>

class HtmlElement : public Node {
private:
	std::string tag;
	std::vector<Attribute*> attributes;
	std::vector<Node*> childNodes;
	void write(std::ostream& output, int depth) const;
	static bool contains(HtmlElement* parentElement,bool isRoot, HtmlElement* searchElement);
	
public:
	HtmlElement(std::string tag);
	const std::string getTag() const;
	const std::string getId() const;
	const std::vector<Node*> getChildNodes() const;
	const std::vector< HtmlElement*> getChildren() const;
	const std::vector< Attribute*> getAttributes() const;
	const std::string getAttrValue(const std::string& key) const;
	~HtmlElement();

	void addAttribute(Attribute* attribute);
	void addChildNode(Node* node);
	void removeChildNodes();
	void setAttribute(const std::string& key, const std::string& value);
	bool contains(HtmlElement* element);
	
	void write(std::ostream& out) const override;
};
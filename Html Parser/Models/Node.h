#pragma once
#include <fstream>

enum NodeType
{
	text,
	htmlElement
};

class Node
{
private:
	NodeType type;

public:
	Node(NodeType type);
	NodeType getType() const;
	virtual ~Node();

	virtual void write(std::ostream& out) const = 0;
};


#include "Node.h"



Node::Node(NodeType type) : type(type)
{
	
}

NodeType Node::getType() const
{
	return this->type;
}

Node::~Node()
{

}

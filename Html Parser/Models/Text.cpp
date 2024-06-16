#include "Text.h"


Text::Text(const std::string& content) : content(content), Node(NodeType::text)
{}

void Text::write(std::ostream& out) const
{
	out << content;
}
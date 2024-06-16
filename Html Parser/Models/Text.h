#pragma once
#include "Node.h"
#include <string>

class Text : public Node {
private:
	std::string content;

public:
	Text(const std::string& content);

	void write(std::ostream& out) const override;
	
};
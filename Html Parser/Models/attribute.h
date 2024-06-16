#pragma once
#include <string>
#include <iostream>
#include <string>

class Attribute {

private:
	std::string key_;
	std::string value_;

public:
	Attribute();
	Attribute(std::string key, std::string value);

	
	const std::string getKey() const;
	const std::string getValue() const;
	void setValue(const std::string& value);
	
	friend std::ostream& operator<<(std::ostream& output, const Attribute& attribute);
   
};

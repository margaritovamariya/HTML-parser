#include "attribute.h"


Attribute::Attribute()
{
}

Attribute::Attribute(std::string key, std::string value):key_(key), value_(value)
{
}

const std::string Attribute::getKey() const
{
	return this->key_;
}

const std::string Attribute::getValue() const
{
	return this->value_;
}

void Attribute::setValue(const std::string& value)
{
	this->value_ = value;
}

std::ostream& operator<<(std::ostream& output, const Attribute& attribute)
{
	output << attribute.key_ << '=' << '"' << attribute.value_<< '"';
	return output;
}
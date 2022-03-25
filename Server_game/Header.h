#pragma once
#include <ctime>

class Header{

public:

	enum class Type { LOGIN, TIME };

	void setType(Header::Type type);
	Header::Type getType() const;

	time_t getTime() const;

private:

	Type type_;
	time_t time_;

};


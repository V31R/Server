#pragma once
#include <ctime>
#include "Header.h"
class MessageHead : public Header{

#define MAX_SIZE 256

public:

	const unsigned int dataSize{ MAX_SIZE };

	char* getData();

private:

	char data[MAX_SIZE];

};


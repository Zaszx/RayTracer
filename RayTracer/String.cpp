#include "CommonIncludes.h"
#include "String.h"


int String::length() const
{
	return strlen(buffer);
}

char* String::charP() const
{
	return buffer;
}

bool String::sameAs(const String& rhs) const
{
	return strcmp(buffer, rhs.buffer) == 0;
}

void String::operator=(const char* value)
{
	refreshBuffer(strlen(value));
	strcpy(buffer, value);
}

char String::operator[](int index)
{
	assert(index >= 0 && index < length());
	return buffer[index];
}

String::String()
{
	buffer = nullptr;
}

String::String(const char* value)
{
	refreshBuffer(strlen(value)),
	strcpy(buffer, value);
}

String::~String()
{
	refreshBuffer(0);
}

void String::refreshBuffer(int length)
{
	if (buffer)
	{
		delete[] buffer;
	}
	buffer = new char[length];
}


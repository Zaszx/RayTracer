#ifndef __STRING__H__
#define __STRING__H__

class String
{
public:

	String();
	String(const char* value);
	~String();

	int length() const;
	char* charP() const;
	bool sameAs(const String& rhs) const;
	void operator =(const char* value);
	char operator [](int index);

private:

	char* buffer;
	void refreshBuffer(int length);

};

#endif //__STRING__H__
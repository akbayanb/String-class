#include <iostream>
#include <cstring>
#include <cstdarg>
using namespace std;
#pragma once
class String {
	char* stringRep;
	size_t buf_size;

public:
	
	String(const char* str);
	String(size_t len, char s);
	String(size_t len=256);
	String(const String& obj);
	~String();
	const char* getStringRep()const;
	char& getAt(size_t pos)const;
	String& AddCharAt(size_t pos, char c);
	String& DelCharAt(size_t pos);
	String& ConcatStr(const String& str);
	String& ConcatStr(const char* str);
	String & AddStringPart(const String & str, size_t pos, size_t to_pos);
	String& AddStrAt(const String& str, size_t pos);
	String& DelStrAt(size_t beg, size_t end);
	int SubStr(const String& what);
	int SubStr(const char* what);
	String& Replace(const char* what, const char* rep);
	String& Replace(const String& what, const String& rep);
	const char* GetRange(size_t beg, size_t end);
	static String Format(const char* specs, ...);
	size_t size()const;		
	friend ostream& operator<<(ostream& os, String obj);

};
#include "String.h"

String::String(const char * str)
{
	buf_size = strlen(str) + 1;
	stringRep = new char[buf_size];

	char *tmp = stringRep;
	while (*str != '\0') {
		*tmp = *str;
		tmp++;
		str++;
	}
	*tmp = '\0';}

String::String(size_t len, char s)
{
	this->buf_size = len+1;
	this->stringRep = new char[buf_size];
	for (int i = 0; i < buf_size - 1; i++)
		stringRep[i] = s;
	stringRep[buf_size - 1] = '\0';
}

String::String(size_t len)
{
	this->buf_size = len;
	this->stringRep = new char[buf_size];
	stringRep[0] = '\0';
}

String::String(const String & obj)
{
	this->buf_size = obj.buf_size;
	this->stringRep =new char[buf_size];
	for (int i = 0; i <= obj.size(); i++)
		stringRep[i] = obj.stringRep[i];}

String::~String()
{
	delete[] stringRep;
}

const char * String::getStringRep()const
{
	return stringRep;
}

char&  String::getAt(size_t pos)const
{
	return stringRep[pos];
}

String & String::AddCharAt(size_t pos, char c)
{	int str_size = size();
	if (pos <= str_size) {
	   		if (buf_size <= str_size + 1) {
			buf_size *= 2;
			char* tmp = new char[buf_size];
			for (int i = 0; i < str_size; i++)
			{
				tmp[i] = stringRep[i];
			}
			delete[] stringRep;
			stringRep = tmp;
		}			
			stringRep[str_size + 1] = c;
			for (int i = str_size + 1; i > pos; i--)
			{
				swap(stringRep[i - 1], stringRep[i]);
			}
			stringRep[str_size + 1] = '\0';
	}
	return (*this);}


String & String::DelCharAt(size_t pos)
{
	if (pos < size()) {
		for (int i = pos; i < size() + 1; i++)
			stringRep[i] = stringRep[i + 1];
	}
	return (*this);
}

String & String::ConcatStr(const String & str)
{
	int index;
	size_t thisSize=size();
	size_t str_size = str.size();
	
	if ((thisSize + str_size) < buf_size) {
		stringRep[thisSize] = str.getAt(0);
		index = thisSize+1;
		for (int i = 1; i < str.size(); i++, index++)
			stringRep[index] = str.stringRep[i];
		stringRep[thisSize + str_size] = '\0';}
	else
	{	index = thisSize;
		this->buf_size = thisSize + str_size + 1;
		char*tmp = new char[buf_size];
		for (int i = 0; i < thisSize; i++) {
			tmp[i] = stringRep[i];
		}
		for (int i = 0; i < str_size; i++, index++) {
			tmp[index] = str.stringRep[i];
		}
		tmp[thisSize + str_size] = '\0';
		delete[] stringRep;
		stringRep = tmp;}
	return (*this);}

String & String::ConcatStr(const char * str)
{	int index;
	size_t thisSize = size();
	size_t str_size = strlen(str);

	if ((thisSize + str_size) < buf_size) {
		stringRep[thisSize] = str[0];
		index = thisSize + 1;
		for (int i = 1; i < str_size; i++, index++)
			stringRep[index] = str[i];
		stringRep[thisSize + str_size] = '\0';	}
	else
	{	index = thisSize;
		this->buf_size = thisSize + str_size + 1;
		char*tmp = new char[buf_size];
		for (int i = 0; i < thisSize; i++) {
			tmp[i] = stringRep[i];
		}
		for (int i = 0; i < str_size; i++, index++) {
			tmp[index] = str[i];
		}
		tmp[thisSize + str_size] = '\0';
		delete[] stringRep;
		stringRep = tmp;
	}
	return (*this);}

String & String::AddStringPart(const String & str, size_t pos, size_t to_pos=0)
{
	int index = to_pos;
	for (int i = pos; i < str.size(); i++, index++)
	{
		this->AddCharAt(index, str.getAt(i));
	}
	return (*this);}

String & String::AddStrAt(const String & str, size_t pos)
{	AddStringPart((str), 0, pos);
	return(*this);
	/*for (int i = 0; i<str.size(); i++)
	{
		AddCharAt(pos + i,str.stringRep[i]);
	}
	return (*this);*/
}



String & String::DelStrAt(size_t beg, size_t end)
{	for (int i = beg; i <= end; i++)
		DelCharAt(beg);
	return (*this);
}

int String::SubStr(const String & what)
{
	int rez = -1;
	if(strstr(this->getStringRep(), what.getStringRep()))
	return strstr(this->getStringRep(), what.getStringRep()) - this->getStringRep();
	return rez;
}

int String::SubStr(const char * what)
{
	int rez = -1;
	if (strstr(this->getStringRep(), what))
	return strstr(this->getStringRep(), what) - this->getStringRep();
	return rez;
}

String & String::Replace(const char * what, const char * rep)
{	String after_part;
	int k =0;
	while (true) {
		k = SubStr(what);
		if (k == -1) break;
		DelStrAt(k, (k+strlen(what)-1));
		
		AddStrAt(rep, k); } 
	return(*this);}

String & String::Replace(const String & what, const String & rep)
{	int k = 0;
	while (true) {
		k = SubStr(what);
		if (k == -1) break;
		DelStrAt(k, (k + strlen(what.getStringRep()) - 1));
		AddStrAt(rep.getStringRep(), k);	}
	return(*this);
}

const char * String::GetRange(size_t beg, size_t end)
{
	String s;
	for (int i = beg; i <= end; i++)
	{
		s.AddCharAt(s.size(), stringRep[i]);
	}
	return s.getStringRep();
}

String String::Format(const char * specs, ...)
{
	String obj;
	va_list ap;
	va_start(ap, specs);
	while (*specs != '\0') {
		if (*specs == 'i') {
			char buf[15];
			int var = va_arg(ap, int);
		
			_itoa_s(var, buf, 10);
			obj.ConcatStr(buf);
			
		}
		if (*specs == 'c') {
		
			char var = va_arg(ap, char);
			obj.AddCharAt(obj.size(), var);

		}
		specs++;
	}


	return obj;

}

//String String::Format(const char * specs, ...)
//{
//	/*String obj;
//	va_list ap;
//
//	va_start(ap, specs);
//	if (strcmp(specs, "%d"))
//		obj.AddStrAt()
//		cout<<va_arg(ap, int);
//
//
//	va_end(ap);
//	return obj;*/
//}

size_t String::size()const 
{
	char *ptr = stringRep;
	size_t s = 0;
	while (*ptr != '\0')
	{
		s++;
		ptr++;
	}
	return s;
}

ostream& operator<<(ostream& os, String obj) {
	os << obj.stringRep;
	return os;
}
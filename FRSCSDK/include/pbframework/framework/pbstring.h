#ifndef PBSTRING_H
#define PBSTRING_H

#include <stdio.h>
#include <string>
#include <cstdarg>

class PBString : public std::string
{
public:
	PBString();
	PBString(const char *str);
	PBString(const std::string & str);
	~PBString();

	void Format(const char *format, ...);
	bool TrimLeft();
	bool TrimRight();
	bool Trim();

	operator const char *() const;
};
#endif // PBSTRING_H

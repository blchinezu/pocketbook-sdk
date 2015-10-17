#ifndef _PRINTTEXT_H
#define _PRINTTEXT_H

#ifdef __WIN32
	#if defined(TARGET_LIBRARY)
		#define LIB_EXPORT __declspec(dllexport)
	#else
		#define LIB_EXPORT __declspec(dllimport)
	#endif
#else
	#define LIB_EXPORT
#endif

class LIB_EXPORT printtext
{
public:
	printtext();
	~printtext();

	bool set_text(char *text);
	void print_text();
private:
	char somestring[255];
protected:
};

#endif /* _PRINTTEXT_H */

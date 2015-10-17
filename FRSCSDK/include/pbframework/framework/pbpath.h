#ifndef PBPATH_H
#define PBPATH_H

#include "pbstring.h"
#include <inkview.h>

#define STRNULL std::string::npos

class PBPath : public PBString //std::string
{
public:
	PBPath();
	PBPath(const char *path);
	~PBPath();

	const char* GetFileName() const;
	const char* GetMountPrefix() const;

	bool OnFlash() const;
	bool OnSDCard() const;
	bool OnUSB() const;

	const iv_filetype *FileType() const;

	bool IsExist() const;
	bool IsDir() const;
	static bool IsExist(const char *path);
	static bool IsDir(const char *path);
};

#endif // PBPATH_H

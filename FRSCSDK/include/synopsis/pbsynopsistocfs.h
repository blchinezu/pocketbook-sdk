/*
 * Copyright (C) 2011 Denis Kuzko <kda6666@ukr.net>
 */

#ifndef PBSYNOPSISTOCFS_H
#define PBSYNOPSISTOCFS_H

#include <inkview.h>
#include <string>

class PBSynopsisItem;

class PBSynopsisTOCFS
{
public:
	PBSynopsisTOCFS();

public:
	static std::string GetOnlyFileName(const char *src);
	static std::string SynopsisGetInfo(const char *src, const char *starttext, const char *finishtext, int pos, const char *def, int *respos);
	static int SynopsisGetInfoPos(char *dest, const char *src, const char *starttext, const char *finishtext, int pos);
	static int SynopsisGetInfoInt(const char *src, const char *starttext, const char *finishtext, int pos, int def);
	static std::string SynopsisGetInfoString(const char *src, const char *starttext, const char *finishtext, int pos, const char *def);

private:
	static void CalcFileMD5(const char *src, unsigned char *r);
	static void GetMD5(const char *path, char *md5);
	static void SetSourcePath();
	static void SetNotesPath();

	static std::string m_md5;
	static char ms_notespath[512];

public:
	static char *GetActiveContentsBookName(const char *path);
	static void SaveTOCFS();
	static int LoadTOCFS();
	static char *GetNotesPath();
};

#endif // PBSYNOPSISTOCFS_H

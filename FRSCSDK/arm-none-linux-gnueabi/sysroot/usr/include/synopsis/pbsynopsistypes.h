/*
 * Copyright (C) 2011 Denis Kuzko <kda6666@ukr.net>
 */

#ifndef PBSYNOPSISTYPES_H
#define PBSYNOPSISTYPES_H

#include <inkview.h>
#include <string>
#include <vector>

typedef struct SynWordList_s
{
//	std::string word;
	char *word;
	int type;
	int page;
	int x1;
	int y1;
	int x2;
	int y2;
	int pnum;
	int wnum;

} SynWordList;

typedef struct fb2_settings_s
{
	int id;
	int orientation;
	std::string font;
	std::string fontb;
	std::string fonti;
	std::string fontbi;
	int fontsize;
	std::string encoding;
	int linespacing;
	int border;
	int hyphenations;
	int preformatted;
	int textdir;
} fb2_settings;

typedef struct epub_settings_s
{
	int id;
	int orientation;
	int fontsize;
} epub_settings;

#endif

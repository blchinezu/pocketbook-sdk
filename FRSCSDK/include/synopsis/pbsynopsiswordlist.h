/*
 * Copyright (C) 2011 Denis Kuzko <kda6666@ukr.net>
 */

#ifndef PBSYNOPSISWORDLIST_H
#define PBSYNOPSISWORDLIST_H

#include "pbsynopsisdefines.h"
#include "pbsynopsisdefines.h"
#include "pbsynopsistypes.h"
#include <inkview.h>
#include <vector>

class EXPORT PBSynopsisWordList
{
public:
	PBSynopsisWordList();
	~PBSynopsisWordList();
	void Clear();
	std::string GetFirstRow();
	void Add(SynWordList *wlist, int counter, int page);
	int FindXY(int x, int y, int page);

	std::vector<SynWordList> m_WordList;
};

#endif // PBSYNOPSISWORDLIST_H

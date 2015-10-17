/*
 * Copyright (C) 2011 Denis Kuzko <kda6666@ukr.net>
 */

#ifndef PBSYNOPSISBOOKMARK_H
#define PBSYNOPSISBOOKMARK_H

#include "pbsynopsisdefines.h"
#include "pbsynopsiswordlist.h"
#include "pbsynopsisitem.h"
#include "pbsynopsistoc.h"
#include <string>

class EXPORT PBSynopsisBookmark : public PBSynopsisItem
{
public:
	PBSynopsisBookmark();

	void Create(PBSynopsisTOC *SynTOC, PBSynopsisWordList *List, const char *bookmark);
	void Create(PBSynopsisTOC *SynTOC, PBSynopsisWordList *List, long long position);

	// Calculate item sizes
	int CalcItemHeight();
	// try to put item in remaining space
	int TryDrawItem(int space, int /*skip*/);

	void Draw(int posy, int /*space*/, int /*skip*/, int select, int lock_drawing);

	// handler for deleting bookmark
	static void DeleteHandler(int button);

private:
	static PBSynopsisTOC *m_pStaticTOC;
	static PBSynopsisBookmark *m_pStaticBookmark;
};

#endif // PBSYNOPSISBOOKMARK_H

/*
 * Copyright (C) 2011 Denis Kuzko <kda6666@ukr.net>
 */

#ifndef PBSYNOPSISCONTENT_H
#define PBSYNOPSISCONTENT_H

#include "pbsynopsisdefines.h"
#include "pbsynopsisitem.h"
#include <string>

class EXPORT PBSynopsisContent : public PBSynopsisItem
{
public:
	PBSynopsisContent();

	PBSynopsisContent(int level, long long position, char *title);
	PBSynopsisContent(int level, const char *position, char *title);

	// Calculate item sizes
	int CalcItemHeight();
	// try to put item in remaining space
	int TryDrawItem(int space, int /*skip*/);

	void Draw(int posy, int /*space*/, int /*skip*/, int select, int lock_drawing);
};

#endif // PBSYNOPSISCONTENT_H

/*
 * Copyright (C) 2011 Denis Kuzko <kda6666@ukr.net>
 */

#ifndef PBSYNOPSISMARKER_H
#define PBSYNOPSISMARKER_H

#include "pbsynopsisdefines.h"
#include "pbsynopsisitem.h"
#include "pbsynopsistoc.h"

class EXPORT PBSynopsisMarker : public PBSynopsisItem
{
public:
	PBSynopsisMarker();

	void Create(PBSynopsisTOC* SynTOC, long long position, long long endposition, const char *text);
	void Create(PBSynopsisTOC* SynTOC, const char *position, const char *endposition, const char *text);
	void Create(PBSynopsisTOC* SynTOC, long long position, long long endposition, const char *title, const char *text);
	void Create(PBSynopsisTOC* SynTOC, const char *position, const char *endposition, const char *title, const char *text);

	void SetText(const char* text);
	const char* GetText();
	void SetTextHeight(int height);
	int GetTextHeight();

	void SetEndPosition(long long pos);
	long long GetEndLongPosition();
	void SetEndPosition(const char* pos);
	const char* GetEndPosition();

	// Calculate item sizes
	int CalcItemHeight();
	// try to put item in remaining space
	int TryDrawItem(int space, int skip);

	void Draw(int posy, int space, int skip, int select, int lock_drawing);

private:
	int m_Texth;
	std::string m_Text;
	std::string m_endposition;
};

#endif // PBSYNOPSISMARKER_H

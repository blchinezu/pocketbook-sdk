/*
 * Copyright (C) 2011 Denis Kuzko <kda6666@ukr.net>
 */

#ifndef PBSYNOPSISITEM_H
#define PBSYNOPSISITEM_H

#include "pbsynopsisdefines.h"
#include "pbsynopsistree.h"
#include <string>

class EXPORT PBSynopsisItem : public PBSynopsisTree<PBSynopsisItem>
{
public:
	PBSynopsisItem();

	PBSynopsisItem(int type, int level, long long position, char *title);
	PBSynopsisItem(int type, int level, const char *position, char *title);

	void SetHeaderPage(int page);
	int GetHeaderPage();

	void SetShowInfo(int showinfo);
	int GetShowInfo();

	void SetPosition(long long position);
	void SetPosition(const char *position);
	const char *GetPosition();
	long long GetLongPosition();
	void SetTitle(const char *title);
	const char *GetTitle();

	void SetTitleHeight(int height);
	int GetTitleHeight();
	void SetItemHeight(int height);
	int GetItemHeight();

	void DrawSideLines(PBSynopsisItem *item, int posy);

//	void SetDontNeedSaving(bool value);

	virtual void SetText(const char */*text*/);
	virtual const char *GetText();

	virtual	const char* GetImgLink();

	static void PositionToChar(long long src, char *dest);
	static void PositionToLong(const char *src, long long *dest);

// abstract functions
	// Calculate item sizes
	virtual int CalcItemHeight() = 0;

	// try to put item in remaining space
	// space - max height for drawing item
	// skip - size of skipping pixels in item
	virtual int TryDrawItem(int space, int skip) = 0;

	virtual int GetPage() = 0;
	// -1 this less other, 0 - equal, 1 - this more other
	virtual int Compare(PBSynopsisItem *pOther) = 0;
	virtual void Draw(int posy, int space, int skip, int select, int lock_drawing) = 0;

protected:
	int m_Showinfo;
	int m_Headerpage;
	int m_Titleh;
	int m_Itemh;
	std::string m_Bookmark;
	std::string m_Title;
};

#endif // PBSYNOPSISITEM_H

/*
 * Copyright (C) 2011 Denis Kuzko <kda6666@ukr.net>
 */

#ifndef PBSYNOPSISNOTE_H
#define PBSYNOPSISNOTE_H

#include "pbsynopsisdefines.h"
#include "pbsynopsiswordlist.h"
#include "pbsynopsisitem.h"
#include "pbsynopsistoc.h"

class PBSynopsisTOC;

class EXPORT PBSynopsisNote : public PBSynopsisItem
{
public:
	PBSynopsisNote();

	void Create(PBSynopsisTOC* SynTOC, PBSynopsisWordList* WordList, ibitmap* img1, ibitmap* img2, bool hasText = true);

	void SetAPos(int pos);	// after note
	int GetAPos();
	void SetBPos(int pos);	// before note
	int GetBPos();
	void SetText(const char* text);
	const char* GetText();
	void SetTextHeight(int height);
	int GetTextHeight();
	void SetImageHeight(int height);
	int GetImageHeight();
	void SetImgLink(const char* link);
	const char* GetImgLink();
	void LoadImage();
	ibitmap* GetImage();
	void ImageFree();
	void SetEndPosition(long long pos);
	long long GetEndLongPosition();
	void SetEndPosition(const char* pos);
	const char* GetEndPosition();

	// Calculate item sizes
	int CalcItemHeight();
	// try to put item in remaining space
	int TryDrawItem(int space, int skip);

	void Draw(int posy, int space, int skip, int select, int lock_drawing);

	// set start position and end position of note in adobe
	virtual void GetNoteBookmarks(int y1, int y2, char* sbookmark, char* ebookmark);

private:
	short m_Apos;
	short m_Bpos;
	int m_Texth;
	int m_Imgw;
	int m_Imgh;
	ibitmap* m_pImage;
	std::string m_Text;
	std::string m_Imglink;
	std::string m_endposition;
};

#endif // PBSYNOPSISNOTE_H

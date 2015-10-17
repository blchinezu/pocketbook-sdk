/*
 * Copyright (C) 2011 Denis Kuzko <kda6666@ukr.net>
 */

#ifndef PBSYNOPSISNOTECREATOR_H
#define PBSYNOPSISNOTECREATOR_H

#include "pbsynopsisdefines.h"
#include "pbsynopsiswordlist.h"
#include "pbsynopsisnote.h"
#include "pbsynopsistoc.h"

class PBSynopsisNoteCreator
{
public:
	PBSynopsisNoteCreator();

	static void Create(PBSynopsisNote *note, PBSynopsisTOC *SynTOC, PBSynopsisWordList *WordList, ibitmap *img1, ibitmap *img2, bool hasText);
	static char *GetNoteText(int from, int to);
	static ibitmap *GetNoteImage(int /*x1*/, int y1, int /*x2*/, int y2, int from, int to, int page);
	static void SortCoord(int *tanx1, int *tany1, int *tanx2, int *tany2, int *from, int *to);
	static void InvertSelectNoteArea(int x1, int y1, int x2, int y2, int smode, int update);

	static void NotesMenuHandler(int index);
	static int NotesPointerHandler(int type, int par1, int par2);
	static void Move(int step, bool *notfound, int *curword);
	static void MoveUp(bool *_notfound, int *_curword);
	static void MoveDown(bool *_notfound, int *_curword);
	static int NotesHandler(int type, int par1, int par2);
	
	// static variables
	static PBSynopsisNote* s_pNote;
	static PBSynopsisTOC* s_pTOC;
	static bool s_HasText;

private:
	static std::string SaveImageForNote(ibitmap* bm);

};

#endif // PBSYNOPSISNOTECREATOR_H

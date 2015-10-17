/*
 * Copyright (C) 2011 Denis Kuzko <kda6666@ukr.net>
 */

#ifndef PBSYNOPSISTOCHANDLER_H
#define PBSYNOPSISTOCHANDLER_H

#include "pbsynopsisitem.h"
#include "pbsynopsistoc.h"

#define d_pTOC PBSynopsisTOC::s_pOpenTOC

class PBSynopsisItem;

class PBSynopsisTOCHandler
{
public:
	PBSynopsisTOCHandler();

	static void EditTextItem(char *text);
	static void RenameItem(char *text);
	static void DeleteDialog(int button);
	static void EditImageExit(int button);
	static int DeleteActiveContentsItem();
	static void ItemClick(PBSynopsisItem *item);
	static void InitMenuForItem(PBSynopsisItem *item);
	static void PopupMenuHandler(int index);
	static PBSynopsisItem *FindItemByPointer(int y);
	static int PointerHandler(int type, int par1, int par2);
	static int Handler(int type, int par1, int par2);
};

#endif // PBSYNOPSISTOCHANDLER_H

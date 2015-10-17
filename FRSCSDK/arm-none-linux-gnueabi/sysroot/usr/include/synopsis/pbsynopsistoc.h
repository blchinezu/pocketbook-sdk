/*
 * Copyright (C) 2011 Denis Kuzko <kda6666@ukr.net>
 */

#ifndef PBSYNOPSISTOC_H
#define PBSYNOPSISTOC_H

#include "pbsynopsisdefines.h"
#include "pbsynopsisitem.h"
#include "pbsynopsisnote.h"
#include "pbsynopsispen.h"
#include "pbsynopsistochandler.h"
#include "pbsynopsistocfs.h"
#include "pbsynopsissettings.h"
#include <string>

class PBSynopsisPen;

class EXPORT PBSynopsisTOC
{
public:
	PBSynopsisTOC();
	virtual ~PBSynopsisTOC();
	void Clear();

	int Print(PBSynopsisItem *Start);

	PBSynopsisItem *GetHeader();
	PBSynopsisItem *GetHeaderM(int mask);
	void SetCurrent(PBSynopsisItem *cur);
	PBSynopsisItem *GetCurrent();
	void SetPrevCurrent(PBSynopsisItem *prevcur);
	void SetHeaderName(const char *HeaderName);
	const char *GetHeaderName();
	void SetFileName(const char *FileName);
	const char *GetFileName();
	void SetFilePath(const char *FilePath);
	const char *GetFilePath();
	void SetCPage(int page);
	int GetCPage();
	int GetNPage();
	int GetBookFileExist();
	PBSynopsisSettings *GetSettings();
	void SetBackTOCHandler(iv_itemchangehandler hproc);
	iv_handler GetTOCHandler();
	iv_handler GetPrevHandler();
	iv_keyboardhandler GetCProc();
	void SaveTOC();
	int LoadTOC();

	// source
	void SetSourcePath(const char *SourcePath);
	const char *GetSourcePath();
	void SetReaderName(const char *ReaderName);
	const char *GetReaderName();

	// Pen
	PBSynopsisPen *GetPen(const char *spos, const char *epos);

	// adding items
	PBSynopsisItem *AddTOCItem(PBSynopsisItem *NewItem);
	PBSynopsisItem *AddLoadItem(PBSynopsisItem *NewItem);

private:
	PBSynopsisItem *InsertItem(PBSynopsisItem *parent, PBSynopsisItem *NewItem);

public:
	PBSynopsisItem *AddItem(PBSynopsisItem *NewItem);

	// verify existing items
	PBSynopsisItem *ExistItem(PBSynopsisItem *NewItem, int itemType);
	bool IsBookmarkInside(const char *startPosition, const char *endPosition);
	bool IsBookmarkInside(int start_page, int end_page);

private:
	// find default cursor position and unwrap items for cursor
	PBSynopsisItem *GetFirstPageItem();
	PBSynopsisItem *FindShowStartItem(PBSynopsisItem *item); // unwrap items
	PBSynopsisItem *FindStartItem(PBSynopsisItem *pLocation);

public:
	void Open(PBSynopsisItem *pLocation);
	void Draw(int update);

	static char *GetActiveContentsBookName(const char *path);

	virtual PBSynopsisItem *CreateObject(int type) = 0;
	virtual void OnNewItemAdded(PBSynopsisItem */*pItem*/){};
	virtual void OnItemDeleted(PBSynopsisItem */*pItem*/){};
	void DeleteItem(PBSynopsisItem *item);
	PBSynopsisItem *GetMarkerByPos(long long pos);
	void SetVersion(int version);
	int GetVersion();

	static PBSynopsisTOC *s_pOpenTOC;

protected:
	int m_WasLoad;
	int m_EmptyTOC;
	static char s_Text[51200];

private:
	int m_Cpage;
	int m_Npage;
	int m_BookFileExist;

	PBSynopsisItem *m_pHeader;
	PBSynopsisItem *m_pTail;
	PBSynopsisItem *m_pCurrent;
	PBSynopsisItem *m_pPrevCurrent;

	static PBSynopsisSettings *s_pSettings;

	std::string m_HeaderName;
	std::string m_FileName;
	std::string m_FilePath;
	std::string m_SourcePath;
	std::string m_ReaderName;

	iv_handler prevhandler;
	iv_itemchangehandler cproc;

	int m_Version;

	friend class PBSynopsisTOCHandler;
	friend class PBSynopsisTOCFS;
};

#endif // PBSYNOPSISTOC_H

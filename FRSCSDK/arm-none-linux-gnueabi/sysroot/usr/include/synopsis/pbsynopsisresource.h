/*
 * Copyright (C) 2011 Denis Kuzko <kda6666@ukr.net>
 */

#ifndef PBSYNOPSISRESOURCE_H
#define PBSYNOPSISRESOURCE_H

#include <inkview.h>

extern ibitmap synopsis_bookmark, synopsis_note_plus, synopsis_note_minus,
		synopsis_minus, synopsis_plus,
		synopsis_pen_plus, synopsis_pen_minus,
		synopsis_marker_plus, synopsis_marker_minus,
		synopsis_comment_plus, synopsis_comment_minus,
		synopsis_snapshot_plus, synopsis_snapshot_minus;

class PBSynopsisResource
{
public:
	PBSynopsisResource();
	~PBSynopsisResource();

	static void InitResource();
	static void SetHeaderFont();
	static void SetContentFont();
	static void SetActiveFont();
	static void SetSettingsFont(int color);
	static int GetHeaderFontHeight();
	static int GetContentFontHeight();
	static int GetActiveFontHeight();
//	static ibitmap *GetImgContent();
	static ibitmap *GetImgBookmark();
	static ibitmap *GetImgNotePlus();
	static ibitmap *GetImgNoteMinus();
	static ibitmap *GetImgPlus();
	static ibitmap *GetImgMinus();
	static ibitmap *GetImgPenPlus();
	static ibitmap *GetImgPenMinus();
	static ibitmap *GetImgMarkerPlus();
	static ibitmap *GetImgMarkerMinus();
	static ibitmap *GetImgCommentPlus();
	static ibitmap *GetImgCommentMinus();
	static ibitmap *GetImgSnapshotPlus();
	static ibitmap *GetImgSnapshotMinus();

private:
	static ifont *s_pHeaderFont;
	static ifont *s_pContentFont;
	static ifont *s_pActiveFont;
	static ifont *s_pSettingsFont;
	static ibitmap *s_pImg_synopsis_bookmark;
	static ibitmap *s_pImg_synopsis_note_plus;
	static ibitmap *s_pImg_synopsis_note_minus;
	static ibitmap *s_pImg_synopsis_plus;
	static ibitmap *s_pImg_synopsis_minus;
	static ibitmap *s_pImg_synopsis_pen_plus;
	static ibitmap *s_pImg_synopsis_pen_minus;
	static ibitmap *s_pImg_synopsis_marker_plus;
	static ibitmap *s_pImg_synopsis_marker_minus;
	static ibitmap *s_pImg_synopsis_comment_plus;
	static ibitmap *s_pImg_synopsis_comment_minus;
	static ibitmap *s_pImg_synopsis_snapshot_plus;
	static ibitmap *s_pImg_synopsis_snapshot_minus;

};

#endif // PBSYNOPSISRESOURCE_H

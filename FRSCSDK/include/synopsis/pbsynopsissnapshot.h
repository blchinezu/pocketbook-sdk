/*
 * Copyright (C) 2011 Denis Kuzko <kda6666@ukr.net>
 */

#ifndef PBSYNOPSISSNAPSHOT_H
#define PBSYNOPSISSNAPSHOT_H

#include "pbsynopsisdefines.h"
#include "pbsynopsisitem.h"
#include "pbsynopsistoc.h"

class PBSynopsisTOC;

class EXPORT PBSynopsisSnapshot : public PBSynopsisItem
{
public:
	PBSynopsisSnapshot();

	void Create(PBSynopsisTOC* SynTOC, long long position);
	void Create(PBSynopsisTOC* SynTOC, const char *position);

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

	// Calculate item sizes
	int CalcItemHeight();
	// try to put item in remaining space
	int TryDrawItem(int space, int skip);

	void Draw(int posy, int space, int skip, int select, int lock_drawing);

	int CreateHandler(int type, int par1, int par2);

private:
	// Create new snapshot
	// only drawing part there
	void DynamicUpdateRect(int x1, int y1, int x2, int y2, int x3, int y3);
	void DrawDottedLine(int x1, int y1, int x2, int y2);
	void DrawSnapshotRect();
	void FlushSnapshot(int x, int y, int w, int h);
	int m_Snapshot_x1; // first point
	int m_Snapshot_y1; // first point
	int m_Snapshot_x2; // second point
	int m_Snapshot_y2; // second point
	int m_Snapshot_x3; // prev point
	int m_Snapshot_y3; // prev point

	int m_Texth;
	int m_Imgw;
	int m_Imgh;
	ibitmap* m_pImage;
	std::string m_Text;
	std::string m_Imglink;
};

#endif // PBSYNOPSISSNAPSHOT_H

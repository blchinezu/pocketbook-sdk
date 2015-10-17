/*
 * Copyright (C) 2011 Denis Kuzko <kda6666@ukr.net>
 */

#ifndef PBSYNOPSISPEN_H
#define PBSYNOPSISPEN_H

#include "pbsynopsisdefines.h"
#include "pbsynopsisitem.h"
#include "pbsynopsistoc.h"
#include "pbsynopsistoolbar.h"

#define PM_PEN 0
#define PM_ERASER 1

class PBSynopsisTOC;
class PBSVGObjectCreator;
class PBSVGController;
class PBISVGObject;

class EXPORT PBSynopsisPen : public PBSynopsisItem
{
public:
	PBSynopsisPen();
	~PBSynopsisPen();

	PBSynopsisPen(int level, long long position);
	PBSynopsisPen(int level, const char *position);

	void ResizeScreen();
	void Create(PBSynopsisTOC *SynTOC, ibitmap *img, stb_matrix matrix);
	void Create(PBSynopsisTOC *SynTOC, ibitmap *img, stb_matrix matrix, stb_matrix adobe_matrix);
	void SetImageHeight(int height);
	int GetImageHeight();

	// Calculate item sizes
	int CalcItemHeight();
	// try to put item in remaining space
	int TryDrawItem(int space, int skip);

	void Draw(int posy, int space, int skip, int select, int lock_drawing);

	void SetImgLink(const char* link);
	const char* GetImgLink();
	void SetSVGPath(const char* path);
	const char* GetSVGPath();
	void LoadImage();
	ibitmap* GetImage();
	void ImageFree();

	void SetEndPosition(long long pos);
	long long GetEndLongPosition();
	void SetEndPosition(const char* pos);
	const char* GetEndPosition();

	void OutputSVG(stb_matrix matrix);
	int PointerHandler(int type, int par1, int par2);
	void Close();
	void SetMode(int mode);

	void Undo();
	void Redo();
	bool CanUndo();
	bool CanRedo();
	PBISVGObject *GetLastObject();
	void Replay(iv_handler replay);
	bool isDummy();

	void SetSettingsId(int id);
	int GetSettingsId();

	virtual bool Equal(const char *spos, const char *epos) = 0;

protected:
	void LoadSVG(stb_matrix matrix);
	static std::string SaveImage(ibitmap *bm);
	void ZoomIn(int *x, int *y, stb_matrix);

	static PBSynopsisPen* s_pPen;
	static PBSynopsisTOC* s_pTOC;
	int m_PointLTx, m_PointLTy, m_PointRBx, m_PointRBy;
	bool m_Input;

private:
	int m_Imgw;
	int m_Imgh;
	ibitmap* m_pImage;
	std::string m_Imglink;
	std::string m_SVGPath;
	std::string m_endposition;
	PBSVGController *m_pSVGCtrl;
	PBSVGObjectCreator *m_pSVGObjCreator;
	int m_Mode;
	PBISVGObject *m_pLastObject;
	int m_SettingsId;
};

#endif // PBSYNOPSISPEN_H

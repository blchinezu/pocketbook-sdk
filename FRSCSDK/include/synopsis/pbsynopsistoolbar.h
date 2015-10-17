/*
 * Copyright (C) 2011 Denis Kuzko <kda6666@ukr.net>
 */

#ifndef PBSYNOPSISTOOLBAR_H
#define PBSYNOPSISTOOLBAR_H

#include "pbsynopsisdefines.h"
#include <inkview.h>
#include <string>
#include <vector>
#include "pbsynopsisdialog.h"
#include "pbsynopsismenu.h"
#include "pbsynopsissnapshot.h"

#define STBI_MARKER	0x0001
#define STBI_NOTE	0x0002
#define STBI_PEN	0x0004
#define STBI_IMAGE	0x0008
#define STBI_ERASER	0x0010
#define STBI_UNDO	0x0020
#define STBI_REDO	0x0040
#define STBI_SEPARATOR	0x0080
#define STBI_HELP	0x0100
#define STBI_EXIT	0x0200
#define STBI_CONTENT	0x0300

#define STBIS_ACTIVE	0x0001
#define STBIS_FOCUS	0x0002
#define STBIS_PRESS	0x0004
#define STBIS_SELECT	0x0008

#define FREESPACE	14
#define PANELHEIGHT	40
#define TOPBORDER	5

typedef struct
{
	int type;
	int state;
	ibitmap *img;
	int x;
	int w;
} stb_item;

typedef struct
{
	bool visible;
	int x;
	int w;
	std::vector<stb_item> items;
} stb_panel;

typedef struct
{
	double a;
	double b;
	double c;
	double d;
	double e;
	double f;
} stb_matrix;

class PBSynopsisItem;
class PBSynopsisPen;
class PBSynopsisTOC;
class PBSynopsisSnapshot;

class EXPORT PBSynopsisToolBar
{
public:
	PBSynopsisToolBar();
	virtual ~PBSynopsisToolBar();

	void Open(PBSynopsisTOC *toc, iv_handler readerHandler, ibitmap *page, iv_dialoghandler toolHandler, PBSynopsisPen *pen);

	void AddPanel();
	void SetPanelVisible(int panelNo, bool visible);
	void SetPanelPosition(int panelNo, int x);

	void AddItem(int type, int panelNo);
	void SetItemState(int itemNo, int panelNo, int addState, int deleteState);

	void ReDraw(int update);

	void OutputPage(ibitmap *img = NULL, int update = -1, int x = 0, int y = 0, int w = 0, int h = 0);
	void PartialOutputPage(ibitmap *img, int x, int y, int w, int h);
	void InvertOutputPage(int x, int y, int w, int h, bool repaint);
	void UpdateOutputPage(int x, int y, int w, int h, bool bw);

	stb_matrix GetZoomIn();
	stb_matrix GetZoomOut();

	void ZoomIn(int *x, int *y);
	void ZoomIn(int *x, int *y, int *w, int *h);
	void ZoomOut(int *x, int *y);

	void SetPen(PBSynopsisPen *pen);
	PBSynopsisPen *GetPen();

	void OpenMarkerMenu(PBSynopsisItem *item);

private:
	void DrawPanel(int panelNo);
	void SetZoomIn(int x, int y, int w, int h);
	void SetZoomOut(int x, int y, int w, int h);

	// Marker menu
	void BackFromMenu(int index);
	static void EditMarkerText(char *text);
	static void DeleteMarker(int button);
	static void CommentPreviewDialog(int button);
	static void MarkerMenuHandler(int index);

	// Actions with tools
	void UpdatePanelsPositions();
	void SelectFirstActive();
	void UnStateOther(int panelNo, int itemNo, int state);
	void ActivateTool(int panelNo, int itemNo);
	void ActivateButton(int tool, bool active);
	void CheckUndoRedo(int panelNo, int itemNo, int redraw = -1);
	void MoveFocus(int step);
//	static void FocusUpdate();

	// handlers
	static int EventHandler(int type, int par1, int par2);
	void PressToolBarButton(int x, int y);
	void ReleaseToolBarButton(int x, int y);
	int SnapshotHandler(int type, int par1, int par2);
	int PointerHandler(int type, int par1, int par2);
	int KeyHandler(int type, int par1, int par2);

	// Help
	static void HelpDialog(int button);
	void OpenNotesHelp();

	// Snapshot
	std::string SaveSnapshot(int x1, int y1, int x2, int y2);
	static void SnapshotDialog(int button);

	// virtual
	virtual void PageBack() = 0;
	virtual void PageForward() = 0;
	virtual void OpenTOC() = 0;
	virtual void PauseCalcPage() = 0;
	virtual void ContinueCalcPage() = 0;
	virtual void RenderPage() = 0;
	virtual void CreateSnapshot(PBSynopsisSnapshot *snapshot) = 0;

	static PBSynopsisToolBar *m_pThis;
	std::vector<stb_panel> m_Panels;
	ibitmap *m_Page;
	ibitmap *m_StretchPage;
	PBSynopsisPen *m_pPen;
	iv_handler m_ReaderHandler;
	iv_dialoghandler m_ToolHandler;
	stb_matrix m_ZoomIn;
	stb_matrix m_ZoomOut;
	int m_ToolPanelHeight;
	int m_BorderSize;
	int m_SelectToolType;
	bool m_SendOut;
	iv_handler m_HandlerBeforeMenu;
	PBSynopsisTOC *m_pTOC;
	PBSynopsisItem *m_pMenuItem;
	char m_sText[20480];
	bool m_FirstOpen;

	PBSynopsisDialog m_Dialog;
	PBSynopsisMenu m_Menu;

	// snapshot
	int m_Snapshot_x1; // first point
	int m_Snapshot_y1; // first point
	int m_Snapshot_x2; // second point
	int m_Snapshot_y2; // second point
	PBSynopsisSnapshot *m_pSnapshot;

	// Focus
	bool m_Focused;
	int m_Focused_x;

	// adobe
public:
	void SetAdobeZoomIn(stb_matrix matrix);
	void SetAdobePage(ibitmap *page);
	stb_matrix m_AdobeZoomIn;
};

#endif // PBSYNOPSISTOOLBAR_H

#ifndef PBWINDOW_H
#define PBWINDOW_H

#include "pbdef.h"
#include "pbcommand.h"
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>
#include "inkview.h"
#include "inkinternal.h"

#include "pbrect.h"
#include "pbpoint.h"
#include "pbgraphics.h"
#include "pbrecordset.h"

#define BS_NONE 0
#define BS_RECT 1
#define BS_SHADOW 2

#define EVT_COMMAND 500

class PBScrollBar;
class PBTabPanel;

/*
 * Window Styles
 */
#define PBWS_VISIBLE          0x00000001
#define PBWS_DISABLED         0x00000002
#define PBWS_CAPTION          0x00000004
#define PBWS_BORDER           0x00000008
#define PBWS_VSCROLL          0x00000010
#define PBWS_HSCROLL          0x00000020
#define PBWS_AUTOVSCROLL      0x00000040
#define PBWS_AUTOHSCROLL      0x00000080
#define PBWS_LEFTSCROLL       0x00000100
#define PBWS_TOPSCROLL        0x00000200
#define PBWS_TABS	      0x00000400
#define PBWS_SELECT           0x00000800
#define PBWS_TRANSPARENT      0x00001000
#define PBWS_TABSTOP	      0x00002000

class PBWindow
{
public:
	friend class PBGraphics;

	PBWindow();
	virtual ~PBWindow();

	int Create(PBWindow* pParent, int left, int top, int width, int height, int style = 0, int exStyle = 0);
	void ChangeWindowStyle(int styleToSet, int styleToClear);
	void ChangeWindowStyleEx(int styleToSet, int styleToClear);

	void SetBackground(int color);
	virtual void SetBorderStyle(int bstyle);
	void SetBorderSize(int bsize);
	void SetShadowSize(int ssize);
	void SetVisible(bool visible);

	// properties
	int GetCommandID() const;
	void SetCommandID(int commandID);

	const ifont* GetWindowFont();
	void SetWindowFont(const ifont* pFont);

	// координаты окна относительно клиентской области родительского окна
	const PBRect& GetWindowRect() const;
	int GetLeft() const;
	int GetTop() const;
	int GetWidth() const;
	int GetHeight() const;
	int GetRight() const;
	int GetBottom() const;
	void SetWindowPos(int left, int top, int width, int height);
        void SetWindowPos(const PBRect & rect);

	// координаты клиентской области
	int GetClientLeft() const;
	int GetClientTop() const;
	int GetClientWidth() const;
	int GetClientHeight() const;
	PBRect GetClientRect();
	void GetClientRect(PBRect *pRect);

	// возвращает абсолютные координаты окна
	PBRect GetWindowScreenRect();

	int GetBackground() const;
	int GetBorderStyle() const;
	int GetBorderSize() const;
	int GetShadowSize() const;
	bool IsVisible() const;
	bool IsChanged() const;
	bool IsFocusChanged() const;
        bool IsFocused() const;
        void SetFocused();
        bool IsTransparent() const;
	bool IsTabstop() const;

	void SetSelect(bool select);	// Set select for object
	bool IsSelect() const;		// true - this item is selected
	bool ChangedSelection() const;	// true - must redraw selection border

	void Control(bool control);	// true - set for object that it can get the focus
	bool IsControl() const;		// true - object can get focus

	virtual void RemoveFocus();	// remove focus pointer in children
	virtual void SetFocus();	// default - empty; can set selection, changes fields, etc.

	// virtual functions
	virtual int MainHandler(int type, int par1, int par2);
	virtual int OnCommand(int commandId, int par1, int par2);
	virtual int OnChildFocusChanged(PBWindow* pFocused);
	virtual int OnCreate(){return 0;}; //TODO - make abstract

	// virtual callback menu function
	virtual void OnMenu(int index);
	virtual void OpenMenu();

	//int SetPosition(int position);

	// признак - требуется обновление экрана или нет
	bool IsDirty();

	// преобразует абсолютные координаты в относительные
	PBPoint ScreenToClient(const PBPoint &point);
        PBRect ScreenToClient(const PBRect &rect);

	// преобразуют относительные координаты в абсолютные
	PBPoint ClientToScreen(const PBPoint &point);
	PBRect ClientToScreen(const PBRect &rect);

	// отрисовывает окно, обновление экрана при этом не происходит.
	// область, которая была затронута прорисовкой, помечается как требующая обновления на экране
	virtual int OnDraw(bool force) = 0;
	virtual void OnPostDraw(bool /*force*/){};

	// отрисовывает себя и все вложенные окна и обновляет экран
	void ReDraw();

	// mark this window as chandged (need redraw). Also marks static flag m_sRedrawRequired
	void MarkAsChanged();
	void MarkAsFocusChanged();

	PBGraphics* GetGraphics();

	PBScrollBar *GetHScroll();
	PBScrollBar *GetVScroll();
	PBTabPanel *GetTabPanel();

	virtual void Bind(PBRecordset* pRecordset, int row, int col);

	PBWindow *GetParent();

	virtual void Run();	// for PBCommonBox

protected:


	void recalcClientRect();
	void AddChild(PBWindow* pChild);
        void RemoveChild(PBWindow* pChild);

	// возвращает смещение окна относительно начала координат экрана
	// вычисляется как суммарное смещение окна и всех его владельцев
	// используется для пересчета координат из относительных в абсолютные
	void getClientToScreenOffset(PBPoint *pOffset);

	// помечает область, требующую перерисовки. Передаются абслолютные координаты
	void Invalidate(PBRect screenRect, PBScreenUpdateType updateType);
	void DiscardInvalidation();

private:
	int Draw();
	// Resizing component
	virtual void OnResize();

protected:
	typedef std::vector<PBWindow*> TWindowList;
	typedef std::vector<PBWindow*>::iterator TWindowListIt;
	typedef std::vector<PBWindow*>::reverse_iterator TWindowListRIt;

	TWindowList m_Children;
//	std::vector<PBWindow*>::const_iterator m_itActiveChild;
//	std::vector<PBWindow*>::const_iterator m_itSearchChild;

	PBWindow *m_pParent;
	PBGraphics* m_pGraphics;
	int m_commandId;
	const ifont* m_pFont;

	//int m_position;

	// стили окна (скролл бар, рамка и т.д.), общие для всех окон и контролов
	int m_Style;
	// стили, которые переопределяются производными классами
	int m_ExStyle;

	// позиция и размер окна относительно клиентской области родительского окна
	PBRect m_WindowRect;

	// размеры и позиция клиентской области. Обычно это область окна минус рамка, скроллинг, таб.
	PBRect m_ClientRect;

	// позиция и размер области, требующей перерисовки, в абсолютных координатах
	static PBRect m_sDirtyRect;
	static PBScreenUpdateType m_sScreenUpdateType;

	int m_Background;
	int m_BorderStyle;
	int m_BorderSize;
	int m_ShadowSize;

	//bool m_Visible;

	// vertical scroll bar
	PBScrollBar *m_pVScroll;
	// horizontal scroll bar
	PBScrollBar *m_pHScroll;

	// tab panel
	PBTabPanel *m_pTabs;

	// recordset
	PBRecordset* m_pRecordset;
	int m_RecordsetRow;
	int m_RecordsetCol;

	// child which get focus
	PBWindow *m_pFocus;

	// Move focus to other object.
	// par1 - way;
	// focus - object which had focus;
	// round - search from objects round if nothing found in set way;
	//PBWindow *MoveFocus(int par1, PBWindow *focus, bool round);

private:
	// flag - this control has been changed
	bool m_Changed;
	bool m_ChangedSelection;
	// flag - this control can take focus
	bool m_Control;
	// flag - some of the controls has been changed. Screen redraw is required.
	static bool m_sRedrawRequired;

	int Distance(PBPoint p0, PBPoint p1, PBPoint p2);

};

#endif

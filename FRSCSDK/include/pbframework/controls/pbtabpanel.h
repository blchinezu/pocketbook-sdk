#ifndef PBTABPANEL_H
#define PBTABPANEL_H

#include "../framework/pbwindow.h"

#define ALIGNMENT_BOTTOM 0
#define ALIGNMENT_LEFT 1
#define ALIGNMENT_RIGHT 2
#define ALIGNMENT_TOP 3

#define HIDESPACE 20	// Space before first tab and after last tab

class PBTabPanel : protected PBWindow
{
public:
	PBTabPanel();
	~PBTabPanel();

	void Create(PBWindow *pParent);
	void Create(PBWindow *pParent, int total);
	void Create(PBWindow *pParent, int total, int current);
	void Create(PBWindow *pParent, int total, int current, int alignment);

	void SetAlignment(int alignment);
	void SetBackground(int background);
	void SetTabsCount(int tabscount);
	void SetCurrent(int current);
	void SetFont(ifont *font);

	int GetWidth() const;
	int GetHeight() const;
	int GetAlignment() const;
	int GetBackground() const;
	int GetTabsCount() const;
	int GetCurrent() const;

	int OnDraw(bool force);
	void UpdateSize();

	int MainHandler(int type, int par1, int par2);

protected:
	ibitmap *m_pActiveTab;
	ibitmap *m_pInactiveTab;
	int m_Alignment;
	int m_TabsCount;	// total tabs
	int m_TabsCurrent;	// select tabs

private:
	ifont *m_pFont;
	int m_Length;		// length of panel
	int m_X;		// x point of first tab
	int m_Y;		// y point of first tab
	int m_ShiftX;		// step for count point for next tab
	int m_ShiftY;		// step for count point for next tab
	int m_LeftViewTab;	// number of first tab(after tab with points) when some tab from left are hide
	int m_RightViewTab;	// number of last tab(before tab with points) when some tab from right are hide
	int m_ViewTabs;		// count of display tabs

	void RecountNewPosition();	// Recount new parametrs for drawing tabs. Use when change alignment
	void RecountViewTabs();		// Recount display tabs
	void DrawTab(int x, int y, const char *text, bool active);
	bool ClickTab(int x, int y, int tabx, int taby);	// verify tab click
	int GetTabPointer(int x, int y);	// return number of clicked tab

};

#endif // PBTABPANEL_H

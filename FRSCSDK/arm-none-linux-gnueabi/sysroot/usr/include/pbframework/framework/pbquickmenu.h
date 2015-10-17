#ifndef PBQUICKMENU_H
#define PBQUICKMENU_H

#include "pbbitmapbutton.h"

const int QUICK_MENU_SIZE = 322;

class PBQuickMenu : public PBWindow
{
public:
    PBQuickMenu();
	~PBQuickMenu();

	// virtual overloads
	int OnCreate();
	int OnDraw(bool force);
	int OnCommand(int commandId, int par1, int par2);

	// menu specifics
	void Show(int x, int y);
	void Hide();

	PBBitmapButton* CreateButton(int row, int col, int commandID, const ibitmap* pIcon, const char* label, bool updateAfterClose = true);

	int MainHandler(int type, int par1, int par2);

protected:
	void IncrementCol(bool checkOther, bool checkEmpty);
	void IncrementRow(bool checkOther, bool checkEmpty);
	void DecrementCol(bool checkOther, bool checkEmpty);
	void DecrementRow(bool checkOther, bool checkEmpty);

protected:
	ibitmap *m_pImgSave;
	PBBitmapButton* m_buttons[3][3];
	int m_row;
	int m_col;
	std::map<int, bool> m_commandUpdateMap;
};

#endif // PBQUICKMENU_H

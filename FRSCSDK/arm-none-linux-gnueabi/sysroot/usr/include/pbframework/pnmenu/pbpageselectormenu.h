#pragma once
#include "../framework/pbwindow.h"
#include <deque>
class PBPageNavigatorMenu;
class PBPageSelectorMenu: public PBWindow
{
    int PageNumberX, PageNumberY;
    int ActivateIndex;
    int Page;
    PBRect Rects[15];
    PBRect PageNumber;
    PBPageNavigatorMenu *PageNavigator;
    int m_Size;
    int m_SizeB;
    void Draw2BottomButtons();
public:
    int OnDraw(bool force);
    PBPageSelectorMenu(PBPageNavigatorMenu *parent);

    virtual ~PBPageSelectorMenu();
    int MainHandler(int type, int par1, int par2);
    int MainHandler(int type, int par1, int par2, bool &focus);
    void Show();
    void Activate(int n);
    void DeActivate();
    void UpdatePage();
};

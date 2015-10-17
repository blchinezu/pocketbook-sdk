#pragma once
#include "../framework/pbwindow.h"
#include <deque>
#include "pbpageselectormenu.h"

class PBPageHistoryMenu;

class IHistoryPage
{
public:
    virtual ~IHistoryPage()
    {}

    virtual bool operator ==(const IHistoryPage &page) const = 0;

    virtual void GoToPage() = 0;
    virtual void GoToPage(int page) = 0;


    virtual  IHistoryPage *CreatePage(int npage) = 0;    

    virtual std::string ToString() const = 0;

    virtual void Show(const PBRect & rect) = 0;

};
typedef std::deque<IHistoryPage *> THistory;
class PBPageHistoryMenu;
class PBPageNavigatorMenu: public PBWindow
{
    static PBPageNavigatorMenu* s_PageNavigator;
    enum EDirection {LAST, FIRST, PREVIOUS, NEXT};
    enum EShowMode {SHOWMODE, FULLSHOWMODE};
    static const int DEFAULT_TIME_OUT = 1500;
    PBPageHistoryMenu* m_hmenu;
    PBPageSelectorMenu* m_smenu;
    THistory m_hist;
    const ibitmap *RetBitMap;
    EShowMode ShowMode;
    IHistoryPage * RetPage;
    IHistoryPage *RetShowPage;
    IHistoryPage *RetShowPageWait;
    int PageForShowPage;
    void DrawPreviewString(IHistoryPage *ip);
    int gWidth;
    int gHeight;
    int hWidth;
    int titleH, helpH, xH;

    void DrawPreviewString();
    void CommonShowPart(IHistoryPage * page);
    void DrawHelp(const PBRect & rect);

protected:
    //virtual void GoToPage(int) = 0;

    //virtual void GoToPage(EDirection dir) = 0;


public:


    void AddPage();
    void RetPicture(void);
    PBPageHistoryMenu* GetHistoryMenu();
    bool IsPointerIn(PBWindow *w, int par1, int par2);
    bool IsPointerIn(PBRect rect, int par1, int par2);
    bool NeedChangeFocus(int item);
    void ShowPage(IHistoryPage *ip);
    void ShowPageTimer(IHistoryPage *hp, int t = DEFAULT_TIME_OUT);
    void ShowPageTimer(int page, int t = DEFAULT_TIME_OUT);
    static void TimerProc();
    void AssignRetShowPage(IHistoryPage * page);
    void AssignRetShowPageWait(IHistoryPage * page);
    void AssignRetPage(IHistoryPage * page);
    void DeleteHistoryPage(IHistoryPage * page);

    int OnDraw(bool force);
    PBPageNavigatorMenu(PBWindow* pParent);

    virtual ~PBPageNavigatorMenu();

    void FullShow(IHistoryPage * page);

    void Show(IHistoryPage * page);
    int MainHandler(int type, int par1, int par2);
    int Handler(int type, int par1, int par2, bool &retfocus);
    void GotoPage(IHistoryPage * page);
    void GotoPage(int npage);
    bool IsInHistory(IHistoryPage * page);
};


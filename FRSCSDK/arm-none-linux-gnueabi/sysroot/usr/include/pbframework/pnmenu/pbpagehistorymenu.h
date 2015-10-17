#pragma once
#include <vector>
#include <queue>
#include "../framework/pbwindow.h"
#include "pbpagenavigatormenu.h"
class PBToolButton;
//namespace std
//{
//    class string;
//};

class IPage
{
    friend class PBPageNavigator;
    void appendDigit(unsigned char);
    void backSpace();
public:
    enum EPAGE {FIRST, LAST, DIRECT, CANCEL};
    //possible string or number

protected:
    int key;

    //CANCEL is default
    EPAGE page;
public:
    IPage();
    virtual ~IPage();

    IPage(EPAGE page);

    IPage(const int & key, EPAGE page);

    void SetType(EPAGE page);

    EPAGE GetType() const;

    virtual std::string ToString() const; //text info like page number or link

    virtual void Open() = 0;

    const int & GetKey() const;

    void SetKey(const int & key);
    //
    virtual void OnPreview(const int &)
    {

    }
    //


protected:
    bool cancel;
    bool first;
    bool last;
    //bool CanDraw();
};
#include <deque>
#include "../framework/pbwindow.h"
#include "inkview.h"
#include "stdio.h"
#include "../framework/pbrect.h"
class PBToolButton;

class IPosition : public PBWindow
{
    static const int HMARGIN = 15;
    static const int VMARGIN = 20;
    static const int HPAGE_NUMBER__MERGIN = 85;
    static const int VPAGE_NUMBER__MERGIN = 25;

    static const int HFRAME__MERGIN = 6;
    static const int VFRAME__MERGIN = 6;

private:
    IHistoryPage * m_histPage;
    void Init();
    void InitPBWindow();    
public:
    enum EFORMAT {VERTICAL, LANDSCAPE};

    IHistoryPage * ToIHistoryPage() const { return m_histPage;}    
    IPosition(IHistoryPage * page);
    static EFORMAT CurrentOrientation();
    virtual ~IPosition();
    virtual bool operator ==(const IPosition & pos)
    {
        return m_histPage->operator ==(*(pos.ToIHistoryPage()));
    }
    virtual int OnDraw(bool force);
    // Interface IHistoryPage support    
    virtual void GoToPage() { m_histPage->GoToPage();}
    virtual std::string ToString() const { return  m_histPage->ToString();}
    virtual bool operator ==(const IHistoryPage &page) const {
        return *m_histPage == page;
    }    
    //// Interface IHistoryPage support    
    inline bool operator !=(const IPosition & pos)
    {
        return !(*this == pos);
    }    
};
class PBPageNavigatorMenu;
class PBPageHistoryMenu : public PBWindow
{
    ibitmap *m_pImgSave;
    bool m_wasPressed;
    bool m_tryReturnfocus;
    bool m_hasNeighbour;
    PBPageNavigatorMenu *m_MainMenu;

protected:
    int m_state;
    std::deque<IPosition *> m_queue4;

    // 1 2
    // 3 4

public:

    bool exit;
    PBPageHistoryMenu(PBWindow* pParent, PBPageNavigatorMenu * main_menu, int x = 30, int y = 30, int width = 300, int height = 400);


    //int Handler(int type, int par1, int par2, bool &retfocus);  //ret = 1
//    void SetFocus();
//    bool IsFocused();
    //void SetWindowPos(PBRect &);
    void Show(THistory &m_hist);

    IPosition::EFORMAT m_orient;
    static const float DELTA = 0.05;


    virtual ~PBPageHistoryMenu();

    void ClearAll();

    virtual void AddPosition(IHistoryPage * pos);

    //from PBWindow
    virtual void SetFocus();

    virtual void OnResize();

    virtual int OnDraw(bool force);

    virtual int MainHandler(int type, int par1, int par2);

    int MainHandler(int type, int par1, int par2, bool &retfocus);

    virtual int PointerHandler(int type, int par1, int par2);

    void Show();

    void Hide();
private:
    void DoFocusOn(int);
    void SetFocusOnFirst();
};



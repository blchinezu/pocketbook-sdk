#ifndef PBTOOLBUTTON_H
#define PBTOOLBUTTON_H

#include "../framework/pbwindow.h"

#define ALIGNMENT_BOTTOM 0
#define ALIGNMENT_LEFT 1
#define ALIGNMENT_RIGHT 2
#define ALIGNMENT_TOP 3

class PBToolButton : public PBWindow
{
public:
	PBToolButton();
	~PBToolButton();

	int OnCreate();
	int MainHandler(int type, int par1, int par2);
	int OnCommand(int commandId, int par1, int par2);
	virtual void Run();

	void SetText(const char *text);
	void SetImage(ibitmap *image);
	void SetCommand(int command);

	void SetPressed(bool pressed);
	bool IsPressed() const;

	void CanRelease(bool release);

	char *GetText() const;

	void SetFont(const char *fontname, int fontsize, int color);
	void SetTextProperties(int textproperties);
	void SetImageAlignment(int alignment);

	void RemoveFocus();
	void SetFocus();

protected:

private:
	int OnDraw(bool force);

	int m_TextProperties;
	char *m_pText;

	char *m_pFontName;
	int m_FontSize;
	int m_TextColor;
	ifont *m_pFont;
	int m_ImageAlignment;
	ibitmap *m_pImage;
	int m_Command;
	bool m_Pressed;
	bool m_CanRelease;
};

#endif // PBTOOLBUTTON_H

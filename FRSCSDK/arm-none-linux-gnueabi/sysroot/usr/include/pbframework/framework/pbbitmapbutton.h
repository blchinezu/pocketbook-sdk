#ifndef PBBITMAPBUTTON_H
#define PBBITMAPBUTTON_H

#include "pbwindow.h"

// button styles
#define PBWS_BTN_PRESSED	0x00000001

class PBBitmapButton : public PBWindow
{
public:
    PBBitmapButton();

	// virtual overloads
	int OnCreate();
	int OnDraw(bool force);
	int MainHandler(int type, int par1, int par2);

	bool IsPressed();

	const char* GetText() const;
	void SetText(const char* text, int textProperties);

	void SetImage(const ibitmap* pImage, PBAlignment alignment);

protected:
	const ibitmap *m_pImage;

	PBAlignment m_ImageAlignment;
	std::string m_text;
	int m_TextColor;
	int m_TextProperties;
};

#endif // PBBITMAPBUTTON_H

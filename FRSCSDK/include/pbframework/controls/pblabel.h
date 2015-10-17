#ifndef __PBLABEL_H__
#define __PBLABEL_H__

#include "../framework/pbwindow.h"
#include "../framework/pbstring.h"

class PBLabel : public PBWindow
{
public:
	PBLabel();
	~PBLabel();

	// virtual overloads
	int OnCreate();
	int OnDraw(bool force);

	void SetText(const char *text, int properties);
	const char* GetText() const;

	void SetFont(const char *fontname, int fontsize, int color);
	void SetProperties(int properties);

protected:
	int m_Properties;
	PBString m_text;
	int m_TextColor;
	const ifont *m_pFont;
};

#endif /* __PBLABEL_H__ */

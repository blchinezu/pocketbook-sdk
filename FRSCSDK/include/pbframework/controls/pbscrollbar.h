#ifndef __PBSCROLLBAR_H__
#define __PBSCROLLBAR_H__

#include "../framework/pbwindow.h"

typedef enum
{
    PB_VERTICAL,
    PB_HORIZONTAL
} PBORIENTATION;

class PBScrollBar : public PBWindow
{
public:
	PBScrollBar();
	~PBScrollBar();

	bool Create(PBWindow* pParent, int minimum, int maximum, int pageStep, PBORIENTATION orientation);

	int MainHandler(int type, int par1, int par2);

	int maximum() const;
	int minimum() const;
	PBORIENTATION orientation() const;
	int pageStep() const;
	int value() const;

	void setMaximum(int value);
	void setMinimum(int value);
	void setPageStep(int value);
	void setValue(int value);

protected:
private:
	int OnDraw(bool force);
	void updateVisibleState();

	ibitmap* firstControl, *secondControl;
	PBORIENTATION m_orientation;
	int m_maximum;
	int m_minimum;
	int m_pageStep;
	int m_value;
};

#endif /* __PBSCROLLBAR_H__ */

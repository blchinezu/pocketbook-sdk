#ifndef PBGRAPHICS_H
#define PBGRAPHICS_H

#include <inkview.h>

#define RIGHTTOP 1
#define TOPRIGHT RIGHTTOP
#define LEFTTOP 2
#define TOPLEFT LEFTTOP
#define LEFTBOTTOM 4
#define BOTTOMLEFT LEFTBOTTOM
#define RIGHTBOTTOM 8
#define BOTTOMRIGHT RIGHTBOTTOM
#define FILLCORN 16

class PBWindow;

class PBGraphics
{
public:
	PBGraphics(PBWindow *pParent);
	~PBGraphics();

	void Create(PBWindow *pParent);

// Graphic functions

	void DrawSelection(int x, int y, int w, int h, int color);

	void DrawPixel(int x, int y, int color);

	void DimArea(int x, int y, int w, int h, int color);
	void DrawRect(int x, int y, int w, int h, int color);
	void StretchBitmap(int x, int y, int w, int h, const ibitmap *src, int flags);
	void DrawLine(int x1, int y1, int x2, int y2, int color);
	void DrawTextRect(int x, int y, int w, int h, const char *s, int flags);
	void DrawBitmap(int x, int y, const ibitmap *b);
	void DrawBitmapBW(int x, int y, const ibitmap *b);

	void FillArea(int x, int y, int w, int h, int color);
	void DrawBitmapRect(int x, int y, int w, int h, ibitmap *b, int flags);
	void DrawBitmapRectBW(int x, int y, int w, int h, ibitmap *b, int flags);

	void RotateBitmap(ibitmap **pbm, int rotate);

// Curves and Circles

	void DrawCurve(int x, int y, int radius, int corns, int color);
	void DrawCurve(int x, int y, int radius, int corns, int thickness, int color);
	void DrawCircle(int x, int y, int radius, int color);
	void DrawCircle(int x, int y, int radius, int color, bool fill);
	void DrawCircle(int x, int y, int radius, int thickness, int color);

	void DrawShadow(int x, int y, int w, int h, int radius, int shadowsize, int color);
	void DrawFrame(int x, int y, int w, int h, int radius, int thickness, int color);
	void DrawFrame(int x, int y, int w, int h, int radius, int thickness, int shadowsize, int color);

// Font functions

	ifont *OpenFont(const char *name, int size, int aa);
	void SetFont(const ifont *font, int color);

// Hourglass
	void ShowHourglass();
	void ShowHourglassAt(int x, int y);
	void HideHourglass();

// Menu functions
	void OpenMenu(PBWindow *client, imenu *menu, int pos, int x, int y);
	static void MenuHandler(int index);

// Panel
	int DrawPanel(const ibitmap *icon, const char *text, const char *title, int percent);

// Object which calling menu or something else in future
	static PBWindow *m_pClient;

	void drawCircleEx(int x, int y, int w, int h, int r, int thickness, int lineColor);
	void fillCircleEx(int x, int y, int w, int h, int r, int fillColor);
	void invertCircleEx(int x, int y, int w, int h, int r);
	void DrawRectEx(int x, int y, int w, int h, int cornerRadius, int thickness, int lineColor, int fillColor);
	void FillRectEx(int x, int y, int w, int h, int cornerRadius, int fillColor);
	void InvertRectEx(int x, int y, int w, int h, int cornerRadius);

private:
	PBWindow *m_pParent;

// private methods

	void CoordsX(int *x);
	void CoordsX(int *x1, int *x2);
	void CoordsY(int *y);
	void CoordsY(int *y1, int *y2);
};

#endif // PBGRAPHICS_H

/*
 * Copyright (C) 2011 Denis Kuzko <kda6666@ukr.net>
 */

#ifndef PBSYNOPSISMENU_H
#define PBSYNOPSISMENU_H

#include <inkview.h>
#include <string>
#include <vector>

typedef struct synopsis_imenu_s
{
	int type;
	int index;
	std::string text;
	ibitmap *img;
} synopsis_imenu;

typedef struct synopsis_imenu_pos_s
{
	int x;
	int y;
} synopsis_imenu_pos;

class PBSynopsisMenu
{
public:
	PBSynopsisMenu();
	~PBSynopsisMenu();

	void Open(iv_menuhandler handler);
	void Open(const synopsis_imenu *items, iv_menuhandler handler);
	void Clear();

	void SetHeaderText(const char *text);
	void AddItem(int type, int index, const char *text, ibitmap *bmp);

private:
	void CalcWindowHeight();
	void DrawWindow();
	static int EventHandler(int type, int par1, int par2);

	iv_menuhandler m_Handler;
	iv_handler m_PrevHandler;
	int m_x;
	int m_y;
	int m_w;
	int m_h;
	int m_ItemHeight;
	int m_Select;

	std::string m_HeaderText;
	std::vector<synopsis_imenu> m_vItems;
	std::vector<synopsis_imenu_pos> m_vItemsPos;

	static PBSynopsisMenu *m_pThis;
	ibitmap *m_pBackground;
};

#endif // PBSYNOPSISMENU_H

/*
 * Copyright (C) 2011 Denis Kuzko <kda6666@ukr.net>
 */

#ifndef PBSYNOPSISDIALOG_H
#define PBSYNOPSISDIALOG_H

#include <inkview.h>
#include <string>
#include <vector>

#define DLG_TEXT 1
#define DLG_IMG 2
#define DLG_IMGTEXT 3

#define DLG_BTN_CLOSE 1
#define DLG_BTN_EDIT 2
#define DLG_BTN_OK 3
#define DLG_BTN_DELETE 4

typedef struct dialog_content_s
{
	int type;
	std::string text;
	ibitmap *img;
} dialog_content;

typedef struct dialog_button_s
{
	int type;
	std::string text;
	int x;
	int y;
	int w;
	int h;
} dialog_button;

class PBSynopsisDialog
{
public:
	PBSynopsisDialog();
	~PBSynopsisDialog();

	void Open(iv_dialoghandler handler);
	void Clear();

	void SetHeaderText(const char *text);
	void AddContent(const char *text, ibitmap *img = NULL);
//	void AddContent(dialog_content *content);
	void AddButton(int type, const char *text);

private:
	void CalcWindowHeight();
	void DrawWindow();
	void DrawBtn(int btn, bool sel);
	static int EventHandler(int type, int par1, int par2);

	iv_dialoghandler m_Handler;
	iv_handler m_PrevHandler;
	int m_x;
	int m_y;
	int m_w;
	int m_h;

	std::string m_HeaderText;
	std::vector<dialog_content> m_vContent;
	std::vector<dialog_button> m_vButtons;

	static PBSynopsisDialog *m_pThis;
	ibitmap *m_pBackground;

	int m_SelBtn;
};

#endif // PBSYNOPSISDIALOG_H

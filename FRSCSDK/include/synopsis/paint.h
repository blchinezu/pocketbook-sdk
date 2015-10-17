/*
 * Copyright (C) 2011 Denis Kuzko <kda6666@ukr.net>
 */

#ifndef PAINT_H
#define PAINT_H

#include <inkinternal.h>
#include <inkview.h>

#define TOOL_NULL 0
#define TOOL_PEN_SMALL 1
#define TOOL_PEN_MEDIUM 2
#define TOOL_PEN_BIG 3
#define TOOL_ERASE_SMALL 4
#define TOOL_ERASE_BIG 5
#define TOOL_MOVE 6
#define TOOL_UNDO 7
#define TOOL_SAVE_EXIT 8
#define TOOL_EXIT 9

typedef struct itool_s{
	
	int type;
	ibitmap *image;
	int x, y;
	int w, h;
	int select;
	
} itool;

void OpenPaint(char *BitmapName, itool *tools, iv_dialoghandler backproc);

#endif // PAINT_H

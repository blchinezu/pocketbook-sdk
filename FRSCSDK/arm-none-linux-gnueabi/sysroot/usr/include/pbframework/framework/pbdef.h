#ifndef PBDEF_H
#define PBDEF_H

#include <string>
#define REPORT_FUNCTION fprintf(stderr, "WARNING: %s not overloaded\n", __PRETTY_FUNCTION__);return 0;
#define REPORT_PROCEDURE fprintf(stderr, "WARNING: %s not overloaded\n", __PRETTY_FUNCTION__);return;

typedef enum _PBScreenUpdateType
{
	updateNone,
	updateRectBW,
	updateRect,
	updateFullScreen
} PBScreenUpdateType;

typedef enum _PBAlignment
{
	aligmentBottom,
	aligmentTop,
	aligmentLeft,
	aligmentRigth,
	aligmentCenter
} PBAlignment;

//const int def_CloseApp          =   1;
//const int def_Border3x3         =   324;
//const int def_BorderFrame2x4w   =   433;
//const int def_BorderFrame2x4h   =   218;
//const int def_BorderFrame1x4w   =   433;
//const int def_BorderFrame1x4h   =   116;
//
//const int def_BtnOffsetX        =   29;
//const int def_BtnOffsetY        =   20;
//const int def_BtnNoStrOffsetXY  =   29;
//const int def_BtnRotateOffsetXY =   16;
//const int def_BtnStdWidth       =   32;
//const int def_BtnStdHeight      =   32;
//const int def_BtnRotateWidth    =   58;
//const int def_BtnRotateHeight   =   58;
//const int def_BitmapMenuWidth   =   94;
//const int def_BitmapMenuHeight  =   94;
//const int def_BLACK             =   0;
//const int def_WHITE             =   0xffffff;
//const int def_CountBtnMainMenu1 =   9;
//const int def_CountBtnSubMenu2  =   8;
//const int def_CountBtnSubMenu3  =   4;
//const int def_CountBtnSubMenu4  =   4;
//const std::string NOSTR         =  "";

#endif // PBDEF_H

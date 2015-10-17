#ifndef INKVIEW_H
#define INKVIEW_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/sysinfo.h>
#include <signal.h>
#include <errno.h>
#include <zlib.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_IMAGE_H
#include FT_OUTLINE_H

#ifdef __cplusplus
extern "C"
{
#endif

#define APP_UID 101
#define APP_GID 101

#ifndef IVSAPP
#if !defined(__CYGWIN__) && defined(__i386__)
#  define DIRPREFIX "/usr/local/pocketbook"
#else
#  define DIRPREFIX ""
#endif
#define FLASHDIR DIRPREFIX "/mnt/ext1"
#define SDCARDDIR DIRPREFIX "/mnt/ext2"
#define USBDIR DIRPREFIX "/mnt/ext3"
#define SYSTEMDATA DIRPREFIX "/ebrmain"
#define USERDATA FLASHDIR "/system"
#define USERDATA2 SDCARDDIR "/system"
#define TEMPDIR DIRPREFIX "/tmp"
#else
#define FLASHDIR "./system/mnt/ext1"
#define SDCARDDIR "./system/mnt/ext2"
#define USBDIR "./system/mnt/ext3"
#define SYSTEMDATA "./system"
#define USERDATA SYSTEMDATA
#define USERDATA2 SDCARDDIR "/system"
#define TEMPDIR "./system/tmp"
#endif

#define SYSTEMFONTDIR SYSTEMDATA "/fonts"
#define USERFONTDIR USERDATA "/fonts"
#define TEMPFONTPATH TEMPDIR "/fonts"
#define PHOTOTEMPDIR TEMPDIR "/photo"
#define USERPROFILES USERDATA "/profiles"
#define USERPROFILES2 USERDATA2 "/profiles"
#define CURRENTPROFILE USERPROFILES "/.current"
#define LASTPROFILE USERPROFILES "/.last"
#define SALVAGEPROFILES USERPROFILES "/.salvage"
#define CONFIGPATH USERDATA "/config"
#define STATEPATH USERDATA "/state"
#define SYSTEMTHEMESPATH SYSTEMDATA "/themes"
#define USERTHEMESPATH USERDATA "/themes"
#define GLOBALCONFIGFILE CONFIGPATH "/global.cfg"
#define NETWORKCONFIGFILE CONFIGPATH "/network.cfg"
#define TSCALDATA CONFIGPATH "/tsc.dat"
#define TSCALDATA2 TEMPDIR "/tsc.dat"
#define SYSTEMLANGPATH SYSTEMDATA "/language"
#define USERLANGPATH USERDATA "/language"
#define SYSTEMKBDPATH SYSTEMDATA "/language/keyboard"
#define USERKBDPATH USERDATA "/language/keyboard"
#define SYSTEMDICTPATH SYSTEMDATA "/dictionaries"
#define USERDICTPATH1 USERDATA "/dictionaries"
#define USERDICTPATH2 USERDATA2 "/dictionaries"
#define SYSTEMLOGOPATH SYSTEMDATA "/logo"
#define USERLOGOPATH USERDATA "/logo"
#define NOTESPATH FLASHDIR "/notes"
#define GAMEPATH FLASHDIR "/applications"
#define USERAPPDIR USERDATA "/bin"
#define CACHEPATH USERDATA "/cache"
#define BACKUPDIR SDCARDDIR "/backup"
#define USERBOOKSHELF USERDATA "/bin/bookshelf.app"
#define SYSTEMBOOKSHELF SYSTEMDATA "/bin/bookshelf.app"
#define USERMPD USERDATA "/bin/mpd.app"
#define SYSTEMMPD SYSTEMDATA "/bin/mpd.app"
#define STATECLEANER SYSTEMDATA "/bin/cleanstate.sh"
#define BACKUPSCRIPT SYSTEMDATA "/bin/backup.sh"
#define RESTORESCRIPT SYSTEMDATA "/bin/restore.sh"
#define NETAGENT SYSTEMDATA "/bin/netagent"
#define BOOKLANDAPP SYSTEMDATA "/bin/bookland.app"
#define USERMPLAYER USERDATA "/bin/mplayer.so"
#define USERBOOKINFO USERDATA "/bin/bookinfo.so"
#define POCKETBOOKSIG USERDATA "/.pocketbook"
#define LASTOPENBOOKS STATEPATH "/lastopen.txt"
#define FAVORITES USERDATA "/favorite"
#define CURRENTBOOK TEMPDIR "/.current"
#define BOOKSHELFSTATE TEMPDIR"/.bsstate"
#define BOOKSHELFSTATE_NV STATEPATH "/.bsstate"
#define HISTORYFILE TEMPDIR "/history.txt"
#define DICKEYBOARD TEMPDIR "/dictionary.kbd"
#define PLAYLISTFILE TEMPDIR "/playlist.pls"
#define NETAGENTLOG TEMPDIR "/netagent.log"
#define ADOBEPATH FLASHDIR "/.adobe-digital-editions"
#define ADOBEPATH2 SDCARDDIR "/.adobe-digital-editions"
#define HANDLERSPATH CONFIGPATH "/handlers.cfg"
#define URLHISTORY CACHEPATH "/urlhistory.txt"
#define WEBCACHE "/tmp/webcache"
#define WEBCACHEINDEX WEBCACHE "/index"
#define WIDGETSCONFIG CONFIGPATH "/widgets"
#define WIDGETSOPEN WIDGETSCONFIG "/open.cfg"

#define DEFAULTFONT "LiberationSans"
#define DEFAULTFONTB "LiberationSans-Bold"
#define DEFAULTFONTI "LiberationSans-Italic"
#define DEFAULTFONTBI "LiberationSans-BoldItalic"
#define DEFAULTFONTM "LiberationMono"

#define PF_LOCAL  0x01
#define PF_SDCARD 0x02

#define SYSTEMDEPTH 8

#define MSG_REQUEST 0x7fffffff
#define MSG_OK 1
#define MSG_ERROR 0

#define MSG_FORMAT     0x101
#define MSG_SETTIME    0x102
#define MSG_SETPROFILE 0x103
#define MSG_PWENCRYPT  0x104
#define MSG_PWDECRYPT  0x105
#define MSG_RESTART    0x106
#define MSG_REMOUNTFS  0x107
#define MSG_REG_CHECK	 0x10d
#define MSG_REG_WRITE	 0x10e
#define MSG_DEVICEKEY  0xad0be01

#define EVT_INIT 21
#define EVT_EXIT 22
#define EVT_SHOW 23
#define EVT_REPAINT 23
#define EVT_HIDE 24
#define EVT_KEYDOWN 25
#define EVT_KEYPRESS 25
#define EVT_KEYUP 26
#define EVT_KEYRELEASE 26
#define EVT_KEYREPEAT 28
#define EVT_POINTERUP 29
#define EVT_POINTERDOWN 30
#define EVT_POINTERMOVE 31
#define EVT_POINTERLONG 34
#define EVT_POINTERHOLD 35
#define EVT_ORIENTATION 32

#define EVT_TOUCHUP   40
#define EVT_TOUCHDOWN 41
#define EVT_TOUCHMOVE 42

#define EVT_SNAPSHOT 71
#define EVT_FSCHANGED 72

#define EVT_MP_STATECHANGED 81
#define EVT_MP_TRACKCHANGED 82

#define EVT_PREVPAGE 91
#define EVT_NEXTPAGE 92
#define EVT_OPENDIC  93

#define EVT_TAB 119
#define EVT_PANEL 120
#define EVT_PANEL_ICON 121
#define EVT_PANEL_TEXT 122
#define EVT_PANEL_PROGRESS 123
#define EVT_PANEL_MPLAYER 124
#define EVT_PANEL_USBDRIVE 125
#define EVT_PANEL_NETWORK 126
#define EVT_PANEL_CLOCK 127
#define EVT_PANEL_BLUETOOTH 128

#define EVT_BT_RXCOMPLETE 171
#define EVT_BT_TXCOMPLETE 172

#define EVT_SYNTH_ENDED 200
#define EVT_DIC_CLOSED	201

#define ISKEYEVENT(x) ((x)>=25 && (x)<=28)
#define ISPOINTEREVENT(x) (((x)>=29 && (x)<=31) || ((x)>=34 && (x)<=35))
#define ISPANELEVENT(x) ((x)>=119 && (x) <= 132)

#undef KEY_UP
#undef KEY_DOWN
#undef KEY_LEFT
#undef KEY_RIGHT
#undef KEY_OK
#undef KEY_BACK
#undef KEY_MENU
#undef KEY_DELETE
#undef KEY_MUSIC
#undef KEY_POWER
#undef KEY_PREV
#undef KEY_NEXT
#undef KEY_MINUS
#undef KEY_PLUS
#undef KEY_0
#undef KEY_1
#undef KEY_2
#undef KEY_3
#undef KEY_4
#undef KEY_5
#undef KEY_6
#undef KEY_7
#undef KEY_8
#undef KEY_9

#define KEY_BACK 0x1b
#define KEY_DELETE 0x08
#define KEY_OK 0x0a
#define KEY_UP 0x11
#define KEY_DOWN 0x12
#define KEY_LEFT 0x13
#define KEY_RIGHT 0x14
#define KEY_MINUS 0x15
#define KEY_PLUS 0x16
#define KEY_MENU 0x17
#define KEY_MUSIC 0x1e
#define KEY_POWER 0x01
#define KEY_PREV 0x18
#define KEY_NEXT 0x19
#define KEY_PREV2 0x1c
#define KEY_NEXT2 0x1d

#define KEY_0 0x30
#define KEY_1 0x31
#define KEY_2 0x32
#define KEY_3 0x33
#define KEY_4 0x34
#define KEY_5 0x35
#define KEY_6 0x36
#define KEY_7 0x37
#define KEY_8 0x38
#define KEY_9 0x39

#define BLACK 0x000000
#define DGRAY 0x555555
#define LGRAY 0xaaaaaa
#define WHITE 0xffffff

#define ITEM_HEADER 1
#define ITEM_ACTIVE 2
#define ITEM_INACTIVE 3
#define ITEM_SUBMENU 5
#define ITEM_SEPARATOR 6
#define ITEM_BULLET 7
#define ITEM_HIDDEN 128

#define KBD_NORMAL 0
#define KBD_ENTEXT 1
#define KBD_PHONE 2
#define KBD_NUMERIC 4
#define KBD_IPADDR 5
#define KBD_FILENAME 6
#define KBD_URL 7
#define KBD_DATE 8
#define KBD_TIME 9
#define KBD_DATETIME 10
#define KBD_HEX 11

#define KBD_UPPER 0x10
#define KBD_LOWER 0x20
#define KBD_FIRSTUPPER 0x30

#define KBD_PASSWORD  0x100
#define KBD_NOSELECT  0x200
#define KBD_SCREENTOP 0x400

#define KBD_PASSEVENTS 0x8000

#define ICON_INFORMATION 1
#define ICON_QUESTION 2
#define ICON_WARNING 3
#define ICON_ERROR 4

#define DEF_BUTTON1 0
#define DEF_BUTTON2 0x1000

#define PANELICON_BOOK ((const ibitmap *) -11)
#define PANELICON_LOAD ((const ibitmap *) -12)

#define LIST_BEGINPAINT 1
#define LIST_PAINT 2
#define LIST_ENDPAINT 3
#define LIST_OPEN 4
#define LIST_MENU 5
#define LIST_DELETE 6
#define LIST_EXIT 7
#define LIST_ORIENTATION 8
#define LIST_POINTER 9
#define LIST_INFO 11
#define LIST_SCROLL 12

#define LISTFLAG_SCROLL 0x40000000

#define BMK_CLOSED -1
#define BMK_SELECTED 1
#define BMK_ADDED 2
#define BMK_REMOVED 3
#define BMK_PAINT 4

#define CFG_TEXT 1
#define CFG_CHOICE 2
#define CFG_INDEX 3
#define CFG_TIME 4
#define CFG_FONT 5
#define CFG_FONTFACE 6
#define CFG_INFO 7
#define CFG_NUMBER 8
#define CFG_ENTEXT 9
#define CFG_PASSWORD 10
#define CFG_IPADDR 11
#define CFG_URL 12
#define CFG_PHONE 13
#define CFG_ACTIONS 14
#define CFG_CUSTOM 30
#define CFG_SUBMENU 31

#define CFG_HIDDEN 128

#define ALIGN_LEFT 1
#define ALIGN_CENTER 2
#define ALIGN_RIGHT 4
#define ALIGN_FIT 8
#define VALIGN_TOP 16
#define VALIGN_MIDDLE 32
#define VALIGN_BOTTOM 64
#define ROTATE 128
#define HYPHENS 256
#define DOTS 512
#define RTLAUTO 1024
#define UNDERLINE 2048
#define STRETCH 4096
#define TILE 8192

#define ARROW_LEFT    1
#define ARROW_RIGHT   2
#define ARROW_UP      3
#define ARROW_DOWN    4
#define SYMBOL_OK     5
#define SYMBOL_PAUSE  6
#define SYMBOL_BULLET 7
#define ARROW_UPDOWN  8

#define IMAGE_BW    1
#define IMAGE_GRAY2 2
#define IMAGE_GRAY4 4
#define IMAGE_GRAY8 8
#define IMAGE_RGB   24

#define ROTATE0    0
#define ROTATE90   1
#define ROTATE270  2
#define ROTATE180  3

#define XMIRROR    4
#define YMIRROR    8

#define DITHER_THRESHOLD 0
#define DITHER_PATTERN 1
#define DITHER_DIFFUSION 2

#define MP_STOPPED 0
#define MP_REQUEST_FOR_PLAY 1
#define MP_PLAYING 2
#define MP_PAUSED 3
#define MP_PREVTRACK 4
#define MP_NEXTTRACK 5

#define MP_ONCE 0
#define MP_CONTINUOUS 1
#define MP_RANDOM 2

#define FTYPE_UNKNOWN 0
#define FTYPE_BOOK 1
#define FTYPE_PICTURE 2
#define FTYPE_MUSIC 3
#define FTYPE_APPLICATION 4
#define FTYPE_WEBLINK 5
#define FTYPE_FOLDER 255

#define OB_ADDTOLAST  0x01
#define OB_WITHRETURN 0x02
#define OB_SOFTUPDATE 0x10

#define NET_BLUETOOTH  0x0001
#define NET_WIFI       0x0002
#define NET_BTREADY    0x0100
#define NET_WIFIREADY  0x0200
#define NET_CONNECTED  0x0f00

#define CONN_GPRS 1
#define CONN_WIFI 2

#define BLUETOOTH_OFF 0
#define BLUETOOTH_HIDDEN 1
#define BLUETOOTH_VISIBLE 2

#define NET_OK		0
#define NET_CONNECT	1
#define NET_TRANSFER	2

#define NET_FAIL	-11
#define NET_ABORTED	-12
#define NET_EINIT	-13
#define NET_EWRONGID	-14
#define NET_ENETWORK	-15
#define NET_EFILE	-16
#define NET_EPIPE	-17
#define NET_ETHREAD	-18
#define NET_EPROTO	-19
#define NET_EURL	-20
#define NET_ERESOLVE	-21
#define NET_ECONNECT	-22
#define NET_EACCESS	-23
#define NET_ENOTFOUND	-24
#define NET_EPARTIAL	-25
#define NET_EBROKEN	-26
#define NET_ETIMEOUT	-27
#define NET_ESERVER	-28
#define NET_EHTTP	-29
#define NET_EHARDWARE	-30
#define NET_ENOTCONF	-31
#define NET_EBADCONF	-32
#define NET_ENODEVICE	-33
#define NET_EPPP	-34
#define NET_EDISABLED	-35

#define GSENSOR_OFF 0
#define GSENSOR_ON 1
#define GSENSOR_INTR 2

#define VN_NOPATH   0x01
#define VN_NOESCAPE 0x02
#define VN_ABSOLUTE 0x04
#define VN_RELATIVE 0x08

typedef struct irect_s {

	short x;
	short y;
	short w;
	short h;
	int flags;

} irect;

typedef struct ibitmap_s {

	unsigned short width;
	unsigned short height;
	unsigned short depth;
	unsigned short scanline;
	unsigned char data[];

} ibitmap;

typedef int  (*iv_handler)(int type, int par1, int par2);
typedef void (*iv_timerproc)();

typedef void (*iv_menuhandler)(int index);
typedef void (*iv_keyboardhandler)(char *text);
typedef void (*iv_dialoghandler)(int button);
typedef void (*iv_timeedithandler)(long newtime);
typedef void (*iv_fontselecthandler)(char *fontr, char *fontb, char *fonti, char *fontbi);
typedef void (*iv_dirselecthandler)(char *path);
typedef void (*iv_confighandler)();
typedef void (*iv_itemchangehandler)(char *name);
typedef void (*iv_pageselecthandler)(int page);
typedef void (*iv_bmkhandler)(int action, int page, long long position);
typedef void (*iv_tochandler)(long long position);
typedef void (*iv_itempaint)(int x, int y, int index, int selected);
typedef int  (*iv_listhandler)(int action, int x, int y, int idx, int state);
typedef void (*iv_rotatehandler)(int direction);
typedef int  (*iv_turnproc)(int direction);
typedef int  (*iv_recurser)(char *path, int type, void *data);

typedef int  (*iv_hashenumproc)(char *name, void *value, void *userdata);
typedef int  (*iv_hashcmpproc)(char *name1, void *value1, char *name2, void *value2);
typedef void * (*iv_hashaddproc)(void *data);
typedef void (*iv_hashdelproc)(void *data);

typedef struct ihash_item_s {

	char *name;
	void *value;
	struct ihash_item_s *next;

} ihash_item;

typedef struct ihash_s {

	int prime;
	int count;
	iv_hashaddproc addproc;
	iv_hashdelproc delproc;
	struct ihash_item_s **items;

} ihash;

typedef struct imenu_s {

	short type;
	short index;
	char *text;
	struct imenu_s *submenu;

} imenu;

typedef struct icanvas_s {

	int width;
	int height;
	int scanline;
	int depth;
	int clipx1, clipx2;
	int clipy1, clipy2;
	unsigned char *addr;

} icanvas;

typedef struct ifont_s {

	char *name;
	char *family;
	int size;
	unsigned char aa;
	unsigned char isbold;
	unsigned char isitalic;
	unsigned char _r1;
	unsigned short charset;
	unsigned short _r2;
	int color;
	int height;
	int linespacing;
	int baseline;
	void *fdata;

} ifont;

typedef struct ievent_s {

	iv_handler hproc;
	unsigned short type;
	unsigned short _reserved;
	unsigned short par1;
	unsigned short par2;

} ievent;

typedef struct iconfig_s {

	char *filename;
	ihash *hash;
	ihash *vhash;
	int changed;

} iconfig;

typedef struct iconfigedit_s {

	int type;
	const ibitmap *icon;
	char *text;
	char *hint;
	char *name;
	char *deflt;
	char **variants;
	struct iconfigedit_s *submenu;

} iconfigedit;

typedef struct oldconfigedit_s {

	char *text;
	char *name;
	int type;
	char *deflt;
	char **variants;

} oldconfigedit;

typedef struct tocentry_s {

	int level;
	int page;
	long long position;
	char *text;

} tocentry;

typedef struct itimer_s {

	iv_timerproc tp;
	int weak;
	long long extime;
	char name[16];

} itimer;

typedef struct bookinfo_s {

	int type;
	char *typedesc;
	char *path;
	char *filename;
	char *title;
	char *author;
	char *series;
	char *genre[10];
	ibitmap *icon;
	int year;
	long size;
	time_t ctime;

} bookinfo;

typedef struct iv_filetype_s {

	char *extension;
	char *description;
	int type;
	char *program;
	ibitmap *icon;

} iv_filetype;

typedef struct iv_template_s {

	int width;
	int height;
	ibitmap *background;
	ibitmap *bg_folder;
	ibitmap *bg_folder_a;
	ibitmap *bg_file;
	ibitmap *bg_file_a;
	irect iconpos;
	irect mediaiconpos;
	irect line1pos;
	irect line2pos;
	irect line3pos;
	ifont *line1font;
	ifont *line2font;
	ifont *line3font;

} iv_template;

typedef struct iv_wlist_s {

	char *word;
	short x1;
	short y1;
	short x2;
	short y2;

} iv_wlist;


typedef struct iv_netinfo_s {

	int connected;
	char name[64];
	char device[64];
	char security[64];
	char prefix[64];
	int index;
	int atime;
	int speed;
	int reserved_0e;
	unsigned long bytes_in;
	unsigned long bytes_out;
	unsigned long packets_in;
	unsigned long packets_out;

} iv_netinfo;

typedef struct iv_sessioninfo_s {
	
	char *url;
	char *ctype;
	long response;
	int length;
	int progress;

} iv_sessioninfo;

typedef iv_wlist* (*pointer_to_word_hand_t)(int x, int y, int forward);

void OpenScreen();
void OpenScreenExt();
void InkViewMain(iv_handler h);
void CloseApp();

// Screen information

int ScreenWidth();
int ScreenHeight();

// Orientation and g-sensor
// Set screen orientation: 0=portrait, 1=landscape 90, 2=landscape 270, 3=portrait 180
// For global settings: -1=auto (g-sensor)

void SetOrientation(int n);
int GetOrientation();
void SetGlobalOrientation(int n);
int GetGlobalOrientation();
int QueryGSensor();
void SetGSensor(int mode);
int ReadGSensor(int *x, int *y, int *z);
void CalibrateGSensor();

// Graphic functions. Color=0x00RRGGBB

void ClearScreen();
void SetClip(int x, int y, int w, int h);
void DrawPixel(int x, int y, int color);
void DrawLine(int x1, int y1, int x2, int y2,int color);
void DrawRect(int x, int y, int w, int h, int color);
void FillArea(int x, int y, int w, int h, int color);
void InvertArea(int x, int y, int w, int h);
void InvertAreaBW(int x, int y, int w, int h);
void DimArea(int x, int y, int w, int h, int color);
void DrawSelection(int x, int y, int w, int h, int color);
void DitherArea(int x, int y, int w, int h, int levels, int method);
void Stretch(const unsigned char *src, int format, int sw, int sh, int scanline, int dx, int dy, int dw, int dh, int rotate);
void SetCanvas(icanvas *c);
icanvas *GetCanvas();
void Repaint();

// Bitmap functions

ibitmap *LoadBitmap(const char *filename);
int SaveBitmap(const char *filename, ibitmap *bm);
ibitmap *BitmapFromScreen(int x, int y, int w, int h);
ibitmap *BitmapFromScreenR(int x, int y, int w, int h, int rotate);
ibitmap *NewBitmap(int w, int h);
ibitmap *LoadJPEG(const char *path, int w, int h, int br, int co, int proportional);
void DrawBitmap(int x, int y, const ibitmap *b);
void DrawBitmapArea(int x, int y, const ibitmap *b, int bx, int by, int bw, int bh);
void DrawBitmapRect(int x, int y, int w, int h, ibitmap *b, int flags);
void DrawBitmapRect2(irect *rect, ibitmap *b);
void StretchBitmap(int x, int y, int w, int h, const ibitmap *src, int flags);
void TileBitmap(int x, int y, int w, int h, const ibitmap *src);
ibitmap *CopyBitmap(const ibitmap *bm);
void MirrorBitmap(ibitmap *bm, int m);

// Text functions

char **EnumFonts();
ifont *OpenFont(const char *name, int size, int aa);
void CloseFont(ifont *f);
void SetFont(ifont *font, int color);
void DrawString(int x, int y, const char *s);
void DrawStringR(int x, int y, const char *s);
int TextRectHeight(int width, const char *s, int flags);
char *DrawTextRect(int x, int y, int w, int h, const char *s, int flags);
char *DrawTextRect2(irect *rect, const char *s);
int CharWidth(unsigned  short c);
int StringWidth(const char *s);
int DrawSymbol(int x, int y, int symbol);
void RegisterFontList(ifont **fontlist, int count);
void SetTextStrength(int n);

// Screen update functions

void FullUpdate();
void SoftUpdate();
void PartialUpdate(int x, int y, int w, int h);
void PartialUpdateBW(int x, int y, int w, int h);
void DynamicUpdateBW(int x, int y, int w, int h);
void FineUpdate();
void DynamicUpdate();
int FineUpdateSupported();

// Event handling functions

iv_handler SetEventHandler(iv_handler hproc);
iv_handler SetEventHandlerEx(iv_handler hproc);
iv_handler GetEventHandler();
void SendEvent(iv_handler hproc, int type, int par1, int par2);
void FlushEvents();

// Timer functions

void SetHardTimer(const char *name, iv_timerproc tproc, int ms);
void SetWeakTimer(const char *name, iv_timerproc tproc, int ms);
long long QueryTimer(iv_timerproc tp);
void ClearTimer(iv_timerproc tproc);

// UI functions

void OpenMenu(imenu *menu, int pos, int x, int y, iv_menuhandler hproc);
void OpenMenu3x3(const ibitmap *mbitmap, const char *strings[9], iv_menuhandler hproc);
void OpenList(const char *title, const ibitmap *background, int itemw, int itemh, int itemcount, int cpos, iv_listhandler hproc);
void OpenDummyList(const char *title, const ibitmap *background, char *text, iv_listhandler hproc);
char **EnumKeyboards();
void LoadKeyboard(const char *kbdlang);
void OpenKeyboard(const char *title, char *buffer, int maxlen, int flags, iv_keyboardhandler hproc);
void OpenCustomKeyboard(const char *filename, const char *title, char *buffer, int maxlen, int flags, iv_keyboardhandler hproc);
void CloseKeyboard();
void OpenPageSelector(iv_pageselecthandler hproc);
void OpenTimeEdit(const char *title, int x, int y, long intime, iv_timeedithandler hproc);
void OpenDirectorySelector(const char *title, char *buf, int len, iv_dirselecthandler hproc);
void OpenFontSelector(const char *title, const char *font, int with_size, iv_fontselecthandler hproc);
void OpenBookmarks(int page, long long position, int *bmklist, long long *poslist,
		int *bmkcount, int maxbmks, iv_bmkhandler hproc);
void SwitchBookmark(int page, long long position, int *bmklist, long long *poslist,
		int *bmkcount, int maxbmks, iv_bmkhandler hproc);
void OpenContents(tocentry *toc, int count, long long position, iv_tochandler hproc);
void OpenRotateBox(iv_rotatehandler hproc);
void Message(int icon, const char *title, const char *text, int timeout);
void Dialog(int icon, const char *title, const char *text, const char *button1, const char *button2, iv_dialoghandler hproc);
void CloseDialog();
void OpenProgressbar(int icon, const char *title, const char *text, int percent, iv_dialoghandler hproc);
int  UpdateProgressbar(const char *text, int percent);
void CloseProgressbar();
void ShowHourglass();
void ShowHourglassAt(int x, int y);
void HideHourglass();
void DisableExitHourglass();
void SetPanelType(int type);
int  DrawPanel(const ibitmap *icon, const char *text, const char *title, int percent);
int  DrawTabs(const ibitmap *icon, int current, int total);
int  PanelHeight();
void SetKeyboardRate(int t1, int t2);

// Configuration functions

iconfig * GetGlobalConfig();
iconfig * OpenConfig(const char *path, iconfigedit *ce);
int SaveConfig(iconfig *cfg);
void CloseConfig(iconfig *cfg);
int ReadInt(iconfig *cfg, const char *name, int deflt);
char *ReadString(iconfig *cfg, const char *name, const char *deflt);
char *ReadSecret(iconfig *cfg, const char *name, const char *deflt);
void WriteInt(iconfig *cfg, const char *name, int value);
void WriteString(iconfig *cfg, const char *name, const char *value);
void WriteSecret(iconfig *cfg, const char *name, const char *value);
void WriteIntVolatile(iconfig *cfg, const char *name, int value);
void WriteStringVolatile(iconfig *cfg, const char *name, const char *value);
void DeleteInt(iconfig *cfg, const char *name);
void DeleteString(iconfig *cfg, const char *name);
void OpenConfigEditor(const char *header, iconfig *cfg, iconfigedit *ce, iv_confighandler hproc, iv_itemchangehandler cproc);
void OpenConfigSubmenuExt(const char *title, iconfigedit *ice, int pos);
void OpenConfigSubmenu(const char *title, iconfigedit *ice);
void UpdateCurrentConfigPage();
void UpdateConfigPage(const char *title, iconfigedit *ice);
void CloseConfigLevel();
void GetKeyMapping(char *act0[], char *act1[]);
unsigned long QueryDeviceButtons();

// String hash functions

ihash * hash_new(int prime);
void hash_add(ihash *h, const char *name, const char *value);
void hash_delete(ihash *h, const char *name);
char *hash_find(ihash *h, const char *name);

// Object hash functions

ihash * vhash_new(int prime, iv_hashaddproc addproc, iv_hashdelproc delproc);
void vhash_add(ihash *h, const char *name, const void *value);
void vhash_delete(ihash *h, const char *name);
void *vhash_find(ihash *h, const char *name);

// Common hash functions

void hash_clear(ihash *h);
void hash_destroy(ihash *h);
int  hash_count(ihash *h);
void hash_enumerate(ihash *h, iv_hashcmpproc cmpproc, iv_hashenumproc enumproc, void *userdata);

// filesystem functions

int iv_stat(const char *name, struct stat *st);
int iv_access(const char *pathname, int mode);
FILE *iv_fopen(const char *name, const char *mode);
int iv_fread(void *buffer, int size, int count, FILE *f);
int iv_fwrite(const void *buffer, int size, int count, FILE *f);
int iv_fseek(FILE *f, long offset, int whence);
long iv_ftell(FILE *f); 
int iv_fclose(FILE *f);
int iv_fgetc(FILE *f);
char *iv_fgets(char *string, int n, FILE *f);
int iv_mkdir(const char *pathname, mode_t mode);
void iv_buildpath(const char *filename);
DIR *iv_opendir(const char *dirname);
struct dirent *iv_readdir(DIR *dir);
int iv_closedir(DIR *dir);
int iv_unlink(const char *name);
int iv_rmdir(const char *name);
int iv_truncate(const char *name, int length);
int iv_rename(const char *oldname, const char *newname);
void iv_preload(const char *name, int count);
void iv_sync();
int iv_validate_name(const char *s, int flags);

// ipc functions

long iv_ipc_request(long type, long attr, unsigned char *data, int inlen, int outlen);
long iv_ipc_cmd(long type, long param);

// Language functions

char ** EnumLanguages();
void LoadLanguage(const char *lang);
void AddTranslation(const char *label, const char *trans);
char *GetLangText(const char *s);
char *GetLangTextF(const char *s, ...);
void SetRTLBook(int rtl);
int IsRTL();  // depends only on the system language
int IsBookRTL();	// can be overwritten by application

#define T(x) GetLangText(#x)
#define TF(x...) GetLangTextF(x)

// User profile functions

char **EnumProfiles();
int GetProfileType(const char *name);
int CreateProfile(const char *name, int type);
int RenameProfile(const char *oldname, const char *newname);
int DeleteProfile(const char *name);
char *GetCurrentProfile();
void SetCurrentProfile(const char *name, int flags);
void OpenProfileSelector();

// Theme functions

char ** EnumThemes();
void OpenTheme(const char *path);
ibitmap *GetResource(const char *name, const ibitmap *deflt);
int GetThemeInt(const char *name, int deflt);
char *GetThemeString(const char *name, const char *deflt);
ifont *GetThemeFont(const char *name, const char *deflt);
void GetThemeRect(const char *name, irect *rect, int x, int y, int w, int h, int flags);

// Book functions

iv_filetype *GetSupportedFileTypes();
bookinfo *GetBookInfo(const char *name);
ibitmap *GetBookCover(const char *name, int width, int height);
char *GetAssociatedFile(const char *name, int index);
char *CheckAssociatedFile(const char *name, int index);
void SetReadMarker(const char *name, int isread);
iv_filetype *FileType(const char *path);
void SetFileHandler(const char *path, const char *handler);
char *GetFileHandler(const char *path);
void OpenBook(const char *path, const char *position, int flags);
void BookReady(const char *path);
char **GetLastOpen();
void AddLastOpen(const char *path);
void OpenLastBooks();

// Media functions

void OpenPlayer();
void PlayFile(const char *filename);
void LoadPlaylist(char **pl);
char **GetPlaylist();
void PlayTrack(int n);
void PreviousTrack();
void NextTrack();
int GetCurrentTrack();
int GetTrackSize();
void SetTrackPosition(int pos);
int GetTrackPosition();
void SetPlayerState(int state);
int GetPlayerState();
void SetPlayerMode(int mode);
int GetPlayerMode();
void TogglePlaying();
void SetVolume(int n);
int GetVolume();
void SetEqualizer(int *eq);
void GetEqualizer(int *eq);

// Notepad functions

char **EnumNotepads();
void OpenNotepad(const char *name);
void CreateNote(const char *filename, const char *title, long long position);
void CreateNoteFromImages(const char *filename, const char *title, long long position, ibitmap *img1, ibitmap *img2);
void CreateNoteFromPage(const char *filename, const char *title, long long position);
void CreateEmptyNote(const char *text);
void OpenNotesMenu(const char *filename, const char *title, long long position);

// Dictionary functions

char **EnumDictionaries();
int OpenDictionary(const char *name);
void CloseDictionary();
int LookupWord(const char *what, char **word, char **trans);
int LookupWordExact(const char *what, char **word, char **trans);
int LookupPrevious(char **word, char **trans);
int LookupNext(char **word, char **trans);
void OpenDictionaryView(iv_wlist *wordlist, const char *dicname);
void OpenControlledDictionaryView(pointer_to_word_hand_t pointer_handler, iv_wlist *wordlist, const char *dicname);

// Text reflow API

void iv_reflow_start(int x, int y, int w, int h, int scale);
void iv_reflow_bt();
void iv_reflow_et();
void iv_reflow_div();
void iv_reflow_addchar(int code, int x, int y, int w, int h);
void iv_reflow_addimage(int x, int y, int w, int h, int flags);
int iv_reflow_subpages();
void iv_reflow_render(int spnum);
int iv_reflow_getchar(int *x, int *y);
int iv_reflow_getimage(int *x, int *y, int *scale);
int iv_reflow_words();
char *iv_reflow_getword(int n, int *spnum, int *x, int *y, int *w, int *h);
void iv_reflow_clear();

// Additional functions
void iv_sleepmode(int on);
int GetSleepmode();
int GetBatteryPower();
int GetTemperature();
int IsCharging();
int IsUSBconnected();
int IsSDinserted();
int IsPlayingMP3();
int IsKeyPressed(int key);
char *GetDeviceModel();
char *GetHardwareType();
char *GetSoftwareVersion();
int GetHardwareDepth();
char *GetSerialNumber();
char *GetWaveformFilename();
char *GetDeviceKey();
unsigned char *GetDeviceFingerprint();
char *CurrentDateStr();
char *DateStr(time_t t);
int GoSleep(int ms, int deep);
void SetAutoPowerOff(int en);
void PowerOff();
int SafeMode();
void OpenMainMenu();
int WriteStartupLogo(const ibitmap *bm);
int PageSnapshot();
int RestoreStartupLogo();
int QueryTouchpanel();
void CalibrateTouchpanel();
void OpenCalendar();

int QueryNetwork();
char *GetHwAddress();
int GetBluetoothMode();
int SetBluetoothMode(int mode, int flags);
char **EnumBTdevices();
void OpenBTdevicesMenu(char *title, int x, int y, iv_itemchangehandler hproc);
int BtSendFiles(char *mac, char **files);
char **EnumWirelessNetworks();
char **EnumConnections();
int GetBTservice(const char *mac, const char *service);
int NetConnect(const char *name);
int NetDisconnect();
void OpenNetworkInfo();
void *QuickDownload(const char *url, int *retsize, int timeout);
int NewSession();
void CloseSession(int id);
void SetUserAgent(int id, const char *ua);
void SetProxy(int id, const char *host, int port, const char *user, const char *pass);
int Download(int id, const char *url, const char *postdata, FILE **fp, int timeout);
int DownloadTo(int id, const char *url, const char *postdata, const char *filename, int timeout);
int GetSessionStatus(int id);
char * GetHeader(int id, const char *name);
iv_sessioninfo *GetSessionInfo(int id);
void PauseTransfer(int id);
void ResumeTransfer(int id);
void AbortTransfer(int id);
char *NetError(int e);
void NetErrorMessage(int e);


int iv_strcmp(const char *s1, const char *s2);
int iv_strncmp(const char *s1, const char *s2, size_t n);
int iv_strcasecmp(const char *s1, const char *s2);
int iv_strncasecmp(const char *s1, const char *s2, size_t n);
int escape(const char *val, char *buf, int size);
int unescape(const char *val, char *buf, int size);
void trim_right(char *s);
unsigned short *get_encoding_table(const char *enc);
int convert_to_utf(const char *src, char *dest, int destsize, const char *enc);
int utf2ucs(const char *s, unsigned short *us, int maxlen);
int utf2ucs4(const char *s, unsigned int *us, int maxlen);
int ucs2utf(const unsigned short *us, char *s, int maxlen);
int utfcasecmp(const char *sa, const char *sb);
int utfncasecmp(const char *sa, const char *sb, int n);
char *utfcasestr(const char *sa, const char *sb);
void utf_toupper(char *s);
void utf_tolower(char *s);
void md5sum(const unsigned char *data, int len, unsigned char *digest);
int base64_encode(const unsigned char *in, int len, char *out);
int base64_decode(const char *in, unsigned char *out, int len);
int copy_file(const char *src, const char *dst);
int move_file(const char *src, const char *dst);
int copy_file_with_af(const char *src, const char *dst);
int move_file_with_af(const char *src, const char *dst);
int unlink_file_with_af(const char *name);
int recurse_action(const char *path, iv_recurser proc, void *data, int creative, int this_too);

// dialog show on the screen
int GetDialogShow(); // 1 - dialog showing, 0 - dialog hidden.

#ifdef __cplusplus
}
#endif

#endif


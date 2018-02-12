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
#include <grp.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/sysinfo.h>
#include <signal.h>
#include <errno.h>
#include <zlib.h>
#include <ft2build.h>
#include <pthread.h>
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
#define SECAPP_UID 102
#define SECAPP_GID 102

#if !(defined(IVSAPP) || defined(EMULATOR))
#if !defined(__CYGWIN__) && defined(__i386__)
#  define DIRPREFIX "/usr/local/pocketbook"
#error lmnlk
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
#define SECUREDIR DIRPREFIX "/mnt/secure"
#else
#define FLASHDIR "./system/mnt/ext1"
#define SDCARDDIR "./system/mnt/ext2"
#define USBDIR "./system/mnt/ext3"
#define SYSTEMDATA "./system"
#define USERDATA SYSTEMDATA
#define USERDATA2 SDCARDDIR "/system"
#define TEMPDIR "./system/tmp"
#define SECUREDIR "./system/mnt/secure"
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
#define CUSTOMRESOURCEPATH USERDATA "/resources"
#define GLOBALCONFIGFILE CONFIGPATH "/global.cfg"
#define NETWORKCONFIGFILE CONFIGPATH "/network.cfg"
#define TSCALDATA CONFIGPATH "/tsc.dat"
#define TSCALDATA2 TEMPDIR "/tsc.dat"
#define SYSTEMLANGPATH SYSTEMDATA "/language"
#define USERLANGPATH USERDATA "/language"
#define SYSTEMKBDPATH SYSTEMDATA "/language/keyboard"
#define USERKBDPATH USERDATA "/language/keyboard"
#define SYSTEMDICTPATH SYSTEMDATA "/dictionaries"
#define SECUREDICTPATH SECUREDIR "/dictionaries"
#define USERDICTPATH1 USERDATA "/dictionaries"
#define USERDICTPATH2 USERDATA2 "/dictionaries"
#define SYSTEMLOGOPATH SYSTEMDATA "/logo"
#define USERLOGOPATH USERDATA "/logo"
#define NOTESPATH FLASHDIR "/notes"
#define NOTESPATH2 SDCARDDIR "/notes"
#define GAMEPATH FLASHDIR "/applications"
#define OLDGAMEPATH FLASHDIR "/games"
#define USERAPPDIR USERDATA "/bin"
#define CACHEPATH USERDATA "/cache"
#define BACKUPDIR SDCARDDIR "/backup"
#define USERBOOKSHELF USERDATA "/bin/bookshelf.app"
#define SYSTEMBOOKSHELF SYSTEMDATA "/bin/bookshelf.app"
#define USERMPD USERDATA "/bin/mpd.app"
#define SYSTEMMPD SYSTEMDATA "/bin/mpd.app"
#define OBREEYSYNC_APP_PATH SYSTEMDATA "/bin/obreeysync.app"
#define READER_CONTROLLER_APP_PATH SYSTEMDATA "/bin/reader_controller.app"
#define DB_SERVER_APP_PATH SYSTEMDATA "/bin/db-server.app"

#define READER_APP_PATH SYSTEMDATA "/bin/eink-reader.app"
#define OBREEYSYNC_V2_APP_PATH SYSTEMDATA "/bin/universal_sync.app"
#define OBREEYSOCIAL_APP_PATH SYSTEMDATA "/bin/obreeysocial.app"
#define USAGE_STAT_APP_PATH SYSTEMDATA "/bin/usage_stat.app"
#define DROPBOX_APP_PATH SYSTEMDATA "/bin/dropbox.app"
#define CONTROL_PANEL_APP_PATH SYSTEMDATA "/bin/control_panel_mgr.app"
#define USEREXPLORER USERDATA "/bin/explorer.app"
#define SYSTEMEXPLORER SYSTEMDATA "/bin/explorer.app"
#define USERTASKMGR USERDATA "/bin/taskmgr.app"
#define SYSTEMTASKMGR SYSTEMDATA "/bin/taskmgr.app"
#define STATECLEANER SYSTEMDATA "/bin/cleanstate.sh"
#define BACKUPSCRIPT SYSTEMDATA "/bin/backup.sh"
#define RESTORESCRIPT SYSTEMDATA "/bin/restore.sh"
#define NETAGENT SYSTEMDATA "/bin/netagent"
#define BOOKLANDAPP SYSTEMDATA "/bin/bookland.app"
#define USERMPLAYER USERDATA "/bin/mplayer.so"
#define USERBOOKINFO USERDATA "/bin/bookinfo.so"
#define POCKETBOOKSIG USERDATA "/.pocketbook"
#define USERSCANNER USERDATA "/bin/scanner.app"
#define SYSTEMSCANNER SYSTEMDATA "/bin/scanner.app"
#define FRONTLIGHT_APP	"front-light.app"
#define USERFRONTLIGHT USERDATA "/bin/" FRONTLIGHT_APP
#define SYSTEMSFRONTLIGHT SYSTEMDATA "/bin/" FRONTLIGHT_APP
#define LASTOPENBOOKS STATEPATH "/lastopen.txt"
#define CURRENTBOOK_SAVE STATEPATH "/current"
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
#define SWUPDATESTATUS SECUREDIR "/swupdate.db"
#define TASKINFOPATH "/var/run/task"
#define DOWNLOADFOLDER FLASHDIR "/Downloads"
#define CERTIFICATESFOLDER USERDATA "/Certificates"
#define PROXYCONFIGFILE "/var/etc/proxy"
#define AUTO_CONNECT_APP SYSTEMDATA "/bin/auto_connect.app"
#define SILENT_CONNECT_CFG CONFIGPATH"/silent_connection.cfg"

#define SOCIAL_DIRECTORY CONFIGPATH "/readrate"       // All readrate files should be stored in the directory
#define SOCIAL_PENDING_ACTIONS_FILE SOCIAL_DIRECTORY"/pending_action.dat"
#define SOCIALCONFIG SOCIAL_DIRECTORY"/social.cfg"

#define UNIVERSAL_SYNC_DIRECTORY CONFIGPATH "/universal_sync"       // All sync files should be stored in the directory
#define UNIVERSAL_SYNC_CONFIG UNIVERSAL_SYNC_DIRECTORY "/sync.cfg"

#define DROPBOX_DIRECTORY CONFIGPATH "/dropbox"
#define DROPBOX_CONFIG DROPBOX_DIRECTORY "/dropbox.cfg"

#define PBCLOUD_CONFIG_FILE CONFIGPATH "/pbcloud.cfg"

#define DEMO_APP_PATH SYSTEMDATA "/bin/picviewer.app"
#define DEMO_IMAGES_PATH USERDATA "/demo"

#define CHECKUPDATE_INFO_PATH "/tmp/newsw.info"

#define DEVICE_VARIABLE_CFG SECUREDIR "/device.cfg"

#define LOGO_APP_PATH SYSTEMDATA "/bin/power_off_logo.app"

//#define DEFAULTFONT "LiberationSans"
//#define DEFAULTFONTB "LiberationSans-Bold"
//#define DEFAULTFONTI "LiberationSans-Italic"
//#define DEFAULTFONTBI "LiberationSans-BoldItalic"
//#define DEFAULTFONTM "LiberationMono"
extern const char * OBREEY_BSCONFIG_PARAMETR;
extern const char * OBREEY_STORE_BSCONFIG_PARAM;
extern const char * OBREEY_SOCIAL_COOKIES_PATH;
#define PROFILE_LOCAL  0x01
#define PROFILE_SDCARD 0x02

#define SYSTEMDEPTH 8

#define MAXMSGSIZE 65520

#define MSG_REQUEST  0x7fffffff
#define MSG_XREQUEST 0x7c000000
#define MSG_OK 1
#define MSG_ERROR 0

#define MSG_FORMAT            0x101
#define MSG_SETTIME           0x102
#define MSG_SETPROFILE        0x103
#define MSG_PWENCRYPT         0x104
#define MSG_PWDECRYPT         0x105
#define MSG_RESTART           0x106
#define MSG_REMOUNTFS         0x107
#define MSG_WRITELOGO         0x108
#define MSG_RESTORELOGO       0x109
#define MSG_SUSPEND           0x10a
#define MSG_IOC_ENCRYPT       0x10b
#define MSG_IOC_DECRYPT       0x10c
#define MSG_REG_CHECK         0x10d
#define MSG_REG_WRITE         0x10e
#define MSG_GETSERIAL         0x10f
#define MSG_REBOOT	      0x110
#define MSG_REBOOT_AND_UPDATE 0x111
#define MSG_TIMESTAMP         0x112
#define MSG_UPDATESTATUS      0x113
#define MSG_DISABLE_GSENSOR   0x114
#define MSG_ENABLE_GSENSOR    0x115
#define MSG_CONFIG_CHANGED    0x116
#define MSG_SET_LED           0x117
#define MSG_ENCRYPT_MEM       0x118
#define MSG_DECRYPT_MEM       0x119
#define MSG_GETDEVICEID       0x11a
#define MSG_SETFRONTLIGHT     0x11b
#define MSG_ACTUALIZEFRONTLIGHT 0x11c
#define MSG_UPDATE_SERVICE_STATUSES    0x11d
#define MSG_FACTORY_RESET	0x11e
#define MSG_SETTIME_FROM_NTP 0x11f
#define MSG_GET_IS_TIME_MONOTONIC_AFTER_LAST_NTP_SYNC 0x120
#define MSG_GET_PARTNER_ID 0x121
#define MSG_UPDATE_PARTNER_ID 0x122
#define MSG_BAN_SUSPEND       0x123
#define MSG_BACKUP	0x124
#define MSG_RESTORE	0x125

#define MSG_FBINFO            0x201
#define MSG_ORIENTATION       0x202
#define MSG_UPDPARTIAL        0x203
#define MSG_UPDDYNAMIC        0x204
#define MSG_UPDFULL           0x205
#define MSG_EINKPM            0x206
#define MSG_EINKTEMP          0x207

#define MSG_TASK_REGISTER       0x501
#define MSG_TASK_NEWSUBTASK     0x502
#define MSG_TASK_SWITCHSUBTASK  0x503
#define MSG_TASK_ENDSUBTASK     0x504
#define MSG_TASK_SETPARAMETERS  0x505
#define MSG_TASK_SETSUBTASKINFO 0x506
#define MSG_TASK_FOREGROUND     0x507
#define MSG_TASK_BACKGROUND     0x508
#define MSG_TASK_CLOSE          0x509
#define MSG_TASK_LIST           0x50a
#define MSG_TASK_PREVIOUS       0x50b
#define MSG_TASK_INFO           0x50c
#define MSG_TASK_SENDEVENT      0x50d
#define MSG_TASK_SENDREQUEST    0x50e
#define MSG_TASK_ADDREQLISTENER 0x510
#define MSG_TASK_DELREQLISTENER 0x511
#define MSG_TASK_GLOBALREQUEST  0x512
#define MSG_TASK_SENDEVENTSYNC  0x513
#define MSG_TASK_INITIALIZED	0x514
#define MSG_TASK_PREVIOUS_INSTACK   0x515
#define MSG_TASK_COPY_ACTIVE_FB	0x516
#define MSG_TASK_SEND_REQUEST_NOWAIT      0x517


#define MSG_START_SERVICES	0x600
#define MSG_LAST_OPEN_OPENED	0x601

#define MSG_DEVICEKEY         0xad0be01
#define MSG_RESETKEY          0xad0be02

#define EVT_INIT 21
#define EVT_EXIT 22
#define EVT_SHOW 23
#define EVT_HIDE 24
#define EVT_KEYDOWN 25
#define EVT_KEYPRESS 25
#define EVT_KEYUP 26
#define EVT_KEYRELEASE 26
#define EVT_KEYREPEAT 28
#define EVT_POINTERUP 29
#define EVT_POINTERDOWN 30
#define EVT_POINTERMOVE 31
//comes from inkview only after calling AddScrolledArea function
#define EVT_SCROLL 33 //par1 is (irect *) -- scrolled area from wich scrolling was started, par2 is (deltaX (highest word) and deltaY(lowest word))
#define EVT_POINTERLONG 34
#define EVT_POINTERHOLD 35
#define EVT_POINTERDRAG 44 //like EVT_POINTERMOVE, but has non sensitive zone, which smooths finger touch bounce.
#define EVT_POINTERCANCEL 45

#define EVT_ORIENTATION 32
#define EVT_FOCUS 36
#define EVT_UNFOCUS 37
#define EVT_ACTIVATE 38
#define EVT_MTSYNC 39

#define EVT_TOUCHUP   40
#define EVT_TOUCHDOWN 41
#define EVT_TOUCHMOVE 42
#define EVT_REPAINT 43

#define EVT_QN_MOVE    51
#define EVT_QN_RELEASE 52
#define EVT_QN_BORDER  53

#define EVT_SNAPSHOT 71
#define EVT_FSINCOMING 72
#define EVT_FSCHANGED 73

#define EVT_MP_STATECHANGED 81
#define EVT_MP_TRACKCHANGED 82

#define EVT_PREVPAGE 91
#define EVT_NEXTPAGE 92
#define EVT_OPENDIC  93
#define EVT_CONTROL_PANEL_ABOUT_TO_OPEN  94


#define EVT_PANEL_BLUETOOTH_A2DP 118

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
#define EVT_PANEL_TASKLIST 129
#define EVT_PANEL_OBREEY_SYNC 130
#define EVT_PANEL_SETREADINGMODE 131
#define EVT_PANEL_SETREADINGMODE_INVERT 132
#define EVT_PANEL_FRONT_LIGHT 133

#define EVT_GLOBALREQUEST 149
#define EVT_GLOBALACTION  150
#define EVT_FOREGROUND    151
#define EVT_BACKGROUND    152
#define EVT_SUBTASKCLOSE  153
#define EVT_CONFIGCHANGED 154
#define EVT_SAVESTATE     155
#define EVT_OBREEY_CONFIG_CHANGED 156

#define EVT_SDIN          161
#define EVT_SDOUT         162

#define EVT_BT_RXCOMPLETE 171
#define EVT_BT_TXCOMPLETE 172

#define EVT_SYNTH_ENDED 200
#define EVT_DIC_CLOSED	201
#define	EVT_SHOW_KEYBOARD 202

#define EVT_TEXTCLEAR   209
#define EVT_EXT_KB		210
#define EVT_LETTER      211

#define EVT_CALLBACK    212

#define EVT_SCANPROGRESS 213
#define EVT_STOPSCAN     214
#define EVT_STARTSCAN    215
#define EVT_SCANSTOPPED  216
#define EVT_POSTPONE_TIMED_POWEROFF  217
#define EVT_FRAME_ACTIVATED 218
#define EVT_FRAME_DEACTIVATED 219
#define EVT_READ_PROGRESS_CHANGED 220
#define EVT_DUMP_BITMAPS_DEBUG_INFO 221

#define EVT_NET_CONNECTED	256
#define EVT_NET_DISCONNECTED 257
#define EVT_NET_FOUND_NEW_FW 260
#define EVT_SYNTH_POSITION 261

#define ISKEYEVENT(x) ((x)>=25 && (x)<=28)
#define ISPOINTEREVENT(x) (((x)>=29 && (x)<=31) || ((x)>=34 && (x)<=35) || (x)==44 || (x)==39 || (x)==45)
#define ISPANELEVENT(x) ((x)>=119 && (x) <= 132)


#define IV_KEY_POWER  0x01
#define IV_KEY_DELETE 0x08
#define IV_KEY_OK     0x0a
#define IV_KEY_UP     0x11
#define IV_KEY_DOWN   0x12
#define IV_KEY_LEFT   0x13
#define IV_KEY_RIGHT  0x14
#define IV_KEY_MINUS  0x15
#define IV_KEY_PLUS   0x16
#define IV_KEY_MENU   0x17
#define IV_KEY_PREV   0x18
#define IV_KEY_NEXT   0x19
#define IV_KEY_HOME   0x1a
#define IV_KEY_BACK   0x1b
#define IV_KEY_PREV2  0x1c
#define IV_KEY_NEXT2  0x1d
#define IV_KEY_MUSIC  0x1e
#define IV_KEY_COVEROPEN	0x02
#define IV_KEY_COVERCLOSE	0x03
/* added support for EP34 keys */
#define IV_KEY_ZOOMOUT 0x06
#define IV_KEY_ZOOMIN  0x07
#define IV_KEY_MENU_POWER 0x04

/* KEYBOARD STATE KEYS */
#define IV_KEY_SHIFT 0x0E
#define IV_KEY_LANGUAGECHANGE 0x0F
#define IV_KEY_KEYBOARDCLOSE 0x10

#define IV_KEY_0 0x30
#define IV_KEY_1 0x31
#define IV_KEY_2 0x32
#define IV_KEY_3 0x33
#define IV_KEY_4 0x34
#define IV_KEY_5 0x35
#define IV_KEY_6 0x36
#define IV_KEY_7 0x37
#define IV_KEY_8 0x38
#define IV_KEY_9 0x39

#define KEYMAPPING_GLOBAL 0
#define KEYMAPPING_TXT    1
#define KEYMAPPING_PDF    2

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

#define ITEM_TYPEMASK 31
#define ITEM_HIDDEN 128
#define ITEM_OLDMENU 32768
#define ITEM_ALTSTYLE 64

#define KBD_NORMAL 0
#define KBD_ENTEXT 1
#define KBD_PHONE 2
#define KBD_NUMERIC 4
#define KBD_IPADDR 5
#define KBD_FILENAME 6
#define KBD_URL 7
#define KBD_DATE 8
#define KBD_TIME 9
#define KBD_DATETIME 0x0A
#define KBD_HEX 0x0B
#define KBD_HOURS 0x0C

#define KBD_UPPER 0x10
#define KBD_LOWER 0x20
#define KBD_FIRSTUPPER 0x30

#define KBD_PASSWORD  0x100
#define KBD_NOSELECT  0x200
#define KBD_SCREENTOP 0x400
#define KBD_NOHEADER  0x800

#define KBD_NOEVTSHOW                0x1000
#define KBD_SENDKEYBOARDSTATEEVENTS  0x2000
#define KBD_NOTOUCH                  0x4000
#define KBD_PASSEVENTS               0x8000
#define KBD_NOUPDATE_AFTER_CLOSE    0x10000
#define KBD_EN_DEFAULT              0x20000
#define KBD_NOUPDATE_AFTER_OPEN     0x40000
#define KBD_NO_SELFCLOSE_ON_OK      0x80000
#define KBD_CUSTOM_ENTER_KEY       0x100000
#define KBD_MARKED_ENTER_KEY       0x200000
#define KBD_PASSWORD_WIFI          0x400000
#define KBD_NEXT                   0x800000


#define ICON_INFORMATION 1
#define ICON_QUESTION 2
#define ICON_WARNING 3
#define ICON_ERROR 4
#define ICON_WIFI 5

#define DEF_BUTTON1 0
#define DEF_BUTTON2 0x1000
#define DEF_BUTTON3 0x2000
#define NO_DISMISS  0x8000

#define WITH_SIZE   1

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
#define CFG_CHOICE_SPECIAL_FONT 15
#define CFG_DIRECTORY 16
#define CFG_HOURS 17
#define CFG_CHECKBOX 18

#define CFG_SUBMENU_ACTION 29
#define CFG_CUSTOM 30
#define CFG_SUBMENU 31


#define CFG_MASK 127
#define CFG_FLAG_MASK ( ~ CFG_MASK )

#define CFG_HIDDEN 128
#define CFG_READONLY 256
#define CFG_BSCSPEC 512 // special used in bsconfig

#define ALLTASKS       -1
#define MAINTASK       -2
#define OTHERTASKS     -3
#define THISTASK       -4
#define ACTIVETASK     -5
#define MPLAYERTASK    -6
#define DICTIONARYTASK -7
#define ALLSUBTASKS    -1
#define CURRENTSUBTASK -6

#define TASK_HIDDEN          0x0001
#define TASK_COPYLASTFB      0x0002
#define TASK_NOUPDATEONFOCUS 0x0004
#define TASK_SINGLEINSTANCE  0x0008
#define TASK_SPYEVENTS       0x0010
#define TASK_OUTOFSTACK      0x0020
#define TASK_NOFORCEDKILL    0x0040
#define TASK_MAKEACTIVE      0x0080
#define TASK_GROUP1          0x0100
#define TASK_GROUP2          0x0200
#define TASK_OOMPROOF        0x4000
#define TASK_AUTORESTART     0x8000
#define TASK_DONTSENDTASKMSG 0x00010000
#define TASK_DONTCHANGE      0xffffffff

#define TASK_BACKGROUND ((TASK_HIDDEN | TASK_NOUPDATEONFOCUS | TASK_OUTOFSTACK))
#define TASK_NOHANDLER ((TASK_BACKGROUND | TASK_DONTSENDTASKMSG)) //use if program has not main hander. For background processes like services.

#define RQL_ADD		1
#define RQL_REPLACE	2
#define RQL_ADDIFNONE	3
#define RQL_REMOVE	4

#define REQ_KEYLOCK     65
#define REQ_MAINMENU    66
#define REQ_EXIT        67
#define REQ_LASTOPEN    68
#define REQ_PROFILES    69
#define REQ_SCREENSHOT  70
#define REQ_CALC        71
#define REQ_PLAYER      72
#define REQ_PLAYPAUSE   73
#define REQ_VOLUMEUP    74
#define REQ_VOLUMEDOWN  75
#define REQ_NETWORK     76
#define REQ_BTSWITCH    77
#define REQ_DROPCONN    78
#define REQ_TASKMGR     79
#define REQ_SWITCHTASK  80
#define REQ_FLIPTASK    81
#define REQ_KILLTASK    82
#define REQ_POWEROFF    83
#define REQ_OPENBOOK	84
#define REQ_BOOKSTATE	85
#define REQ_BOOKOPENED	86 //copy from fc622-mt
#define REQ_HEADCHNG	87
#define REQ_OPENBOOK2	88
#define REQ_FRONTLIGHT	89
#define REQ_KEYUNLOCK	90
#define REQ_HOURGLASS	91
#define REQ_MESSAGEBOX  92
#define REQ_KEYHARDLOCK 93
#define REQ_PB_CLOUD_NEW_POSITION 94

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
#define TO_UPPER 16384

#define FR_CLOSE               1
#define FR_MOVEUP              2
#define FR_MOVEDOWN            4
#define FR_DICTIONARY 0x04000000
#define FR_NOMARGIN   0x08000000
#define FR_OVERLAP    0x10000000
#define FR_HEADER     0x20000000
#define FR_UPDATE     0x40000000

#define FR_INFO     0x00010000
#define FR_WARNING  0x00020000
#define FR_ERROR    0x00030000
#define FR_DIALOG   0x00040000
#define FR_APP      0x00050000

#define ARROW_LEFT    1
#define ARROW_RIGHT   2
#define ARROW_UP      3
#define ARROW_DOWN    4
#define SYMBOL_OK     5
#define SYMBOL_PAUSE  6
#define SYMBOL_BULLET 7
#define ARROW_UPDOWN  8
#define SYMBOL_MENU	  9

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

#define A2DITHER   16

#define DITHER_THRESHOLD 0
#define DITHER_PATTERN 1
#define DITHER_DIFFUSION 2

#define QN_X       0x01000
#define QN_Y       0x02000
#define QN_XY      0x03000
#define QN_SWAIT   0x04000
#define QN_RWAIT   0x08000
#define QN_CLEANUP 0x10000

typedef enum PB_STATE_e {
    MP_STOPPED = 0,
    MP_REQUEST_FOR_PLAY,
    MP_PLAYING,
    MP_PAUSED,
    MP_PREVTRACK,
    MP_NEXTTRACK,
    MP_TRACK_FINISHED,  // Transitional state when player finish to play track in MP_ONCE mode (after several second player authomatically switches to PB_STOPPED)
    MP_LOAD_FILE_AND_PAUSE,
}PB_STATE;

#define MP_ONCE 0
#define MP_CONTINUOUS 1
#define MP_RANDOM 2

typedef enum PB_TTS_STATE_e {
TTS_STOPPED = 0,
TTS_PLAYING,
TTS_PAUSED
} PB_TTS_STATE;

#define FTYPE_UNKNOWN 0
#define FTYPE_BOOK 1
#define FTYPE_PICTURE 2
#define FTYPE_MUSIC 3
#define FTYPE_APPLICATION 4
#define FTYPE_WEBLINK 5
#define FTYPE_FOLDER 255

#define OB_ADDTOLAST   0x01
#define OB_WITHRETURN  0x02
#define OB_PARAMSFIRST 0x04
#define OB_NONEWTASK   0x08
#define OB_SOFTUPDATE  0x10
#define OB_NOHOURGLASS 0x20

#define NET_BLUETOOTH	0x0001
#define NET_WIFI	0x0002
#define NET_CDMA3G	0x0004
#define NET_BTREADY	0x0100
#define NET_WIFIREADY	0x0200
#define NET_CDMA3GREADY	0x0400
#define NET_CONNECTED	0x0f00

#define CONN_GPRS	1
#define CONN_WIFI	2
#define CONN_CDMA3G	3

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
#define NET_EDHCP	-36
#define NET_EWRONGKEY	-37
#define NET_EAUTH	-38

typedef enum {
	NO = 0,
	WEP,
	WPAEAP,
	WPAPSK,
} WIFI_SECURITY;

typedef enum {
	NET_STATE_UNKNOWN = -1,
	DISCONNECTED = 0,
	CONNECTING,
	CONNECTED,
} NET_STATE;

#define GSENSOR_OFF 0
#define GSENSOR_ON 1
#define GSENSOR_INTR 2

#define VN_NOPATH   0x01
#define VN_NOESCAPE 0x02
#define VN_ABSOLUTE 0x04
#define VN_RELATIVE 0x08

#define A2DP_DISCONNECTED 0
#define A2DP_CONNECTED_TO_SNK 1

/* Curl Flags (CF) */
#define CF_CONFIG_RESUME 1

// Vlad >>>>>>>>>
#define FONT_ACTIVATE_CODE 0x8FA5F3C7
// Vlad <<<<<<<<<

/*
 * TOUCHDRAGDEADZONE = R^2, R - radius of non sensitive touch zone relatively EVT_POINTERDOWN,
 * if dX^2+dY^2 by EVT_POINTERMOVE > TOUCHDRAGDEADZONE, than generate EVT_POINTERDRAG
 */
#define TOUCHDRAGDEADZONE (HWC_LNI633 ? 324 : (HWC_EP7A ? 330 : (HWC_DISPLAY_8INCH_1200 ? 900 : (HWC_DISPLAY_6INCH_758 ? 330 : 200)))) // = R^2

// DEFAULT FONTS
typedef enum
{
    FONT_STD = 0,
    FONT_BOLD = 1,
    FONT_ITALIC = 2,
    FONT_BOLDITALIC = 3,
    FONT_MONO = 4
} FONT_TYPE;

typedef enum
{
	SFLAGS_NONE				= 0x00,
	SFLAGS_LEFT				= 0x01,
	SFLAGS_RIGHT			= 0x02,
	SFLAGS_RIGHT_LEFT		= SFLAGS_RIGHT | SFLAGS_LEFT,							// 0x03
	SFLAGS_UP				= 0x04,
	SFLAGS_UP_LEFT			= SFLAGS_UP | SFLAGS_LEFT,								// 0x05
	SFLAGS_UP_RIGHT			= SFLAGS_UP | SFLAGS_RIGHT,								// 0x06
	SFLAGS_UP_RIGHT_LEFT	= SFLAGS_UP | SFLAGS_RIGHT | SFLAGS_LEFT,				// 0x07
	SFLAGS_DOWN				= 8,
	SFLAGS_DOWN_LEFT		= SFLAGS_DOWN | SFLAGS_LEFT,							// 0x09
	SFLAGS_DOWN_RIGHT		= SFLAGS_DOWN | SFLAGS_RIGHT,							// 0x0a
	SFLAGS_DOWN_RIGHT_LEFT	= SFLAGS_DOWN | SFLAGS_RIGHT | SFLAGS_LEFT,				// 0x0b
	SFLAGS_DOWN_UP			= SFLAGS_DOWN | SFLAGS_UP,								// 0x0c
	SFLAGS_DOWN_UP_LEFT		= SFLAGS_DOWN | SFLAGS_UP | SFLAGS_LEFT,				// 0x0d
	SFLAGS_DOWN_UP_RIGHT	= SFLAGS_DOWN | SFLAGS_UP | SFLAGS_RIGHT,				// 0x0e
	SFLAGS_ALL				= SFLAGS_LEFT | SFLAGS_RIGHT | SFLAGS_UP | SFLAGS_DOWN,	// 0x0f
} SideFlags;


 /**
  * Enum wich can be used for SetPanelType function
  * @see SetPanelType(int)
  */
typedef enum
{
	PANEL_DISABLED          = 0,          /**< PANEL is completely off */
	PANEL_ENABLED           = 1 << 1,     /**< PANEL is on, if any other flag is set panel is treated as active */
	PANEL_EVENT_NO_HANDLING = 1 << 2      /**< PANEL is on and could be drawn but it does not handle pointer events, 
	                                        * it is good to use in pair with SetManualPanelUpdates(int enable, iv_panelupdateshandler handler) 
	                                        * @see SetManualPanelUpdates(int enable, iv_panelupdateshandler handler) 
	                                        */
} PANEL_FLAGS;
char *iv_get_default_font(FONT_TYPE fonttype);

#define DEFAULTFONT iv_get_default_font(FONT_STD)
#define DEFAULTFONTB iv_get_default_font(FONT_BOLD)
#define DEFAULTFONTI iv_get_default_font(FONT_ITALIC)
#define DEFAULTFONTBI iv_get_default_font(FONT_BOLDITALIC)
#define DEFAULTFONTM iv_get_default_font(FONT_MONO)
//
#define I_UNUSED(arg) (void)arg;

typedef struct irect_s {

    int x;
    int y;
    int w;
    int h;
    int flags;

} irect;

typedef struct ibitmap_s {

    unsigned short width;
    unsigned short height;
    unsigned short depth;
    unsigned short scanline;
    unsigned char data[];

} ibitmap;
/** 
 * Struct wich can be used for function OpenControlPanel
 * currently is a stub, 
 * @see OpenControlPanel(control_panel*)
 */
typedef struct control_panel_s {
    int flags; /**< is a SET of flags, currently not used */
} control_panel;

typedef int  (*iv_handler)(int type, int par1, int par2);
typedef void (*iv_timerproc)();
typedef void (*iv_timerprocEx)(void* context);

typedef void (*iv_menuhandler)(int index);
typedef void (*iv_keyboardhandler)(char *text);
typedef void (*iv_keyboardhandlerex)(char *text, void* data);
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
typedef int  (*iv_msghandler)(int task, void *message, int len);
typedef int  (*iv_requestlistener)(int request, void *data, int inlen, int outlen);

typedef int  (*iv_hashenumproc)(char *name, void *value, void *userdata);
typedef int  (*iv_hashcmpproc)(char *name1, void *value1, char *name2, void *value2);
typedef void * (*iv_hashaddproc)(void *data);
typedef void (*iv_hashdelproc)(void *data);
typedef void (*iv_panelupdateshandler)(int x, int y, int w, int h);


struct TransparentDefinition
{
	char m_TRANSPARENT_MATRIX[256];
	int m_isInitTransparentMatrix;
	int	m_PercentOfTransparent;
};

typedef struct TransparentDefinition TransparentHandle;

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

typedef enum {
    FM_SHOW_SIZE = 0x00001,
} FONT_MENU_FLAGS;

typedef struct iuser_font_s {
    char *show_font_name;
    char *real_font_name;
    ifont *font;
} iuser_font;

typedef struct ifont_list_s {
    iuser_font *list;
    int count;
} ifont_list;

typedef struct ifont_menu_s {
    char *menu_title;
    char *current_font;
    FONT_MENU_FLAGS flags;
    iv_fontselecthandler hproc;
    ifont_list *user_fonts;
} ifont_menu;

typedef struct imenu_s {

    short type;
    short index;
    char *text;
    struct imenu_s *submenu;

} imenu;

typedef struct imenuex_s {

    short type;
    short index;
    char *text;
    struct imenuex_s *submenu;
    ibitmap *icon;
    void *reserved;
    const ifont *font;

} imenuex;

typedef struct icanvas_s {

    int width;
    int height;
    int scanline;
    int depth;
    int clipx1, clipx2;
    int clipy1, clipy2;
    unsigned char *addr;

} icanvas;

// Struct for context menu properties
typedef struct icontext_menu_properties_s {
    ifont *font_normal, *font_selected, *font_disabled;
    int background_color_normal;
    int background_color_disabled;
    int blackout;
    int item_height;
    int item_border_indent_horizontal;
    int separator_indent_horizontal;
    int separator_indent_vertical;
    int separator_height;
    int separator_style;
    int separator_color;
    int separator_frequency;
    int marker_height;
    int marker_indent_horizontal;
    int marker_style;
    int marker_color;
    int border_size;
    int border_radius;
    int title_height;
    int enable_pointer;
    int font_normal_color, font_selected_color, font_disabled_color;
    int bullet_show;
    /**
     * @brief bullet_style - style of bullet element. 
     * Values:
     * 0 - default
     * 1 - draw bitmap at all elements
     * By default it has been set to zero and it mean that we draw a bullet as a symbol only at one element.
     */
    int bullet_style;
    int item_border_indent_vertical;
    int background_style;
}icontext_menu_properties;

// Old functional, use ifont_menu struct
typedef struct ifont_selector_properties {
    unsigned short custom_font_enable;
} font_selector_properties;

typedef struct icontext_menu_s {
    const char *id;
    iv_menuhandler hproc;
    const imenuex *menuex;
    const imenu *menu;
    irect pos_selected_item;
    irect pos_menu;
    icontext_menu_properties *properties;
    int active_element;
    short enable_pointer;
    short enable_aura;
    short use_own_font;
    short update_after_close;
    short only_choise;
} icontext_menu;

// Struct for caption options
typedef struct iapp_caption_s
{
    irect rect_portrait;
    irect rect_landscape;
    ifont * font;
    int title_height;
    int background_color;
    short is_active;
    short is_uppercase;
} iapp_caption;

//Task manager struct
typedef struct itaskmgr_s {
    int title_height;
    ifont *title_font;
    ifont *task_font;
    ifont *task_title_font;
    int style;
    int profile_present;
    int profile_height;
    ifont *profile_font;
    int shortcut_height;
    int shortcut_width;
    ifont *shortcut_font;
    int task_height;
    int full_height;
    int full_width;
    int width;
    int height;
    int x;
    int y;
    int border_size;
    int indent_from_border;
    ibitmap **bitmap;
    int bitmap_count;
    int separator_size;
    int exit_button_indent;
    int background_style;
    int separator_color;
    int border_color;
} itaskmgr;

typedef struct ipager_s {
    ifont *page_font;
    int height;
    int indent_horizontal;
    int left_width;
    int page_width;
    int rigth_width;
    int separator_size;
    const ibitmap *icon_left;
    const ibitmap *icon_right;
    int current_page;
    int total_pages;
    irect position;
    int orientation;
}ipager;

typedef struct iselection_s {
    int selection_style;
    int background_color;
    int background_style;
    int border_size;
    int border_radius;
    int indent_horizontal;
    int indent_left;
    int indent_right;
}iselection;

typedef enum {
    STYLE_UNKNOWN = 0,
    STYLE_KEYBOARD = 1,
    STYLE_TOUCHPANEL = 2,
    STYLE_TOUCHPANEL_KEYBORAD = 3,
    STYLE_MAX_NOT_USED = 4
} AppStyles;

typedef struct iappstyle_s {
    AppStyles app_style;
}iappstyle;

typedef struct ievent_s {

    iv_handler hproc;
    unsigned short type;
    unsigned short mod;
    unsigned short par1;
    unsigned short par2;

} ievent;

typedef struct iconfig_s {

    char *filename;
    ihash *hash;
    ihash *vhash;
    ihash *modified_hash;
    char **deleted_keys;
    int changed;

} iconfig;

typedef struct iconfigedit_s {

    int type; //7 lowest bits of type meen type, other beets are flags; use CFG_MASK CFG_FLAG_MASK constants
    const ibitmap *icon;
    char *text;
    char *hint;
    char *name;
    char *deflt;
    char **variants;
    struct iconfigedit_s *submenu; // if type == CFG_CHOICE_SPECIAL_FONT then submenu use as (ifont *)
    ibitmap **icon_theme;
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
    char name[32];
    void* context;
    long long lastchecktime;
} itimer;

typedef struct bookinfo_s {

    int type;
    char *typedesc;
    char *path;
    char *filename;
    char *title;
    char *author;
    char *series;
    int	 numinseries;
    char *genre[10];
    ibitmap *icon;
    int year;
    long size;
    time_t ctime;
    char* isbn;
    char* meta_id;
	char* first_author;
	int drm;
	char *annotation;
    char *lang;
    char *publisher;
    char *identifiers;

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

typedef struct iv_fbinfo_s {

    int version;
    unsigned int flags;
    int shmkey;
    int shmsize;
    int refkey;
    int refsize;
    int width;
    int height;
    int vdepth;
    int ndepth;
    int orientation;
    int _deprecated_cwidth;
    int _deprecated_cheight;
    int scanline;
    int fb_offset;
    int fb_size;
    int ev_offset;
    int ev_size;
    int evhead;
    int evtail;
    int einkversion;
    int reserved[15];
    unsigned char data[0];
    int fb_y_offset;

} iv_fbinfo;

typedef struct subtaskinfo_s {

    int id;
    char *name;
    char *book;
    int fgindex;
    int order;
    int rsv_1s;

} subtaskinfo;

typedef struct taskinfo_s {

    int task;
    int nsubtasks;
    unsigned int flags;
    int fbshmkey;
    int fbshmsize;
    pid_t mainpid;
    char *appname;
    ibitmap *icon;
    subtaskinfo *subtasks;
    int rsv_1;
    int rsv_2;
    int rsv_3;
    int rsv_4;

} taskinfo;

//input_dev_e is touch 'devtype'; describes a input device.
enum input_dev_e {
	UNKNOWN = 0,
	CAPTOUCH,
	DIGITIZER,

	MAX_INPUT_DEV,
};

typedef struct iv_mtinfo_s {

    int active;
    int x;
    int y;
    int pressure;
    enum input_dev_e devtype;
    int rsv_2;
    long long timems;
} iv_mtinfo;

//scaned wifi ap information
typedef struct apinfo_s {
	char ssid[36];
	int mode;
	int channel;
	WIFI_SECURITY security;
	int quality;
	int level;
	int noise;
	unsigned char mac[8];
	time_t timestamp; //the last scanned time
} wifiapinfo;

typedef struct wifi_ap_list_s {
	int ap_quantity;
	wifiapinfo apinfo[];
} iv_wifi_ap_list;

typedef iv_wlist* (*pointer_to_word_hand_t)(int x, int y, int forward);

/*
 * name of network interface or IPv4 address in IPv4 numbers-and-dots representation.
 */
typedef union { char intr[8]; char addr[16]; char hw_addr[18]; } network_interface;

typedef struct network_interface_array_s {
	unsigned int count;
	network_interface net_int[];
}network_interface_array;

/*
 * Bluetooth services
 */
#define MAX_BT_SERVICE_USER 16

enum bt_service_e {
	BT_UNKNOWN = 0,
	BT_AUTH,
	BT_OBEX,
	BT_SECOND_SCREEN
};

enum bt_service_state_e {
	BT_SERVICE_ACTIVE = 0,
	BT_SERVICE_CANCEL,
	BT_SERVICE_ERROR
};

enum obex_status_e {
	OBEX_UNKNOWN = 0,
	OBEX_ERROR,
	OBEX_REQUEST_AUTH,
	OBEX_REQUEST_AUTH_DONE,
	OBEX_TRANSFERRING,
	OBEX_DONE
};

struct obex_service_s {
	enum obex_status_e status;
	int auth;

	long filesize;
	long transferred;

	char name[128];
	char path[256];
	char description[128];
	char mimetype[64];
};

typedef struct bt_service_obj_s {
	int id;
	enum bt_service_e service;
	enum bt_service_state_e state;
	int lock;
	pid_t users[MAX_BT_SERVICE_USER];
	union {
		struct obex_service_s obex;
		char service_data[1024];
	};
} bt_service_obj;

/*
 * struct which consist main information about any network interface.
 */
typedef struct {
	network_interface ip_addr; //ip address of interface
	network_interface mask; //mask
	network_interface br_addr; //broadcast address
	network_interface hw_addr; //hardware address (MAC)
} network_interface_info;

typedef struct icolor_map_s {

	int *from_color;
	int *to_color;
	int size;

} icolor_map;

 /**
  * Enum APPLICATION_ATTRIBUTE wich can be used for setting current application attributes
  * @see SetCurrentApplicationAttribute, TestCurrentApplicationAttribute
  */
typedef enum
{
	APPLICATION_READER                 = 0,      /**< application is a reader, affects behavior of panel
	                                               * for proper work, set this attribute before first acces to panel API
	                                               */
	APPLICATION_ATTRIBUTE_MAX          = 31      /**< maximal value of the attribute */
} APPLICATION_ATTRIBUTE;

void OpenScreen();
void OpenScreenExt();
void InkViewMain(iv_handler h);
void CloseApp();
void InitInkview(int reg_flags);

// Return irect struct

irect iRect(int x, int y, int w, int h, int flags);

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

enum estyle{
    ROUND_ALL = 1,
    ROUND_TOP,
    ROUND_DOWN,
    ROUND_LEFT,
    ROUND_RIGHT,
    ROUND_TOP_LEFT,
    ROUND_TOP_RIGHT,
    ROUND_BOTTOM_LEFT,
    ROUND_BOTTOM_RIGHT
};

void ClearScreen();
void SetClip(int x, int y, int w, int h);
void SetClipRect(const irect *rect);
void GetClip(int *x, int *y, int *w, int *h);
irect GetClipRect();
irect MergeClipRect(const irect *rect);
void DrawPixel(int x, int y, int color);
void DrawLine(int x1, int y1, int x2, int y2,int color);
void DrawLineEx(int x1, int y1, int x2, int y2, int color, int step);
void DrawRect(int x, int y, int w, int h, int color);
void DrawRectRound(int, int, int, int, int, int);
void FillArea(int x, int y, int w, int h, int color);
void FillAreaRect(const irect *rect, int color);
void InvertArea(int x, int y, int w, int h);
void InvertAreaBW(int x, int y, int w, int h);
icolor_map *ColorMapCreate(int size);
void ColorMapDestroy(icolor_map **map);
void InvertAreaMap(int x, int y, int w, int h, icolor_map *map);
void DimArea(int x, int y, int w, int h, int color);
void DrawSelection(int x, int y, int w, int h, int color);
void DrawCircle(int x0, int y0, int radius, int color);
void DrawPickOut(int x, int y, int w, int h, const char *key);
void DrawPickOutEx(const irect *rect, const char *key);
void DitherArea(int x, int y, int w, int h, int levels, int method);
void DitherAreaQuick2Level(int dx, int dy, int dw, int dh);
void QuickFloyd16Dither(unsigned char * buffer, int row_size, int left, int top, int width, int height);
void Stretch(const unsigned char *src, int format, int sw, int sh, int scanline, int dx, int dy, int dw, int dh, int rotate);
void StretchArea(const unsigned char *src, int format, int sx, int sy, int sw, int sh, int scanline, int dx, int dy, int dw, int dh, int rotate);
void StretchAreaBW(const unsigned char *src, int format, int sx, int sy, int sw, int sh, int scanline, int dx, int dy, int dw, int dh);
void SetCanvas(icanvas *c);
icanvas *GetCanvas();
void Repaint();
void DrawFrame(int x, int y, int w, int h, ibitmap *icon, char *title, int flags, irect *clientarea);
int CheckFramePointer(int x, int y, int w, int h, int flags, int ptx, int pty);
void DrawBorder(const irect *border_rect, int border_size, int style, int radius, int color);
void DrawPager(ipager *pager);
irect GetPagerRect(ipager *pager);
int GetPagerHeight(ipager *pager);
int IsPagerEvent(ipager *pager, int type, int x, int y);
int PagerHandler(ipager *pager, int type, int x, int y);

/**
  * Draw diagonal hatch in area. step should be positive and (step - 1) is horizontal distance in pixels between hatches
  * (e.g. step 1 means no distance)
  * IMPORTANT! this function works incorrectly and actually uses width = w + 1
  */
void DrawDiagonalHatch(int x, int y, int w, int h, int step, int color);
void DrawDiagonalHatchLimits(int x, int y, int w, int h, int step, int color, int (*limit)(int, int));

/// Tranparent specified rect
void Transparent(int x, int y, int w, int h, int percent);
void TransparentRect(irect rect, int percent);

// Bitmap functions

ibitmap *LoadBitmap(const char *filename);
ibitmap *zLoadBitmap(void *zf, const char *filename);
int SaveBitmap(const char *filename, const ibitmap *bm);
ibitmap *BitmapFromScreen(int x, int y, int w, int h);
ibitmap *BitmapFromScreenR(int x, int y, int w, int h, int rotate);
ibitmap *NewBitmap(int w, int h);
void SetLoadImageFlags(int flags);
ibitmap *LoadJPEG(const char *path, int w, int h, int br, int co, int proportional);
ibitmap *LoadTIFF(const char *path, int w, int h, int br, int co, int proportional);
int SaveJPEG(const char *path, ibitmap *bmp, int quality);
ibitmap *LoadPNG(const char *path, int dither);
ibitmap *LoadPNGStretch(const char *path, int width, int height, int proportional, int dither);
int SavePNG(const char *path, const ibitmap *bmp);
void SetTransparentColor(ibitmap **bmp, int color);
ibitmap* CopyBitmapDepth4To8(const ibitmap* bmp);
ibitmap* CopyBitmapDepth8To4(const ibitmap* bmp);
void MoveBitmap(ibitmap* bmp, int offset);
void MoveBitmapRight(ibitmap* bm, int offset);

/**
 * @brief BitmapStretchCopy function copies a part of an other bitmap to the newly created bitmap
 * @param bmp source image
 * @param sx, @param sy, @param sw, @param sh are coordinates of source image part to be copied
 * @param width and @param height are size of the new bitmap
 * @return a pointer of the new bitmap
 */
ibitmap * BitmapStretchCopy(const ibitmap * bmp, int sx, int sy, int sw, int sh, int width, int height);

void DrawBitmap(int x, int y, const ibitmap *b);
void DrawBitmapArea(int x, int y, const ibitmap *b, int bx, int by, int bw, int bh);
void DrawBitmapRect(int x, int y, int w, int h, const ibitmap *b, int flags);
void DrawBitmapRect2(const irect *rect, const ibitmap *b);
void StretchBitmap(int x, int y, int w, int h, const ibitmap *src, int flags);
void TileBitmap(int x, int y, int w, int h, const ibitmap *src);
ibitmap *CopyBitmap(const ibitmap *bm);
void MirrorBitmap(ibitmap *bm, int m);

// Text functions

char **EnumFonts();
char **EnumFontsFromDirectory(const char *directory1, const char *directory2);

typedef struct FontForSort_s {
    char* name;
    int flags;
    char* font;
} FontForSort;

FontForSort* EnumFontsEx();
FontForSort* EnumFontsFromDirectoryEx(const char * directory1, const char * directory2);
void FreeFontsForSort(FontForSort* fonts);

ifont *OpenFont(const char *name, int size, int aa);
void CloseFont(ifont *f);
void SetFont(const ifont *font, int color);
const ifont *GetFont();
void DrawString(int x, int y, const char *s);
void DrawStringR(int x, int y, const char *s);
int TextRectHeight(int width, const char *s, int flags);
int TextRectHeightEx(int width, int height, const char *s, int flags);
int MinimalTextRectWidth(int w, const char *s);
char *DrawTextRect(int x, int y, int w, int h, const char *s, int flags);
char *DrawTextRect2(const irect *rect, const char *s);
char *DrawTextRect3(int x, int y, int w, int h, const char *s, int flags, int * height);
int CharWidth(unsigned  short c);
int StringWidthExt(const char *s, int l);
int StringWidth(const char *s);
int GetMultilineStringWidth(const char *str, const int area_width, ifont *font, const int flags);
int DrawSymbol(int x, int y, int symbol);
void RegisterFontList(ifont **fontlist, int count);
void SetTextStrength(int n);

// Screen update functions

void FullUpdate();
void FullUpdateHQ();
void SoftUpdate();
void SoftUpdateHQ();
void PartialUpdate(int x, int y, int w, int h);
void PartialUpdateBlack(int x, int y, int w, int h);
void PartialUpdateBW(int x, int y, int w, int h);
void PartialUpdateHQ(int x, int y, int w, int h);
void PartialUpdateDU4(int x, int y, int w, int h);
void DynamicUpdate(int x, int y, int w, int h);
void DynamicUpdateBW(int x, int y, int w, int h);

/**
  * Fast update of the screen area. This function call is asyncronous (return before update finished).
  * It takes some time (hardware dependent, for 622 it is 125 ms) to actually update screen and calling any screen update function
  * during this time for the intersected screen area may lead to artefacts on resulting image.
  * TODO clarify is it neccesary to call dithering before the call?
  */
void DynamicUpdateA2(int x, int y, int w, int h);
void ExitUpdateA2();
int IsInA2Update();
void FineUpdate();
//void DynamicUpdate();
int FineUpdateSupported();
int HQUpdateSupported();
void ScheduleUpdate(int x, int y, int w, int h, int bw);
void WaitForUpdateComplete();

// Event handling functions
iv_handler SetEventHandler(iv_handler hproc);
iv_handler SetEventHandlerEx(iv_handler hproc);
iv_handler GetEventHandler();
void SendEvent(iv_handler hproc, int type, int par1, int par2);
void ProcessEventLoop();
void FlushEvents();
char *iv_evttype(int type);
char IsAnyEvents();
void PrepareForLoop(iv_handler hproc);
void ClearOnExit();

// Timer functions

void SetHardTimer(const char *name, iv_timerproc tproc, int ms);
void SetHardTimerEx(const char* name, iv_timerprocEx tproc, void* context, int ms);
void SetWeakTimer(const char *name, iv_timerproc tproc, int ms);
void SetWeakTimerEx(const char* name, iv_timerprocEx tp, void* context, int ms);
long long QueryTimer(iv_timerproc tp);
long long QueryTimerEx(iv_timerprocEx tp, void* context);
void ClearTimer(iv_timerproc tproc);
void ClearTimerEx(iv_timerprocEx tproc, void* context);
void ClearTimerByName(const char *name);

// UI functions
void OpenMenu(imenu *menu, int pos, int x, int y, iv_menuhandler hproc);
void OpenMenuEx(imenuex *menu, int pos, int x, int y, iv_menuhandler hproc);
void UpdateMenuEx(imenuex *menu);
void OpenContextMenu(const icontext_menu *menu);
void SetContextMenu(const icontext_menu *menu);
icontext_menu * CreateContextMenu(const char *id);
void CloseContextMenu(icontext_menu * menu);

void OpenMenu3x3(const ibitmap *mbitmap, const char *strings[9], iv_menuhandler hproc);
irect GetMenuRect(const imenu *menu);
irect GetMenuRectEx(const imenuex *menu);
void OpenList(const char *title, const ibitmap *background, int itemw, int itemh, int itemcount, int cpos, iv_listhandler hproc);
void SetListHeaderLevel(int level);
int GetListHeaderLevel();
void OpenDummyList(const char *title, const ibitmap *background, char *text, iv_listhandler hproc);
char **EnumKeyboards();
void LoadKeyboard(const char *kbdlang);
/**
 * @brief GetKeyboardFlags is thread safe in device environment
 * @return flags with wich keyboard was opened
 */
int GetKeyboardFlags();
void OpenKeyboard(const char *title, char *buffer, int maxlen, int flags, iv_keyboardhandler hproc);
void OpenKeyboardEx(const char *title, char *buffer, int maxlen, int flags, iv_keyboardhandlerex hproc, void* cb_data);
void DrawKeyboard();
void OpenCustomKeyboard(const char *filename, const char *title, char *buffer, int maxlen, int flags, iv_keyboardhandler hproc);
void CloseKeyboard();
void GetKeyboardRect(irect *rect);
irect GetKeyboardRectWithParams(char *title, char *buffer, int flags);
int IsKeyboardOpened();
void OpenPageSelector(iv_pageselecthandler hproc);
void OpenTimeEdit(const char *title, int x, int y, long intime, iv_timeedithandler hproc);
void OpenDirectorySelector(const char *title, char *buf, int len, iv_dirselecthandler hproc);
void OpenFontSelector(const char *title, const char *font, int with_size, iv_fontselecthandler hproc);
void OpenFontSelectorEx(const ifont_menu *menu);
ifont_menu GetFontMenuStruct();
void ClearFontMenuStruct(ifont_menu *menu);
void ClearFontListStruct(ifont_list *list);
// Temporary function for tunneling font menu properties thru configeditor
void SetFontMenuStruct(ifont_menu * menu);

void OpenBookmarks(int page, long long position, int *bmklist, long long *poslist,
        int *bmkcount, int maxbmks, iv_bmkhandler hproc);
void SwitchBookmark(int page, long long position, int *bmklist, long long *poslist,
        int *bmkcount, int maxbmks, iv_bmkhandler hproc);
void OpenContents(tocentry *toc, int count, long long position, iv_tochandler hproc);
void OpenRotateBox(iv_rotatehandler hproc);
void Message(int icon, const char *title, const char *text, int timeout);
void Dialog(int icon, const char *title, const char *text, const char *button1, const char *button2, iv_dialoghandler hproc);
void Dialog3(int icon, const char *title, const char *text, const char *button1, const char *button2, const char *button3, iv_dialoghandler hproc);
int DialogSynchro(int icon, const char *title, const char *text, const char *button1, const char *button2, const char *button3);
void CloseDialog();
void OpenProgressbar(int icon, const char *title, const char *text, int percent, iv_dialoghandler hproc);
int  UpdateProgressbar(const char *text, int percent);
void CloseProgressbar();
void ShowHourglassForce();
void ShowHourglass();
void ShowHourglassAt(int x, int y);
void ShowHourglassForceAt(int x, int y);
void ShowPureHourglass();
void ShowPureHourglassForce();
void HideHourglass();
void DisableExitHourglass();
void LockDevice();

// enable: 0 -- Panel updates by timer, 1 --user updates panel by himself
// handler -- handles updates
void SetManualPanelUpdates(int enable, iv_panelupdateshandler handler); 
//if after_time is set to -1, changes mode in panel.reading.mode.delay milliseconds, if is set to 0 changes mode immediately, if other changes mode in after_time milliseconds
void SetReadingMode(int enable, int after_time, int update);

/**
  * Function changes panel working style
  * @param type when is 0 panel is completely off, otherwise it is a set of PANEL_FLAGS
  * @see enum PANEL_FLAGS
**/
void SetPanelType(int type);
int GetPanelType();
/**
 * @brief SetShowStatusBar is called to show enable/disable showing status bar in reader
 * @param show takes 0 to disable status bar, othe value to enable
 */
void SetShowPanelReader(int show);
int IsShowPanelReader();
int  SetPanelSeparatorEnabled(int enable); // Calling procedure you enable horizontal separator, it separates bottom panel from other page contents
int IsPanelSeparatorEnabled();
void InitPanel();
void SetPanelKeyForFullScreenEnabled(const char *key);

/**
 * @brief StartPanelProgress start gui animation on panel
 * @param progress currently not used, but may be used in future, values between 0 - 100
 * after @param timeoutMs will be automatically stoped, negative value meens animation will run always
 */
void StartPanelProgress(int progress, int timeoutMs);

/**
 * @brief StopPanelProgress stops gui animation
 */
void StopPanelProgress();

int  DrawPanel(const ibitmap *icon, const char *text, const char *title, int percent);
int  DrawPanel2(const ibitmap *icon, const char *text, const char *title, int percent, int readingModeEnable); // almost the same as DrawPanel when have 0 in readingModeEnable parameter
int  DrawPanel3(const ibitmap *icon, int currentPage, int totalPages, int readingModeEnable); // almost the same as DrawPanel when have 0 in readingModeEnable parameter
int  DrawPanel4(const ibitmap *icon, const char * bookName, int currentPage, int totalPages, int readingModeEnable);
int  DrawPanel5(const ibitmap *icon, const char *text, const char *title, int percent, int readingModeEnable); // almost the same as DrawPanel2, but output text.
int  DrawTabs(const ibitmap *icon, int current, int total);
/**
 * @brief OpenControlPanel calls control panel application
 * @param ctx is parameter wich contains 
 * special panel configurations options
 */
void OpenControlPanel(control_panel * ctx);
int  PanelHeight();
void SetKeyboardRate(int t1, int t2);
int QuickNavigatorSupported(int flags);
void QuickNavigator(int x, int y, int w, int h, int cx, int cy, int flags);
void SetQuickNavigatorXY(int x, int y);

// Functions for applications caption
void DrawApplicationCaption(const char * caption, const irect *title_rect);
int GetCaptionHeight();
void SetApplicationCaptionHeight(int h);
iapp_caption * LoadApplicationCaptionProperties();

// Task manager functions
itaskmgr * LoadTaskManagerProperties();

ipager * LoadPagerProperties();
iselection * LoadSelectionProperties(const char *key);
icontext_menu_properties * LoadContextMenuProperties();
AppStyles GetAppGlobalStyle();
AppStyles GetAppStyle(const char *key);
iappstyle *GetAppStyleEx(const char *key);
font_selector_properties * GetFontSelectorProperties();
const char *GetCustomFontString();

// Configuration functions

iconfig * GetGlobalConfig();
iconfig * OpenConfig(const char *path, iconfigedit *ce);
int RefreshConfig(iconfig **cfg); //update memory copy config from his file
int SaveConfig(iconfig *cfg);
void CloseConfig(iconfig *cfg);
void CloseConfigNoSave(iconfig *cfg);

int ReadInt(iconfig *cfg, const char *name, int deflt);
const char *ReadString(iconfig *cfg, const char *name, const char *deflt);
const char *ReadSecret(iconfig *cfg, const char *name, const char *deflt);
void WriteInt(iconfig *cfg, const char *name, int value);
void WriteString(iconfig*cfg, const char *name, const char *value);
void WriteSecret(iconfig *cfg, const char *name, const char *value);
void WriteIntVolatile(iconfig *cfg, const char *name, int value);
void WriteStringVolatile(iconfig *cfg, const char *name, const char *value);
void DeleteInt(iconfig *cfg, const char *name);
void DeleteString(iconfig *cfg, const char *name);
void SetConfigEditorBackground(ibitmap * bmp); // set background before calling OpenConfigEditor proc
void OpenConfigEditor(const char *header, iconfig *cfg, iconfigedit *ce, iv_confighandler hproc, iv_itemchangehandler cproc);
void OpenConfigSubmenuExt(const char *title, iconfigedit *ice, int pos);
void OpenConfigSubmenu(const char *title, iconfigedit *ice);
void UpdateCurrentConfigPage();
void UpdateConfigPage(const char *title, iconfigedit *ice);
void CloseConfigLevel();
void NotifyConfigChanged();
void ClearConfig(iconfig *cfg);
/**
 * @brief GetKeyMapping used to read TEXT key mapping from default config
 * @param act0 and @param act1 are are arrays of CSTtring wich look like "@KA_..." 
 * FOR EXAMPLE act0[KEY_PREV] will contain an action wich should happen when user PRESSES IV_KEY_PREV,
 * act1[KEY_PREV] will contain an action wich should happen when user HOLS IV_KEY_PREV,
 * IMPORTANT !! pointers are not always valid, use strdup to handle it
 */
void GetKeyMapping(const char *act0[], const char *act1[]);
/**
 * @brief GetKeyMappingEx is similar to GetKeyMapping
 * @param what may be KEYMAPPING_GLOBAL or KEYMAPPING_TXT or KEYMAPPING_PDF
 * @param act0 @see GetKeyMapping
 * @param act1 @see GetKeyMapping
 * @param count contains key count, it is the size of act0 and act1 maximal size
 * IMPORTANT !! pointers are not always valid, use strdup to handle it
 */ 
void GetKeyMappingEx(int what, const char *act0[], const char *act1[], int count);
int AdjustDirectionKeys(int key);
unsigned long QueryDeviceButtons();
int IsJoystickButtonsPresent();

// Multitasking

#define TCAP(s) (0x50000000 | ((s[0] & 0x7f) | ((s[1] & 0x7f) << 7) | ((s[2] & 0x7f) << 14) | ((s[3] & 0x7f) << 21)))

int MultitaskingSupported();
int NewTask(const char *path, char * const args[], const char *appname, const char *name, const ibitmap *icon, unsigned int flags);
int NewTaskEx(const char *path, char * const args[], const char *appname, const char *name, const ibitmap *icon, unsigned int flags, int run_as_reader_if_needed);
int NewSubtask(char *name);
int SwitchSubtask(int subtask);
void SubtaskFinished(int subtask);
int GetCurrentTask();
void GetActiveTask(int *task, int *subtask);
int IsTaskActive();
void GetPreviousTask(int *task, int *subtask);
void GetPreviousTaskInStack(int *task, int *subtask);
int GetTaskList(int *list, int size);
taskinfo *GetTaskInfo(int task);
int FindTaskByBook(const char *name, int *task, int *subtask);
int FindTaskByAppName(const char *name);
int SetTaskParameters(int task, const char *appname, const char *name, ibitmap *icon, unsigned int flags);
int SetSubtaskInfo(int task, int subtask, const char *name, const char *book);
int SetActiveTask(int task, int subtask);
void GoToBackground();
int CloseTask(int task, int subtask, int force);
int SendEventTo(int task, int type, int par1, int par2);
int SendEventSyncTo(int task, int type, int par1, int par2);
int SendMessageTo(int task, int request, void *message, int len);
int SetRequestListener(int request, int flags, iv_requestlistener hproc);
int SendRequest(int request, void *data, int inlen, int outlen, int timeout);
int SendRequestNoWait(int request, void *data, int inlen, int outlen);
int SendRequestTo(int task, int request, void *data, int inlen, int outlen, int timeout);
int SendRequestToNoWait(int task, int request, void *data, int inlen, int outlen);
int SendGlobalRequest(int param);
void SetMessageHandler(iv_msghandler hproc);
void OpenTaskList();
icanvas *GetTaskFramebuffer(int task);
iv_fbinfo *GetTaskFramebufferInfo (int task);
void ReleaseTaskFramebuffer(icanvas *fb);
void iv_wait_task_activation(int timeout);

/*
 * Copy framebuffer from currently active task (mpc->activetask)
 * to framebuffer of task has called this function.
 * It might be used in hidden or background tasks,
 * when need send Dialog or Message to user on background of currently active task.
 */
void CopyActiveFb(void);

int GetFrontlightVersion(void);

/*
 * Returns frontlight state (0-100 - brightness, negative value if off)
 * returns INT_MIN if can't read or not supported
 */
int GetFrontlightState(void);

/*
 * Sets frontlight state (0-100 - brightness, negative value if off)
 */
void SetFrontlightState(int flstate);

/*
 * Sets frontlight state (0-100 - brightness, negative value if off)
 *   temporary for use when about to keylock and this value should not be stored
 */
void SetFrontlightStateEx(int flstate, int temporary);

/*
 * If supported open special application
 */
void OpenFrontLightConfig();
/*
    On/off FrontLight
*/
void SwitchFrontlightState();

/*
 * Returns frontlight color (0-100 - day-night)
 * returns INT_MIN if can't read or not supported
 */
int GetFrontlightColor(void);

/*
 * Sets frontlight state (0-100 - day-night)
 */
void SetFrontlightColor(int color);

// String hash functions

ihash * hash_new(int prime);
void hash_add(ihash *h, const char *name, const char *value);
void hash_delete(ihash *h, const char *name);
const char *hash_find(ihash *h, const char *name);

// Object hash functions

ihash * vhash_new(int prime, iv_hashaddproc addproc, iv_hashdelproc delproc);
void vhash_add(ihash *h, const char *name, const void *value);
void vhash_delete(ihash *h, const char *name);
const void *vhash_find(ihash *h, const char *name);

// Common hash functions

void hash_clear(ihash *h);
void hash_destroy(ihash *h);
int  hash_count(ihash *h);
void hash_enumerate(ihash *h, iv_hashcmpproc cmpproc, iv_hashenumproc enumproc, void *userdata);
ihash *hash_merge(ihash *base_hash, ihash *hash_to_merge);
int hash_merge_to(ihash *base_hash, ihash *hash_to_merge, ihash *dest_hash);
ihash *hash_copy(ihash *source_hash);
int hash_copy_to(ihash *source_hash, ihash *dest_hash);

// filesystem functions

int iv_stat(const char *name, struct stat *st);
int iv_access(const char *pathname, int mode);
FILE *iv_fopen(const char *name, const char *mode);
int iv_fread(void *buffer, int size, int count, FILE *f);
int iv_fwrite(const void *buffer, int size, int count, FILE *f);
int iv_fseek(FILE *f, long offset, int whence);
long iv_ftell(FILE *f);
int iv_fclose(FILE *f);
int iv_fclose_no_sync(FILE *f);
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
void iv_setbgresponse(int t);
void Path2String(const char * path, char * string, int maxLength);

// ipc functions

long iv_ipc_request(long type, long attr, unsigned char *data, int inlen, int outlen);
long iv_ipc_request_secure(long type, long param, unsigned char *data, int inlen, int outlen);
long iv_ipc_cmd(long type, long param);
long iv_ipc_request_with_timeout(long type, long param, unsigned char *data, int inlen, int outlen, int timeout_ms);

// Language functions

char ** EnumLanguages();
void LoadLanguage(const char *lang);
void AddTranslation(const char *label, const char *trans);
// return translation for current language, do translate on english
const char *GetCurrentLangText(const char *s);
const char *GetLangText(const char *s);
const char *GetLangTextF(const char *s, ...);
const char *GetLangTextPlural(const char *s, int amount);
void SetRTLBook(int rtl);
int IsRTL();  // depends only on the system language
int IsBookRTL();	// can be overwritten by application

//#define T(x) GetLangText(#x)
//#define TF(x...) GetLangTextF(x)

// User profile functions
typedef struct iprofile_s {
	char *name;
	char *path;
	int type;
	ibitmap *avatar;
} iprofile;

typedef struct iprofiles_s {
	iprofile *profile;
	int count;
} iprofiles;

// Profiles functions

// Old functions. Will be removed in future
char **EnumProfiles();
int GetProfileType(const char *name);
ibitmap **EnumProfileAvatars();
ibitmap *GetProfileAvatar(const char *name);
int SetProfileAvatar(const char *name, ibitmap *ava);
int RenameProfile(const char *oldname, const char *newname);
int DeleteProfile(const char *name);
char *GetCurrentProfile();
void SetCurrentProfile(const char *name, int flags);
int GetProfilesCountAfterEnum();
void OpenProfileSelector();
int ScanProfiles(const char *path, int type, iprofiles *profiles);
int GetLocalProfilesLimit();
int GetSDProfilesLimit();
int GetProfilesLimit();

// New function for work with profiles
iprofile CreateProfileStruct();
iprofiles CreateProfilesStruct();
void ClearProfilesStruct(iprofiles *profiles);
void ClearProfileStruct(iprofile *profile);
int ScanProfiles(const char *path, int type, iprofiles *profiles);
int GetProfilesList(iprofiles *profiles);
int CreateProfile(const char *name, int type);
int DeleteProfileEx(const iprofile *profile);
int RenameProfileEx(const iprofile *profile, const char *new_name);
int GetCurrentProfileEx(iprofile *profile);
int SetCurrentProfileEx(const iprofile *profile);
int GetProfilesCount();

// Theme functions

char ** EnumThemes();
void OpenTheme(const char *path);
ibitmap *GetResource(const char *name, const ibitmap *deflt);
int GetThemeInt(const char *name, int deflt);
const char *GetThemeString(const char *name, const char *deflt);
ifont *GetThemeFont(const char *name, const char *deflt);
void GetThemeRect(const char *name, irect *rect, int x, int y, int w, int h, int flags);
ibitmap *GetKeyResource(const char *key, const ibitmap *deflt);
unsigned short IsResourcePresent(const char *name);

// Book functions

iv_filetype *GetSupportedFileTypes();
int GetSupportedFileTypesLength();
bookinfo *GetBookInfo(const char *name);
bookinfo *GetBookInfoExt(const char *path, const char *separator);
char *GetBookISBN(const char *path);
ibitmap *GetBookCover(const char *name, int width, int height);

typedef enum MencaFileStatus_e {
    kMencaNoStatus,
    kMencaInCloud,
    kMencaSyncing,
    kMencaDownloaded
} MencaFileStatus;

typedef struct BookSyncStatus_s{
    MencaFileStatus menca_status_;
} BookSyncStatus;

BookSyncStatus GetBookSyncStatus(const char *path);

char *GetAssociatedFile(const char *name, int index);
char *CheckAssociatedFile(const char *name, int index);
iv_filetype *FileType(const char *path);
iv_filetype *FileTypeExt(const char *path, struct stat *f_stat);
void SetFileHandler(const char *path, const char *handler);
const char *GetFileHandler(const char *path);
void PackParameters(int argc, const char * const * argv, void ** data, int * len);
void UnpackParameters(void * data, int len, int * argc, char *** argv);
int OpenBook(const char *path, const char *parameters, int flags);
int OpenBook2(const char *path, int argc, const char *const*argv, int flags);

void BookPreparing(const char *path);
void BookReady(const char *path);
char **GetLastOpen();
void AddLastOpen(const char *path);
void OpenLastBooks();
void FlushLastOpen();

/**
  \brief Try to find ISBN in text by regular expression patern. Return first occurence which match pattern.
  \param text text to search in
  \return pointer to isbn (null terminated string that should be freed by caller) or NULL if not found or error occurs
  */
char* FindIsbnInText(const char* text);

// Media functions

void OpenPlayer();
void ClosePlayer();
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

int GetHighVolumeTimeout();
void ResetHighVolumeTimeout();
void IncreaseHighVolumeInterval(int value);
void LoadHighVolumeTimeout();
void SaveHighVolumeTimeout();
int GetSafeVolumeLimit();
int GetHighVolumeMaxInterval();


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

/**
 * @brief GetWordListWithPrefix get up to maxWords words with given prefix from current dictionary.
 *  Function is not reentrant
 * @param prefix - prefix to find words (in utf-8)
 * @param maxWords - maximum words to find (should not be > 255)
 * @param wordList - resulting list of words (in utf-8), caller should not free the list
 * @return number of words found or 0 on error
 */
int GetWordListWithPrefix(const char *prefix_utf8, int maxWords, char ***wordList);

void OpenDictionaryView(iv_wlist *wordlist, const char *dicname);
void OpenControlledDictionaryView(pointer_to_word_hand_t pointer_handler, iv_wlist *wordlist, const char *dicname);
void OpenFastTranslation(pointer_to_word_hand_t pointer_handler, iv_wlist *wordlist, int pos, const char *dicname);

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

//Scrolling functions

//be sure to use RemoveScrolledArea after calling this function
//Used to receive EVT_SCROLL message
void AddScrolledArea(irect * area, int receivePointerUp);
void RemoveScrolledArea(irect * area);
void ClearAllScrolledAreas();
void SetMinimalXScrollIndent(irect * area, int Xindent);
void SetMinimalYScrollIndent(irect * area, int Yindent);
int IsAnyScrolledArea();

// Additional functions
void SetCurrentApplicationAttribute(APPLICATION_ATTRIBUTE attribute, int on);
int TestCurrentApplicationAttribute(APPLICATION_ATTRIBUTE attribute);
void iv_fullscreen();
void iv_nofullscreen();
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
const char *GetExternalCardSerialNumber();
char *GetWaveformFilename();
char *GetDeviceKey();
unsigned char *GetDeviceFingerprint();
char *CurrentDateStr();
char *DateStr(time_t t);
int GoSleep(int ms, int deep);
void BanSleep(int sec);
void SetAutoPowerOff(int en);
void PowerOff();
int SafeMode();
void OpenMainMenu();
void CloseAllTasks();
int WriteStartupLogo(const ibitmap *bm);
int PageSnapshot();
int RestoreStartupLogo();
int QueryTouchpanel();
void CalibrateTouchpanel();
void CalibrateTouchDevice(enum input_dev_e TouchDevice);
void OpenCalendar();
int StartSoftwareUpdate();
int HavePowerForSoftwareUpdate();

/*
 * If your task has done all work at this time, you may use this function
 * to force going to sleep. Next going to sleep will be as soon as possible.
 */
void ForcingSleep(void);

int WiFiPower(int status);

/*
 * Basic scan wifi networks function. It works in two modes:
 * 1) if gots ap_list_ as NULL, that scanning air is for the open wifi networks
 * 2) if gots ap_list_ as pointer to array iv_wifi_ap_list, that scanning air is only for
 * essid which filled in ap_list_. Current operation can take more time, in average 1 essid per sec.
 * Return new iv_wifi_ap_list allocated in memory or NULL if error.
 */
iv_wifi_ap_list *GetWiFiScanResults(iv_wifi_ap_list *aps);


//==========Scan Process Functions =========
/*
 * Start wifi scan process. If start was OK return 0 else return -1.
 */
int WiFiScanProcessStart(void);
/*
 * Function for setup new iv_wifi_ap_list to selective scan list.
 * Usually this scan need for hidden wifi networks.
 */
void WiFiScanProcessSetSelectiveList(iv_wifi_ap_list *list);
/*
 * Get scan process results. Its included open air scan + results of setted essid list scan.
 * Results allocated in new memory. Will need free it.
 * Can return NULL if error.
 */
iv_wifi_ap_list *WiFiScanProcessGetResults(void);
/*
 *Stop wifi scan process. Clean memory.
 */
int WiFiScanProcessStop(void);
//==========END Scan Process Functions =========
int QueryNetwork();
char *GetHwAddress();
char *GetHwBTAddress();
char *GetHw3GIMEI();
int GetBluetoothMode();
int SetBluetoothMode(int mode, int flags);
char **EnumBTdevices();
void OpenBTdevicesMenu(char *title, int x, int y, iv_itemchangehandler hproc);
int BtSendFiles(char *mac, char **files);
char **EnumWirelessNetworks();
char **EnumConnections();
int GetBTservice(const char *mac, const char *service);
int NetConnect(const char *name);
int NetConnect2(const char *name, int showHourglass);
int NetConnectSilent(const char *name);
int NetConnectAsync(int (*cb)(int status));
int NetDisconnect();
int NetDisconnectAsync(int (*cb)(int status));
iv_netinfo *NetInfo();
void OpenNetworkInfo();
char *GetUserAgent();
char *GetDefaultUserAgent();
char *GetProxyUrl();
void *QuickDownloadExt2(const char *url, int *retsize, int timeout, char *cookie, char *post, int * error_code);
void *QuickDownloadExt(const char *url, int *retsize, int timeout, char *cookie, char *post);
void *QuickDownload(const char *url, int *retsize, int timeout);
int NewSession();
void CloseSession(int id);
void SetUserAgent(int id, const char *ua);
void SetProxy(int id, const char *host, int port, const char *user, const char *pass);
int Download(int id, const char *url, const char *postdata, FILE **fp, int timeout);
int DownloadTo(int id, const char *url, const char *postdata, const char *filename, int timeout);
int DownloadTo_Crutch(int id, const char *url, const char *postdata, const char *filename, int timeout); // Don't use this function, it will be deleted
int SetSessionFlag(int _id, int _flag, void *_value);
int GetSessionStatus(int id);
const char * GetHeader(int id, const char *name);
iv_sessioninfo *GetSessionInfo(int id);
void PauseTransfer(int id);
void ResumeTransfer(int id);
void AbortTransfer(int id);
const char *NetError(int e);
void NetErrorMessage(int e);
int GetA2dpStatus();
void SetPort(int port);
iv_mtinfo *GetTouchInfo();
iv_mtinfo *GetTouchInfoI(unsigned int index);
int QueryHeadphone();
char * wpa_passphrase(char * ssid, char * passphrase);


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
int utf_toupper_ext(char* src, int src_len, char** dest, int* dest_len);
int utf_tolower_ext(char* src, int src_len, char** dest, int* dest_len);

#define CHANGE_CASE_ON_STACK(buf, f) { \
    char* CHANGE_CASE_ON_STACK_dest_ = NULL; \
    int CHANGE_CASE_ON_STACK_dest_len_ = 0; \
    f((buf), -1, &CHANGE_CASE_ON_STACK_dest_, &CHANGE_CASE_ON_STACK_dest_len_); \
    strncpy((buf), CHANGE_CASE_ON_STACK_dest_, sizeof(buf) - 1); \
    (buf)[sizeof(buf) - 1]  = 0; \
    free(CHANGE_CASE_ON_STACK_dest_); \
}

#define UTF_TO_UPPER_ON_STACK(buf) CHANGE_CASE_ON_STACK(buf, utf_toupper_ext)
#define UTF_TO_LOWER_ON_STACK(buf) CHANGE_CASE_ON_STACK(buf, utf_tolower_ext)

#define CHANGE_CASE_ON_HEAP(buf, f) { \
    char* CHANGE_CASE_ON_HEAP_dest_ = NULL; \
    int CHANGE_CASE_ON_HEAP_dest_len_ = 0; \
    int res = f((buf), -1, &CHANGE_CASE_ON_HEAP_dest_, &CHANGE_CASE_ON_HEAP_dest_len_); \
    if (res >= 0) { \
        free(buf); \
        (buf) = CHANGE_CASE_ON_HEAP_dest_; \
    } \
}

#define UTF_TO_UPPER_ON_HEAP(buf) CHANGE_CASE_ON_HEAP(buf, utf_toupper_ext)
#define UTF_TO_LOWER_ON_HEAP(buf) CHANGE_CASE_ON_HEAP(buf, utf_tolower_ext)

void md5sum(const unsigned char *data, int len, unsigned char *digest);
int base64_encode(const unsigned char *in, int len, char *out);
int base64_decode(const char *in, unsigned char *out, int len);
int copy_file(const char *src, const char *dst);
int move_file(const char *src, const char *dst);
int copy_file_with_af(const char *src, const char *dst);
int move_file_with_af(const char *src, const char *dst);
int unlink_file_with_af(const char *name);
int recurse_action(const char *path, iv_recurser proc, void *data, int creative, int this_too);
void LeaveInkViewMain();
int IsInRect(int x, int y, const irect * rect);
void MD5PartFile(const char *src, unsigned char *r);
unsigned int crc32hash(const char *buf, unsigned int len);
int FastBookHash(const char* filename, char * result, int result_size);
// dialog show on the screen

int GetDialogShow(); // 1 - dialog showing, 0 - dialog hidden.
void SetMenuFont(ifont *font); // font for menu (one time using), need to set every times when open menu.

/// Functionality to work with obreey sync service

#define IV_OSY_STATUS_TURNED_OFF 0
#define IV_OSY_STATUS_WRONG_LOGIN_PASSWORD 1
#define IV_OSY_STATUS_DOWNLOADING 2
#define IV_OSY_STATUS_PAUSED 3
#define IV_OSY_STATUS_IDLE 4
#define IV_OSY_STATUS_ERROR 5

/**
 * \brief Get status for obreey sync. If obreey sync is not available than status is 0
 */
int iv_get_obreey_status();

// Custom dialog // ->

typedef enum
{
	kBTInfo,
	kBTAttention,
	kBTWarning,
	kBTQuestion,
	kBTButton,
} eBubbleTypes;

typedef struct icustombubble_s
{
// bubble
	int type;
	irect bubble_pos;
	irect arrow_pos;
	ibitmap *arrow_bmp;
	ibitmap *icon_bmp;
// text	in bubble
	irect text_pos;
	ifont *font;
	char *text;
} icustombubble;

typedef struct icustomhero_s
{
	irect pos;
	char *name;
	ibitmap *hero_bmp;
	int max_bubbles;
	irect **bubbles;
} icustomhero;

typedef void (*iv_custombubbledraw)(icustombubble *bubble);
typedef void (*iv_customherodraw)(icustomhero *hero);

typedef struct icustomdialog_s
{
	int timeout;
	int bubble_count;
	icustombubble **bubbles;
	icustomhero *hero;
	iv_customherodraw hero_draw;
	iv_custombubbledraw bubble_draw;
	iv_dialoghandler cb_handler;
	int cancel_enable_;
} icustomdialog;

icustomdialog *CustomDialogCreate(eBubbleTypes info_bubble_type, const char *hero_name, int bubble_count);
void CustomDialogRender(icustomdialog *dialog);
void CustomDialogShow(icustomdialog *dialog);
void CustomDialogDestroy(icustomdialog *dialog);


// Custom dialog // <-

typedef enum proxy_type_e {
	http = 0,
	socks4,
	socks5
} proxy_type;

typedef char proxy_settings;

/*
 * Create proxy settings object, with params, what has got function;
 */
proxy_settings *create_proxy_object (proxy_type type, const char *host, int port, const char *user, const char *pass);

/*
 * Create the proxy_settings object in memory, which will be allocate
 * and copy from the proxy_settings object, which took in params, to this memory.
 * Return NULL if no free memory;
 */
proxy_settings *copy_proxy_object (proxy_settings *proxy);

/*
 * Free memory which was allocated under proxy object.
 */
void clean_proxy_object (proxy_settings **proxy);

/*
 * Delete proxy config file.
 */
void delete_proxy (void);

/*
 * Set global proxy settings
 */
int set_proxy(proxy_settings *proxy);

/*
 * Get current proxy settings.
 * Return NULL, when proxy was not setted or memory allocation error.
 */
proxy_settings *get_proxy (void);

/*
 * Function is the collector of network interface info.
 * The interface name that will be collected info transfer in interface value.
 * Returns is pointer to network_interface_info struct, which contain info about assigned interface.
 * May return NULL, if error occurred. If interface is NULL, then using eth0 by default.
 */
network_interface_info *GetNetInfo (const network_interface *interface);

/*
 * The purpose of func is to get current default gateway for assigned interface.
 * Func can return NULL pointer if error occured. In another case return pointer into
 * string that contain IPv4 numbers-and-dots notation. The result is malloced, and it should be cleared.
 */
network_interface *GetNetGateway (const network_interface *interface);

/*
 * The purpose of func is to get current IPv4 addresses, that resolving dns.
 * The results of func are network_interface_array, that contain quantity and array of ip addresses of DNS services
 * Can return NULL if error occurred. The array should be cleared by free after usage.
 */
network_interface_array *GetNetDNS (void);

/*
 * Get network signal quality for current connection.
 * Return -1 if interface has not been found or error has occurred,
 * otherwise - number of quality in range 0...5
 */
int GetNetSignalQuality (void);

/*
 * Returns current connection state
 */
NET_STATE GetNetState(void);

/*
 * Returns last connection error which are described NET_E* defines.
 * If connection is established that returns NET_OK.
 */
int GetLastNetConnectionError(void);

/*
 * Starts/stops network manager service.
 * It should be run before using network manager interface
 * @status: 1-on; 0-off;
 * Returns NET_OK if service has started/stopped without errors. Other case NET_E* error.
 */
int NetMgr(int status);
/*
 * Returns netmgr status; May return 0 or -1 if network manager is off.
 */
int NetMgrStatus(void);
/*
 * Update wifi poweroff timeout. It is used with configurator.
 */
int NetMgrPing(void);

/*
 * Returns list of currently known networks in old network config format.
 * @path saving config path.
 */
int GetNetList(const char *path);
/*
 * Adds network configured in old network config format.
 * ssid might be preset in string like \"name\" or hex format
 * key might be preset in string like \"key\" or wpa_passphrase format
 */
int NetAdd(const char *path);
/*
 * Deletes network from known
 */
int NetDelete(const char *path);
int NetDelete_by_ssid(const char *ssid);
/*
 * Selects to connect already known network.
 */
int NetSelect(const char *path);
/*
 * Selects to connect already known network.
 */
int NetSelect_by_ssid(const char *ssid);

#define iverror(x...) do { \
	extern char *program_invocation_name; \
	fprintf(stderr,"[%i : %s] (%s)",getpid(),program_invocation_name,__func__); \
	fprintf(stderr, x); \
} while(0);

/*
 * The enum of cover cache storages
 * for different readers or apps - different cache folders
 */
typedef enum COVERCACHE_STORAGES_e {
	CCS_NONE		= 0,
	CCS_ADOBE,
	CCS_FBREADER,
	CCS_DJVIEWER,
	CCS_MAXSTORAGE,
} COVERCACHE_STORAGES;

/*
 * Save source ibitmap in compressed form in specified storage for specified file.
 * File name of cached ibitmap consist of MD5PartFile from specified file and extension ".dat".
 * Function refresh cache map and remove old cache.
 */
int CoverCachePut(COVERCACHE_STORAGES storage, const char *file_path, ibitmap *bmp);

/*
 * Return uncompressed ibitmap from specified storage for specified file.
 */
ibitmap *CoverCacheGet(COVERCACHE_STORAGES storage, const char *file_path);

/*
 * Postpone timed poweroff to let device long-running background tasks
 */
int PostponeTimedPoweroff(void);

char *arc_filename(const char *name);

const char* get_partner_id(void);

int get_keylock();

int is_enough_free_space();

const char* get_file_extension(const char* filename);

int get_screen_dpi();


void DebugResourceBitmaps_trackBitmapCreation(const char* name, const ibitmap* bmp);
void DebugResourceBitmaps_trackBitmapDrawing(const ibitmap* bmp, int x, int y);
void DebugResourceBitmaps_generateReport(const char* filename);
void DebugResourceBitmaps_trackBitmapCopy( const ibitmap* from, const ibitmap* to);
ibitmap *CopyBitmapNoTrack(const ibitmap *bm);
int DebugResourceBitmaps_isEnabled();



#define HIGH_PRIORITY_JOB_OPEN_BOOK 1

int isHighPriorityJobRunning();
void startHighPriorityJob(int job_id, int timeout_sec); // Set high priority job status for timeout_sec
void finishHighPriorityJob(int job_id);


int haveDictionaryKeyboard();

#ifdef __cplusplus
}


#endif

#endif


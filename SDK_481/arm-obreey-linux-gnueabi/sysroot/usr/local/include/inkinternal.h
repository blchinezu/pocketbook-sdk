#ifndef INKINTERNAL_H #define INKINTERNAL_H

#include "inkview.h"
#include "inkplatform.h"

#ifndef EMULATOR
#include <dlfcn.h>
#include <sys/ioctl.h>
#include <linux/rtc.h>

#include <sys/socket.h>
#include <net/if.h>
#include <netinet/in.h>

#else
#endif

#ifdef __cplusplus
extern "C"
{
#endif

//#define IVDBG(x...) fprintf(stderr, x);
#define IVDBG(x...)

#define PBDRM_PDFREADER "pdfviewer.app"

#define MAXPATHLENGTH 1024
#define MAXEVENTS 64  //must be powers of 2
#define MAXDICTS 255

#define SLEEPDELAY 1500LL
#define EINKDELAY (HWC_A13 ? 350LL : 1500LL)

#define MAXVOL 36
#define MAXSHAREDEVENTS 128
#define MAXUIDATA 4096

#define WF_TYPE_GRAY       0
#define WF_TYPE_BW         1
#define WF_TYPE_OPTIMIZED  0xea
#define WF_TYPE_BWFORCED   0xeb
#define WF_TYPE_GU         0xec
#define WF_TYPE_GC         0xee
#define WF_TYPE_A2         0xef
#define WF_TYPE_A2IN       0xe6
#define WF_TYPE_A2OUT      0xe7
#define WF_TYPE_PARTIALHQ  0xe9
#define WF_TYPE_GL16       0xed
#define WF_TYPE_DU4        0xe5

#define EPDC_PIXELCHANGED 0x80000000
#define EPDC_GRAYSCALE    0x40000000
#define EPDC_COLLISION    0x20000000
#define EPDC_FULL         0x10000000
#define EPDC_FORCELUT     0x08000000
#define EPDC_LOGO         0x04000000
#define EPDC_PARTIALHQ    0x02000000

#define SHOWCLOCK_ONTURN 0
#define SHOWCLOCK_NOHIDE 1
#define SHOWCLOCK_ALWAYS 2
#define SHOWCLOCK_OFF 3

#define USBSTATE_ONLINE   1
#define USBSTATE_PCLINK   2
#define USBSTATE_MOUNTED  4
#define USBSTATE_EJECT    8
#define USBSTATE_CHARGING 16
#define USBSTATE_USBNET   32

#define PWRACT_LAST 0
#define PWRACT_LOCK 1
#define PWRACT_MMNU 2
#define PWRACT_EXIT 3
#define PWRACT_SCRN 4
#define PWRACT_PROF 5
#define PWRACT_SPWR 6
#define PWRACT_MP3O 7
#define PWRACT_BTSW 8
#define PWRACT_TASK 9
#define PWRACT_DRPC 29
#define PWRACT_STTY 30
#define PWRACT_NONE 31

#define IN_PLAYER 1
#define IN_LASTOPEN 2
#define IN_DIALOG 4
#define IN_MENU 8
#define IN_KEYBOARD 16
#define IN_QNAVIGATOR 32
#define NO_HOURGLASS 64
#define NO_DISPLAY 128
#define IS_EXTERNAL 512
#define COVER_FRAME 1024

#define UIQ_NONE           0
#define UIQ_MESSAGE        1
#define UIQ_DIALOG         2
#define UIQ_EVENT          3
#define UIQ_TEXTENTRY      4
#define UIQ_PROGRESSBAR    5
#define UIQ_NPROGRESSBAR   6
#define UIQ_UPDATE         7
#define UIQ_EVENT_MAIN     8
#define UIQ_DISMISS      127

#define UIQ_IDLE           0
#define UIQ_PENDING        1
#define UIQ_PROCESSING     2
#define UIQ_OK             3
#define UIQ_CANCEL         4

#define UPD_RESULT_NONE        0
#define UPD_RESULT_QUERY       5
#define UPD_RESULT_FAIL       10
#define UPD_RESULT_CANCELED   11
#define UPD_RESULT_NOIMAGE    12
#define UPD_RESULT_CORRUPTED  13
#define UPD_RESULT_POWERLOW   14
#define UPD_RESULT_WRONGMODEL 15
#define UPD_RESULT_OK         99

#define RECT_ROUND_TL	(1 << 0)
#define RECT_ROUND_TR	(1 << 1)
#define RECT_ROUND_LL	(1 << 2)
#define RECT_ROUND_LR	(1 << 3)

#define INKFLAG_SW_16GRAYS     0x01
#define INKFLAG_3BIT_WAVEFORM  0x02
#define INKFLAG_A2PLUS         0x04

typedef enum EPARTNER_ID {
    PARTNER_INVALID = -1,
    PARTNER_DEFAULT = 0,
    PARTNER_TITELIVE,
    PARTNER_OSIANDER,
    PARTNER_MAYERSCHE,
    PARTNER_IBS,
    PARTNER_LEGALO,
    PARTNER_TEA,
    PARTNER_ALZA,
    PARTNER_EBOOKIT,
    PARTNER_EMPIK,
    PARTNER_APOLLO,
    PARTNER_MENCA,
    PARTNER_LIBRONET,
    PARTNER_UMBREIT
} PARTNER_ID;

//#define DEEPSLEEPTIME 600000LL
#define DEEPSLEEPTIME 300000LL
#define BATTERYCHECKTIME 7200000LL
#define MINSUSPENDTIME (5000LL)

#define A13_SLEEP_REFRESH_TIME 300000LL // 5 minutes

#define DEVICEID_LEN        32    

#define SN_ORSIO "92457"

#define C24TO8(c) (((((c) >> 16) & 255) * 77 + (((c) >> 8) & 255) * 151 + ((c) & 255) * 28) >> 8)

#define ISLTRALPHA(c)  (((c) >= 0x41 && (c) <= 0x5a)     || \
            ((c) >= 0x61 && (c) <= 0x7a)     || \
            ((c) >= 0xc0 && (c) <= 0x2b8)    || \
            ((c) >= 0x386 && (c) <= 0x587))

#define ISRTLALPHA(c)  (((c) >= 0x591 && (c) <= 0x6ff)   || \
            ((c) >= 0xfb1d && (c) <= 0xfdff) || \
            ((c) >= 0xfe70 && (c) <= 0xfefc))

#define ISRTLPUNCT(c)  (((c) >= 0x20 && (c) <= 0x2f)     || \
            ((c) >= 0x3a && (c) <= 0x3f)     || \
            ((c) >= 0xa1 && (c) <= 0xbf)     || \
            ((c) >= 0x2010 && (c) <= 0x2046))

#define ISRTLDIGIT(c) (((c) >= '0' && (c) <= '9') || ((c) == '%'))

#define DEFAULT_3G_CONNECTION_NAME "@Default_3G_conn"

#if ! (defined(EMULATOR) || defined(IVSAPP))
#define MULTITASKING (ivmpc->vid == 0x544d)
#define ISACTIVETASK ((!MULTITASKING) || ivmpc->activetask == ivstate.taskid)
#else
#define MULTITASKING 0
#define ISACTIVETASK 1
#endif

#define TASKMQADDR(t) (0x7a000000 | (t))

typedef struct iv_netcookie_s {

    int enumid;
    char *name;
    char *value;
    char *domain;
    char *path;
    int name_len;
    int value_len;
    int domain_len;
    int path_len;

} iv_netcookie;

typedef struct iv_scroll_s {
    int window_x;
    int window_y;
    int window_w;
    int window_h;
    int content_x;
    int content_y;
    int content_h;
    int content_w;
//	int current_pos;
//	int count_elements;
//	int count_elements_on_page;
//	int percet_present_element;
} scroll_s;

typedef struct iv_glyph_s {

    unsigned short chr;
    short left;
    short top;
    unsigned char width;
    unsigned char height;
    unsigned char data[0];

} iv_glyph;

typedef struct iv_state_s {

    int isopen;
    char *theme;
    char *lang;
    char *kbdlang;
    unsigned char pwract1;
    unsigned char pwract2;
    unsigned char timeformat;
    unsigned char gsense;
    unsigned char showclock;
    unsigned char _reserved1;
    unsigned char keylock;
    unsigned char demo;
    unsigned char antialiasing;
    unsigned char uiquery;
        unsigned char canbedefaultfont;
    unsigned char _reserved3;

    pid_t pid;
    iv_handler hproc;
    iv_handler mainhproc;

    icanvas *framebuffer;
    icanvas *canvas;
    int orientation;

    iconfig *cfg;
    FT_Library ftlibrary;
    ihash *fonthash;
    ifont *current_font;
    FT_Face current_face;
    int current_color;
    int current_aa;
    unsigned char **cw_cache;
    unsigned short **kerning_cache;
    iv_glyph **glyph_cache;

    char *font;
    char *fontb;
    char *fonti;
    char *fontbi;

    int keylocktm;
    int powerofftm;
    int allowkeyup;
    int currentkey;
    int keyrepeats;
    int initialized;
    volatile sig_atomic_t exiting;
    int usbmode;
    int uiflags;
    int taskid;
    int needupdate;
    int poweroffenable;
    int sleepenable;
    long long waketime;
    long long sleeptime;
    long long measuretime;

    itimer *timers;
    int ntimers;

    ievent *events;
    int evtstart;
    int evtend;

    int keytime1;
    int keytime2;
    int msgtop;

    int ptrx;
    int ptry;

    ifont **fontlist;
    int fontcount;

    struct {
        int raw;
        int a;
        int b;
        int c;
        int d;
        int e;
        int f;
        int nx;
        int ny;
    } tsc[MAX_INPUT_DEV];

    FT_Face current_zface;
    unsigned int touchdragdeadzone;
    int panel_position;  //0 - bottom, 1  - top
    time_t adjtime_ts;
    char *locale;
} iv_state;

typedef struct iv_caches_s {

    int size;
    int refs;
    unsigned char **cw_cache;
    unsigned short **kerning_cache;
    iv_glyph **glyph_cache_aa;
    iv_glyph **glyph_cache_noaa;

} iv_caches;

typedef struct iv_fontdata_s {

    int refs;
    FT_Face face;
    FT_Face zface;
    int nglyphs;
    int nsizes;
    iv_caches *caches;

} iv_fontdata;

typedef struct iv_uiqrecord_s {

    int type;
    int icon;
    char *title;
    char *text;
    char *button1;
    char *button2;
    int maxsize;
    int flags;
    int timeout;
    int percent;
    int evtype;
    int evpar1;
    int evpar2;
    int reserved_01;
    int reserved_02;
    int reserved_03;
    int reserved_04;
    int reserved_05;

} iv_uiqrecord;

typedef struct iv_event_s {

    int type;
    int mod;
    int par1;
    int par2;

} iv_event;

/*
 * EVT_EVENTS ver.II
 * The first bit of event field is determined that using event type II
 */

typedef struct hw_event_data_common_s {
	int mod;
	int par1;
	int par2;
} hw_event_data_common;

//EVT_POINTERUP, EVT_POINTERDOWN, EVT_POINTERMOVE
typedef struct hw_event_data_pointer_s {
	int id;
	int x;
	int y;
	int pressure;
	enum input_dev_e devtype;
} hw_event_data_pointer;

typedef struct hw_event_s {
	int type;
	union {
		hw_event_data_common common;
		hw_event_data_pointer pointer;
	};
    struct timeval time;
} hw_event;

typedef struct iv_mpctl_s {

    unsigned char reserved0;
    unsigned char poweroff;
    unsigned char lockdisplay;
    unsigned char capstate;
    unsigned char sdstate;
    unsigned char wakeup;
    unsigned char safe_mode;
    unsigned char inkflags;
    unsigned char orientation;
    unsigned char keylock;
    unsigned char usbstate;
    unsigned char umoverride;

    pid_t watchpid;
    pid_t mainpid;
    pid_t apppid;
    pid_t mppid;
    pid_t nagtpid;
    int activetask;
    int activesubtask;

    int power;
    int pkey;
    int vid;

    PB_STATE state;
    short mode;
    short track;
    PB_TTS_STATE tts_state;
    short scanning_state;
    short adobe_scanning_state;
    short text_recognition_flag;
    short reserved_9;

    int tracksize;
    int position;
    int newposition;

    short volume;
    short equalizer[32];
    short filter_changed;
    short reserved_0c;

    unsigned char btready;
    unsigned char wifiready;
    unsigned char cdma3gready;
    unsigned char connected;
    unsigned char rfcomm;
    unsigned char netscan;
    unsigned char reserved_0d;
    unsigned char reserved_0e;
    unsigned char reserved_0f;

    char netname[64];
    char netdevice[16];
    char netsecurity[16];
    char netprefix[16];
    int con_index;
    int con_time;
    int con_speed;
    int net_signal_quality;

    NET_STATE netstate;
    int last_connection_error;

    unsigned long bytes_in;
    unsigned long bytes_out;
    unsigned long packets_in;
    unsigned long packets_out;

    unsigned long net_timeout;
    unsigned long reserved_11;
    unsigned long reserved_12;
    unsigned long reserved_13;

    unsigned long keymask;
    unsigned long lastactivity;
    unsigned long gka0;
    unsigned long gka1;

    int evtsize;
    int evthead;
    int evttail;
    hw_event evt[MAXSHAREDEVENTS+1];
    int uisequence;
    int uiquery;
    int uistatus;
    unsigned int uidata[MAXUIDATA];

	int obreey_sync_status;
	int messages_count; // Number of new messages to show on panel
	int dialog_h[16];   // heights of dialog windows
	int headphone_status;
	int frontlight_state;
	int frontlight_slider;
	int books_db_changes;
	time_t adjtime_mono;
    int unsafe_volume_timer;
    int lux_auto;
    int lux_bright[101];
    int frontlight_auto;

	struct {
		int numframes;
		int fps;
		int x;
		int y;
	} hourglass;

	pid_t bstask;
	pid_t exptask;
	pid_t mgrtask;
	pid_t scannertask;
	pid_t obreeypid;
	pid_t obreey_social_pid;
	pid_t usage_stat_pid;
	pid_t dropbox_pid;
	pid_t demoviewerpid;
	pid_t send_to_pb_pid;
	pid_t control_panel_pid;
	pid_t menca_pid;
    pid_t push_notification_pid;

} iv_mpctl;

typedef struct eink_cmd_s {

    int owner;
    int command;
    int nwrite;
    int nread;
    unsigned char data[0];

} eink_cmd;

typedef struct eink_updateinfo_s {
    int x;
    int y;
    int w;
    int h;
    int bw;
} eink_updateinfo;

typedef struct upd_status_s {

    unsigned long action_timestamp;
    char version[16];
    unsigned long sw_timestamp;
    unsigned long sw_info1;
    unsigned long sw_info2;
    unsigned long sw_info3;
    unsigned char source;
    unsigned char unused;
    unsigned char result;
    unsigned char commit;

} upd_status_record;

struct id2code_s {
    unsigned idx;
    unsigned code;
};

struct iv_img_conv {
    void *src;
    void *dest;
    int width;
    int height;
    int src_scanline;
    int dest_scanline;
};
 
typedef struct cookie_node_s {
    iv_netcookie * cookie;
    struct cookie_node_s * next;
} cookie_node;

static const struct id2code_s id2code_nx611[] = {
        {0x1c,0x00020},
        {0x67,0x00400},
        {0x6c,0x00200},
        {0x69,0x00004},
        {0x6a,0x00040},
        {0x3d,0x00800},
        {0x3e,0x01000},
        {0,0}, //terminating entry
};

//temporary keycode for alpha3 kernel release
static const struct id2code_s id2code_fc622[] = {
        {0x01,0x10000},//home
        {0x02,0x00800},//prev
        {0x03,0x01000},//next
        {0x04,0x00008},//menu
        {0x05,0x04000},//power
        {0,0}, //terminating entry
};

static const struct id2code_s id2code_fc650[] = {
        {102,0x10000},//home
        {105,0x01000},//prev
        {106,0x00800},//next
        {139,0x00008},//menu
        {116,0x04000},//power
        {108,0x02000},//next2
        {103,0x08000},//prev2
        {152,0x1000000},//cover
        {0,0}, //terminating entry
};

static const struct id2code_s id2code_lni633[] = {
        {0x71,0x10000},//home
        {0x73,0x00800},//prev
        {0x72,0x01000},//next
        {0x70,0x00008},//menu
        {0x7d,0x04000},//power
        {0x7f,0x800000},//power key have 2 events - shot & long
        {0,0}, //terminating entry
};

static const struct id2code_s id2code_624[] = {
        { 108,0x10000},//home
        { 102,0x00800},//prev
        { 158,0x01000},//next
        {  28,0x00008},//menu
        { 116,0x04000},//power
        {0,0}, //terminating entry
};

static const struct id2code_s id2code_420[] = {
        { 102,0x00800},//prev
        { 158,0x01000},//next
        { 116,0x04000},//power
        {0,0}, //terminating entry
};

static const struct id2code_s id2code_515[] = {
        { 102,0x00800},//prev
        { 158,0x01000},//next
        {  28,0x00020},//ok
        { 103,0x00400},//up
        { 108,0x00200},//down
        { 105,0x00004},//left
        { 106,0x00040},//right
        { 116,0x04000},//power
        {0,0}, //terminating entry
};

static const struct id2code_s id2code_630[] = {
        {  28, 0x00800}, //prev
        { 158, 0x01000}, //next
        { 116, 0x04000},//power
        {0,0}, //terminating entry
};

static const struct id2code_s id2code_fc613[] = {
        {0x1,0x00020},//ok
        {0x4,0x00400},//up
        {0x5,0x00200},//down
        {0x3,0x00004},//left
        {0x2,0x00040},//right
        {0x7,0x00800},//prev
        {0x6,0x01000},//next
        {0x8,0x04000},//power
        {0, 0} // terminating
};

static const struct id2code_s id2code_840[] = {
        { 158,0x01000},//prev
        {  28,0x00800},//next
        { 116,0x04000},//power
        {0,0}, //terminating entry
};

extern iv_mtinfo mtinfo[5];
extern iv_state ivstate;
extern iv_mpctl *ivmpc;
extern iv_fbinfo *fbinfo;

extern ifont *title_font, *window_font, *header_font, *menu_s_font, *menu_n_font;
extern ifont *butt_n_font, *butt_s_font;
extern int window_color, header_color, menu_n_color, menu_s_color, menu_d_color;
extern int butt_n_color, butt_s_color;
extern ibitmap *button_normal, *button_selected;
extern ibitmap *button_back, *button_prev, *button_next;
extern int title_style, title_height;
extern iapp_caption *app_caption;
extern itaskmgr *taskmgr;

extern ibitmap def_icon_question, def_icon_information, def_icon_warning, def_icon_error;
extern ibitmap def_fileicon, def_folder;
extern ibitmap def_hourglass, def_lock;
extern ibitmap def_button_normal, def_button_selected;
extern ibitmap def_pageentry;
extern ibitmap def_bmk_panel, def_bmk_active, def_bmk_inactive, def_bmk_actnew;
extern ibitmap def_tab_panel, def_tab_active, def_tab_inactive;
extern ibitmap def_leaf_open, def_leaf_closed;
extern ibitmap def_battery_0, def_battery_1, def_battery_2, def_battery_3, def_battery_4;
extern ibitmap def_battery_5, def_battery_c, def_battery_u;
extern ibitmap def_button_back, def_button_prev, def_button_next;
extern ibitmap def_progress_left, def_progress_right, def_progress_empty, def_progress_filled;
extern ibitmap def_tsk_arrow, def_tsk_arrow_a, def_tsk_clr, def_tsk_clr_a, def_tsk_bs, def_tsk_bs_a;
extern ibitmap def_tsk_enter, def_tsk_enter_a, def_tsk_can, def_tsk_can_a, def_tsk_123, def_tsk_123_a;
extern ibitmap keyboard_arrow, keyboard_bs, keyboard_eye;
extern ibitmap keyboard_word_left, keyboard_word_center, keyboard_word_right, keyboard_marker;
extern ibitmap keyboard_close_bg, keyboard_close_button, keyboard_area_filler, keyboard_foot_center;
extern ibitmap keyboard_button_center, keyboard_button_center_a, keyboard_button_sep;
extern ibitmap keyboard_search, keyboard_comment;
extern ibitmap def_qi_btsw, def_qi_lock, def_qi_mmnu, def_qi_mp3o, def_qi_scrn, def_qi_spwr;
extern ibitmap def_p_book, def_p_loading;
extern ibitmap def_playing, def_usbinfo, def_gprsinfo, def_wifiinfo, def_cdma3ginfo, def_usbex;
extern ibitmap def_bluetooth, def_a2dpheadset, def_tasklist;
extern ibitmap def_frame_selector_bl_5px, def_frame_selector_br_5px;
extern ibitmap def_frame_topleft, def_frame_top, def_frame_topright, def_header_topleft, def_header_top;
extern ibitmap def_header_topleft_overlap, def_header_topright_overlap;
extern ibitmap def_frame_topleft_overlap, def_frame_topright_overlap;
extern ibitmap def_header_topright, def_frame_left, def_frame_right, def_frame_bottomleft;
extern ibitmap def_frame_bottom, def_frame_bottomright;
extern ibitmap def_button_moveup, def_button_movedown, def_button_close;
extern ibitmap def_button_moveup_a, def_button_movedown_a, def_button_close_a;
extern ibitmap def_dic_toolbar, def_dic_wordlist, def_dic_voice, def_dic_keybd, def_dic_switch;
extern ibitmap def_dic_dots, def_dic_wordbg, def_dic_error, def_dic_close, def_dic_area, def_dic_hdivider;
extern ibitmap def_dic_translate;
extern ibitmap swupdate_bm;
extern ibitmap obreey_sync_wrong_settings, obreey_sync_error, obreey_sync_idle, obreey_sync_downloading,
       obreey_sync_paused;

int hw_init();

int hw_io_init();
int hw_eink_init();
int hw_gsensor_init();
int hw_touchpanel_init();
int hw_captouch_init();
void hw_close();
void hw_io_close();
void hw_eink_close();
void hw_gsensor_close();
void hw_touchpanel_close();
void hw_captouch_close();
int hw_safemode();
int hw_einkversion();
void hw_displaysize(int *w, int *h);
void hw_set_fb_orientation(icanvas *fb, int n);
int hw_update_fb_orientation(icanvas *fb);
int hw_ioctl(int cmd, void *data);
icanvas *hw_getframebuffer();
int hw_depth();
int hw_depth_hq();
int hw_update(int x, int y, int w, int h, int bw);
unsigned long do_partial_update(int x, int y, int w, int h, int bw, int dynamic);
void hw_fullupdate();
void hw_fullupdate_hq();
void hw_refine16();
int hw_capable16();
void hw_switch_dynamic(int n);
void hw_override_update(int mode);
void hw_suspend_display();
void hw_resume_display();
void hw_restore_screen(int deep);
void hw_wait_luts_complete();
int hw_useraction();
int hw_keystate(int key);
int hw_nextevent(hw_event *);
int hw_nextevent_mon(hw_event *);
int hw_nextevent_key(int *type, int *mod, int *par1, int *par2);
int hw_nextevent_ts(int *type, int *mod, int *par1, int *par2);
int hw_nextevent_cap(int *type, int *mod, int *par1, int *par2);
int hw_nextevent_extkb(int *type, int *mod, int *par1, int *par2);
int hw_ts_active();
int hw_captouch_active();
int hw_isplaying();
int hw_isttsplaying();
int hw_isscanning();
int hw_isadobescanning();
int hw_ischarging();
int hw_isusbconnected();
int hw_isusbhostconnected();
int hw_isusbstorattached();
int hw_isusbmounted();
int hw_issdinserted();
const char *hw_external_card_serial_number(void);
void hw_usbhostpower(int n);
int hw_power();
int hw_temperature();
int hw_sleep(int ms, int deep);
time_t hw_gettime();
long long hw_timeinms();
void hw_setalarm(int ms);
void hw_say_poweroff();
int hw_shutting_down();
void hw_registerapp(pid_t pid);
int hw_read_file(const char *name, char *buf, int size);
int hw_write_file(const char *name, const char *buf, int size);
char *hw_serialnumber();
char *hw_password();
unsigned int hw_pkey();
int hw_get_device_id(char *buffer, size_t buflen);
char *hw_waveform_filename();
char *hw_getmodel();
char *hw_getplatform();
char *hw_getmac();
char *hw_getbtmac();
char *hw_get3gimei();
int hw_geta2dpstatus(void);
int hw_writelogo(const ibitmap *bm, int permanent);
int hw_restorelogo();
int hw_usbready();
void hw_usblink();
void hw_set_keylock(int en);
int hw_get_keylock();
void hw_setglobalkeymask(long gka0, long gka1);
int hw_touchpanel_ready();
int hw_gsensor_ready();
int hw_read_gsensor(int *x, int *y, int *z, int raw);
int hw_last_orientation();
void hw_set_gsensor(int mode);
void hw_suspend_gsensor();
void hw_resume_gsensor();
unsigned char *hw_calibrate_gsensor();
void hw_adjust_gsensor(unsigned char *data);
int hw_captouch_ready();
int hw_read_captouch();
int hw_flash_mounted();
int has_secure_storage();
void hw_winmessage(char *title, char *text, int flags);
int iv_check_pointerscroll(int type, int par1, int par2);

int hw_iicreadb(int addr, int reg, int count, char *data);
int hw_iicwriteb(int addr, int reg, int count, char *data);
int hw_iicreadw(int addr, int reg, int count, short *data);
int hw_iicwritew(int addr, int reg, int count, short *data);

long hw_ipcrequest_to(int mq, long type, long param, void *data, int inlen, int outlen, int timeout);
long hw_ipcrequest(long type, long param, void *data, int inlen, int outlen, int timeout);
long hw_ipcrequest_secure(long type, long param, void *data, int inlen, int outlen, int timeout);
long hw_ipcreply(long addr, long type, long param, void *data, int len);
int  hw_ipcread(int addr, int *replyaddr, int *type, int *param, void *data, int size);


//==============
int hw_wifi_scan_process_start(void);
void hw_wifi_scan_process_set_selective_list(iv_wifi_ap_list *);
iv_wifi_ap_list *hw_wifi_scan_process_get_results(void);
int hw_wifi_scan_process_stop(void);
//==============
int hw_check_net_dev_working(void);
iv_wifi_ap_list * hw_wifi_scan(iv_wifi_ap_list * ap_list);

int hw_querynetwork();
int hw_btcontrol(int mode, int flags);

//check bt module status
int hw_btstatus();

//check wifi module status (on is 1; off is 0)
int hw_wifi_status();

//check cdmi3g module status (on is 1; off is 0)
int hw_cdma3g_status();

int hw_hidstatus(void);
char **hw_enum_btdevices();
char **hw_enum_wireless();
int hw_get_btservice(const char *mac, const char *service);
int hw_net_connect(const char *name, int silent); // silent to suppress screen output
int hw_net_disconnect();
iv_netinfo *hw_net_info();
void hw_uiclear();
int hw_uiquery();
void hw_uiresponse(int status, char *data);

void hw_mp_loadplaylist(char **pl);
char **hw_mp_getplaylist();
void hw_mp_playtrack(int n);
int hw_mp_currenttrack();
int hw_mp_tracksize();
void hw_mp_settrackposition(int pos);
int hw_mp_trackposition();
void hw_mp_setstate(int state);
int hw_mp_getstate();
void hw_mp_setmode(int mode);
int hw_mp_getmode();
void hw_mp_setvolume(int n);
int hw_mp_getvolume();
void hw_mp_setequalizer(int *eq);
void hw_mp_getequalizer(int *eq);
void iv_check_player_state_change();

void *hw_task_checkmessages(int *replyaddr, int *type, int *param, int *size);
int hw_task_register(char *appname, char *name, ibitmap *icon, unsigned int flags);
int hw_task_newsubtask(char *name);
int hw_task_switchsubtask(int subtask);
void hw_task_subtaskfinished(int subtask);
int hw_task_current();
int hw_task_list(int *list, int size);
int hw_task_previous(int *task, int *subtask);
int hw_task_previous_instack(int *task, int *subtask);
taskinfo *hw_task_info(int task);
int hw_task_findbybook(char *name, int *task, int *subtask);
int hw_task_findbyappname(char *name);
int hw_task_setparameters(int task, char *appname, char *name, ibitmap *icon, unsigned int flags);
int hw_task_setsubtaskinfo(int task, int subtask, char *name, char *book);
int hw_task_foreground(int task, int subtask);
void hw_task_background();
void hw_task_close(int task, int subtask, int force);
int hw_task_sendevent(int task, int hdest, int type, int par1, int par2);
int hw_task_sendevent_sync(int task, int hdest, int type, int par1, int par2);
int hw_task_message(int task, void *message, int len);
int hw_task_sendrequest(int task, int req, void *data, int inlen, int outlen, int timeout);
int hw_task_setrequestlistener(int req, int flags);
int hw_task_inrequest();
icanvas *hw_gettaskfb(taskinfo *ti);
iv_fbinfo *hw_gettaskfbinfo(taskinfo *ti);
void hw_releasetaskfb(icanvas *fb);

int hw_get_frontlight_state(void);
void hw_set_frontlight_state(int flstate, int previous);

void iv_extend_wtime(long long t);
iv_handler iv_seteventhandler(iv_handler hproc);
iv_handler iv_restoreeventhandler(iv_handler hproc, int keytm1, int keytm2);
void iv_enqueue(iv_handler hproc, int type, int par1, int par2);
long long iv_get_first_timer();
void iv_process_timers();
char **iv_enum_files(char ***list, char *path1, char *path2, char *path3, char *extension, int dropext);
int iv_enum_dictionaries(char ***p_dlist, char ***p_fnlist, int onlysystem, int showhidden);
void iv_drawsymbol(int x, int y, int size, int symbol, int color);
irect *iv_windowframe(int x, int y, int w, int h, int bordercolor, int windowcolor, char *title, int button);
void iv_scrollbar(int x, int y, int w, int h, int percent);
int iv_textblock(int x, int y, int w, unsigned short *p, int len, int color, int angle, int rtlbase);
void iv_stretch(const unsigned char *src, int format, int sx, int sy, int sw, int sh, int srclw,
        int dx, int dy, int dw, int dh, int flags, const unsigned char *mask, int masklw);
void iv_area(int dstx, int dsty, int width, int height,
        unsigned char *pixels, int srclw,
        unsigned char *mask, int masklw,
        int srcx, int srcy, int depth);
void iv_draw_hourglass_frame(int x, int y, int frame, int pure);
int iv_msgtop();
void iv_timechanged();
void def_openplayer();
bookinfo *def_getbookinfo(const char *path);
ibitmap *def_getbookcover(const char *path, int width, int height);
int iv_player_handler(int type, int par1, int par2);
void iv_setsoftupdate();
void iv_actualize_panel(int update);
void iv_update_panel(int with_time);
int iv_panelevent(int x, int y, int *type, int *par1, int *par2);
void iv_update_orientation(int isexternal);
void iv_check_gsensor();
int iv_transform_key(int key);
void iv_keyswitch_rtl(int *par);
void iv_getkeymapping(int what, char *act0[], char *act1[], int count);
void iv_getglobalkeymapping(char *act0[], char *act1[], int count);
void iv_rise_poweroff_timer();
void iv_key_timer();
void iv_poweroff_timer();
void iv_panelupdate_timer();
void iv_exit_actions();
void iv_exit_handler();
void iv_setup_touchpanel();
void hw_ts_default(int *a, int *b, int *c, int *d, int *e, int *f, int *nx, int *ny);
int iv_transform_pointer(hw_event *);
void iv_setup_gsensor();
char *iv_shortpower_action(int times);
int iv_init_profiles();
int iv_use_profiles(int nocache);
int iv_switch_profile(const char *name);
void iv_check_profile();
void iv_invertitem(int x, int y, int w, int h, int d);
void iv_check_uiquery();
void iv_hintmsg(int x, int y, const char *s, ...);
void global_key_action(char *name);
int iv_qn_handleevent(int type, int par1, int par2);
int iv_check_task_messages();
void iv_foreground_event();
void iv_background_event();
void iv_openmainmenu();
void iv_openlastbooks();
void iv_opencalendar();
void iv_openplayer();
void iv_toggleplaying();
void iv_pause();
void iv_volumeup();
void iv_volumedown();
int iv_panel_used();
void init_partner();
void hw_clear_last_update_time(void);
long long hw_get_last_update_time(void);

int pager_height();
int check_rtlbase(unsigned short *p, int len);
unsigned short *rtl_convert_l(unsigned short *s, int len, unsigned short **pos, int *back);
unsigned short *rtl_convert_r(unsigned short *s, int len);
void arabic_shape(unsigned short *buffer, int len, int tashkeel);
unsigned short *arabic_shape_copy(unsigned short *dest, int sourceLength, int tashkeelFlag);

/*
 * function is obsolete, use GetCookies instead
 * may give not full data
 */
int EnumCookie(iv_netcookie *cookie_rec);

/*
 * function is used in pair with EnumCookie wich is obsolete
 */
void EnumCookieFree(iv_netcookie *cookie_rec);

/*
 * Returnes cookie_node chain
 */
const cookie_node * GetCookies();

// encrypt and decrypt data with device specific key
// returns length of output buffer or -1 if error happened
// buffer should be freed by caller
// output buffer larger than input buffer
int EncryptMem(const void *indata, size_t inlength, unsigned char **outdata);
int DecryptMem(const void *indata, size_t inlength, unsigned char **outdata);


/**
 * \brief Set status for obreey sync. Status become available for other processes through iv_get_obreey_status
 * \param new_status status to set. Should be one of the value defined through IV_OSY_STATUS_*
 * Function is not thread safe
 */
void iv_set_obreey_status(int new_status);

/*
 * Function is the collector of network interface info.
 * The interface name that will be collected info transfer in interface value.
 * Returns is pointer to network_interface_info struct, which contain info about assigned interface.
 * May return NULL, if error occurred. If interface is NULL, then using eth0 by default.
 */
network_interface_info *hw_get_network_interface_info (const network_interface *interface);

/*
 * The purpose of func is to get current default gateway for assigned interface.
 * Func can return NULL pointer if error occured. In another case return pointer into
 * string that contain IPv4 numbers-and-dots notation. The result is malloced, and it should be cleared.
 */
network_interface *hw_get_net_gateway_info (const network_interface *interface);

/*
 * The purpose of func is to get current IPv4 addresses, that resolving dns.
 * The results of func are network_interface_array, they contain quantity and array of ip addresses of DNS services
 * Can return NULL if error occurred. The array should be cleared by free after usage.
 */
network_interface_array *hw_get_net_dns_info (void);

/*
 * Get network signal quality for current connection.
 * Return -1 if interface has not been found or error has occurred,
 * otherwise - number of quality in range 0...5
 */
int hw_get_net_signal_quality(void);

/*
 * Returns 128 bit ID that device unique and not known when device manufactured
 */
const char *GetDeviceID(void);

/*
 * Returns PARTNER_ID, no parnter is DEFAULT == 0
 */
PARTNER_ID GetCustomizedPartner(void);

/*
 * Signals to monitor task started and initialized
 */
void SignalTaskStarted(void);

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
 * Sets drag dead zone in square pixels (i.e. for 20 px drag zone pass 20*20=400 as argument)
 */
void SetTouchDragDeadZone(unsigned int squarepx);

/*
 * Gets drag dead zone in square pixels (i.e. for 20 px drag zone will return 20*20=400 like it was passed in SetTouchDragDeadZone)
 *   default value in TOUCHDRAGDEADZONE macro
 */
unsigned int GetTouchDragDeadZone(void);

ibitmap *bm_make(unsigned char *bmdata, int w, int h);
void bm_dither(unsigned char *data, int sx, int sy, int w, int h, int lw, int levels);

int hw_ussdquery(char *ussd, char **msg);

/*
 * Check if battery is full by using kernel information if supported or battery SOC if not
 */
int hw_is_battery_full(void);

/*
 * Extend time to sleep will be thrown off.
 */
void hw_force_to_sleep(void);


/*
 * Converts timeval structure to timems
 */
long long timeval2timems(struct timeval *time);

/*
 * Convert RGB565 image to 8-bit greyscale
 */
void iv_rgb565_to_gs(struct iv_img_conv *c);

/*
 * Convert RGB24 image to 8-bit greyscale
 */
void iv_rgb24_to_gs(struct iv_img_conv *c);

/*
 * Convert 4-bit image to 8-bit greyscale
 */
void iv_gs4_to_gs(struct iv_img_conv *c);

/*
 * Copy 8-bit greyscale image
 */
void iv_gs_to_gs(struct iv_img_conv *c);


#ifdef __cplusplus
}
#endif

#endif

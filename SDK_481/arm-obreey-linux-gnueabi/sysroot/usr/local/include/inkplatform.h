#ifndef INKPLATFORM_H
#define INKPLATFORM_H

#ifdef __cplusplus
extern "C"
{
#endif

/*

 [ 63 62 61 60 | 59 58 57 56 | 55 54 53 52 | 51 50 49 48 | 47 46 45 44 | 43 42 41 40 | 39 38 37 36 | 35 34 33 32 ]
 .             .  cdma/3g    .  captouch   .           * .    WiFi module     .  bluetooth module  . touchscreen .
 .             . 0=none      . 0=none      .           | .   0=none           . 0=none             . 0=none      .
 .             . 1=.....     . 1=AD7147/1  .           | .   1=WG7210         . 1=WG7210           . 1=S3C-resist.
 .             .             .             .           | .   2=GM9601         . 2=?                . 2=hanvon    .
 .             .             .             .           | .   3=BCM4329        . 3=BCM4329          . 3=cap (EP7) .
 .             .             .             .           | .   4=GB9619         .                    . 4=IR (LNI)  .
 .             .             .             .           | .   5=PW621-M        .                    .             .
 .             .             .             .           | .   11=rtl8189fs     .                    .             .
 .             .             .             .           | .                    .                    .             .
 .             .             .             .           `usb host              .                    .             .
 .             .             .             .             .                    .                    .             .

 [ 31 30 29 28 | 27 26 25 24 | 23 22 21 20 | 19 18 17 16 | 15 14 13 12 | 11 10  9  8 |  7  6  5  4 |  3  2  1  0 ]
 .  USB        .  audio      .  g-sensor   .  *+* .   keyboard         .  controller .  display    .  board type .
 . 0=none      . 0=none      . 0=none      .   |  .  0=6"ntx           . 0=PVI       . 0=6"600x800 . 0=EB100     .
 . 1=ISP1582   . 1=UDA1345   . 1=MMA7455/1 .   |  .  1=pb360/611/613   . 1=Epson/GP  . 1=5"600x800 . 1=EB600     .
 . 2=RTS5105   . 2=ALC5623   . 2=MMA7455/2 .   |  .  2=cookie          . 2=Epson/M   . 2=8"1024x768. 2=EB500     .
 . 3=internal  . 3=.....     . 3=?         .   |  .  3=9d7linear       . 3=iMX50x    . 3=9"1200x825. 3=COOKIE    .
 .             .             . 4=ADXL345/1 .   |  .  4=ep1234          .             .             . 6=iMX357    .
 .             .             . 5=ADXL345/2 .   |  .  5=ep7             .             .             . 7=EP1234    .
 .             .             . 6=MMA7660/1 .   |  .                    .             .             . 8=NX611     .
 .             .             .             .   |  .                    .             .             . 9=EP7(622)  .
 .             .             .             .   |  .                    .             .             . 10=LNI633   .
 .             .             .             .   |  .                    .             .             . 11=EP8(613) .
                                               `display orientation (1=topdown)

*/

extern unsigned long long hwconfig;
extern char hw_platform[];

#define HWCONFIG_DEFAULT 0x0000000021000000LL

#ifndef HWLIB
#include <hwconfig.h>
///#include <oldconfig.h>

extern int (*_device_platform)();
extern int (*_device_display)();
extern int (*_device_epdc)();
extern int (*_device_keyboard)();
extern int (*_device_display_position)();
extern int (*_device_gyroscope)();
extern int (*_device_audio)();
extern int (*_device_usb)();
extern int (*_device_touchpanel)();
extern int (*_device_bluetooth)();
extern int (*_device_wifi)();
extern int (*_device_has_usbhost)();
extern int (*_device_has_extcard)();
extern int (*_device_frontlight)();
extern int (*_device_lightsensor)();
extern int (*_device_gsm)();
extern int (*_device_slider)();

#define HWC_PLATFORM     (int)(*_device_platform)()
#define HWC_DISPLAY      (int)(*_device_display)()
#define HWC_CONTROLLER   (int)(*_device_epdc)()
#define HWC_KEYBOARD     (int)(*_device_keyboard)()
#define HWC_DPOS         (int)(*_device_display_position)()
#define HWC_GSENSOR      (int)(*_device_gyroscope)()
#define HWC_AUDIO        (int)(*_device_audio)()
#define HWC_USB          (int)(*_device_usb)()
#define HWC_TOUCHPANEL   (int)(*_device_touchpanel)()
#define HWC_BLUETOOTH    (int)(*_device_bluetooth)()
#define HWC_WIFI         (int)(*_device_wifi)()
#define HWC_USBHOST      (int)(*_device_has_usbhost)()
#define HWC_EXTCARD      (int)(*_device_has_extcard)()
#define HWC_FRONTLIGHT   (int)(*_device_frontlight)()
#define HWC_LIGHTSENSOR  (int)(*_device_lightsensor)()
#define HWC_CAPTOUCH     0
#define HWC_CDMA3G       (int)(*_device_gsm)()
#define HWC_SLIDER       (int)(*_device_slider)()
#else
#include <hwconfig.h>

#define HWC_PLATFORM     (int)device_platform()
#define HWC_DISPLAY      (int)device_display()
#define HWC_CONTROLLER   (int)device_epdc()
#define HWC_KEYBOARD     (int)device_keyboard()
#define HWC_DPOS         (int)device_display_position()
#define HWC_GSENSOR      (int)device_gyroscope()
#define HWC_AUDIO        (int)device_audio()
#define HWC_USB          (int)device_usb()
#define HWC_TOUCHPANEL   (int)device_touchpanel()
#define HWC_BLUETOOTH    (int)device_bluetooth()
#define HWC_WIFI         (int)device_wifi()
#define HWC_USBHOST      (int)device_has_usbhost()
#define HWC_EXTCARD      (int)device_has_extcard()
#define HWC_FRONTLIGHT   (int)device_frontlight()
#define HWC_LIGHTSENSOR  (int)device_lightsensor()
#define HWC_CAPTOUCH     0
#define HWC_CDMA3G       (int)device_gsm()
#define HWC_SLIDER       (int)device_slider()

//#define HWC_PLATFORM     ((int)(hwconfig & 15))
//#define HWC_DISPLAY      ((int)((hwconfig >> 4) & 15))
//#define HWC_CONTROLLER   ((int)((hwconfig >> 8) & 15))
//#define HWC_KEYBOARD     ((int)((hwconfig >> 12) & 31))
//#define HWC_DPOS         ((int)((hwconfig >> 18) & 3))
//#define HWC_GSENSOR      ((int)((hwconfig >> 20) & 15))
//#define HWC_AUDIO        ((int)((hwconfig >> 24) & 15))
//#define HWC_USB          ((int)((hwconfig >> 28) & 15))
//#define HWC_TOUCHPANEL   ((int)((hwconfig >> 32) & 15))
//#define HWC_BLUETOOTH    ((int)((hwconfig >> 36) & 63))
//#define HWC_WIFI         ((int)((hwconfig >> 42) & 63))
//#define HWC_USBHOST      ((int)((hwconfig >> 48) & 1))
//#define HWC_EXTCARD      ((int)((hwconfig >> 49) & 1))
//#define HWC_FRONTLIGHT   ((int)((hwconfig >> 50) & 1))
//#define HWC_LIGHTSENSOR  ((int)((hwconfig >> 51) & 1))
//#define HWC_CAPTOUCH     ((int)((hwconfig >> 52) & 15))
//#define HWC_CDMA3G       ((int)((hwconfig >> 56) & 15))
//#define HWC_SLIDER       ((int)((hwconfig >> 60) & 7))
#endif

#define HWC_EB100 (HWC_PLATFORM == 0)
#define HWC_EB600 (HWC_PLATFORM == 1)
#define HWC_EB500 (HWC_PLATFORM == 2)
#define HWC_COOKIE (HWC_PLATFORM == 3)
#define HWC_IMX357 (HWC_PLATFORM == 6)
#define HWC_EP1234 (HWC_PLATFORM == 7)
#define HWC_IMX508 (HWC_PLATFORM == 8)
#define HWC_EP7 (HWC_PLATFORM == 9)
#define HWC_LNI633 (HWC_PLATFORM == 10)
#define HWC_EP8 (HWC_PLATFORM == 11)
#define HWC_EP7A (HWC_PLATFORM == 12)
#define HWC_EP801 (HWC_PLATFORM == 13)
#define HWC_A13 (HWC_PLATFORM == 14)
#define HWC_EP9 (HWC_PLATFORM == 15)
#define HWC_A23 (HWC_PLATFORM == 4)
#define HWC_631 (HWC_PLATFORM == 5)

#define HWC_EP78	(HWC_EP7 || HWC_EP8)
#define HWC_EP789	(HWC_EP7 || HWC_EP8 || HWC_EP9)

//TODO add determine DIGITIZER
#define HWC_DIGITIZER (0)
#define HWC_PLATFORM_SAMSUNG (HWC_PLATFORM <= 3)
#define HWC_PLATFORM_FREESCALE (HWC_PLATFORM == 6 || HWC_PLATFORM == 8)
#define HWC_PLATFORM_FOXCONN (HWC_PLATFORM == 7 || HWC_PLATFORM == 9 || HWC_PLATFORM == 11 || HWC_PLATFORM == 12)

#define HWC_KEYBOARD_NTX600 (HWC_KEYBOARD == 0)
#define HWC_KEYBOARD_POCKET360 (HWC_KEYBOARD == 1)
#define HWC_KEYBOARD_COOKIE (HWC_KEYBOARD == 2)
#define HWC_KEYBOARD_DIGITEKA (HWC_KEYBOARD == 3)
#define HWC_KEYBOARD_EP1234 (HWC_KEYBOARD == 4)
#define HWC_KEYBOARD_POCKET611 (HWC_KEYBOARD == 1 && HWC_IMX508)
#define HWC_KEYBOARD_POCKET613 (HWC_KEYBOARD == 1 && HWC_EP8)
#define HWC_KEYBOARD_EP7 (HWC_KEYBOARD == 5)
#define HWC_KEYBOARD_LNI633 (HWC_KEYBOARD_EP7 && HWC_LNI633)
#define HWC_KEYBOARD_POCKET515 (HWC_KEYBOARD == 1 && HWC_A13)
#define HWC_KEYBOARD_POCKET624 (HWC_KEYBOARD_EP7 && HWC_A13)
#define HWC_KEYBOARD_POCKET650 (HWC_KEYBOARD == 6)
#define HWC_KEYBOARD_POCKET840 (HWC_KEYBOARD == 7)
#define HWC_KEYBOARD_POCKET630 (HWC_KEYBOARD == 8)
#define HWC_KEYBOARD_POCKET420 (HWC_KEYBOARD == 9)
#define HWC_KEYBOARD_POCKET620 (HWC_KEYBOARD == 10)
#define HWC_KEYBOARD_POCKET631 (HWC_KEYBOARD == KEYBOARD_POCKET631)
#define HWC_KEYBOARD_POCKET641 (HWC_KEYBOARD == KEYBOARD_POCKET641)

#define HWC_NAVIKEYS (HWC_KEYBOARD == 0 || HWC_KEYBOARD == 1 || HWC_KEYBOARD == 4)

#define HWC_DISPLAY_6INCH (HWC_DISPLAY == 0)
#define HWC_DISPLAY_5INCH (HWC_DISPLAY == 1)
#define HWC_DISPLAY_8INCH (HWC_DISPLAY == 2)
#define HWC_DISPLAY_9INCH (HWC_DISPLAY == 3)
#define HWC_DISPLAY_6INCH_758 (HWC_DISPLAY == 4) // display 1024x758 6" HD
#define HWC_DISPLAY_8TRITON (HWC_DISPLAY == 5) // display 1800x800 8"
#define HWC_DISPLAY_8INCH_1200 (HWC_DISPLAY == 6) // display 1600x1200 8"
#define HWC_DISPLAY_4INCH_480_800 (HWC_DISPLAY == 8) // display 480x800 4.3"
#define HWC_DISPLAY_6INCH_1072_1448 (HWC_DISPLAY == 9) // display 1448x1072 6"

#define HWC_CONTROLLER_PVI (HWC_CONTROLLER == 0)
#define HWC_CONTROLLER_EPSON (HWC_CONTROLLER == 1 || HWC_CONTROLLER == 2)
// pearl is not controller, use HWC_EINK_PEARL for this check!
#define HWC_CONTROLLER_IMX (HWC_CONTROLLER == 3 || HWC_CONTROLLER == 4)
#define HWC_CONTROLLER_A13 (HWC_CONTROLLER == 5)

#define HWC_CONTROLLER_DEPTH ((HWC_CONTROLLER > 0) ? 3 : 2)

#define HWC_SERIAL_RTS (HWC_PLATFORM == 0)
#define HWC_SERIAL_NOR2 ((HWC_PLATFORM >= 1 && HWC_PLATFORM <= 3) || HWC_PLATFORM == 6)
#define HWC_SERIAL_IOC (HWC_PLATFORM == 7 || HWC_PLATFORM == 8 || HWC_PLATFORM == 9)
#define HWC_SERIAL_SD ( (HWC_PLATFORM >= 10 && HWC_PLATFORM <= 15) || (HWC_PLATFORM == 4) || HWC_631 )
#define HWC_PASSWORD_VIVI (HWC_PLATFORM == 0)
#define HWC_PASSWORD_NOR2 ((HWC_PLATFORM >= 1 && HWC_PLATFORM <= 3) || HWC_PLATFORM == 6)
#define HWC_PASSWORD_IOC (( HWC_PLATFORM >= 7 &&  HWC_PLATFORM <= 15) || HWC_631 )

//Touch capabilities definitions
#define HWC_MULTITOUCHPANEL (HWC_TOUCHPANEL >= 3 && HWC_TOUCHPANEL <= 10)
#define HWC_TOUCH_NEED_CALIBRATION (HWC_TOUCHPANEL == 1 || HWC_TOUCHPANEL == 2)
#define HWC_FINGERS_TOUCHPANEL (HWC_MULTITOUCHPANEL) //use this macros for fingers touch input screen.

#define HWC_USE_WATCHDOG (HWC_PLATFORM != 0)
#define HWC_HAS_AUDIO (HWC_AUDIO != 0)
#define HWC_USE_ALSA (HWC_AUDIO == 4 || HWC_EP801 || HWC_EP9)
#define HWC_HAS_USB (HWC_USB != 0)
#define HWC_HAS_GSENSOR (HWC_GSENSOR != 0)
#define HWC_GSENSOR_ADJUSTABLE (HWC_GSENSOR == 1 || HWC_GSENSOR == 2)
#define HWC_HAS_TOUCHPANEL (HWC_TOUCHPANEL != 0)
#define HWC_HAS_TOUCHSLIDER (HWC_EP801) //slider type
#define HWC_HAS_SLIDER (HWC_SLIDER || HWC_HAS_TOUCHSLIDER) //use for check that device has slider
#define HWC_HAS_CAPTOUCH (HWC_CAPTOUCH != 0)
#define HWC_HAS_DIGITIZER (HWC_DIGITIZER != 0)
#define HWC_HAS_WIFI (HWC_WIFI != 0)
#define HWC_HAS_BLUETOOTH (HWC_BLUETOOTH != 0)

#define HWC_SUSPEND_CMD (HWC_PLATFORM == 0)
#define HWC_CANNOT_SHUTDOWN (HWC_PLATFORM == 1 || HWC_PLATFORM == 2)
#define HWC_MANUAL_WAVEFORM (HWC_CONTROLLER == 1 || HWC_CONTROLLER == 2 || HWC_CONTROLLER == 3)
//#define HWC_EINK_PM_IOCTL (HWC_PLATFORM != 0)
#define HWC_EINK_PM_IOCTL (HWC_PLATFORM > 0 && HWC_PLATFORM < 7)

#define EINK_EP_NEWDRIVER (HWC_EP1234 && (hw_einkversion() >= 0x0101) )
#define HWC_EINK_PEARL (HWC_EP7 || HWC_LNI633 || HWC_EP7A || HWC_EP801 || HWC_A13 || HWC_EP9 || HWC_A23 || HWC_631)

#define HWC_HAS_FRONTLIGHT (HWC_EP7A || HWC_EP801 || (HWC_A13 && HWC_FRONTLIGHT) || HWC_EP9 || HWC_631)

#define HWC_HAS_LIGHTSENSOR (HWC_LIGHTSENSOR != 0)

#define HWC_HAS_EXTERNAL_CARD (! (HWC_A13 || HWC_A23 || HWC_631) || HWC_EXTCARD)
#define HWC_EINK_COLOUR (HWC_EP801)

// UI design switches
#define HWC_DESIGN_KEYBOARD (HWC_KEYBOARD == 1)  // keyboard like 360,611,613,515
#define HWC_DESIGN_TOUCH (HWC_HAS_TOUCHPANEL)

#ifdef __cplusplus
}
#endif

#endif

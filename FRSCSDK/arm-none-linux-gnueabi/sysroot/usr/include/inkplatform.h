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
 .             .             .             .           | .   3=BCM4329        . 3=BCM4329          .             .
 .             .             .             .           | .   4=GB9619         .                    .             .
 .             .             .             .           | .   5=PW621-M        .                    .             .
 .             .             .             .           | .                    .                    .             .
 .             .             .             .           `usb host              .                    .             .
 .             .             .             .             .                    .                    .             .

 [ 31 30 29 28 | 27 26 25 24 | 23 22 21 20 | 19 18 17 16 | 15 14 13 12 | 11 10  9  8 |  7  6  5  4 |  3  2  1  0 ]
 .  USB        .  audio      .  g-sensor   .  *+* .   keyboard         .  controller .  display    .  board type .
 . 0=none      . 0=none      . 0=none      .   |  .  0=6"ntx           . 0=PVI       . 0=6"600x800 . 0=EB100     .
 . 1=ISP1582   . 1=UDA1345   . 1=MMA7455/1 .   |  .  1=5"pb360         . 1=Epson/GP  . 1=5"600x800 . 1=EB600     .
 . 2=RTS5105   . 2=ALC5623   . 2=MMA7455/2 .   |  .  2=cookie          . 2=Epson/M   . 2=8"1024x768. 2=EB500     .
 . 3=internal  . 3=.....     . 3=?         .   |  .  3=9d7linear       .             . 3=9"1200x825. 3=COOKIE    .
 .             .             . 4=ADXL345/1 .   |  .  4=ep1234          .             .             . 6=iMX357    .
 .             .             . 5=ADXL345/2 .   |  .                    .             .             . 7=EP1234    .
 .             .             . 6=MMA7660/1 .   `display orientation (1=topdown)      .             .             .

*/

extern unsigned long long hwconfig;
extern char hw_platform[];

#define HWCONFIG_DEFAULT 0x0000000021000000LL

#define HWC_PLATFORM     ((int)(hwconfig & 15))
#define HWC_DISPLAY      ((int)((hwconfig >> 4) & 15))
#define HWC_CONTROLLER   ((int)((hwconfig >> 8) & 15))
#define HWC_KEYBOARD     ((int)((hwconfig >> 12) & 31))
#define HWC_DPOS         ((int)((hwconfig >> 18) & 3))
#define HWC_GSENSOR      ((int)((hwconfig >> 20) & 15))
#define HWC_AUDIO        ((int)((hwconfig >> 24) & 15))
#define HWC_USB          ((int)((hwconfig >> 28) & 15))
#define HWC_TOUCHPANEL   ((int)((hwconfig >> 32) & 15))
#define HWC_BLUETOOTH    ((int)((hwconfig >> 36) & 63))
#define HWC_WIFI         ((int)((hwconfig >> 42) & 63))
#define HWC_USBHOST      ((int)((hwconfig >> 48) & 1))
#define HWC_CAPTOUCH     ((int)((hwconfig >> 52) & 15))
#define HWC_CDMA3G       ((int)((hwconfig >> 56) & 15))

#define HWC_EB100 (HWC_PLATFORM == 0)
#define HWC_EB600 (HWC_PLATFORM == 1)
#define HWC_EB500 (HWC_PLATFORM == 2)
#define HWC_COOKIE (HWC_PLATFORM == 3)
#define HWC_IMX357 (HWC_PLATFORM == 6)
#define HWC_EP1234 (HWC_PLATFORM == 7)

#define HWC_PLATFORM_SAMSUNG (HWC_PLATFORM <= 5)
#define HWC_PLATFORM_FREESCALE (HWC_PLATFORM == 6)
#define HWC_PLATFORM_FOXCONN (HWC_PLATFORM == 7)

#define HWC_KEYBOARD_NTX600 (HWC_KEYBOARD == 0)
#define HWC_KEYBOARD_POCKET360 (HWC_KEYBOARD == 1)
#define HWC_KEYBOARD_COOKIE (HWC_KEYBOARD == 2)
#define HWC_KEYBOARD_DIGITEKA (HWC_KEYBOARD == 3)
#define HWC_KEYBOARD_EP1234 (HWC_KEYBOARD == 4)

#define HWC_DISPLAY_6INCH (HWC_DISPLAY == 0)
#define HWC_DISPLAY_5INCH (HWC_DISPLAY == 1)
#define HWC_DISPLAY_8INCH (HWC_DISPLAY == 2)
#define HWC_DISPLAY_9INCH (HWC_DISPLAY == 3)

#define HWC_CONTROLLER_PVI (HWC_CONTROLLER == 0)
#define HWC_CONTROLLER_EPSON (HWC_CONTROLLER == 1 || HWC_CONTROLLER == 2)

#define HWC_CONTROLLER_DEPTH ((HWC_CONTROLLER > 0) ? 3 : 2)

#define HWC_SERIAL_RTS (HWC_PLATFORM == 0)
#define HWC_SERIAL_NOR2 ((HWC_PLATFORM >= 1 && HWC_PLATFORM <= 3) || HWC_PLATFORM == 6)
#define HWC_SERIAL_IOC (HWC_PLATFORM == 7)
#define HWC_PASSWORD_VIVI (HWC_PLATFORM == 0)
#define HWC_PASSWORD_NOR2 ((HWC_PLATFORM >= 1 && HWC_PLATFORM <= 3) || HWC_PLATFORM == 6)
#define HWC_PASSWORD_IOC (HWC_PLATFORM == 7)

#define HWC_USE_WATCHDOG (HWC_PLATFORM != 0)
#define HWC_HAS_AUDIO (HWC_AUDIO != 0)
#define HWC_HAS_USB (HWC_USB != 0)
#define HWC_HAS_GSENSOR (HWC_GSENSOR != 0)
#define HWC_GSENSOR_ADJUSTABLE (HWC_GSENSOR == 1 || HWC_GSENSOR == 2)
#define HWC_HAS_TOUCHPANEL (HWC_TOUCHPANEL != 0)
#define HWC_HAS_CAPTOUCH (HWC_CAPTOUCH != 0)
#define HWC_SUSPEND_CMD (HWC_PLATFORM == 0)
#define HWC_CANNOT_SHUTDOWN (HWC_PLATFORM == 1 || HWC_PLATFORM == 2)
#define HWC_MANUAL_WAVEFORM (HWC_CONTROLLER == 1 || HWC_CONTROLLER == 2)
//#define HWC_EINK_PM_IOCTL (HWC_PLATFORM != 0)
#define HWC_EINK_PM_IOCTL (HWC_PLATFORM != 0 && HWC_PLATFORM != 7)

#define EINK_EP_NEWDRIVER (HWC_EP1234 && (hw_einkversion() >= 0x0101) )

#ifdef __cplusplus
}
#endif

#endif

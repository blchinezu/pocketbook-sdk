#ifndef __SA1100_FRONTLIGHT_H
#define __SA1100_FRONTLIGHT_H

/*************************************************************
 *  IOCTL calls for fronlight driver
 *
 *    _SA1100_FL_IOCTL_ON:  enables the frontlight (ignores arg)
 *    _SA1100_FL_IOCTL_OFF: disables the frontlight (ignores arg)
 *    _SA1100_FL_IOCTL_INTENSITY:  sets the intensity where the
 *      argument is a value between 0..100  (see sa1100_fl_setintenisty)
 *
 *************************************************************/

#define _SA1100_FL_IOCTL_ON		1
#define _SA1100_FL_IOCTL_OFF		2
#define _SA1100_FL_IOCTL_INTENSITY	3
#define _SA1100_FL_IOCTL_BACKLIGHT  4
#define _SA1100_FL_IOCTL_CONTRAST	5
#define _SA1100_FL_IOCTL_GET_BACKLIGHT  6
#define _SA1100_FL_IOCTL_GET_CONTRAST  7


#define FL_MAJOR   60 
#define FL_NAME   "sa1100-fl"



/*************************************************************
 * Set the intensity for the frontlight, any value between 0..100
 */

static int sa1100_fl_setintensity(int intensity); 

static int sa1100_bl_setting(int need_value);
static int sa1100_contrast_setting(int need_value);

/* Backlight function */
static int sa1100_bl_function(int up);
static int sa1100_contrast_function(int up);

/*************************************************************
 * Turn on the frontlight
 */

static int sa1100_fl_enable(void);

/*************************************************************
 * Turn off the frontlight
 */

static int sa1100_fl_disable(void);

#endif /*  __SA1100_FRONTLIGHT_H  */

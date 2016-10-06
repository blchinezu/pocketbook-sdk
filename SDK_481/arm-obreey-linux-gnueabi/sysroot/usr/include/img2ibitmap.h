#ifndef IBITMAP_H
#define IBITMAP_H

#include <inkview.h>

#ifdef __cplusplus
extern "C" {
#endif

ibitmap* bmp2ibitmap(const char *infile);
ibitmap* gif2ibitmap(const char *infile);
ibitmap* tiff2ibitmap(const char *infile);

ibitmap* new_ibitmap(unsigned short width,
                     unsigned short height, 
                     unsigned short depth);

void set_max_ibitmap_depth(int maxdepth);
int get_max_ibitmap_depth(void);
int get_opt_ibitmap_depth(int input_depth);

/* In the following, set 'skip_check' to non-zero value if you don't
 * want to test to see if (x,y) is a valid pixel location. */

unsigned char getBrightness(ibitmap *bm, int x, int y, int skip_check);

int getRGB(ibitmap *bm,
           int x,
           int y,
           unsigned char *r,
           unsigned char *g,
           unsigned char *b,
           int skip_check);

int setRGB(ibitmap *bm,
           int x,
           int y,
           unsigned char r,
           unsigned char g,
           unsigned char b,
           int skip_check);

#ifdef __cplusplus
}
#endif
#endif  /* IBITMAP_H */

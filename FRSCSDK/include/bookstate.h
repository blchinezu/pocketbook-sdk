#ifndef BOOKSTATE_H
#define BOOKSTATE_H

#include <time.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef void *bsHandle;

bsHandle bsLoad(char *bookpath);

char *bsGetPosition(bsHandle bstate);
int bsGetCPage(bsHandle bstate);
int bsGetNPage(bsHandle bstate);
time_t bsGetOpenTime(bsHandle bstate);
int bsGetCompleted(bsHandle bstate);
int bsGetFavorite(bsHandle bstate);
char *bsGetCustom(bsHandle bstate);

void bsSetPosition(bsHandle bstate, char *position);
void bsSetCPage(bsHandle bstate, int cpage);
void bsSetNPage(bsHandle bstate, int npage);
void bsSetOpenTime(bsHandle bstate, time_t opentime);
void bsSetCustom(bsHandle bstate, char *custom);

int bsSave(bsHandle bstate);
void bsClose(bsHandle bstate);

#ifdef __cplusplus
}
#endif

#endif // BOOKSTATE_H

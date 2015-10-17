#ifndef TTSENGINE_H
#define TTSENGINE_H

#define EXPORTED_FUNC __attribute__ ((visibility ("default")))
#ifdef __cplusplus
extern "C"
{
#endif

#define TTSPATH SECUREDIR"/tts/"
#define TTSDESC "langinfo.cfg"
#define NOLINGWARE "@no_lingware"

// init all for ttsengine
int ttsengine_init() EXPORTED_FUNC;

// enum avaible languages
char **ttsengine_enumlang() EXPORTED_FUNC;

// synth text
int ttsengine_synthtext(int id, const void *text) EXPORTED_FUNC;

// synth text file content
int ttsengine_synthfile(int id, const char *filename) EXPORTED_FUNC;

// setup volume 0..100
int ttsengine_setvolume(int volume) EXPORTED_FUNC;

// get current volume value
int ttsengine_getvolume() EXPORTED_FUNC;

// increase volume 10
int ttsengine_volumeup() EXPORTED_FUNC;

// decrease volume 10
int ttsengine_volumedown() EXPORTED_FUNC;

// pause synth of text
int ttsengine_pause() EXPORTED_FUNC;

// cancel all synth jobs
void ttsengine_cancel() EXPORTED_FUNC;

// destroy ttsengine
void ttsengine_destroy() EXPORTED_FUNC;

// returns name of engine
const char* ttsengine_name() EXPORTED_FUNC;

#ifdef __cplusplus
}
#endif

#endif

/*
 * libjingle
 * Copyright 2004--2010, Google Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef TALK_SOUND_ALSASYMBOLTABLE_H_
#define TALK_SOUND_ALSASYMBOLTABLE_H_

#include "talk/base/latebindingsymboltable.h"

namespace cricket {

// The ALSA symbols we need, as an X-Macro list.
// This list must contain precisely every libasound function that is used in
// alsasoundsystem.cc.
#define ALSA_SYMBOLS_LIST \
  X(snd_device_name_free_hint) \
  X(snd_device_name_get_hint) \
  X(snd_device_name_hint) \
  X(snd_pcm_avail_update) \
  X(snd_pcm_close) \
  X(snd_pcm_delay) \
  X(snd_pcm_drop) \
  X(snd_pcm_open) \
  X(snd_pcm_prepare) \
  X(snd_pcm_readi) \
  X(snd_pcm_recover) \
  X(snd_pcm_set_params) \
  X(snd_pcm_start) \
  X(snd_pcm_stream) \
  X(snd_pcm_wait) \
  X(snd_pcm_writei) \
  X(snd_strerror)

LATE_BINDING_SYMBOL_TABLE_DECLARE_BEGIN(AlsaSymbolTable)
#define X(sym) \
    LATE_BINDING_SYMBOL_TABLE_DECLARE_ENTRY(AlsaSymbolTable, sym)
ALSA_SYMBOLS_LIST
#undef X
LATE_BINDING_SYMBOL_TABLE_DECLARE_END(AlsaSymbolTable)

}  // namespace cricket

#endif  // TALK_SOUND_ALSASYMBOLTABLE_H_

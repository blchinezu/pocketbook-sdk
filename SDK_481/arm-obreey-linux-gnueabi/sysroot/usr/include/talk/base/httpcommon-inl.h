/*
 * libjingle
 * Copyright 2004--2005, Google Inc.
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

#ifndef TALK_BASE_HTTPCOMMON_INL_H__
#define TALK_BASE_HTTPCOMMON_INL_H__

#include "talk/base/common.h"
#include "talk/base/httpcommon.h"

namespace talk_base {

///////////////////////////////////////////////////////////////////////////////
// Url
///////////////////////////////////////////////////////////////////////////////

template<class CTYPE>
void Url<CTYPE>::do_set_url(const CTYPE* val, size_t len) {
  if (ascnicmp(val, "http://", 7) == 0) {
    val += 7; len -= 7;
    secure_ = false;
  } else if (ascnicmp(val, "https://", 8) == 0) {
    val += 8; len -= 8;
    secure_ = true;
  } else {
    clear();
    return;
  }
  const CTYPE* path = strchrn(val, len, static_cast<CTYPE>('/'));
  if (!path) {
    path = val + len;
  }
  size_t address_length = (path - val);
  do_set_address(val, address_length);
  do_set_full_path(path, len - address_length);
}

template<class CTYPE>
void Url<CTYPE>::do_set_address(const CTYPE* val, size_t len) {
  if (const CTYPE* colon = strchrn(val, len, static_cast<CTYPE>(':'))) {
    host_.assign(val, colon - val);
    // Note: In every case, we're guaranteed that colon is followed by a null,
    // or non-numeric character.
    port_ = static_cast<uint16>(::strtoul(colon + 1, NULL, 10));
    // TODO: Consider checking for invalid data following port number.
  } else {
    host_.assign(val, len);
    port_ = HttpDefaultPort(secure_);
  }
}

template<class CTYPE>
void Url<CTYPE>::do_set_full_path(const CTYPE* val, size_t len) {
  const CTYPE* query = strchrn(val, len, static_cast<CTYPE>('?'));
  if (!query) {
    query = val + len;
  }
  size_t path_length = (query - val);
  if (0 == path_length) {
    // TODO: consider failing in this case.
    path_.assign(1, static_cast<CTYPE>('/'));
  } else {
    ASSERT(val[0] == static_cast<CTYPE>('/'));
    path_.assign(val, path_length);
  }
  query_.assign(query, len - path_length);
}

template<class CTYPE>
void Url<CTYPE>::do_get_url(string* val) const {
  CTYPE protocol[9];
  asccpyn(protocol, ARRAY_SIZE(protocol), secure_ ? "https://" : "http://");
  val->append(protocol);
  do_get_address(val);
  do_get_full_path(val);
}

template<class CTYPE>
void Url<CTYPE>::do_get_address(string* val) const {
  val->append(host_);
  if (port_ != HttpDefaultPort(secure_)) {
    CTYPE format[5], port[32];
    asccpyn(format, ARRAY_SIZE(format), ":%hu");
    sprintfn(port, ARRAY_SIZE(port), format, port_);
    val->append(port);
  }
}

template<class CTYPE>
void Url<CTYPE>::do_get_full_path(string* val) const {
  val->append(path_);
  val->append(query_);
}

template<class CTYPE>
bool Url<CTYPE>::get_attribute(const string& name, string* value) const {
  if (query_.empty())
    return false;
  
  std::string::size_type pos = query_.find(name, 1);
  if (std::string::npos == pos)
    return false;

  pos += name.length() + 1;
  if ((pos > query_.length()) || (static_cast<CTYPE>('=') != query_[pos-1]))
    return false;

  std::string::size_type end = query_.find(static_cast<CTYPE>('&'), pos);
  if (std::string::npos == end) {
    end = query_.length();
  }
  value->assign(query_.substr(pos, end - pos));
  return true;
}

///////////////////////////////////////////////////////////////////////////////

}  // namespace talk_base

#endif  // TALK_BASE_HTTPCOMMON_INL_H__

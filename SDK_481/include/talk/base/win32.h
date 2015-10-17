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

#ifndef TALK_BASE_WIN32_H_
#define TALK_BASE_WIN32_H_

#ifdef WIN32

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <winsock2.h>
#include <windows.h>

#ifndef SECURITY_MANDATORY_LABEL_AUTHORITY
// Add defines that we use if we are compiling against older sdks
#define SECURITY_MANDATORY_MEDIUM_RID               (0x00002000L)
#define TokenIntegrityLevel static_cast<TOKEN_INFORMATION_CLASS>(0x19)
typedef struct _TOKEN_MANDATORY_LABEL {
    SID_AND_ATTRIBUTES Label;
} TOKEN_MANDATORY_LABEL, *PTOKEN_MANDATORY_LABEL;
#endif  // SECURITY_MANDATORY_LABEL_AUTHORITY

#undef SetPort

#include <string>

#include "talk/base/stringutils.h"
#include "talk/base/basictypes.h"

namespace talk_base {

const char* win32_inet_ntop(int af, const void *src, char* dst, socklen_t size);
int win32_inet_pton(int af, const char* src, void *dst);

///////////////////////////////////////////////////////////////////////////////

inline std::wstring ToUtf16(const char* utf8, size_t len) {
  int len16 = ::MultiByteToWideChar(CP_UTF8, 0, utf8, len, NULL, 0);
  wchar_t* ws = STACK_ARRAY(wchar_t, len16);
  ::MultiByteToWideChar(CP_UTF8, 0, utf8, len, ws, len16);
  return std::wstring(ws, len16);
}

inline std::wstring ToUtf16(const std::string& str) {
  return ToUtf16(str.data(), str.length());
}

inline std::string ToUtf8(const wchar_t* wide, size_t len) {
  int len8 = ::WideCharToMultiByte(CP_UTF8, 0, wide, len, NULL, 0, NULL, NULL);
  char* ns = STACK_ARRAY(char, len8);
  ::WideCharToMultiByte(CP_UTF8, 0, wide, len, ns, len8, NULL, NULL);
  return std::string(ns, len8);
}

inline std::string ToUtf8(const std::wstring& wstr) {
  return ToUtf8(wstr.data(), wstr.length());
}

// Convert FILETIME to time_t
void FileTimeToUnixTime(const FILETIME& ft, time_t* ut);

// Convert time_t to FILETIME
void UnixTimeToFileTime(const time_t& ut, FILETIME * ft);

// Convert a Utf8 path representation to a non-length-limited Unicode pathname.
bool Utf8ToWindowsFilename(const std::string& utf8, std::wstring* filename);

// Convert a FILETIME to a UInt64
inline uint64 ToUInt64(const FILETIME& ft) {
  ULARGE_INTEGER r = {ft.dwLowDateTime, ft.dwHighDateTime};
  return r.QuadPart;
}

enum WindowsMajorVersions {
  kWindows2000 = 5,
  kWindowsVista = 6,
};
bool GetOsVersion(int* major, int* minor, int* build);

inline bool IsWindowsVistaOrLater() {
  int major;
  return (GetOsVersion(&major, NULL, NULL) && major >= kWindowsVista);
}

inline bool IsWindowsXpOrLater() {
  int major, minor;
  return (GetOsVersion(&major, &minor, NULL) &&
          (major >= kWindowsVista ||
          (major == kWindows2000 && minor >= 1)));
}

// Determine the current integrity level of the process.
bool GetCurrentProcessIntegrityLevel(int* level);

inline bool IsCurrentProcessLowIntegrity() {
  int level;
  return (GetCurrentProcessIntegrityLevel(&level) &&
      level < SECURITY_MANDATORY_MEDIUM_RID);
}

bool AdjustCurrentProcessPrivilege(const TCHAR* privilege, bool to_enable);

///////////////////////////////////////////////////////////////////////////////

}  // namespace talk_base

#endif  // WIN32
#endif  // TALK_BASE_WIN32_H_

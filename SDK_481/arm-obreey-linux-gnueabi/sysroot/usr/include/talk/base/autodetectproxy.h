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

#ifndef TALK_BASE_AUTODETECTPROXY_H_
#define TALK_BASE_AUTODETECTPROXY_H_

#include <string>

#include "talk/base/constructormagic.h"
#include "talk/base/cryptstring.h"
#include "talk/base/proxyinfo.h"
#include "talk/base/signalthread.h"

namespace talk_base {

///////////////////////////////////////////////////////////////////////////////
// AutoDetectProxy
///////////////////////////////////////////////////////////////////////////////

class AsyncSocket;

class AutoDetectProxy : public SignalThread {
 public:
  explicit AutoDetectProxy(const std::string& user_agent);

  const ProxyInfo& proxy() const { return proxy_; }

  void set_server_url(const std::string& url) {
    server_url_ = url;
  }
  void set_proxy(const SocketAddress& proxy) {
    proxy_.type = PROXY_UNKNOWN;
    proxy_.address = proxy;
  }
  void set_auth_info(bool use_auth, const std::string& username,
                     const CryptString& password) {
    if (use_auth) {
      proxy_.username = username;
      proxy_.password = password;
    }
  }

 protected:
  virtual ~AutoDetectProxy();

  // SignalThread Interface
  virtual void DoWork();
  virtual void OnMessage(Message *msg);

  void Next();
  void Complete(ProxyType type);

  void OnConnectEvent(AsyncSocket * socket);
  void OnReadEvent(AsyncSocket * socket);
  void OnCloseEvent(AsyncSocket * socket, int error);

 private:
  std::string agent_;
  std::string server_url_;
  ProxyInfo proxy_;
  AsyncSocket* socket_;
  int next_;

  DISALLOW_IMPLICIT_CONSTRUCTORS(AutoDetectProxy);
};

}  // namespace talk_base

#endif  // TALK_BASE_AUTODETECTPROXY_H_

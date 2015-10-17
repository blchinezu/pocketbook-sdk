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

#ifndef TALK_P2P_BASE_UDPPORT_H_
#define TALK_P2P_BASE_UDPPORT_H_

#include <string>

#include "talk/p2p/base/port.h"

namespace talk_base {
class Thread;
class Network;
class SocketAddress;
}

namespace cricket {

extern const char LOCAL_PORT_TYPE[];  // type of UDP ports

// Communicates using a local UDP port.
class UDPPort : public Port {
 public:
  static UDPPort* Create(talk_base::Thread* thread,
                         talk_base::PacketSocketFactory* factory,
                         talk_base::Network* network,
                         const talk_base::IPAddress& ip,
                         int min_port, int max_port) {
    UDPPort* port = new UDPPort(thread, factory, network,
                                ip, min_port, max_port);
    if (!port->Init()) {
      delete port;
      port = NULL;
    }
    return port;
  }
  virtual ~UDPPort();

  virtual void PrepareAddress();
  virtual Connection* CreateConnection(const Candidate& address,
                                       CandidateOrigin origin);

  virtual int SetOption(talk_base::Socket::Option opt, int value);
  virtual int GetError();

 protected:
  UDPPort(talk_base::Thread* thread, talk_base::PacketSocketFactory* factory,
          talk_base::Network* network, const talk_base::IPAddress& ip,
          int min_port, int max_port);
  bool Init();

  // Handles sending using the local UDP socket.
  virtual int SendTo(const void* data, size_t size,
                     const talk_base::SocketAddress& remote_addr, bool payload);

  void OnAddressReady(talk_base::AsyncPacketSocket* socket,
                      const talk_base::SocketAddress& address);

  // Dispatches the given packet to the port or connection as appropriate.
  void OnReadPacket(talk_base::AsyncPacketSocket* socket,
                    const char* data, size_t size,
                    const talk_base::SocketAddress& remote_addr);

 private:
  talk_base::AsyncPacketSocket* socket_;
  int error_;
};

}  // namespace cricket

#endif  // TALK_P2P_BASE_UDPPORT_H_

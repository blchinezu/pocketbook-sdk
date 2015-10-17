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

#ifndef TALK_BASE_SOCKETADDRESS_H_
#define TALK_BASE_SOCKETADDRESS_H_

#include <string>
#include <vector>
#include <iosfwd>
#include "talk/base/basictypes.h"
#include "talk/base/ipaddress.h"

#undef SetPort

struct sockaddr_in;
struct sockaddr_storage;

namespace talk_base {

// Records an IP address and port.
class SocketAddress {
 public:
  // Creates a nil address.
  SocketAddress();

  // Creates the address with the given host and port. Host may be a
  // literal IP string or a hostname to be resolved later with ResolveIP().
  SocketAddress(const std::string& hostname, int port);

  // Creates the address with the given IP and port.
  // IP is given as an integer in host byte order. V4 only, to be deprecated.
  SocketAddress(uint32 ip_as_host_order_integer, int port);

  // Creates the address with the given IP and port.
  SocketAddress(const IPAddress& ip, int port);

  // Creates a copy of the given address.
  SocketAddress(const SocketAddress& addr);

  // Resets to the nil address.
  void Clear();

  // Determines if this is a nil address (empty hostname, any IP, null port)
  bool IsNil() const;

  // Returns true if ip and port are set.
  bool IsComplete() const;

  // Replaces our address with the given one.
  SocketAddress& operator=(const SocketAddress& addr);

  // Changes the IP of this address to the given one, and clears the hostname
  // IP is given as an integer in host byte order. V4 only, to be deprecated..
  void SetIP(uint32 ip_as_host_order_integer);

  // Changes the IP of this address to the given one, and clears the hostname.
  void SetIP(const IPAddress& ip);

  // Changes the hostname of this address to the given one.
  // Does not resolve the address; use Resolve to do so.
  void SetIP(const std::string& hostname);

  // Sets the IP address while retaining the hostname.  Useful for bypassing
  // DNS for a pre-resolved IP.
  // IP is given as an integer in host byte order. V4 only, to be deprecated.
  void SetResolvedIP(uint32 ip_as_host_order_integer);

  // Sets the IP address while retaining the hostname.  Useful for bypassing
  // DNS for a pre-resolved IP.
  void SetResolvedIP(const IPAddress& ip);

  // Changes the port of this address to the given one.
  void SetPort(int port);

  // Returns the hostname.
  const std::string& hostname() const { return hostname_; }

  // Returns the IP address as a host byte order integer.
  // Returns 0 for non-v4 addresses.
  uint32 ip() const;

  const IPAddress& ipaddr() const;

  // Returns the port part of this address.
  uint16 port() const;

  // Returns the scope ID associated with this address. Scope IDs are a
  // necessary addition to IPv6 link-local addresses, with different network
  // interfaces having different scope-ids for their link-local addresses.
  // IPv4 address do not have scope_ids and sockaddr_in structures do not have
  // a field for them.
  int scope_id() const {return scope_id_; }
  void SetScopeID(int id) { scope_id_ = id; }

  // Returns the IP address (or hostname) in printable form.
  std::string IPAsString() const;

  // Returns the port as a string.
  std::string PortAsString() const;

  // Returns hostname:port or [hostname]:port.
  std::string ToString() const;

  // Parses hostname:port and [hostname]:port.
  bool FromString(const std::string& str);

  friend std::ostream& operator<<(std::ostream& os, const SocketAddress& addr);

  // Determines whether this represents a missing / any IP address.
  // That is, 0.0.0.0 or ::.
  // Hostname and/or port may be set.
  bool IsAnyIP() const;
  inline bool IsAny() const { return IsAnyIP(); }  // deprecated

  // Determines whether the IP address refers to a loopback address.
  // For v4 addresses this means the address is in the range 127.0.0.0/8.
  // For v6 addresses this means the address is ::1.
  bool IsLoopbackIP() const;

  // Determines wither the IP address refers to any adapter on the local
  // machine, including the loopback adapter.
  bool IsLocalIP() const;

  // Determines whether the IP address is in one of the private ranges:
  // For v4: 127.0.0.0/8 10.0.0.0/8 192.168.0.0/16 172.16.0.0/12.
  // For v6: FE80::/16 and ::1.
  bool IsPrivateIP() const;

  // Determines whether the hostname has been resolved to an IP.
  bool IsUnresolvedIP() const;
  inline bool IsUnresolved() const { return IsUnresolvedIP(); }  // deprecated

  // Attempt to resolve a hostname to IP address.
  // Returns false if resolution is required but failed, and sets error.
  // 'force' will cause re-resolution of hostname.
  // TODO: Deprecate this function.
  bool ResolveIP(bool force = false, int* error = NULL);

  // Determines whether this address is identical to the given one.
  bool operator ==(const SocketAddress& addr) const;
  inline bool operator !=(const SocketAddress& addr) const {
    return !this->operator ==(addr);
  }

  // Compares based on IP and then port.
  bool operator <(const SocketAddress& addr) const;

  // Determines whether this address has the same IP as the one given.
  bool EqualIPs(const SocketAddress& addr) const;

  // Determines whether this address has the same port as the one given.
  bool EqualPorts(const SocketAddress& addr) const;

  // Hashes this address into a small number.
  size_t Hash() const;

  // Write this address to a sockaddr_in.
  // If IPv6, will zero out the sockaddr_in and sets family to AF_UNSPEC.
  void ToSockAddr(sockaddr_in* saddr) const;

  // Read this address from a sockaddr_in.
  bool FromSockAddr(const sockaddr_in& saddr);

  // Read and write the address to/from a sockaddr_storage.
  // Dual stack version always sets family to AF_INET6, and maps v4 addresses.
  // The other version doesn't map, and outputs an AF_INET address for
  // v4 or mapped addresses, and AF_INET6 addresses for others.
  // Returns the size of the sockaddr_in or sockaddr_in6 structure that is
  // written to the sockaddr_storage, or zero on failure.
  size_t ToDualStackSockAddrStorage(sockaddr_storage* saddr) const;
  size_t ToSockAddrStorage(sockaddr_storage* saddr) const;

  // Converts the IP address given in 'compact form' into dotted form.
  // IP is given as an integer in host byte order. V4 only, to be deprecated.
  // TODO: Deprecate this.
  static std::string IPToString(uint32 ip_as_host_order_integer);

  // Converts the IP address given in dotted form into compact form.
  // Only dotted names (A.B.C.D) are  converted.
  // Output integer is returned in host byte order.
  // TODO: Deprecate, replace wth agnostic versions.
  static bool StringToIP(const std::string& str, uint32* ip);
  static uint32 StringToIP(const std::string& str);

  // Converts the IP address given in printable form into an IPAddress.
  static bool StringToIP(const std::string& str, IPAddress* ip);

  // Get a list of the local machine's ip addresses.
  // TODO: Move to nethelpers or similar (doesn't belong in socketaddress).
  static bool GetLocalIPs(std::vector<IPAddress>* ips);

 private:
  // Get local machine's hostname.
  static std::string GetHostname();
  std::string hostname_;
  IPAddress ip_;
  uint16 port_;
  int scope_id_;
  bool literal_;  // Indicates that 'hostname_' contains a literal IP string.
};

bool SocketAddressFromSockAddrStorage(const sockaddr_storage& saddr,
                                      SocketAddress* out);

}  // namespace talk_base

#endif  // TALK_BASE_SOCKETADDRESS_H_

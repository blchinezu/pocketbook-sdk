/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtNetwork module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QNATIVESOCKETENGINE_P_H
#define QNATIVESOCKETENGINE_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of the QLibrary class.  This header file may change from
// version to version without notice, or even be removed.
//
// We mean it.
//
#include "QtNetwork/qhostaddress.h"
#include "private/qabstractsocketengine_p.h"
#ifndef Q_OS_WIN
#  include "qplatformdefs.h"
#  include <netinet/in.h>
#else
#  include <winsock2.h>
#endif

QT_BEGIN_NAMESPACE

// Use our own defines and structs which we know are correct
#  define QT_SS_MAXSIZE 128
#  define QT_SS_ALIGNSIZE (sizeof(qint64))
#  define QT_SS_PAD1SIZE (QT_SS_ALIGNSIZE - sizeof (short))
#  define QT_SS_PAD2SIZE (QT_SS_MAXSIZE - (sizeof (short) + QT_SS_PAD1SIZE + QT_SS_ALIGNSIZE))
struct qt_sockaddr_storage {
      short ss_family;
      char __ss_pad1[QT_SS_PAD1SIZE];
      qint64 __ss_align;
      char __ss_pad2[QT_SS_PAD2SIZE];
};

#ifdef Q_OS_WIN
#define QT_SOCKLEN_T int
#define QT_SOCKOPTLEN_T int
#endif

// sockaddr_in6 size changed between old and new SDK
// Only the new version is the correct one, so always
// use this structure.
struct qt_in6_addr {
    quint8 qt_s6_addr[16];
};
struct qt_sockaddr_in6 {
    short   sin6_family;            /* AF_INET6 */
    quint16 sin6_port;              /* Transport level port number */
    quint32 sin6_flowinfo;          /* IPv6 flow information */
    struct  qt_in6_addr sin6_addr;  /* IPv6 address */
    quint32 sin6_scope_id;          /* set of interfaces for a scope */
};

union qt_sockaddr {
    sockaddr a;
    sockaddr_in a4;
    qt_sockaddr_in6 a6;
    qt_sockaddr_storage storage;
};

class QNativeSocketEnginePrivate;
#ifndef QT_NO_NETWORKINTERFACE
class QNetworkInterface;
#endif

class Q_AUTOTEST_EXPORT QNativeSocketEngine : public QAbstractSocketEngine
{
    Q_OBJECT
public:
    QNativeSocketEngine(QObject *parent = 0);
    ~QNativeSocketEngine();

    bool initialize(QAbstractSocket::SocketType type, QAbstractSocket::NetworkLayerProtocol protocol = QAbstractSocket::IPv4Protocol);
    bool initialize(qintptr socketDescriptor, QAbstractSocket::SocketState socketState = QAbstractSocket::ConnectedState);

    qintptr socketDescriptor() const;

    bool isValid() const;

    bool connectToHost(const QHostAddress &address, quint16 port);
    bool connectToHostByName(const QString &name, quint16 port);
    bool bind(const QHostAddress &address, quint16 port);
    bool listen();
    int accept();
    void close();

#ifndef QT_NO_NETWORKINTERFACE
    bool joinMulticastGroup(const QHostAddress &groupAddress,
                            const QNetworkInterface &iface);
    bool leaveMulticastGroup(const QHostAddress &groupAddress,
                             const QNetworkInterface &iface);
    QNetworkInterface multicastInterface() const;
    bool setMulticastInterface(const QNetworkInterface &iface);
#endif

    qint64 bytesAvailable() const;

    qint64 read(char *data, qint64 maxlen);
    qint64 write(const char *data, qint64 len);

    qint64 readDatagram(char *data, qint64 maxlen, QHostAddress *addr = 0,
                            quint16 *port = 0);
    qint64 writeDatagram(const char *data, qint64 len, const QHostAddress &addr,
                             quint16 port);
    bool hasPendingDatagrams() const;
    qint64 pendingDatagramSize() const;

    qint64 bytesToWrite() const;

    qint64 receiveBufferSize() const;
    void setReceiveBufferSize(qint64 bufferSize);

    qint64 sendBufferSize() const;
    void setSendBufferSize(qint64 bufferSize);

    int option(SocketOption option) const;
    bool setOption(SocketOption option, int value);

    bool waitForRead(int msecs = 30000, bool *timedOut = 0);
    bool waitForWrite(int msecs = 30000, bool *timedOut = 0);
    bool waitForReadOrWrite(bool *readyToRead, bool *readyToWrite,
                            bool checkRead, bool checkWrite,
                            int msecs = 30000, bool *timedOut = 0);

    bool isReadNotificationEnabled() const;
    void setReadNotificationEnabled(bool enable);
    bool isWriteNotificationEnabled() const;
    void setWriteNotificationEnabled(bool enable);
    bool isExceptionNotificationEnabled() const;
    void setExceptionNotificationEnabled(bool enable);

public Q_SLOTS:
    // non-virtual override;
    void connectionNotification();

private:
    Q_DECLARE_PRIVATE(QNativeSocketEngine)
    Q_DISABLE_COPY(QNativeSocketEngine)
};

#ifdef Q_OS_WIN
class QWindowsSockInit
{
public:
    QWindowsSockInit();
    ~QWindowsSockInit();
    int version;
};
#endif

class QSocketNotifier;

class QNativeSocketEnginePrivate : public QAbstractSocketEnginePrivate
{
    Q_DECLARE_PUBLIC(QNativeSocketEngine)
public:
    QNativeSocketEnginePrivate();
    ~QNativeSocketEnginePrivate();

    qintptr socketDescriptor;

    QSocketNotifier *readNotifier, *writeNotifier, *exceptNotifier;

#ifdef Q_OS_WIN
    QWindowsSockInit winSock;
#endif

    enum ErrorString {
        NonBlockingInitFailedErrorString,
        BroadcastingInitFailedErrorString,
        NoIpV6ErrorString,
        RemoteHostClosedErrorString,
        TimeOutErrorString,
        ResourceErrorString,
        OperationUnsupportedErrorString,
        ProtocolUnsupportedErrorString,
        InvalidSocketErrorString,
        HostUnreachableErrorString,
        NetworkUnreachableErrorString,
        AccessErrorString,
        ConnectionTimeOutErrorString,
        ConnectionRefusedErrorString,
        AddressInuseErrorString,
        AddressNotAvailableErrorString,
        AddressProtectedErrorString,
        DatagramTooLargeErrorString,
        SendDatagramErrorString,
        ReceiveDatagramErrorString,
        WriteErrorString,
        ReadErrorString,
        PortInuseErrorString,
        NotSocketErrorString,
        InvalidProxyTypeString,
        TemporaryErrorString,

        UnknownSocketErrorString = -1
    };

    void setError(QAbstractSocket::SocketError error, ErrorString errorString) const;

    // native functions
    int option(QNativeSocketEngine::SocketOption option) const;
    bool setOption(QNativeSocketEngine::SocketOption option, int value);

    bool createNewSocket(QAbstractSocket::SocketType type, QAbstractSocket::NetworkLayerProtocol &protocol);

    bool nativeConnect(const QHostAddress &address, quint16 port);
    bool nativeBind(const QHostAddress &address, quint16 port);
    bool nativeListen(int backlog);
    int nativeAccept();
#ifndef QT_NO_NETWORKINTERFACE
    bool nativeJoinMulticastGroup(const QHostAddress &groupAddress,
                                  const QNetworkInterface &iface);
    bool nativeLeaveMulticastGroup(const QHostAddress &groupAddress,
                                   const QNetworkInterface &iface);
    QNetworkInterface nativeMulticastInterface() const;
    bool nativeSetMulticastInterface(const QNetworkInterface &iface);
#endif
    qint64 nativeBytesAvailable() const;

    bool nativeHasPendingDatagrams() const;
    qint64 nativePendingDatagramSize() const;
    qint64 nativeReceiveDatagram(char *data, qint64 maxLength,
                                     QHostAddress *address, quint16 *port);
    qint64 nativeSendDatagram(const char *data, qint64 length,
                                  const QHostAddress &host, quint16 port);
    qint64 nativeRead(char *data, qint64 maxLength);
    qint64 nativeWrite(const char *data, qint64 length);
    int nativeSelect(int timeout, bool selectForRead) const;
    int nativeSelect(int timeout, bool checkRead, bool checkWrite,
                     bool *selectForRead, bool *selectForWrite) const;
#ifdef Q_OS_WIN
    void setPortAndAddress(sockaddr_in * sockAddrIPv4, qt_sockaddr_in6 * sockAddrIPv6,
                           quint16 port, const QHostAddress & address, sockaddr ** sockAddrPtr, QT_SOCKLEN_T *sockAddrSize);
#endif

    void nativeClose();

    bool checkProxy(const QHostAddress &address);
    bool fetchConnectionParameters();
};

QT_END_NAMESPACE

#endif // QNATIVESOCKETENGINE_P_H

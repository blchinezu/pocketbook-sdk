#ifndef PBINTERFACE_H
#define PBINTERFACE_H


//Use duplicate
#include "qwebkitplatformplugin.h"

#include "pbinterfacehelper.h"
#include <QtCore/qglobal.h>
#include <functional>
#include <QtCore/QMutex>
#include <QtCore/QRect>

#include <QUrl>
#include <QObject>
#include <functional>
class PBInterfacePrivate;
class PBBearerInterface;

QT_BEGIN_HEADER
QT_BEGIN_NAMESPACE

QT_MODULE(PBInterface)
class PBBearerInterface;
class PBPlatformInterface;
class QWebSelectData;
class QPBWebNotificationDataPrivate;
class PBINTERFACESHARED_EXPORT WebNotificationData {
public:
    virtual ~WebNotificationData() {}

    virtual const QString title() const = 0;
    virtual const QString message() const = 0;
    virtual const QByteArray iconData() const = 0;
    virtual const QUrl openerPageUrl() const = 0;
};
class PBINTERFACESHARED_EXPORT QPBWebNotificationData : public WebNotificationData 
{
public:
    QPBWebNotificationData(const QString & msg, bool confirm = false);
    QPBWebNotificationData(const QPBWebNotificationData & data);
    QPBWebNotificationData(const WebNotificationData & data);
    virtual ~QPBWebNotificationData();
    virtual const QString title() const;
    virtual const QString message() const;
    virtual const QByteArray iconData() const;
    virtual const QUrl openerPageUrl() const;
    virtual bool confirm() const;
private:
    QPBWebNotificationDataPrivate * m_pimpl;
};
class PBINTERFACESHARED_EXPORT PBInterface : public QObject
{
    Q_OBJECT
public:
    typedef std::function<void (bool)> THandlerKeybOpenClosed;
    static PBInterface * Instance();
    ~PBInterface();
    enum CONNECTION_TYPE {WIFI, CDMA3G, NOTCONNECTED};
    enum CONNECTION_RESULT {CONNECTED, CANCELED, CONNECTING, NONE};
    enum DIALOG_RESULT {DIALOG_NONE, DIALOG_BUTTON1, DIALOG_BUTTON2, DIALOG_BUTTON3};
    void SetConnectToTheNetworkByDefault(bool connect=true);
    void ListenKeybOpenClosed(THandlerKeybOpenClosed handler);
    void ConnectToTheNetwork();
    bool IsNetworkConnectionEstablished();
    void SetBearerDelegate(PBBearerInterface * delegate);
    void SetPlatformDelegate(PBPlatformInterface * delegate);
    CONNECTION_RESULT ConnectionResult();
    CONNECTION_TYPE LastConnectionType();
    bool IsKeyboardOpened();


    void OpenMenu(const QWebSelectData&, const std::function<void(int)> & selected);

    DIALOG_RESULT OpenInkviewSynchroDialog(int icon, const QString & title, const QString & text, const QString &button1, const QString &button2="", const QString &button3="");

    void ShowMessage(int icon, const QString & title, const QString & text, int timeouMS = 5000);

    /*
    // call from Qt thread and must be synchro for qt thread
    void ShowNotification(const QPBWebNotificationData&);
    */

    /**
     * @brief EnterA2Update tells Update object to set fast a2 (white/black) update mode
     * func is called from qt thread
     * @param area is screen part of further a2 updates
     * @return false when it is already A2 or area differs
     */
    bool EnterA2Update(const QRect & area);
    
    /**
     * @brief LeaveA2Update tells Update object to return to normal full grayscale update mode 
     * func is called from qt thread
     * @return false when it is not A2 and function does nothing
     */
    bool LeaveA2Update();
    
    /**
     * @brief IsA2Update checks update mode
     * @return true when it is fast a2 update mode
     */
    bool IsA2Update();
    
signals:
    void signalKeyboardWasOpened(bool opened);
    void signalEnterA2Update(QRect);
    void signalLeaveA2Update();
    void signalSoftwareInputPanelRequested();

private:
    void KeyBoardOpenedClosedLocalHandler(bool opened);
    
    PBInterface();
    static PBInterface * instance;
    PBInterfacePrivate * d;
};

class PBINTERFACESHARED_EXPORT QPBNavigationKeys : public QObject
{
    Q_OBJECT
public:
    enum TKeyBehaviour {NORMAL, MOUSE_MOVE};
    static bool hasNavigationKeys();
    static void setKeyBehavior(QPBNavigationKeys::TKeyBehaviour behavior);
    static QPBNavigationKeys * Instance();
    static TKeyBehaviour behavior();
signals:
    void signalKeyBehaviorChanged(QPBNavigationKeys::TKeyBehaviour behavior);
private:
    void setKeyBehaviorPrivate(TKeyBehaviour behavior);
private:
    const bool m_hasNavigationKeys;
    QMutex m_setMutex;
    QAtomicInt m_currentBehavior;
    QPBNavigationKeys();
    friend QPBNavigationKeys *InstancePrivate();
};

class PBBearerInterface
{
public:
    virtual ~PBBearerInterface(){}
    virtual void SetConnectToTheNetworkByDefault(bool connect=true) = 0;
    virtual void ConnectToTheNetwork() = 0;
    virtual bool IsNetworkConnectionEstablished() = 0;
    virtual PBInterface::CONNECTION_RESULT Result() = 0;
    virtual PBInterface::CONNECTION_TYPE LastConnectionType() = 0;
};


class PBPlatformInterface
{
public:
    void userSelected(int );
    virtual void ListenKeybOpenClosed(PBInterface::THandlerKeybOpenClosed handler) = 0;
    virtual ~PBPlatformInterface(){}
    virtual bool IsKeyboardOpened() = 0;
    // call from Qt thread and must be synchro for qt thread
    virtual void OpenMenu(const QWebSelectData&, const std::function<void(int)> & selected) = 0;
    // call from Qt thread and must be synchro for qt thread
    virtual void ShowNotification(const QPBWebNotificationData&) = 0;
    virtual bool IsA2Update() = 0;
};
QT_END_NAMESPACE
QT_END_HEADER
#endif // PBINTERFACE_H


#pragma once
#include <QtCore/QEvent>
#include <QtCore/QSet>
#include <QtCore/QMap>
#include "pbinterfacehelper.h"
class PBINTERFACESHARED_EXPORT PBEvent : public QEvent
{
    Q_GADGET
    
public:
    enum PBType {
        PBRequestSoftwareInputPanel = QEvent::MaxUser - 1000
    };
    class PBEventMap : public QMap<PBEvent::PBType, QEvent::Type> 
    {
    typedef QMap<PBEvent::PBType, QEvent::Type> TBase;
    public:
        PBEventMap() {
            TBase::insert(PBEvent::PBRequestSoftwareInputPanel, QEvent::RequestSoftwareInputPanel);
        }
    };
    PBEvent(PBEvent::PBType type); 
    virtual ~PBEvent();
    PBType pbType() const;
    static bool isRegisterPBEvent(const PBEvent * );
private:
    static void registerPBEvent(PBEvent * );
    static void deregisterPBEvent(PBEvent * );
    static const PBEventMap m_eventMap;
    PBType m_type;
};
class PBINTERFACESHARED_EXPORT PBRequestSoftwareInputPanelEvent : public PBEvent 
{
    Q_GADGET
public: 
    PBRequestSoftwareInputPanelEvent(bool english = false);
    bool english() const;
private:
    bool m_english;
};


#pragma once
#include <inklog.h>
#include <QtCore/QString>
#include <QtCore/QRect>
#include <QtCore/QVariant>
template <int LOG_LEVEL_SYSTEM>
class MDebug 
{
    QString m_strOut;
    bool m_always;
    int m_log_level;
    const char * m_file_name;
    int m_line;
    const char *m_pretty_func;
    const char* m_format;
    va_list m_args;
    mutable bool m_print;
    
public:
    MDebug(int log_level, const char * file_name, int line, const char *pretty_func, bool always) :
        m_always(always),
        m_log_level(log_level),
        m_file_name(file_name),
        m_line(line),
        m_pretty_func(pretty_func)
    {
        m_print = false;
    }
    MDebug(const MDebug &deb) {
        (*this) = deb;
    }

    ~MDebug() {
        if (m_print && (m_always || m_log_level <= LOG_LEVEL_SYSTEM)) {
            pb_print_log2(m_log_level, m_file_name, m_line, m_pretty_func, "%s", m_strOut.toStdString().c_str());
        }
    }
    MDebug & operator = (const MDebug &deb) {
        m_always = deb.m_always;
        m_log_level = deb.m_log_level;
        m_file_name = deb.m_file_name;
        m_line = deb.m_line;
        m_pretty_func = deb.m_pretty_func;
        m_strOut = deb.m_strOut;
        deb.m_print = false;
        m_print = true;
        return * this;
    }

    MDebug & operator << (const QString &str)
    {
        m_print = true;
        m_strOut += str;
        return *this;
    }
};
template <int LOG_LEVEL,class T> struct SPIKE {
    static MDebug<LOG_LEVEL> Add(MDebug<LOG_LEVEL> dbg, const T & c)
    {
        QVariant var(c);
        return (dbg << (var.toString()));
    }
};
template <int LOG_LEVEL> struct SPIKE<LOG_LEVEL, QRect> {
    static MDebug<LOG_LEVEL> Add(MDebug<LOG_LEVEL> dbg, const QRect & rect)
    {
        QString rectStr = QString("QRect(%1, %2, %3, %4)").arg(rect.x()).arg(rect.y()).arg(rect.width()).arg(rect.height());
        return (dbg << rectStr);
    }
};

template <int LOG_LEVEL> struct SPIKE<LOG_LEVEL, QSize> {
    static MDebug<LOG_LEVEL> Add(MDebug<LOG_LEVEL> dbg, const QSize & size)
    {
        QString rectStr = QString("QSize(%1, %2)").arg(size.width()).arg(size.height());
        return (dbg << rectStr);
    }
};

template <int LOG_LEVEL> struct SPIKE<LOG_LEVEL, QPoint> {
    static MDebug<LOG_LEVEL> Add(MDebug<LOG_LEVEL> dbg, const QPoint & point)
    {
        QString rectStr = QString("QPoint(%1, %2)").arg(point.x()).arg(point.y());
        return (dbg << rectStr);
    }
};

template <int LOG_LEVEL,class T> 
MDebug<LOG_LEVEL> operator << (MDebug<LOG_LEVEL> dbg, const T & c)
{
    return SPIKE<LOG_LEVEL, T>::Add(dbg, c);
}

inline MDebug<PB_LOG_LEVEL> mDebug(int log_level, const char * file_name, int line, const char *pretty_func, bool always = false) {
    return MDebug<PB_LOG_LEVEL>(log_level, file_name, line, pretty_func, always);
}

#define PB_TRACEQ() mDebug(PB_LOG_LEVEL_TRACE, __FILE__, __LINE__, __PRETTY_FUNCTION__)

#define PB_INFOQ() mDebug(PB_LOG_LEVEL_INFO, __FILE__, __LINE__, __PRETTY_FUNCTION__)

#define PB_WARNQ() mDebug(PB_LOG_LEVEL_WARNING, __FILE__, __LINE__, __PRETTY_FUNCTION__)

#define PB_ERRORQ() mDebug(PB_LOG_LEVEL_ERROR, __FILE__, __LINE__, __PRETTY_FUNCTION__)


#define PB_ALWAYS_TRACEQ() mDebug(PB_LOG_LEVEL_TRACE, __FILE__, __LINE__, __PRETTY_FUNCTION__, true)

#define PB_ALWAYS_INFOQ() mDebug(PB_LOG_LEVEL_INFO, __FILE__, __LINE__, __PRETTY_FUNCTION__, true)

#define PB_ALWAYS_WARNQ() mDebug(PB_LOG_LEVEL_WARNING, __FILE__, __LINE__, __PRETTY_FUNCTION__, true)

#define PB_ALWAYS_ERRORQ() mDebug(PB_LOG_LEVEL_ERROR, __FILE__, __LINE__, __PRETTY_FUNCTION__, true)




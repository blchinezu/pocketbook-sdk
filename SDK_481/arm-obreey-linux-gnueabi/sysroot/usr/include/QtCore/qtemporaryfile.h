/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtCore module of the Qt Toolkit.
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

#ifndef QTEMPORARYFILE_H
#define QTEMPORARYFILE_H

#include <QtCore/qiodevice.h>
#include <QtCore/qfile.h>

#ifdef open
#error qtemporaryfile.h must be included before any header file that defines open
#endif

QT_BEGIN_NAMESPACE


#ifndef QT_NO_TEMPORARYFILE

class QTemporaryFilePrivate;
class QLockFilePrivate;

class Q_CORE_EXPORT QTemporaryFile : public QFile
{
#ifndef QT_NO_QOBJECT
    Q_OBJECT
#endif
    Q_DECLARE_PRIVATE(QTemporaryFile)

public:
    QTemporaryFile();
    explicit QTemporaryFile(const QString &templateName);
#ifndef QT_NO_QOBJECT
    explicit QTemporaryFile(QObject *parent);
    QTemporaryFile(const QString &templateName, QObject *parent);
#endif
    ~QTemporaryFile();

    bool autoRemove() const;
    void setAutoRemove(bool b);

    // ### Hides open(flags)
    bool open() { return open(QIODevice::ReadWrite); }

    QString fileName() const;
    QString fileTemplate() const;
    void setFileTemplate(const QString &name);
#if QT_DEPRECATED_SINCE(5,1)
    QT_DEPRECATED inline static QTemporaryFile *createLocalFile(const QString &fileName)
        { return createNativeFile(fileName); }
    QT_DEPRECATED inline static QTemporaryFile *createLocalFile(QFile &file)
        { return createNativeFile(file); }
#endif
    inline static QTemporaryFile *createNativeFile(const QString &fileName)
        { QFile file(fileName); return createNativeFile(file); }
    static QTemporaryFile *createNativeFile(QFile &file);

protected:
    bool open(OpenMode flags);

private:
    friend class QFile;
    friend class QLockFilePrivate;
    Q_DISABLE_COPY(QTemporaryFile)
};

#endif // QT_NO_TEMPORARYFILE

QT_END_NAMESPACE

#endif // QTEMPORARYFILE_H

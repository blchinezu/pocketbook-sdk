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

#ifndef QMIMEDATA_H
#define QMIMEDATA_H

#include <QtCore/qvariant.h>
#include <QtCore/qobject.h>

QT_BEGIN_NAMESPACE


class QUrl;
class QMimeDataPrivate;

class Q_CORE_EXPORT QMimeData : public QObject
{
    Q_OBJECT
public:
    QMimeData();
    ~QMimeData();

    QList<QUrl> urls() const;
    void setUrls(const QList<QUrl> &urls);
    bool hasUrls() const;

    QString text() const;
    void setText(const QString &text);
    bool hasText() const;

    QString html() const;
    void setHtml(const QString &html);
    bool hasHtml() const;

    QVariant imageData() const;
    void setImageData(const QVariant &image);
    bool hasImage() const;

    QVariant colorData() const;
    void setColorData(const QVariant &color);
    bool hasColor() const;

    QByteArray data(const QString &mimetype) const;
    void setData(const QString &mimetype, const QByteArray &data);
    void removeFormat(const QString &mimetype);

    virtual bool hasFormat(const QString &mimetype) const;
    virtual QStringList formats() const;

    void clear();
protected:
    virtual QVariant retrieveData(const QString &mimetype,
                                      QVariant::Type preferredType) const;
private:
    Q_DISABLE_COPY(QMimeData)
    Q_DECLARE_PRIVATE(QMimeData)
};

QT_END_NAMESPACE

#endif // QMIMEDATA_H

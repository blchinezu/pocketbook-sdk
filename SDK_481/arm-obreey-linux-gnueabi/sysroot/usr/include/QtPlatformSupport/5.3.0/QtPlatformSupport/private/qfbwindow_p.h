/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the plugins of the Qt Toolkit.
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

#ifndef QFBWINDOW_P_H
#define QFBWINDOW_P_H

#include <qpa/qplatformwindow.h>

QT_BEGIN_NAMESPACE

class QFbBackingStore;
class QFbScreen;

class QFbWindow : public QPlatformWindow
{
public:
    QFbWindow(QWindow *window);
    ~QFbWindow();

    void raise() Q_DECL_OVERRIDE;
    void lower() Q_DECL_OVERRIDE;

    void setGeometry(const QRect &rect) Q_DECL_OVERRIDE;
    void setVisible(bool visible) Q_DECL_OVERRIDE;

    void setWindowState(Qt::WindowState state) Q_DECL_OVERRIDE;
    void setWindowFlags(Qt::WindowFlags type) Q_DECL_OVERRIDE;
    Qt::WindowFlags windowFlags() const;

    WId winId() const Q_DECL_OVERRIDE { return mWindowId; }

    void setBackingStore(QFbBackingStore *store) { mBackingStore = store; }
    QFbBackingStore *backingStore() const { return mBackingStore; }

    QFbScreen *platformScreen() const;

    virtual void repaint(const QRegion&);

    void propagateSizeHints() Q_DECL_OVERRIDE { }
    bool setKeyboardGrabEnabled(bool) Q_DECL_OVERRIDE { return false; }
    bool setMouseGrabEnabled(bool) Q_DECL_OVERRIDE { return false; }

protected:
    friend class QFbScreen;

    QFbBackingStore *mBackingStore;
    QRect mOldGeometry;
    Qt::WindowFlags mWindowFlags;
    Qt::WindowState mWindowState;

    WId mWindowId;
};

QT_END_NAMESPACE

#endif // QFBWINDOW_P_H


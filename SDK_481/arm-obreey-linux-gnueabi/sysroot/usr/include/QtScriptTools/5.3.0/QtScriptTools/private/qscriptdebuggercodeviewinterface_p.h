/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtSCriptTools module of the Qt Toolkit.
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

#ifndef QSCRIPTDEBUGGERCODEVIEWINTERFACE_P_H
#define QSCRIPTDEBUGGERCODEVIEWINTERFACE_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtWidgets/qwidget.h>

QT_BEGIN_NAMESPACE

class QPoint;
class QStringList;

class QScriptDebuggerCodeViewInterfacePrivate;
class Q_AUTOTEST_EXPORT QScriptDebuggerCodeViewInterface:
    public QWidget
{
    Q_OBJECT
public:
    ~QScriptDebuggerCodeViewInterface();

    virtual QString text() const = 0;
    virtual void setText(const QString &text) = 0;

    virtual int cursorLineNumber() const = 0;
    virtual void gotoLine(int lineNumber) = 0;

    virtual int find(const QString &exp, int options = 0) = 0;

    virtual void setExecutionLineNumber(int lineNumber, bool error) = 0;
    virtual void setExecutableLineNumbers(const QSet<int> &lineNumbers) = 0;

    virtual int baseLineNumber() const = 0;
    virtual void setBaseLineNumber(int lineNumber) = 0;

    virtual void setBreakpoint(int lineNumber) = 0;
    virtual void deleteBreakpoint(int lineNumber) = 0;
    virtual void setBreakpointEnabled(int lineNumber, bool enable) = 0;

Q_SIGNALS:
    void breakpointToggleRequest(int lineNumber, bool on);
    void breakpointEnableRequest(int lineNumber, bool enable);
    void toolTipRequest(const QPoint &pos, int lineNumber, const QStringList &path);

protected:
    QScriptDebuggerCodeViewInterface(
        QScriptDebuggerCodeViewInterfacePrivate &dd,
        QWidget *parent, Qt::WindowFlags flags);

private:
    Q_DECLARE_PRIVATE(QScriptDebuggerCodeViewInterface)
    Q_DISABLE_COPY(QScriptDebuggerCodeViewInterface)
};

QT_END_NAMESPACE

#endif

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

#ifndef QSCRIPTDEBUGGERCODEVIEW_P_H
#define QSCRIPTDEBUGGERCODEVIEW_P_H

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

#include "qscriptdebuggercodeviewinterface_p.h"

QT_BEGIN_NAMESPACE

class QScriptDebuggerCodeViewPrivate;
class Q_AUTOTEST_EXPORT QScriptDebuggerCodeView:
    public QScriptDebuggerCodeViewInterface
{
    Q_OBJECT
public:
    QScriptDebuggerCodeView(QWidget *parent = 0);
    ~QScriptDebuggerCodeView();

    QString text() const;
    void setText(const QString &text);

    int cursorLineNumber() const;
    void gotoLine(int lineNumber);

    int find(const QString &exp, int options = 0);

    void setExecutionLineNumber(int lineNumber, bool error);
    void setExecutableLineNumbers(const QSet<int> &lineNumbers);

    int baseLineNumber() const;
    void setBaseLineNumber(int lineNumber);

    void setBreakpoint(int lineNumber);
    void deleteBreakpoint(int lineNumber);
    void setBreakpointEnabled(int lineNumber, bool enable);

    bool event(QEvent *e);

private:
    Q_DECLARE_PRIVATE(QScriptDebuggerCodeView)
    Q_DISABLE_COPY(QScriptDebuggerCodeView)
};

QT_END_NAMESPACE

#endif

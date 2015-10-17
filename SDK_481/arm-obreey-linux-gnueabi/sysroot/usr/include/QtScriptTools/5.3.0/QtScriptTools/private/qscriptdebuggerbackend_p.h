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

#ifndef QSCRIPTDEBUGGERBACKEND_P_H
#define QSCRIPTDEBUGGERBACKEND_P_H

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

#include <QtCore/qobjectdefs.h>

#include <QtCore/qpair.h>

#include "qscriptbreakpointdata_p.h"
#include "qscriptscriptdata_p.h"

QT_BEGIN_NAMESPACE

class QScriptContext;
class QScriptEngine;
class QScriptDebuggerCommandExecutor;
class QScriptDebuggerEvent;
class QScriptValue;
class QScriptValueIterator;
class QScriptObjectSnapshot;
class QStringList;

typedef QPair<QList<qint64>, QList<qint64> > QScriptScriptsDelta;
typedef QPair<QList<qint64>, QList<qint64> > QScriptContextsDelta;

class QScriptDebuggerBackendPrivate;
class Q_AUTOTEST_EXPORT QScriptDebuggerBackend
{
public:
    QScriptDebuggerBackend();
    virtual ~QScriptDebuggerBackend();

    void attachTo(QScriptEngine *engine);
    void detach();

    QScriptEngine *engine() const;

    void stepInto(int count = 1);
    void stepOver(int count = 1);
    void stepOut();
    void continueEvalution();
    void interruptEvaluation();
    void runToLocation(const QString &fileName, int lineNumber);
    void runToLocation(qint64 scriptId, int lineNumber);
    void returnToCaller(int contextIndex, const QScriptValue &value);
    void evaluate(int contextIndex, const QString &program,
                  const QString &fileName, int lineNumber);

    int setBreakpoint(const QScriptBreakpointData &data);
    bool deleteBreakpoint(int id);
    void deleteAllBreakpoints();
    QScriptBreakpointData breakpointData(int id) const;
    bool setBreakpointData(int id, const QScriptBreakpointData &data);
    QScriptBreakpointMap breakpoints() const;

    QScriptScriptMap scripts() const;
    QScriptScriptData scriptData(qint64 id) const;
    void scriptsCheckpoint();
    QScriptScriptsDelta scriptsDelta() const;
    qint64 resolveScript(const QString &fileName) const;

    int contextCount() const;
    QScriptContext *context(int index) const;
    QStringList backtrace() const;
    QList<qint64> contextIds() const;
    QScriptContextsDelta contextsCheckpoint();

    int newScriptObjectSnapshot();
    QScriptObjectSnapshot *scriptObjectSnapshot(int id) const;
    void deleteScriptObjectSnapshot(int id);

    int newScriptValueIterator(const QScriptValue &object);
    QScriptValueIterator *scriptValueIterator(int id) const;
    void deleteScriptValueIterator(int id);

    QScriptValue traceFunction() const;
    QScriptValue assertFunction() const;
    QScriptValue fileNameFunction() const;
    QScriptValue lineNumberFunction() const;

    void doPendingEvaluate(bool postEvent);

    bool ignoreExceptions() const;
    void setIgnoreExceptions(bool ignore);

    QScriptDebuggerCommandExecutor *commandExecutor() const;
    void setCommandExecutor(QScriptDebuggerCommandExecutor *executor);

    virtual void resume() = 0;

protected:
    virtual void event(const QScriptDebuggerEvent &event) = 0;

protected:
    QScriptDebuggerBackend(QScriptDebuggerBackendPrivate &dd);
    QScopedPointer<QScriptDebuggerBackendPrivate> d_ptr;

private:
    Q_DECLARE_PRIVATE(QScriptDebuggerBackend)
    Q_DISABLE_COPY(QScriptDebuggerBackend)
};

QT_END_NAMESPACE

#endif

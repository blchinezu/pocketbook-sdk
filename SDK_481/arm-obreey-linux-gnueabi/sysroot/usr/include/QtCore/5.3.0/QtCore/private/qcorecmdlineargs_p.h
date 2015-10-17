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

#ifndef QCORECMDLINEARGS_P_H
#define QCORECMDLINEARGS_P_H

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

#include "QtCore/qstring.h"
#include "QtCore/qstringlist.h"

QT_BEGIN_NAMESPACE

#if defined(Q_OS_WIN) && !defined(Q_OS_WINRT)

QT_BEGIN_INCLUDE_NAMESPACE
#  include "QtCore/qvector.h"
#  include <qt_windows.h>
QT_END_INCLUDE_NAMESPACE

// template implementation of the parsing algorithm
// this is used from qcoreapplication_win.cpp and the tools (rcc, uic...)

template<typename Char>
static QVector<Char*> qWinCmdLine(Char *cmdParam, int length, int &argc)
{
    QVector<Char*> argv(8);
    Char *p = cmdParam;
    Char *p_end = p + length;

    argc = 0;

    while (*p && p < p_end) {                                // parse cmd line arguments
        while (QChar((short)(*p)).isSpace())                          // skip white space
            p++;
        if (*p && p < p_end) {                                // arg starts
            int quote;
            Char *start, *r;
            if (*p == Char('\"')) {
                quote = *p;
                start = ++p;
            } else {
                quote = 0;
                start = p;
            }
            r = start;
            while (*p && p < p_end) {
                if (quote) {
                    if (*p == quote) {
                        p++;
                        if (QChar((short)(*p)).isSpace())
                            break;
                        quote = 0;
                    }
                }
                if (*p == '\\') {                // escape char?
                    // testing by looking at argc, argv shows that it only escapes quotes
                    if (p < p_end && (*(p+1) == Char('\"')))
                        p++;
                } else {
                    if (!quote && (*p == Char('\"'))) {
                        quote = *p++;
                        continue;
                    } else if (QChar((short)(*p)).isSpace() && !quote)
                        break;
                }
                if (*p)
                    *r++ = *p++;
            }
            if (*p && p < p_end)
                p++;
            *r = Char('\0');

            if (argc >= (int)argv.size()-1)        // expand array
                argv.resize(argv.size()*2);
            argv[argc++] = start;
        }
    }
    argv[argc] = 0;

    return argv;
}

static inline QStringList qWinCmdArgs(QString cmdLine) // not const-ref: this might be modified
{
    QStringList args;

    int argc = 0;
    QVector<wchar_t*> argv = qWinCmdLine<wchar_t>((wchar_t *)cmdLine.utf16(), cmdLine.length(), argc);
    for (int a = 0; a < argc; ++a) {
        args << QString::fromWCharArray(argv[a]);
    }

    return args;
}

static inline QStringList qCmdLineArgs(int argc, char *argv[])
{
    Q_UNUSED(argc)
    Q_UNUSED(argv)
    QString cmdLine = QString::fromWCharArray(GetCommandLine());
    return qWinCmdArgs(cmdLine);
}

#else  // Q_OS_WIN && !Q_OS_WINRT

static inline QStringList qCmdLineArgs(int argc, char *argv[])
{
    QStringList args;
    for (int i = 0; i != argc; ++i)
        args += QString::fromLocal8Bit(argv[i]);
    return args;
}

#endif // !Q_OS_WIN || Q_OS_WINRT

QT_END_NAMESPACE

#endif // QCORECMDLINEARGS_WIN_P_H

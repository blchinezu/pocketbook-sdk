/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtWidgets module of the Qt Toolkit.
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

#ifndef QCALENDARTEXTNAVIGATOR_P_H
#define QCALENDARTEXTNAVIGATOR_P_H

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

#include <QtCore/qobject.h>
#include <QtCore/qdatetime.h>
#include <QtCore/qbasictimer.h>

#ifndef QT_NO_CALENDARWIDGET

QT_BEGIN_NAMESPACE

class QLabel;
class QCalendarDateValidator;
class QFrame;

class QCalendarTextNavigator: public QObject
{
    Q_OBJECT
public:
    QCalendarTextNavigator(QObject *parent = 0)
        : QObject(parent), m_dateText(0), m_dateFrame(0), m_dateValidator(0), m_widget(0), m_editDelay(1500), m_date(QDate::currentDate()) { }

    QWidget *widget() const;
    void setWidget(QWidget *widget);

    int dateEditAcceptDelay() const;
    void setDateEditAcceptDelay(int delay);

    QDate date() const;
    void setDate(const QDate &date);

    bool eventFilter(QObject *o, QEvent *e);
    void timerEvent(QTimerEvent *e);

signals:
    void dateChanged(const QDate &date);
    void editingFinished();

private:
    void applyDate();
    void updateDateLabel();
    void createDateLabel();
    void removeDateLabel();

    QLabel *m_dateText;
    QFrame *m_dateFrame;
    QBasicTimer m_acceptTimer;
    QCalendarDateValidator *m_dateValidator;
    QWidget *m_widget;
    int m_editDelay;

    QDate m_date;
};

QT_END_NAMESPACE

#endif // QT_NO_CALENDARWIDGET

#endif


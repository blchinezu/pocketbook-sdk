/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtPrintSupport module of the Qt Toolkit.
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


#ifndef QCUPSJOBWIDGET_P_H
#define QCUPSJOBWIDGET_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// to version without notice, or even be removed.
//
// We mean it.
//
//

#include <ui_qcupsjobwidget.h>
#include <private/qcups_p.h>

QT_BEGIN_NAMESPACE

#ifndef QT_NO_PRINTER

class QString;
class QTime;
class QPrinter;

class QCupsJobWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QCupsJobWidget(QWidget *parent = 0);
    ~QCupsJobWidget();
    void setPrinter(QPrinter *printer);
    void setupPrinter();

private Q_SLOTS:
    void toggleJobHoldTime();

private:

    void setJobHold(QCUPSSupport::JobHoldUntil jobHold = QCUPSSupport::NoHold, const QTime &holdUntilTime = QTime());
    QCUPSSupport::JobHoldUntil jobHold() const;
    QTime jobHoldTime() const;

    void setJobBilling(const QString &jobBilling = QString());
    QString jobBilling() const;

    void setJobPriority(int priority = 50);
    int jobPriority() const;

    void setStartBannerPage(const QCUPSSupport::BannerPage bannerPage = QCUPSSupport::NoBanner);
    QCUPSSupport::BannerPage startBannerPage() const;

    void setEndBannerPage(const QCUPSSupport::BannerPage bannerPage = QCUPSSupport::NoBanner);
    QCUPSSupport::BannerPage endBannerPage() const;

    void initJobHold();
    void initJobBilling();
    void initJobPriority();
    void initBannerPages();

    QPrinter *m_printer;
    Ui::QCupsJobWidget m_ui;

    Q_DISABLE_COPY(QCupsJobWidget)
};

#endif // QT_NO_PRINTER

QT_END_NAMESPACE

#endif  // QCUPSJOBWIDGET_P_H

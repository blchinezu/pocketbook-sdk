/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtGui module of the Qt Toolkit.
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
#ifndef QPAGESETUPDIALOG_UNIX_P_H
#define QPAGESETUPDIALOG_UNIX_P_H

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

#include "qglobal.h"

#ifndef QT_NO_PRINTDIALOG

#include "qprinter.h"

#include <QtGui/qpagelayout.h>

#include <ui_qpagesetupwidget.h>

QT_BEGIN_NAMESPACE

class QPrinter;
class QPagePreview;

class QPageSetupWidget : public QWidget {
    Q_OBJECT
public:
    explicit QPageSetupWidget(QWidget *parent = 0);
    explicit QPageSetupWidget(QPrinter *printer, QWidget *parent = 0);

    void setPrinter(QPrinter *printer);
    void selectPrinter(QPrinter::OutputFormat outputFormat, const QString &printerName);
    void setupPrinter() const;

private slots:
    void pageSizeChanged();
    void pageOrientationChanged();
    void pagesPerSheetChanged();
    void unitChanged();
    void topMarginChanged(double newValue);
    void bottomMarginChanged(double newValue);
    void leftMarginChanged(double newValue);
    void rightMarginChanged(double newValue);

private:
    friend class QUnixPrintWidgetPrivate;  // Needed by checkFields()

    void updateWidget();
    void initUnits();
    void initPagesPerSheet();
    void initPageSizes();

    Ui::QPageSetupWidget m_ui;
    QPagePreview *m_pagePreview;
    QPrinter *m_printer;
    QPrinter::OutputFormat m_outputFormat;
    QString m_printerName;
    QPageLayout m_pageLayout;
    QPageLayout::Unit m_units;
    bool m_blockSignals;
};

QT_END_NAMESPACE

#endif // QT_NO_PRINTDIALOG
#endif

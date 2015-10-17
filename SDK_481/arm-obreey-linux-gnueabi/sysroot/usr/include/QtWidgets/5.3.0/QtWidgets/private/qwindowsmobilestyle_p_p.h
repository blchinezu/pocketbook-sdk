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

#ifndef QWINDOWSMOBILESTYLE_P_P_H
#define QWINDOWSMOBILESTYLE_P_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of qapplication_*.cpp, qwidget*.cpp and qfiledialog.cpp.  This header
// file may change from version to version without notice, or even be removed.
//
// We mean it.
//

#include "qwindowsmobilestyle_p.h"
#include "qwindowsstyle_p_p.h"

QT_BEGIN_NAMESPACE

#ifndef QT_NO_STYLE_WINDOWSMOBILE

class QStyleOptionTab;
class QStyleOptionSlider;

class QWindowsMobileStylePrivate : public QWindowsStylePrivate
{
    Q_DECLARE_PUBLIC(QWindowsMobileStyle)
public:
    QWindowsMobileStylePrivate();
    bool doubleControls;
    bool smartphone;
#ifdef Q_OS_WINCE_WM
    bool wm65;
#endif

    QImage imageRadioButton;
    QImage imageRadioButtonChecked;
    QImage imageRadioButtonHighlighted;
    QImage imageChecked;
    QImage imageCheckedBold;
    QImage imageArrowDown;
    QImage imageArrowUp;
    QImage imageArrowLeft;
    QImage imageArrowRight;
    QImage imageArrowDownBig;
    QImage imageArrowUpBig;
    QImage imageArrowLeftBig;
    QImage imageArrowRightBig;
    QImage imageClose;
    QImage imageMaximize;
    QImage imageNormalize;
    QImage imageMinimize;

    void setupWindowsMobileStyle65();

#ifdef Q_OS_WINCE_WM
    //Windows Mobile 6.5 images
    QImage imageScrollbarHandleUp;
    QImage imageScrollbarHandleDown;
    QImage imageScrollbarHandleUpHigh;
    QImage imageScrollbarHandleDownHigh;
    QImage imageScrollbarGripUp;
    QImage imageScrollbarGripDown;
    QImage imageScrollbarGripMiddle;
    QImage imageListViewHighlightCornerLeft;
    QImage imageListViewHighlightCornerRight;
    QImage imageListViewHighlightMiddle;
    QImage imageTabEnd;
    QImage imageTabSelectedEnd;
    QImage imageTabSelectedBegin;
    QImage imageTabMiddle;

    QColor currentTintHigh;
    QColor currentTintButton;

    void tintImagesHigh(QColor color);
    void tintImagesButton(QColor color);
    void tintListViewHighlight(QColor color);

#endif //Q_OS_WINCE_WM

    void drawScrollbarHandleUp(QPainter *p, QStyleOptionSlider *opt, bool completeFrame = false, bool secondScrollBar = false);
    void drawScrollbarHandleDown(QPainter *p, QStyleOptionSlider *opt, bool completeFrame = false, bool secondScrollBar = false);
    void drawScrollbarGroove(QPainter *p, const QStyleOptionSlider *opt);
    void drawScrollbarGrip(QPainter *p, QStyleOptionSlider *newScrollbar, const QStyleOptionComplex *option, bool drawCompleteFrame);
    void drawTabBarTab(QPainter *p, const QStyleOptionTab *tab);
    void drawPanelItemViewSelected(QPainter *painter, const QStyleOptionViewItem *option, QRect rect = QRect());

};

QT_END_NAMESPACE

#endif // QT_NO_STYLE_WINDOWSMOBILE
#endif //QWINDOWSMOBILESTYLE_P_P_H

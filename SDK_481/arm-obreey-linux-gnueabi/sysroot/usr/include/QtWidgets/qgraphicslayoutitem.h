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

#ifndef QGRAPHICSLAYOUTITEM_H
#define QGRAPHICSLAYOUTITEM_H

#include <QtCore/qscopedpointer.h>
#include <QtWidgets/qsizepolicy.h>
#include <QtGui/qevent.h>

QT_BEGIN_NAMESPACE


#if !defined(QT_NO_GRAPHICSVIEW)

class QGraphicsLayoutItemPrivate;
class QGraphicsItem;
class Q_WIDGETS_EXPORT QGraphicsLayoutItem
{
public:
    QGraphicsLayoutItem(QGraphicsLayoutItem *parent = 0, bool isLayout = false);
    virtual ~QGraphicsLayoutItem();

    void setSizePolicy(const QSizePolicy &policy);
    void setSizePolicy(QSizePolicy::Policy hPolicy, QSizePolicy::Policy vPolicy, QSizePolicy::ControlType controlType = QSizePolicy::DefaultType);
    QSizePolicy sizePolicy() const;

    void setMinimumSize(const QSizeF &size);
    inline void setMinimumSize(qreal w, qreal h);
    QSizeF minimumSize() const;
    void setMinimumWidth(qreal width);
    inline qreal minimumWidth() const;
    void setMinimumHeight(qreal height);
    inline qreal minimumHeight() const;

    void setPreferredSize(const QSizeF &size);
    inline void setPreferredSize(qreal w, qreal h);
    QSizeF preferredSize() const;
    void setPreferredWidth(qreal width);
    inline qreal preferredWidth() const;
    void setPreferredHeight(qreal height);
    inline qreal preferredHeight() const;

    void setMaximumSize(const QSizeF &size);
    inline void setMaximumSize(qreal w, qreal h);
    QSizeF maximumSize() const;
    void setMaximumWidth(qreal width);
    inline qreal maximumWidth() const;
    void setMaximumHeight(qreal height);
    inline qreal maximumHeight() const;

    virtual void setGeometry(const QRectF &rect);
    QRectF geometry() const;
    virtual void getContentsMargins(qreal *left, qreal *top, qreal *right, qreal *bottom) const;
    QRectF contentsRect() const;

    QSizeF effectiveSizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const;

    virtual void updateGeometry();

    QGraphicsLayoutItem *parentLayoutItem() const;
    void setParentLayoutItem(QGraphicsLayoutItem *parent);

    bool isLayout() const;
    QGraphicsItem *graphicsItem() const;
    bool ownedByLayout() const;

protected:
    void setGraphicsItem(QGraphicsItem *item);
    void setOwnedByLayout(bool ownedByLayout);
    QGraphicsLayoutItem(QGraphicsLayoutItemPrivate &dd);

    virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const = 0;
    QScopedPointer<QGraphicsLayoutItemPrivate> d_ptr;

private:
    QSizeF *effectiveSizeHints(const QSizeF &constraint) const;
    Q_DECLARE_PRIVATE(QGraphicsLayoutItem)

    friend class QGraphicsLayout;
};

Q_DECLARE_INTERFACE(QGraphicsLayoutItem, "org.qt-project.Qt.QGraphicsLayoutItem")

inline void QGraphicsLayoutItem::setMinimumSize(qreal aw, qreal ah)
{ setMinimumSize(QSizeF(aw, ah)); }
inline void QGraphicsLayoutItem::setPreferredSize(qreal aw, qreal ah)
{ setPreferredSize(QSizeF(aw, ah)); }
inline void QGraphicsLayoutItem::setMaximumSize(qreal aw, qreal ah)
{ setMaximumSize(QSizeF(aw, ah)); }

inline qreal QGraphicsLayoutItem::minimumWidth() const
{ return effectiveSizeHint(Qt::MinimumSize).width(); }
inline qreal QGraphicsLayoutItem::minimumHeight() const
{ return effectiveSizeHint(Qt::MinimumSize).height(); }

inline qreal QGraphicsLayoutItem::preferredWidth() const
{ return effectiveSizeHint(Qt::PreferredSize).width(); }
inline qreal QGraphicsLayoutItem::preferredHeight() const
{ return effectiveSizeHint(Qt::PreferredSize).height(); }

inline qreal QGraphicsLayoutItem::maximumWidth() const
{ return effectiveSizeHint(Qt::MaximumSize).width(); }
inline qreal QGraphicsLayoutItem::maximumHeight() const
{ return effectiveSizeHint(Qt::MaximumSize).height(); }

#endif

QT_END_NAMESPACE

#endif

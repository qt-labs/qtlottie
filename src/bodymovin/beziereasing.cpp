/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the lottie-qt module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
****************************************************************************/

#include <beziereasing_p.h>

QT_BEGIN_NAMESPACE

void BezierEasing::addCubicBezierSegment(const QPointF &c1, const QPointF &c2, const QPointF &endPoint)
{
    mBezier = QBezier::fromPoints(QPointF(0.0, 0.0), c1, c2, endPoint);
}

qreal BezierEasing::valueForProgress(qreal progress) const
{
    qreal res = mBezier.pointAt(tForX(progress)).y();
    return qBound(qreal(0.0), res, qreal(1.0));
}

qreal BezierEasing::tForX(qreal x) const
{
    if (x <= 0.0)
        return 0.0;
    else if (x >= 1.0)
        return 1.0;

    qreal t0 = 0.0;
    qreal t1 = 1.0;

    for (int i = 0; i < 10; i++) {  // 10 iterations gives error smaller than 0.001
        qreal t = qreal(0.5) * (t0 + t1);
        qreal a, b, c, d;
        QBezier::coefficients(t, a, b, c, d);
        qreal xt = a * mBezier.x1 + b * mBezier.x2 + c * mBezier.x3 + d * mBezier.x4;
        if (xt < x)
            t0 = t;
        else
            t1 = t;
    }

    return t0;
}

QT_END_NAMESPACE

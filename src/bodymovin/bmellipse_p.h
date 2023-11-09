// Copyright (C) 2018 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#ifndef BMELLIPSE_P_H
#define BMELLIPSE_P_H

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

#include <QRect>
#include <QPointF>
#include <QBrush>
#include <QPen>
#include <QPainterPath>

#include <QtBodymovin/private/bmshape_p.h>
#include <QtBodymovin/private/bmproperty_p.h>
#include <QtBodymovin/private/bmspatialproperty_p.h>
#include <QtBodymovin/private/bmfill_p.h>
#include <QtBodymovin/private/bmstroke_p.h>

QT_BEGIN_NAMESPACE

class QJsonObject;

class BODYMOVIN_EXPORT BMEllipse : public BMShape
{
public:
    BMEllipse() = default;
    explicit BMEllipse(const BMEllipse &other);
    BMEllipse(const QJsonObject &definition, BMBase *parent = nullptr);

    BMBase *clone() const override;

    void construct(const QJsonObject &definition);

    void updateProperties(int frame) override;
    void render(LottieRenderer &renderer) const override;

    bool acceptsTrim() const override;

    QPointF position() const;
    QSizeF size() const;

protected:
    BMSpatialProperty m_position;
    BMProperty2D<QSizeF> m_size;
};

QT_END_NAMESPACE

#endif // BMELLIPSE_P_H

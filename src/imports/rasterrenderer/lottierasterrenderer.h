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

#ifndef LOTTIERASTERRENDERER_H
#define LOTTIERASTERRENDERER_H

#include <QPainterPath>
#include <QPainter>
#include <QStack>
#include <QRegion>

#include <QtBodymovin/private/lottierenderer_p.h>

QT_BEGIN_NAMESPACE

class QPainter;

class LottieRasterRenderer : public LottieRenderer
{
public:
    explicit LottieRasterRenderer(QPainter *m_painter);
    ~LottieRasterRenderer() override = default;

    void saveState() override;
    void restoreState() override;

    void render(const BMLayer &layer) override;
    void render(const BMRect &rect) override;
    void render(const BMEllipse &ellipse) override;
    void render(const BMRound &round) override;
    void render(const BMFill &fill) override;
    void render(const BMGFill &shape) override;
    void render(const BMStroke &stroke) override;
    void render(const BMBasicTransform &transform) override;
    void render(const BMShapeTransform &transform) override;
    void render(const BMFreeFormShape &shape) override;
    void render(const BMTrimPath &trans) override;
    void render(const BMFillEffect &effect) override;
    void render(const BMRepeater &repeater) override;

protected:
    QPainter *m_painter = nullptr;
    QPainterPath m_unitedPath;
    // TODO: create a context to handle paths and effect
    // instead of pushing each to a stack independently
    QStack<QPainterPath> m_pathStack;
    QStack<const BMFillEffect*> m_fillEffectStack;
    const BMFillEffect *m_fillEffect = nullptr;
    const BMRepeaterTransform *m_repeaterTransform = nullptr;
    int m_repeatCount = 1;
    qreal m_repeatOffset = 0.0;
    bool m_buildingClipRegion = false;
    QPainterPath m_clipPath;

private:
    void applyRepeaterTransform(int instance);
};

QT_END_NAMESPACE

#endif // LOTTIERASTERRENDERER_H


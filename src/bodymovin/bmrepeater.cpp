/****************************************************************************
**
** Copyright (C) 2018 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the lottie-qt module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "bmrepeater_p.h"

BMRepeater::BMRepeater(const QJsonObject &definition, BMBase *parent)
{
    setParent(parent);
    m_transform.setParent(this);
    construct(definition);
}

BMBase *BMRepeater::clone() const
{
    return new BMRepeater(*this);
}

void BMRepeater::construct(const QJsonObject &definition)
{
    qCDebug(lcLottieQtBodymovinParser) << "BMRepeater::construct():" << m_name;

    BMBase::parse(definition);
    if (m_hidden)
        return;

    QJsonObject copies = definition.value(QLatin1String("c")).toObject();
    copies = resolveExpression(copies);
    m_copies.construct(copies);

    QJsonObject offset = definition.value(QLatin1String("o")).toObject();
    offset = resolveExpression(offset);
    m_offset.construct(offset);

    m_transform.construct(definition.value(QLatin1String("tr")).toObject());
}

void BMRepeater::updateProperties(int frame)
{
    m_copies.update(frame);
    m_offset.update(frame);
    m_transform.setInstanceCount(m_copies.value());
    m_transform.updateProperties(frame);
}

void BMRepeater::render(LottieRenderer &renderer) const
{
    renderer.render(*this);
}

int BMRepeater::copies() const
{
    return m_copies.value();
}

qreal BMRepeater::offset() const
{
    return m_offset.value();
}

const BMRepeaterTransform &BMRepeater::transform() const
{
    return m_transform;
}

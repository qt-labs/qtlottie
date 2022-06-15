/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
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
******************************************************************************/

#ifndef BMGLOBAL_H
#define BMGLOBAL_H

#include <QtGlobal>

#if defined(BODYMOVIN_LIBRARY)
#  define BODYMOVIN_EXPORT Q_DECL_EXPORT
#else
#  define BODYMOVIN_EXPORT Q_DECL_IMPORT
#endif

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

#endif // BMGLOBAL_H

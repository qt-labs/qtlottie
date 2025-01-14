// Copyright (C) 2018 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtTest/QtTest>

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "private/bmlayer_p.h"
#include "private/bmrepeater_p.h"

using namespace Qt::StringLiterals;

class tst_BMRepeater : public QObject
{
    Q_OBJECT

public:
    tst_BMRepeater();
    ~tst_BMRepeater();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testStaticInitialCopy();
    void testStaticInitialOffset();
    void testStaticUpdatedCopy();
    void testStaticUpdatedOffset();

    void testAnimatedInitialCopy();
    void testAnimatedInitialOffset();
    void testAnimatedUpdatedCopy();
    void testAnimatedUpdatedOffset();

    void testName();
    void testType();
    void testHidden();
    void testActive();

private:
    void loadTestData(const QString &filename);
    void updateProperty(int frame);

    BMRepeater *m_repeater = nullptr;

};

tst_BMRepeater::tst_BMRepeater()
{

}

tst_BMRepeater::~tst_BMRepeater()
{

}

void tst_BMRepeater::initTestCase()
{

}

void tst_BMRepeater::cleanupTestCase()
{

}

void tst_BMRepeater::testStaticInitialCopy()
{
    loadTestData("repeater_static.json");
    QVERIFY(m_repeater->copies() == 3);
}

void tst_BMRepeater::testStaticInitialOffset()
{
    loadTestData("repeater_static.json");
    QVERIFY(qFuzzyCompare(m_repeater->offset(), 0.0));
}

void tst_BMRepeater::testStaticUpdatedCopy()
{
    loadTestData("repeater_static.json");
    updateProperty(180);
    QVERIFY(m_repeater->copies() == 3);
}

void tst_BMRepeater::testStaticUpdatedOffset()
{
    loadTestData("repeater_static.json");
    updateProperty(180);
    QVERIFY(qFuzzyCompare(m_repeater->offset(), 0.0));
}

void tst_BMRepeater::testAnimatedInitialCopy()
{
    loadTestData("repeater_animated.json");
    updateProperty(0);
    QVERIFY(m_repeater->copies() == 3);
}

void tst_BMRepeater::testAnimatedInitialOffset()
{
    loadTestData("repeater_animated.json");
    updateProperty(0);
    QVERIFY(qFuzzyCompare(m_repeater->offset(), 0.0));
}

void tst_BMRepeater::testAnimatedUpdatedCopy()
{
    loadTestData("repeater_animated.json");
    updateProperty(180);
    QVERIFY(m_repeater->copies() == 30);
}

void tst_BMRepeater::testAnimatedUpdatedOffset()
{
    loadTestData("repeater_animated.json");
    updateProperty(180);
    QVERIFY(qFuzzyCompare(m_repeater->offset(), 15.0));
}

void tst_BMRepeater::testName()
{
    loadTestData("repeater_static.json");
    QVERIFY(m_repeater->name() == QString("Repeater 1"));
}

void tst_BMRepeater::testType()
{
    loadTestData("repeater_static.json");
    QVERIFY(m_repeater->type() == BM_SHAPE_REPEATER_IX);
}

void tst_BMRepeater::testActive()
{
    loadTestData("repeater_static.json");
    QVERIFY(m_repeater->active(100) == true);

    loadTestData("repeater_hidden.json");
    QVERIFY(m_repeater->active(100) == false);
}

void tst_BMRepeater::testHidden()
{
    loadTestData("repeater_static.json");
    QVERIFY(m_repeater->hidden() == false);

    loadTestData("repeater_hidden.json");
    QVERIFY(m_repeater->hidden() == true);
}


void tst_BMRepeater::loadTestData(const QString &filename)
{
    if (m_repeater) {
        delete m_repeater;
        m_repeater = nullptr;
    }

    QFile sourceFile(QFINDTESTDATA(QLatin1String("data/") + filename));
    if (!sourceFile.exists())
        QFAIL("File does not exist");
    if (!sourceFile.open(QIODevice::ReadOnly))
        QFAIL("Cannot read test file");

    QByteArray json = sourceFile.readAll();

    sourceFile.close();

    QJsonDocument doc = QJsonDocument::fromJson(json);
    QJsonObject rootObj = doc.object();
    if (rootObj.empty())
        QFAIL("Cannot parse test file");

    const auto version = QVersionNumber::fromString(rootObj.value("v"_L1).toString());

    QJsonArray layers = rootObj.value(QLatin1String("layers")).toArray();
    QJsonObject layerObj = layers[0].toObject();
    int type = layerObj.value(QLatin1String("ty")).toInt();
    if (type != 4)
        QFAIL("It's not shape layer");

    QJsonArray shapes = layerObj.value(QLatin1String("shapes")).toArray();
    QJsonArray::const_iterator shapesIt = shapes.constBegin();
    BMShape* shape = nullptr;
    while (shapesIt != shapes.end()) {
        QJsonObject childObj = (*shapesIt).toObject();
        shape = BMShape::construct(childObj, version);
        QVERIFY(shape != nullptr);
        if (shape->type() == BM_SHAPE_REPEATER_IX)
            break;
        shapesIt++;
    }

    m_repeater = static_cast<BMRepeater*>(shape);

    QVERIFY(m_repeater != nullptr);
}

void tst_BMRepeater::updateProperty(int frame)
{
    m_repeater->updateProperties(frame);
}

QTEST_MAIN(tst_BMRepeater)
#include "tst_bmrepeater.moc"

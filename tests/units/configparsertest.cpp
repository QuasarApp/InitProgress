//#
//# Copyright (C) 2020-2021 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "configparsertest.h"
#include <quasarapp.h>
#include "CopyrighFixer/config.h"
#include "CopyrighFixer/configparser.h"

ConfigParserTest::ConfigParserTest() {

}

ConfigParserTest::~ConfigParserTest() {

}

void ConfigParserTest::test() {
    testParsOpt();
}

CopyrighFixer::Signature ConfigParserTest::generateRandomSign(QString& filename) const {

    int unixTime = time(0);

    CopyrighFixer::Owner ownerObj;
    ownerObj.setName("QuasarApp");
    ownerObj.setTimePoint(unixTime);

    QMap<int, CopyrighFixer::Owner> OwnerMap;
    OwnerMap.insert(ownerObj.getTimePoint(), ownerObj);

    CopyrighFixer::Signature sign_toJson;
    sign_toJson.setLicenseTitle("Copyright (C) 2020-2021 QuasarApp.");
    sign_toJson.setMessage("Distributed under the lgplv3 software license, see the accompany.");
    sign_toJson.setMapOwners(OwnerMap);
    sign_toJson.toJson(filename);

    return sign_toJson;
}

void ConfigParserTest::testParseConf() const {
    QStringList lstOpt = {"-sourceDir", ".", "-sign", "testSign.json"};
    QuasarAppUtils::Params::parseParams(lstOpt);

    CopyrighFixer::Config testConfig;
    CopyrighFixer::ConfigParser testParserConf;

    // True if parameters were parsed without errors.
    QVERIFY(testParserConf.parseOptions(testConfig));

    // True if signature were parsed without errors.
    QVERIFY(testConfig.getSignVal().isValid());
}

void ConfigParserTest::testSrcKey() const {
    QStringList lstOpt = {"-source", ".", "-sign", "testSign.json"};
    QuasarAppUtils::Params::parseParams(lstOpt);

    CopyrighFixer::Config testConfig;
    CopyrighFixer::ConfigParser testParserConf;

    // True if the sourceDir key is entered correctly.
    QVERIFY(testParserConf.parseOptions(testConfig));
}

void ConfigParserTest::testSrcPath() const {

    QStringList lstOpt = {"-sourceDir", "./ParserProj", "-sign", "testSign.json"};
    QuasarAppUtils::Params::parseParams(lstOpt);

    CopyrighFixer::Config testConfig;
    CopyrighFixer::ConfigParser testParserConf;

    // If the path to the directory is passed incorrectly return false.
    QVERIFY(!testParserConf.parseOptions(testConfig));
}

void ConfigParserTest::testSignKey() const {
    QStringList lstOpt = {"-sourceDir", ".", "-signa", "testSign.json"};
    QuasarAppUtils::Params::parseParams(lstOpt);

    CopyrighFixer::Config testConfig;
    CopyrighFixer::ConfigParser testParserConf;

    // After parse the Config object key sign  should be invalid.
    QVERIFY(!testParserConf.parseOptions(testConfig));
}

void ConfigParserTest::testSignPath() const {
    QStringList lstOpt = {"-sourceDir", ".", "-sign", "/home/testSign.json"};
    QuasarAppUtils::Params::parseParams(lstOpt);

    CopyrighFixer::Config testConfig;
    CopyrighFixer::ConfigParser testParserConf;

    // After parse the Config object path to file signature  should be invalid.
    QVERIFY(!testParserConf.parseOptions(testConfig));

}

void ConfigParserTest::testParsOpt() {

    QString testFileSign = "testSign.json";

    // Initialization of a signature with random parameters.
    generateRandomSign(testFileSign);

    testParseConf();
    QuasarAppUtils::Params::clearParsedData();

    testSrcKey();
    testSrcPath();
    QuasarAppUtils::Params::clearParsedData();

    testSignKey();
    testSignPath();
    QuasarAppUtils::Params::clearParsedData();

    QFile::remove(testFileSign);

}

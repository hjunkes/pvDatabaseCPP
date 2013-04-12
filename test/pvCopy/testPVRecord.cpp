/*testPVRecordMain.cpp */
/**
 * Copyright - See the COPYRIGHT that is included with this distribution.
 * EPICS pvData is distributed subject to a Software License Agreement found
 * in file LICENSE that is included with this distribution.
 */
/**
 * @author mrk
 */

/* Author: Marty Kraimer */

#include <cstddef>
#include <cstdlib>
#include <cstddef>
#include <string>
#include <cstdio>
#include <memory>
#include <iostream>

#include <epicsStdio.h>
#include <epicsMutex.h>
#include <epicsEvent.h>
#include <epicsThread.h>

#include <pv/standardField.h>
#include <pv/standardPVField.h>
#include <pv/pvData.h>
#include <pv/pvAccess.h>
#include <pv/pvCopy.h>
#include <pv/powerSupplyRecordTest.h>


using namespace std;
using std::tr1::static_pointer_cast;
using namespace epics::pvData;
using namespace epics::pvAccess;
using namespace epics::pvDatabase;

static PVRecordPtr createScalar(
    String const & recordName,
    ScalarType scalarType,
    String const & properties)
{
    PVStructurePtr pvStructure = getStandardPVField()->scalar(scalarType,properties);
    PVRecordPtr pvRecord = PVRecord::create(recordName,pvStructure);
    pvStructure.reset();
    return pvRecord;
}

static PVRecordPtr createScalarArray(
    String const & recordName,
    ScalarType scalarType,
    String const & properties)
{
    PVStructurePtr pvStructure = getStandardPVField()->scalarArray(scalarType,properties);
    return PVRecord::create(recordName,pvStructure);
}

static PowerSupplyRecordTestPtr createPowerSupply(String const & recordName)
{
    FieldCreatePtr fieldCreate = getFieldCreate();
    StandardFieldPtr standardField = getStandardField();
    PVDataCreatePtr pvDataCreate = getPVDataCreate();
    size_t nfields = 5;
    StringArray names;
    names.reserve(nfields);
    FieldConstPtrArray powerSupply;
    powerSupply.reserve(nfields);
    names.push_back("alarm");
    powerSupply.push_back(standardField->alarm());
    names.push_back("timeStamp");
    powerSupply.push_back(standardField->timeStamp());
    String properties("alarm,display");
    names.push_back("voltage");
    powerSupply.push_back(standardField->scalar(pvDouble,properties));
    names.push_back("power");
    powerSupply.push_back(standardField->scalar(pvDouble,properties));
    names.push_back("current");
    powerSupply.push_back(standardField->scalar(pvDouble,properties));
    return PowerSupplyRecordTest::create(recordName,
        pvDataCreate->createPVStructure(
            fieldCreate->createStructure(names,powerSupply)));
}

static void scalarTest()
{
    cout << endl << endl << "****scalarTest****" << endl;
    PVRecordPtr pvRecord;
    pvRecord = createScalar("doubleRecord",pvDouble,"alarm,timeStamp.display");
    pvRecord->destroy();
}

static void arrayTest()
{
    cout << endl << endl << "****arrayTest****" << endl;
    PVRecordPtr pvRecord;
    pvRecord = createScalarArray("doubleArrayRecord",pvDouble,"alarm,timeStamp");
    pvRecord->destroy();
}

static void powerSupplyTest()
{
    cout << endl << endl << "****powerSupplyTest****" << endl;
    PowerSupplyRecordTestPtr pvRecord;
    pvRecord = createPowerSupply("powerSupply");
    pvRecord->destroy();
}

int main(int argc,char *argv[])
{
    scalarTest();
    //arrayTest();
    //powerSupplyTest();
    return 0;
}

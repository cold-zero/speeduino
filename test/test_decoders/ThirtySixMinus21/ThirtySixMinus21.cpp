#include <decoders.h>
#include <globals.h>
#include <unity.h>
#include "schedule_calcs.h"
#include "../../test_utils.h"

extern uint16_t ignition1EndTooth;
extern uint16_t ignition2EndTooth;
extern int ignition1EndAngle;
extern int ignition2EndAngle;

static decoder_t test_setup_36_2_1()
{
    //Setup a 36-2-1 wheel
    configPage4.triggerTeeth = 36;
    configPage4.triggerMissingTeeth = 3; // Total missing teeth (1+2)
    configPage4.TrigSpeed = CRANK_SPEED;
    configPage4.trigPatternSec = SEC_TRIGGER_SINGLE;
    configPage4.triggerAngle = 0;
    
    return triggerSetup_ThirtySixMinus21();
}

//************************************** End Teeth Calculation Tests **************************************

void test_thirtysixminus21_end_teeth_wasted_spark_trig0()
{
    //Test the set end tooth function. Conditions:
    //Trigger: 36-2-1
    //Advance: 10
    //triggerAngle=0
    decoder_t decoder = test_setup_36_2_1();
    configPage4.sparkMode = IGN_MODE_WASTED;
    ignition1EndAngle = 360 - 10; //Set 10 degrees advance
    configPage4.triggerAngle = 0; //No trigger offset
    
    decoder.setEndTeeth();
    TEST_ASSERT_EQUAL(33, ignition1EndTooth);
}

void test_thirtysixminus21_end_teeth_wasted_spark_trig90()
{
    //Test the set end tooth function. Conditions:
    //Trigger: 36-2-1
    //Advance: 10
    //triggerAngle=90
    decoder_t decoder = test_setup_36_2_1();
    configPage4.sparkMode = IGN_MODE_WASTED;
    ignition1EndAngle = 360 - 10; //Set 10 degrees advance
    configPage4.triggerAngle = 90; //No trigger offset
    
    decoder.setEndTeeth();
    TEST_ASSERT_EQUAL(27, ignition1EndTooth);
}

void test_thirtysixminus21_end_teeth_wasted_spark_trig180()
{
    //Test the set end tooth function. Conditions:
    //Trigger: 36-2-1
    //Advance: 10
    //triggerAngle=180
    decoder_t decoder = test_setup_36_2_1();
    configPage4.sparkMode = IGN_MODE_WASTED;
    ignition1EndAngle = 360 - 10; //Set 10 degrees advance
    configPage4.triggerAngle = 180; //No trigger offset
    
    decoder.setEndTeeth();
    TEST_ASSERT_EQUAL(18, ignition1EndTooth);
}

void test_thirtysixminus21_end_teeth_wasted_spark_trig270()
{
    //Test the set end tooth function. Conditions:
    //Trigger: 36-2-1
    //Advance: 10
    //triggerAngle=270
    decoder_t decoder = test_setup_36_2_1();
    configPage4.sparkMode = IGN_MODE_WASTED;
    ignition1EndAngle = 360 - 10; //Set 10 degrees advance
    configPage4.triggerAngle = 270; //No trigger offset
    
    decoder.setEndTeeth();
    TEST_ASSERT_EQUAL(7, ignition1EndTooth);
}

void test_thirtysixminus21_end_teeth_after_double_gap()
{
    //Test end teeth calculation for angle after double gap
    decoder_t decoder = test_setup_36_2_1();
    
    configPage4.sparkMode = IGN_MODE_WASTED;
    ignition1EndAngle = 190; //170 degrees ATDC
    configPage4.triggerAngle = 0; //No trigger offset
    
    decoder.setEndTeeth();
    
    //For 36-2-1: tooth 19 should fire at 190°
    //calc: (190-0)/10 = 19, >18 so +2 = 21, margin -1 = 20
    TEST_ASSERT_EQUAL(20, ignition1EndTooth);
}

void test_thirtysixminus21_end_teeth_sequential()
{
    //Test end teeth calculation for sequential mode
    decoder_t decoder = test_setup_36_2_1();
    
    configPage4.sparkMode = IGN_MODE_SEQUENTIAL;
    ignition1EndAngle = 350; //10 degrees BTDC
    configPage4.triggerAngle = 0; //No trigger offset
    
    decoder.setEndTeeth();
    
    //For sequential mode with toothAdder: tooth 35+36=71 should fire at 350°
    //calc: (350-0)/10 = 35, >18 so +2 = 37, margin -1 = 36, +36 = 72
    TEST_ASSERT_EQUAL(33, ignition1EndTooth);
}

void testThirtySixMinus21()
{
    SET_UNITY_FILENAME() {
        // End teeth calculation tests
        RUN_TEST(test_thirtysixminus21_end_teeth_wasted_spark_trig0);
        RUN_TEST(test_thirtysixminus21_end_teeth_wasted_spark_trig90);
        RUN_TEST(test_thirtysixminus21_end_teeth_wasted_spark_trig180);
        RUN_TEST(test_thirtysixminus21_end_teeth_wasted_spark_trig270);
        RUN_TEST(test_thirtysixminus21_end_teeth_after_double_gap);
        RUN_TEST(test_thirtysixminus21_end_teeth_sequential);
    }
}

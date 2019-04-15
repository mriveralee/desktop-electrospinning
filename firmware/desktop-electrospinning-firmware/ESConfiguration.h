
#ifndef ES_CONFIGURATION_H
#define ES_CONFIGURATION_H

#define SUPPORT_ELECTROSPINNING 1

// For macros for debugging
#define DEBUG_ES 0
#define DEBUG_ES_PRINT(x)  {if (DEBUG_ES == 1) { x; }}
#define DEBUG_ES_PRINT2(x)  {if (DEBUG_ES == 2) { x; }}

#define TEMP_TYPE_NTC3950_100K 14
#define TEMP_TYPE_E3D_SEMITECH 8
#define TEMP_TYPE_STANDARD 1

#define ES_TEMP_TYPE TEMP_TYPE_E3D_SEMITECH  // 14 is NTC 3950 100k ; // 8 is E3D Semitech 104GT2 // 1 is just default

#define ES_TEMP_PIN TEMP_1_PIN// We use the normal pin

// PID Controller for Cartridge Heater
#define ES_PID_PGAIN_OR_DEAD_TIME 7
#define ES_PID_I 2
#define ES_PID_D 40
#define ES_PID_INTEGRAL_DRIVE_MAX 250


/////////////////////////////////////////////////////////////////
// Temperature Sensor Decouple Test time
//////
#define ES_DECOUPLE_TEST_PERIOD 20000 //20 seconds


/////////////////////////////////////////////////////////////////
// General Configuration Vars
//////
#define ES_EPSILON 0.001
#define ES_CONDUCTIVE_EXTRUDER_OFFSET_X_IN_MM 56 // 57
#define ES_CONDUCTIVE_EXTRUDER_OFFSET_Y_IN_MM -2 // 3

#define ES_SHARED_HEATER_E1_AND_E2 2
#define ES_CONDUCTIVE_PLA_EXTRUDER_ID 0
#define ES_PLA_EXTRUDER_ID 1
#define ES_ESPLA_EXTRUDER_ID 2



/////////////////////////////////////////////////////////////////
// Electrospinning Extruder Mode Configuration
//////

#define ES_EXTRUDER_NORMAL_STEPS_PER_MM 92
#define ES_EXTRUDER_SPIN_STEPS_PER_MM 92
#define ES_EXTRUDER_X_OFFSET_MM 0

#define ES_EXTRUDER_SPIN_MAX_FEEDRATE 50
#define ES_EXTRUDER_SPIN_MAX_START_FEEDRATE 20
#define ES_EXTRUDER_SPIN_MAX_ACCELERATION 5000

/////////////////////////////////////////////////////////////////
// Electrospinning Printing Area Configuration
// Bounds for the electrospinning region relative to E0 (offsets not included)
// if we aren't in these bounds, the HV gets automagically turned off
// X: [0, 100]
// Y: [90, 210]
#define ES_MIN_EXTRUDER_HV_HEIGHT 22.0000

#define ES_HV_BOUNDS_X_MIN 2
#define ES_HV_BOUNDS_X_MAX 220

#define ES_HV_BOUNDS_Y_MIN 40
#define ES_HV_BOUNDS_Y_MAX 220

#define ES_HV_BOUNDS_Z_MIN ES_MIN_EXTRUDER_HV_HEIGHT
#define ES_HV_BOUNDS_Z_MAX 200

// Controls whether we dynamically compute a Z Height offset based on the current Z layer height
// if false - we always use ES_MIN_EXTRUDER_HV_HEIGHT as offset
#define ES_USE_DYNAMIC_HV_Z_HEIGHT true


////////////////
// Heating method for the extruder
//////////

#define ES_HEATER_PIN HEATER_1_PIN


/////////////////////////////////////////////////////////////////
// High Voltage IR Switching Source Configuration
// See link for RAMPS 1.4 pin layout: http://makerdev.com/blog/wp-content/uploads/2014/02/ramps_fanboard_annotations.jpg
//////
#define ES_HV_IR_SWITCH_PIN 44
#define ES_HV_IR_SWITCH_STATE_OFF LOW
#define ES_HV_IR_SWITCH_STATE_ON HIGH

#endif // ES_CONFIG Included

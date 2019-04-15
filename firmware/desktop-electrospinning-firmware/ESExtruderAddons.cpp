#include "ESExtruderAddons.h"

#include "ESConfiguration.h"

#include "Repetier.h"
#include "Drivers.h"

bool ESExtruderAddons::isHVOn = false;

void ESExtruderAddons::initAddons() {
  Com::printFLN(PSTR("Initializing electrospinning addons..."));
  ESExtruderAddons::initHVIRSwitch();
  ESExtruderAddons::disableHighVoltage();
}

void ESExtruderAddons::printHVWarningMessage() {
  Com::printFLN(PSTR("*** WARNING: HIGH VOLTAGE ENABLED! ***\n"));
  Com::println();
}

bool ESExtruderAddons::isPositionInHVBounds(float x, float y, float z) {
  if (x < (ES_HV_BOUNDS_X_MIN - ES_EPSILON) || x > (ES_HV_BOUNDS_X_MAX + ES_EPSILON)) {
    return false;
  }
  if (y < (ES_HV_BOUNDS_Y_MIN - ES_EPSILON) || y > (ES_HV_BOUNDS_Y_MAX + ES_EPSILON)) {
    return false;
  }
  if (z < (ES_HV_BOUNDS_Z_MIN - ES_EPSILON) || z > (ES_HV_BOUNDS_Z_MAX + ES_EPSILON)) {
    return false;
  }
  return true;
}

float ESExtruderAddons::getESExtruderOffsetZInSteps(float currentZPosInMM, bool isPrinterHomed) {
  float zOffsetInMM = 0;
  if (isPrinterHomed) {
    if (ES_USE_DYNAMIC_HV_Z_HEIGHT) {
      // Dynamic offset
      if (currentZPosInMM >= ES_MIN_EXTRUDER_HV_HEIGHT) {
        zOffsetInMM = 0;
      } else {
        zOffsetInMM = ES_MIN_EXTRUDER_HV_HEIGHT - currentZPosInMM;
      }
    } else {
      // No dynamic offset
      zOffsetInMM = ES_MIN_EXTRUDER_HV_HEIGHT;
    }
  } else {
    // If we weren't homed, we need to be at the very least ES_MIN_EXTRUDER_HV_HEIGHT away
    zOffsetInMM = ES_MIN_EXTRUDER_HV_HEIGHT;
  }
  // Com::printF(PSTR("ZOffsetInSteps: "), zOffsetInMM);
  // Multiply by -1 here since our offset is in the positive Z-direction (normally offsets are done in the negative)
  return -1 * zOffsetInMM * ZAXIS_STEPS_PER_MM;
}

void ESExtruderAddons::initHVIRSwitch() {
  SET_OUTPUT(ES_HV_IR_SWITCH_PIN);
  ESExtruderAddons::disableHighVoltage();
}

void ESExtruderAddons::enableHighVoltage(bool showWarning) {
  WRITE(ES_HV_IR_SWITCH_PIN, ES_HV_IR_SWITCH_STATE_ON);
  if (showWarning) {
    ESExtruderAddons::printHVWarningMessage();
  }
  ESExtruderAddons::isHVOn = true;
}

void ESExtruderAddons::disableHighVoltage() {
  WRITE(ES_HV_IR_SWITCH_PIN, ES_HV_IR_SWITCH_STATE_OFF);
  ESExtruderAddons::isHVOn = false;
}




/**
 *  Add-ons to control the ES Extruder's high voltage
 */

#ifndef ES_EXTRUDER_ADDONS_H
#define ES_EXTRUDER_ADDONS_H

class ESExtruderAddons {
  public:
    // General Add-ons
    static void initAddons();

     // Melt Electrospinning extruder Z-Offset Calculation 
    static float getESExtruderOffsetZInSteps(float currentZPosInMM, bool isPrinterHomed);

    // Helpers for High Voltage
    static void enableHighVoltage(bool showWarning);
    static void disableHighVoltage();

    static void printHVWarningMessage();
    static bool isPositionInHVBounds(float x, float y, float z);

    static inline bool isHVEnabled() {
      return ESExtruderAddons::isHVOn;
    }
    
private:
    static bool isHVOn;

    // HV IR Switch 
    static void initHVIRSwitch();

};

#endif

#include <ir_Lego_PF_BitStreamEncoder.h>
#include <boarddefs.h>
#include <IRremoteInt.h>
#include <IRremote.h>

/* ESPrinterSlaveInfaredSender
   This sketch uses Ken Shirriff's *awesome* IRremote library:
       https://github.com/shirriff/Arduino-IRremote

    This sketch sends an one IR code out of an attached IR LED on pin 3,
    when the voltage on pin 12 is set to high; and another when the voltage is set to low

   Hardware setup:
     * The anode (+, longer leg) of an IR LED should be connected to pin 3 of 
       the Arduino. The cathode (-) should be connected to a 330
       Ohm resistor, which connects to ground.
     * A Wire connecting D44 of a RAMPS 1.4/Mega 3D printer controller should be connected 
     * to pin 12 of this arduino with a current-limiting resistor (470ohm) in between.

*/

/* Define the IR remote button codes. We're only using the
   least signinficant two bytes of these codes. Each one 
   should actually have 0x10EF in front of it. Find these codes
   by running the IRrecvDump example sketch included with
   the IRremote library.*/
//const uint16_t BUTTON_PREFIX = 0x10EF;
//const uint16_t BUTTON_A = 0xF807;      
//const uint16_t BUTTON_CIRCLE = 0x20DF;  

#define SEND_CODE_BUTTON_CIRCLE 0x10EF20DF    // Code for HV ON 
#define SEND_CODE_BUTTON_A 0x10EFF807         // Code for HV OFF

/* Storage variables for the send IR code: */
// The length of the header we send for NEC
unsigned int NEC_HEADER_LENGTH = 16;

// The length of the code in bytes
unsigned int SEND_CODE_LENGTH  = 16; 

// The code we send for the ESP set up
int SEND_CODE_TYPE = NEC;

// Timing Vars
long SEND_TIME_DELAY = 40;
long LAST_SEND_IR_TIME = 0;

const int TRIGGER_SEND_IR_STATUS_PIN = 12;  // Status pin connected to the 3D Printer 
boolean IS_HV_ENABLED = false;

// Enables IR transmit on pin 3
IRsend IR_SENDER; 

// setup() initializes serial and the Infrared receiver.
void setup() {
  // Init the status pin
  pinMode(TRIGGER_SEND_IR_STATUS_PIN, INPUT); 
  Serial.begin(9600);
}


// loop() checks for either a button press or a received IR code.
void loop() {
  // Check if status pin is high
  IS_HV_ENABLED = (digitalRead(TRIGGER_SEND_IR_STATUS_PIN) == HIGH) 
    ? true 
    : false;
   // If hv is enabled we send the Enable symbol
  if (!IS_HV_ENABLED) {
    sendCode(SEND_CODE_TYPE, SEND_CODE_BUTTON_A, NEC_HEADER_LENGTH + SEND_CODE_LENGTH); 
  } else {
    sendCode(SEND_CODE_TYPE, SEND_CODE_BUTTON_CIRCLE, NEC_HEADER_LENGTH + SEND_CODE_LENGTH); 
  }
  delay(SEND_TIME_DELAY);
  LAST_SEND_IR_TIME = millis();
}

void sendCode(int codeType, unsigned int codeToSend, int lenOfIR) {
  if (codeType == NEC) {
    IR_SENDER.sendNEC(codeToSend, lenOfIR);
    Serial.print("Sent NEC ");
    Serial.println(codeToSend, HEX);
  }
}

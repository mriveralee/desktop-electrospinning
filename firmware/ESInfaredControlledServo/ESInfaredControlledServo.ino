#include <ir_Lego_PF_BitStreamEncoder.h>
#include <boarddefs.h>
#include <IRremoteInt.h>
#include <IRremote.h>

#include <Servo.h>

/*
   This sketch received and IRSignal send from an IR LED, 
   then triggers a servo to rotate based on the signal 
   This sketch uses Ken Shirriff's *aweesome* IRremote library:
       https://github.com/shirriff/Arduino-IRremot
   Hardware setup:
     * The output of an IR Receiver Diode (38 kHz demodulating
       version) should be connected to the Arduino's pin 11.
       * The IR Receiver diode should also be powered off the
         Arduino's 5V and GND rails.
*/

/* Define the IR remote button codes. We're only using the
   least signinficant two bytes of these codes. Each one 
   should actually have 0x10EF in front of it. */
const uint16_t BUTTON_PREFIX = 0x10EF;
const uint16_t BUTTON_A = 0xF807;
const uint16_t BUTTON_CIRCLE = 0x20DF;

#define SEND_CODE_BUTTON_CIRCLE 0x10EF20DF
#define SEND_CODE_BUTTON_A 0x10EFF807

/* Connect the output of the IR receiver diode to pin 11. */
int RECV_PIN = 11;

/* Initialize the IR_RECEIVER part of the IRremote  library */
IRrecv IR_RECEIVER(RECV_PIN);
decode_results RECEIVED_RESULTS; // This will store our IR received codes

/* Vars for the Received IR Code */
unsigned int RECEIVED_IR_BUFFER[RAWBUF];// = {BUTTON_PREFIX, BUTTON_CIRCLE}; // Storage for raw (UNKNOWN) codes
boolean WAS_CODE_RECEIVED  = true; // A boolean to keep track of if a code was received
unsigned int RECEIVED_CODE_LENGTH  = 2; // The length of the code
int RECEIVED_CODE_TYPE = NEC; // The type of code (NEC, SONY, UNKNOWN, etc.)
unsigned int RECEIVED_CODE_VALUE  = BUTTON_CIRCLE; // The value of a known code
uint16_t LAST_RECEIVED_CODE = 0; // This keeps track of the last code RX'd
long LAST_IR_RECEIVED_TIMESTAMP = 0; // timestamp from the last ir signal we decoded 


// Set-up for the servo
Servo HV_SERVO_SWITCH;  // create servo object to control a servo
const int HV_SERVO_SWITCH_PIN = A5;   // Servo pin
const int ES_HV_SERVO_STATE_ON = 30; 
const int  ES_HV_SERVO_STATE_GROUNDED = 0;

const int HV_SSR_SWITCH_PIN = A0;         // Solid-state-relay pin

bool IS_HV_ENABLED = false;               // State of HV

// Set-up for the LED Status Pin
const int IR_STATUS_LED_PIN = 3;          // LED to show if IR is being received
const int HV_ENABLED_STATUS_LED_PIN = 2;  // LED to show if HV is on

// IR related
bool IS_IR_RECEIVING = false;
int IR_STATUS_RECEIVING_TIME_DELAY = 100;
long LAST_IR_STATUS_LED_TIME = 0;
long IR_RECEIVING_TIMEOUT_FAILSAFE = 300;


void setup() {
  Serial.begin(9600);
  pinMode(IR_STATUS_LED_PIN, OUTPUT);
  pinMode(HV_ENABLED_STATUS_LED_PIN, OUTPUT);
  pinMode(HV_SSR_SWITCH_PIN, OUTPUT);
  HV_SERVO_SWITCH.attach(HV_SERVO_SWITCH_PIN);
  updateHVServoState();
  updateStatusLEDState();
  IR_RECEIVER.enableIRIn(); // Start the receiver
}


// loop() checks for a received IR code.
void loop() {
  if (IR_RECEIVER.decode(&RECEIVED_RESULTS)) {
    updateIRReceive(); // Sort out the received code
    WAS_CODE_RECEIVED  = true;
    // Do stuff with the code
     /* read the RX'd IR into a 16-bit variable: */
    uint16_t resultCode = (RECEIVED_RESULTS.value & 0xFFFF);

    /* The remote will continue to spit out 0xFFFFFFFF if a 
     button is held down. If we get 0xFFFFFFF, let's just
     assume the previously pressed button is being held down */
    if (resultCode == 0xFFFF) {
      resultCode = LAST_RECEIVED_CODE;
    } else {
      LAST_RECEIVED_CODE = resultCode;
    }

    // This switch statement checks the received IR code against
    // all of the known codes. Each button press produces a 
    // serial output, and has an effect on the LED output.
    switch (resultCode) {
      case BUTTON_CIRCLE:        
        IS_HV_ENABLED = true;
        Serial.println("Circle");
        break;
      case BUTTON_A:
        IS_HV_ENABLED = false;
        Serial.println("A");
        break;
      default:
        Serial.print("Unrecognized code received: 0x");
        Serial.println(RECEIVED_RESULTS.value, HEX);
        // Return to OFF_STATE
        break;        
    }
    // Toggle IR LED Status
    if (IS_IR_RECEIVING) {
          IS_IR_RECEIVING = false;
    } else {
      IS_IR_RECEIVING = true; // Flip IS_IR_RECEIVING
    } 
    IR_RECEIVER.resume(); // re-enable receive 
    LAST_IR_RECEIVED_TIMESTAMP = millis();  // track when we last received a decodeable ir signal
  } 
  
  if (millis() - LAST_IR_RECEIVED_TIMESTAMP >= IR_RECEIVING_TIMEOUT_FAILSAFE) {
    IS_HV_ENABLED = false;
  }
  updateStatusLEDState();
  updateHVServoState();
  updateHVSSRState();
}


void updateIRReceive() {
  RECEIVED_CODE_TYPE = RECEIVED_RESULTS.decode_type;
  RECEIVED_CODE_LENGTH = RECEIVED_RESULTS.rawlen;
  if (RECEIVED_CODE_TYPE == NEC) {
    Serial.print("Received NEC: ");
    if (RECEIVED_RESULTS.value == REPEAT) {
      // Don't record a NEC repeat value as that's useless.
      Serial.println("repeat.");
      //return;
    }
  } 
  Serial.println(RECEIVED_RESULTS.value, HEX);
  RECEIVED_CODE_VALUE = RECEIVED_RESULTS.value;
  RECEIVED_CODE_LENGTH = RECEIVED_RESULTS.bits;
}


void updateHVServoState() {
  if (IS_HV_ENABLED) { 
     HV_SERVO_SWITCH.write(ES_HV_SERVO_STATE_ON);
      Serial.println("HV ON");
  } else {
      HV_SERVO_SWITCH.write(ES_HV_SERVO_STATE_GROUNDED);
      Serial.println("HV OFF");
  }
  delay(15);
}

void updateHVSSRState() {
  digitalWrite(HV_SSR_SWITCH_PIN, IS_HV_ENABLED ? HIGH : LOW);
}

void updateStatusLEDState() {
  if (millis() - LAST_IR_STATUS_LED_TIME  >= IR_STATUS_RECEIVING_TIME_DELAY) {
    digitalWrite(IR_STATUS_LED_PIN, IS_IR_RECEIVING ? HIGH : LOW);
    LAST_IR_STATUS_LED_TIME = millis();
  }
  digitalWrite(HV_ENABLED_STATUS_LED_PIN, IS_HV_ENABLED ? HIGH : LOW);
}

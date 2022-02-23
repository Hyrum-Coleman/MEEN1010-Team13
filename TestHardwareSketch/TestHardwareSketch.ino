/****************************************************************
  Author Names: Hyrum Coleman, Will Connors
  Lab section: 003
  Team number: 13
  Date: 2/15/22
  Sketch Description:

  Button Usage: Up/Down    -
              Left/Right -
              Select     -

  Pin Usage:    Pin type/number     Hardware
              ----------------    ----------------
              13 digital          IR LED
              11 digital          Left Switch
              12 digital          Right Switch
              A7 analog           Built in buttons
*******************************************************************/

/****************************
 ** #defines and #includes **
 ****************************/

/***********************
 ** Global Variables ***
 ***********************/
// *** Declare & Initialize Pins ***
const int ledPin = 13 ;
const int leftSwitchPin = 11;
const int rightSwitchPin = 12;
const int buttonPin = A7;
const int motorPowerPin = 5;
const int motorDirectionPin = 4;
// *** Create Servo Objects ***

// *** Declare & Initialize Program Variables ***

char userInput ('z');
bool newUserInput = 1; // 1 means user just entered a letter
// 0 means no new input

int printDelay = 2000;

// led test variables

int ledOnTime = 1000;
int ledOffTime = 2000;
unsigned long blinkTime = 0;
unsigned long timeSinceLastBlink = 0;
bool ledOn = 0;

// switch test variables

int leftSwitchState = 0;
int rightSwitchState = 0;
unsigned long printTime = 0;
unsigned long timeSinceLastPrint = 0;

// debouncing variables

unsigned long leftSwitchChangeTime = 0;
unsigned long rightSwitchChangeTime = 0;
unsigned long timeSinceLastLeftSwitchChange = 0;
unsigned long timeSinceLastRightSwitchChange = 0;
int switchDebounceTime = 15;

// button test variables

int buttonNumber = 0;
unsigned long cibn = 0;
int buttonPressed = 0;

// debug print function variables

unsigned long debugPrintTime = 0;
unsigned long debugTimeSinceLastPrint = 0;
int debugPrintDelay = 200;  // you can choose this time

// debug blink function variables

const int debugLedPin = 13;   // onboard LED
unsigned long debugBlinkTime = 0;
unsigned long debugTimeSinceLastBlink = 0;
int debugLedHiLo = 0;

// motor test variables

const int motorPower = 255;
bool motorOn = 0; // off is 0 and on is 1
bool motorRight = 0; // off is 0 and on is 1

/********************
 ** Setup Function **
 ********************/
void setup(void) {
  // PUT YOUR SETUP CODE HERE, TO RUN ONCE:

  // *** Initialize Serial Communication ***
  Serial.begin(9600);
  // *** Configure Digital Pins & Attach Servos ***
  pinMode(ledPin, OUTPUT);
  pinMode(leftSwitchPin, INPUT_PULLUP);
  pinMode(rightSwitchPin, INPUT_PULLUP);
  pinMode(motorPowerPin, OUTPUT);
  pinMode(motorDirectionPin, OUTPUT);
  
  // *** Take Initial Readings ***

  // *** Move Hardware to Desired Initial Positions ***

}// end setup() function

/*******************
 ** Loop Function **
 *******************/
void loop(void) {
  //PUT YOUR MAIN CODE HERE, TO RUN REPEATEDLY
  //Serial.print(Serial.available());
  //Serial.println(" bytes available to read");

  if (Serial.available() >= 2)
  {
    userInput = Serial.read();
    Serial.read();
    Serial.print("User entered ");
    Serial.println(userInput);
    Serial.println();
    newUserInput = 1;
  }

  switch (userInput)
  {
    //    case 'a':
    //
    //      //do something once
    //      if (newUserInput == 1)
    //      {
    //        Serial.println("prints once");
    //        newUserInput = 0; //should not delete under any circumstances
    //
    //      }
    //      //do something over and over
    //      Serial.println("prints over and over");
    //      delay(500);
    //      break;

    case 'a':
      if (newUserInput == 1)
      {
        Serial.println("Test a: Check that IR LED is blinking");
        newUserInput = 0; //should not delete under any circumstances

      }
      // call testing function
      TestIRLED();
      break;

    case 'b':
      if (newUserInput == 1)
      {
        Serial.println("Test b: Press the switches to test");
        newUserInput = 0; //should not delete under any circumstances

      }
      //do something over and over
      TestSwitches();
      break;

    case 'c':

      //do something once
      if (newUserInput == 1)
      {
        Serial.println("Test c: Press the buttons to test");
        newUserInput = 0; //should not delete under any circumstances

      }
      //do something over and over
      TestButtons();
      break;

    case 'z':
      //do something once
      if (newUserInput == 1)
      {
        PrintMenu();
        newUserInput = 0; //should not delete under any circumstances
      }
      break;

    default:
      //do something once
      if (newUserInput == 1)
      {
        Serial.println("Waiting for a valid user input");
        Serial.println("Enter z to print menu");
        newUserInput = 0;
      }
      break;



  }
} // end loop() function

/****************************
 ** User-Defined Functions **
 ****************************/

void TurnMotorOn(void)
{
  if(motorOn == 0)
  {
    digitalWrite(motorDirectionPin, motorRight);
    analogWrite(motorPowerPin, motorPower);
    motorOn = 1;
  }
}

void TurnMotorOff(void)
{
  if(motorOn == 1)
  {
    analogWrite(motorPowerPin, 0);
    motorOn = 0;
  }
}
 
// create custom headers as necessary to clearly organize your sketch
// e.g., Button functions, DC Motor functions, Servo functions, etc.

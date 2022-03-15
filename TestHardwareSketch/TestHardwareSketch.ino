/****************************************************************
  Author Names: Hyrum Coleman, Will Connors
  Lab section: 003
  Team number: 13
  Date: 2/23/22
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
              04 digital          Motor Direction
              05 digital          Motor Power
              A5 analog           IR Sensor
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
const int irSensorPin = A5;

// *** Create Servo Objects ***

// *** Declare & Initialize Program Variables ***

char userInput ('z');
bool newUserInput = 1; // 1 means user just entered a letter
// 0 means no new input

int printDelay = 200;

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

// print sensor value variable

int irSensorValue = 0;

// get encoder boolean variable

bool black = 1;

// count stripes variables

unsigned long stripeChangeTime = 0;
unsigned long timeSinceLastStripeChange = 0;
int counts = 24;

// test motor modification variables

unsigned long incrementTime = 0;
unsigned long timeSinceLastIncrement = 0;

// move launcher variables

bool startMotion = 0;
int desiredPosition = 24;

//Test Aim Fire - Part 1

int desiredServoAngle = 90;
int servoAngleIncrement = 5;

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
  black = GetEncoderBoolean();
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
    //       // CODE HERE (Once code)
    //        newUserInput = 0; //should not delete under any circumstances
    //
    //      }
    //      //do something over and over
    //      // CODE HERE (Over and over code)
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
    case 'd':

      //do something once
      if (newUserInput == 1)
      {
        Serial.println("Press the left and right buttons to test the motor");
        newUserInput = 0; //should not delete under any circumstances

      }
      //do something over and over
      TestMotor();
      break;
    case 'e':

      //do something once
      if (newUserInput == 1)
      {
        Serial.println("Press the left and right buttons to test the motor and sensor");
        newUserInput = 0; //should not delete under any circumstances

      }
      //do something over and over
      TestMotor();
      break;
    case 'f':

      //do something once
      if (newUserInput == 1)
      {
        Serial.println("Press the left and right buttons to test the motor and encoder");
        newUserInput = 0; //should not delete under any circumstances

      }
      //do something over and over
      TestMotor();
      break;
    case 'g':

      //do something once
      if (newUserInput == 1)
      {
        Serial.println("Press the left and right buttons to count stripes");
        Serial.println("Press the up and down buttons to increment count");
        Serial.println("Press the select button to set counts to 24");
        newUserInput = 0; //should not delete under any circumstances

      }
      //do something over and over
      TestMotor();
      break;
    case 'h':

      //do something once
      if (newUserInput == 1)
      {
        startMotion = 0;
        Serial.println("Press the left and right buttons to increment desired position");
        Serial.println("Press the up and down buttons to increment counts");
        Serial.println("Press the select button to send the launcher to the desired position");
        newUserInput = 0; //should not delete under any circumstances

      }
      //do something over and over
      TestMoveLauncher();
      break;
    case 'i':

      //do something once
      if (newUserInput == 1)
      {
        Serial.println("Press the up/down/left/right buttons to increment desiredServoAngle");
        Serial.println("Press the select button to command the servo to fire the solenoid!");
        newUserInput = 0; //should not delete under any circumstances

      }
      //do something over and over
      TestAimFire();
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
  if (motorOn == 0)
  {
    digitalWrite(motorDirectionPin, motorRight);
    analogWrite(motorPowerPin, motorPower);
    motorOn = 1;
  }
}

void TurnMotorOff(int reverseTime)
{
  if (motorOn == 1)
  {
    analogWrite(motorPowerPin, 0);
    delay(10);
    //think about this

    digitalWrite(motorDirectionPin, !motorRight);
    //motorRight != 0;
    analogWrite(motorPowerPin, motorPower);
    delay(reverseTime);
    analogWrite(motorPowerPin, 0);
    motorOn = 0;
  }
}

bool GetEncoderBoolean(void)
{
  int lowThreshold = 80;
  int highThreshold = 300;
  int irSensorValue = analogRead(irSensorPin);
  if ((black == 1) && (irSensorValue < lowThreshold))
  {
    return 0;
  }
  else if ((black == 0) && (irSensorValue > highThreshold))
  {
    return 1;
  }
  else
  {
    return black;
  }
}

void CountStripes(void)
{
  int prevBlack = black;
  black = GetEncoderBoolean();
  timeSinceLastStripeChange = millis() - stripeChangeTime;
  if (black != prevBlack)
  {
    stripeChangeTime = millis();
    if (motorRight)
    {
      counts++;
    }
    else
    {
      counts--;
    }
    Serial.print("Count is: ");
    Serial.print(counts);
    Serial.print(" ... time since last stripe change is: ");
    Serial.println(timeSinceLastStripeChange);
  }
}
// create custom headers as necessary to clearly organize your sketch
// e.g., Button functions, DC Motor functions, Servo functions, etc.

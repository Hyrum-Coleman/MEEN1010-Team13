void NotMoving(void)
{
  leftSwitchState = digitalRead(leftSwitchPin);
  rightSwitchState = digitalRead(rightSwitchPin);
  // at home
  if (leftSwitchState == 1)
  {
    //AtHome();
  }
  // at reloader
  else if (rightSwitchState == 1)
  {
    //AtReloader();
  }
  // at target
  else if (desiredPosition == counts)
  {
    //AtTarget();
  }

}

void AtReloader(void)
{
  switch (state)
  {
    case 1: // dispense ball
      //command the servo
      reloaderServo.write(dispenseAngle);
      Serial.println(F("DISPENSING"));
      // change the state, update the time
      state = 2;
      stateChangeTime = millis();
      break;
    case 2: // Delay, then stop dispensing
      timeSinceLastStateChange = millis() - stateChangeTime;
      if (timeSinceLastStateChange > dispenseDelay)
      {
        // command the servo
        reloaderServo.write(holdAngle);
        Serial.println(F("HOLDING"));
        // change the state, update the time
        state = 3;
        stateChangeTime = millis();
      }
      break;
    case 3: // delay, then set motion variables
      timeSinceLastStateChange = millis() - stateChangeTime;
      if (timeSinceLastStateChange > 1000)
      {
        // set motion variables
        Serial.println(F("BALL RELOADED - setting motion variables"));
        userInput = 'x'; //TEMPORARY
        // change the state
        state = 1;
      }
      break;
  }
}

void AtHome(void)
{
  switch (state)
  {
    case 1: // turn the LED on
      // turn the LED on
      TurnLEDOn();
      Serial.println(F("The LED is on! Starting Timer"));
      // change the state, update the time
      state = 2;
      stateChangeTime = millis();
      break;
    case 2: // delay, then turn the LED off
      timeSinceLastStateChange = millis() - stateChangeTime;
      if (timeSinceLastStateChange > dispenseDelay)
      {
        // turn the LED off
        TurnLEDOff();
        Serial.println(F("The LED is off! Triggering Timer"));
        // change the state
        state = 3;
      }
      break;
    case 3: // set the motion variables
      // set motion variables
      Serial.println(F("Setting motion variables"));
      userInput = 'x'; // temporary
      // change the state
      state = 1;
  }
}

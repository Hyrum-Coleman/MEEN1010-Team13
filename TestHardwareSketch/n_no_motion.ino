void NotMoving(void)
{
  leftSwitchState = digitalRead(leftSwitchPin);
  rightSwitchState = digitalRead(rightSwitchPin);
  // at home
  if (leftSwitchState == 1)
  {
    AtHome();
  }
  // at reloader
  else if (rightSwitchState == 1)
  {
    AtReloader();
  }
  // at target
  else if (desiredPosition == counts)
  {
    AtTarget();
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
      if (timeSinceLastStateChange > motionVariableDelay)
      {
        // set motion variables
        startMotion = 1;
        headed = 1;
        target++;
        Serial.println(F("BALL RELOADED - setting motion variables"));
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
      digitalWrite(ledPin, HIGH);
      // TurnLEDOn(); // ask alex if this will be slower than just using digital write
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
        digitalWrite(ledPin, LOW);
        //TurnLEDOff();
        Serial.println(F("The LED is off! Triggering Timer"));
        // change the state
        state = 3;
      }
      break;
    case 3: // set the motion variables
      // set motion variables
      Serial.println(F("Setting motion variables"));
      if (target < 5)
      {
        if ((target == 0) && (userInput == 'v'))
        {
          Serial.println("Calling ComputeStuff()");
          ComputeStuff();
        }
        startMotion = 1;
        headed = 1;
        // change the state
        state = 1;
      }
      else
      {
        target = 0;
        // change the state
        state = 0;
        Serial.println(F("All done :)"));
        if (userInput == 'v')
        {
          Serial.println("done");
        }
        userInput = 'x';
      }
  }
}

void AtTarget(void)
{
  switch (state)
  {
    case 1: // command launcher servo to firing angle
      // command the launcher servo
      desiredServoAngle = writeToServo[target];
      launcherServo.write(desiredServoAngle);
      Serial.print(F("Commanding launcher servo to "));
      Serial.print(desiredServoAngle);
      Serial.print(F(" for target "));
      Serial.println(target);
      //change the state, update the time
      state = 2;
      stateChangeTime = millis();
      break;
    case 2: // delay, then turn the solenoid on
      timeSinceLastStateChange = millis() - stateChangeTime;
      if (timeSinceLastStateChange > solenoidActivationDelay)
      {
        // turn the solenoid on
        digitalWrite(solenoidDirectionPin, HIGH);
        analogWrite(solenoidPowerPin, solenoidPower);
        Serial.println("Firing Solenoid! Bombs away boys!");
        // change the state, update the time
        state = 3;
        stateChangeTime = millis();
      }
      break;
    case 3: // delay, then turn the solenoid off
      timeSinceLastStateChange = millis() - stateChangeTime;
      if (timeSinceLastStateChange > solenoidActivationTime)
      {
        // turn the solenoid off
        analogWrite(solenoidPowerPin, 0);
        Serial.println("All the bombs have been dropped! Fire Ceased!");
        //change the state, update the time
        state = 4;
        stateChangeTime = millis();
      }
      break;
    case 4: // delay, then command the launcher servo to the reload angle
      timeSinceLastStateChange = millis() - stateChangeTime;
      if (timeSinceLastStateChange > reloadAngleDelay)
      {
        // command the launcher servo
        launcherServo.write(reloadAngle); 
        // change the state
        state = 5;
      }
      break;
    case 5: // set the motion variables
      // set motion variables
      startMotion = 1;
      if (target < 5)
      {
        headed = 2;
      }
      else
      {
        headed = 0;
      }
      Serial.println(F("Target actions complete - setting motion variables"));
      // change the state
      state = 1;
      break;
  }
}

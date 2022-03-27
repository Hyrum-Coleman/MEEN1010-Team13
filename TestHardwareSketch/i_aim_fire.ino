void TestAimFire(void)
{
  int prevButtonPressed = buttonPressed;
  ReadButtons();
  switch (buttonPressed)
  {
    case cUpButtonPressed:
      servoAngleIncrement = 5;
      ChangeDesiredServoAngle(servoAngleIncrement);
      break;
      
    case cDownButtonPressed:
      servoAngleIncrement = -5;
      ChangeDesiredServoAngle(servoAngleIncrement);
      break;
      
    case cLeftButtonPressed:
      servoAngleIncrement = -1;
      ChangeDesiredServoAngle(servoAngleIncrement);
      break;
      
    case cRightButtonPressed:
      servoAngleIncrement = 1;
      ChangeDesiredServoAngle(servoAngleIncrement);
      break;
      
    case cSelectButtonPressed:
      if (buttonPressed != prevButtonPressed)
      {
        if (state > 0)
        {
          Serial.println(F("Action is still in progress, wait a little longer please"));
        }
        else
        {
          state = 1;
          stateChangeTime = millis();
        }
      }
      break;
    case cNoButtonPressed:
      break;
    default:
      break;
  }
  switch (state)
  {
    case 1: // delay, then comand the servo
      timeSinceLastStateChange = millis() - stateChangeTime;
      if (timeSinceLastStateChange > 1000)
      {
        //command the servo
        launcherServo.write(desiredServoAngle);
        Serial.print(F("Launcher servo commanded to "));
        Serial.println(desiredServoAngle);
        //change the state, update the time
        state = 2;
        stateChangeTime = millis();
      }
      break;
    case 2: // delay, then turn the solenoid on
      timeSinceLastStateChange = millis() - stateChangeTime;
      if (timeSinceLastStateChange > 1000)
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
        // change the state
        state = 0;
      }
      break;
  }
}

void ChangeDesiredServoAngle(int servoAngleIncrement)
{
  int prevButtonPressed = buttonPressed;
  timeSinceLastIncrement = millis() - incrementTime;
  if ((buttonPressed != prevButtonPressed) || timeSinceLastIncrement > 250)
  {
    incrementTime = millis();
    desiredServoAngle = desiredServoAngle + servoAngleIncrement;
    desiredServoAngle = constrain(desiredServoAngle, 0, 180);
    Serial.print(F("The desired servo angle is: "));
    Serial.println(desiredServoAngle);
  }
}

void TestAimFire(void)
{
  int prevButtonPressed = buttonPressed;
  ReadButtons();
  switch (buttonPressed)
  {
    case 3:
    case 1:
    case 4:
    case 2:
      switch (buttonPressed)
      {
        case 3:
          servoAngleIncrement = 5;
          break;
        case 1:
          servoAngleIncrement = -5;
          break;
        case 4:
          servoAngleIncrement = -1;
          break;
        case 2:
          servoAngleIncrement = 1;
          break;
      }
      timeSinceLastIncrement = millis() - incrementTime;
      if ((buttonPressed != prevButtonPressed) || timeSinceLastIncrement > 250)
      {
        incrementTime = millis();
        desiredServoAngle = desiredServoAngle + servoAngleIncrement;
        desiredServoAngle = constrain(desiredServoAngle, 0, 180);
        Serial.print(F("The desired servo angle is: "));
        Serial.println(desiredServoAngle);
      }
      break;
    case 5:
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
    case 0:
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

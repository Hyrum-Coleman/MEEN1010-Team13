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
        Serial.print("The desired servo angle is: ");
        Serial.println(desiredServoAngle);
      }
      break;

    case 5:
      //nothing yet
      break;

    case 0:
      break;

    default:
      break;
  }
}

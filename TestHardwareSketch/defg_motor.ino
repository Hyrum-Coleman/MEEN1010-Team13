void TestMotor(void)
{
  ReadButtons();
  switch (buttonPressed)
  {
    case 3:  //Up button
      //Doing nothing
      break;

    case 1:  //Down button
      //Doing nothing
      break;

    case 4:  //Left button
      motorRight = 0;
      TurnMotorOn();
      break;

    case 2:  //Right button
      motorRight = 1;
      TurnMotorOn();
      break;

    case 5:  //Select button
      //Doing nothing
      break;

    case 0:  //No button
      TurnMotorOff();
      break;

    default:
      //Doing nothing
      break;
  }

  if (motorOn)
  {
    switch (userInput)
    {
      case 'd':
        PrintLeftRight();
        break;
      case 'e':
        //nothing yet :troll:
        break;
      case 'f':
        //nothing yet :troll:
        break;
      case 'g':
        //nothing yet :troll:
        break;
    }
  }


}

void PrintLeftRight(void)
{
  timeSinceLastPrint = millis() - printTime;
  if (timeSinceLastPrint > printDelay)
  {
    printTime = millis();
    Serial.print("Launcher is moving ");
    if (motorRight)
    {
      Serial.println("RIGHT");
    }
    else
    {
      Serial.println("LEFT");
    }
  }
}

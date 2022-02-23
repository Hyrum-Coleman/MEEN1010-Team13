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
        PrintSensorValue();
        break;
      case 'f':
        PrintBlackWhite();
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
void PrintSensorValue(void)
{
  irSensorValue = analogRead(irSensorPin);
  timeSinceLastPrint = millis() - printTime;
  if (timeSinceLastPrint > 50)
  {
    printTime = millis();
    char printArray[1000];
    sprintf(printArray, "The sensor value is %d\n", irSensorValue);
    Serial.print(printArray);
  }
}
void PrintBlackWhite(void)
{
  bool prevBlack = black;
  black = GetEncoderBoolean();
  if (black != prevBlack)
  {
    if (black == 1)
      Serial.println("Over black");
    else
      Serial.println("Over White");
  }
}

void TestMotor(void)
{
  int prevButtonPressed = buttonPressed;
  ReadButtons();
  switch (buttonPressed)
  {
    case 3:  //Up button
    case 1:  //Down button
      timeSinceLastIncrement = millis() - incrementTime;
      if ((prevButtonPressed != buttonPressed) || (timeSinceLastIncrement > 250))
      {
        incrementTime = millis();
        if (buttonPressed == 3)
        {
          counts++;
        }
        else if (buttonPressed == 1)
        {
          counts--;
        }
        Serial.print(F("Counts is: "));
        Serial.println(counts);
      }
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
      if (counts != 24)
      {
        counts = 24;
        Serial.print(F("IDK dawg, counts is "));
        Serial.print(counts);
        Serial.println(F(" now (ツ)_/¯"));
      }
      break;

    case 0:  //No button
      TurnMotorOff(10);
      if (userInput == 'g')
      {
        CountStripes();
      }
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
        CountStripes();
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
    Serial.print(F("Launcher is moving "));
    if (motorRight)
    {
      Serial.println(F("RIGHT"));
    }
    else
    {
      Serial.println(F("LEFT"));
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
    Serial.print(F("The sensor value is "));
    Serial.println(irSensorValue);
  }
}
void PrintBlackWhite(void)
{
  bool prevBlack = black;
  black = GetEncoderBoolean();
  if (black != prevBlack)
  {
    if (black == 1)
    {
      Serial.println(F("Over black"));
    }
    else
    {
      Serial.println(F("Over white"));
    }

  }
}

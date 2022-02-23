void ReadButtons(void)
{
  //Keep track of the previous button number
  int prevButtonNumber = buttonNumber;

  // Read the button value
  int buttonVal = analogRead(buttonPin);

  // Determine the button number that corresponds to the button value

  // ASK ALEX IF NO CURLY BRACKETS IS OK FOR GRADING PURPOSES
  if (buttonVal < 5)
  {
    buttonNumber = 1;
  }
  else if ((buttonVal > 115) && (buttonVal < 175))
  {
    buttonNumber = 2;
  }
  else if ((buttonVal > 305) && (buttonVal < 365))
  {
    buttonNumber = 3;
  }
  else if ((buttonVal > 480) && (buttonVal < 540))
  {
    buttonNumber = 4;
  }
  else if ((buttonVal > 715) && (buttonVal < 775))
  {
    buttonNumber = 5;
  }
  else if (buttonVal > 1015)
  {
    buttonNumber = 0;
  }
  else
  {
    buttonNumber = -1;
  }

  // Determine if the button number is an actual button press or a bounce
  if (buttonNumber == prevButtonNumber)
  {
    cibn = cibn + 1;
    if (cibn > 100)
    {
      buttonPressed = buttonNumber;
    }
  }
  else
  {
    cibn = 0;
  }
}

void TestButtons(void)
{
  //Keep track of the previously pressed button
  int prevButtonPressed = buttonPressed;

  // Check what button is currently pressed
  ReadButtons();

  // If appropriate, print a new message
  timeSinceLastPrint = millis() - printTime;
  if ((timeSinceLastPrint > printDelay) || (buttonPressed != prevButtonPressed))
  {
    printTime = millis();
    switch (buttonPressed)
    {
      case 3:
        Serial.println("UP button is pressed");
        break;

      case 1:
        Serial.println("DOWN button is pressed");
        break;

      case 4:
        Serial.println("LEFT button is pressed");
        break;

      case 2:
        Serial.println("RIGHT button is pressed");
        break;

      case 5:
        Serial.println("SELECT button ispressed");
        break;

      case 0:
        Serial.println("NO buttons are pressed");
        break;

      default:
        Serial.println("Something has gone terribly wrong");
        break;
    }
  }

}

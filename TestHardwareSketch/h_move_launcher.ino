void TestMoveLauncher(void)
{
  int prevButtonPressed = buttonPressed;
  ReadButtons();
  switch (buttonPressed)
  {
    case cUpButtonPressed:  //Up button
    case cDownButtonPressed:  //Down button
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

    case cLeftButtonPressed:  //Left button
    case cRightButtonPressed:  //Right button
      timeSinceLastIncrement = millis() - incrementTime;
      if ((prevButtonPressed != buttonPressed) || (timeSinceLastIncrement > 250))
      {
        incrementTime = millis();
        if (buttonPressed == 4)
        {
          desiredPosition--;
        }
        else if (buttonPressed == 2)
        {
          desiredPosition++;
        }
        Serial.print("Desired position is: ");
        Serial.println(desiredPosition);
      }
      break;

    case cSelectButtonPressed:  //Select button
      startMotion = 1;
      break;

    case cNoButtonPressed:  //No button
      MoveLauncher();
      break;

    default:
      //Doing nothing
      break;
  }
}

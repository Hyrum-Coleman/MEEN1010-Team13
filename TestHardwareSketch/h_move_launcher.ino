void TestMoveLauncher(void)
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
    case 2:  //Right button
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

    case 5:  //Select button
      startMotion = 1;
      break;

    case 0:  //No button
      MoveLauncher();
      break;

    default:
      //Doing nothing
      break;
  }
}

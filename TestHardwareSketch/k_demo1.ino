void Demo1(void)
{
  int prevButtonPressed = buttonPressed;
  ReadButtons();
  switch (buttonPressed)
  {
    case cUpButtonPressed:
    case cDownButtonPressed:
      timeSinceLastIncrement = millis() - incrementTime;
      if ((prevButtonPressed != buttonPressed) || (timeSinceLastIncrement > 250))
      {
        incrementTime = millis();
        if (buttonPressed == 3)
        {
          target++;
        }
        else if (buttonPressed == 1)
        {
          target--;
        }
        target = constrain(target, 0, 5);
        Serial.print(F("Target is: "));
        Serial.println(target);
      }
      break;

    case cLeftButtonPressed:
    case cRightButtonPressed:
      timeSinceLastIncrement = millis() - incrementTime;
      if ((prevButtonPressed != buttonPressed) || (timeSinceLastIncrement > 250))
      {
        incrementTime = millis();
        if (buttonPressed == 4)
        {
          headed--;
        }
        else if (buttonPressed == 2)
        {
          headed++;
        }
        headed = constrain(headed, 0, 2);
        Serial.print("Headed is: ");
        Serial.println(headed);
      }
      break;
    case cSelectButtonPressed:
      startMotion = 1;
      state = 1;
      break;
    case cNoButtonPressed:
      MoveLauncher();
      break;

  }
}

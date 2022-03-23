void Demo1(void)
{
  int prevButtonPressed = buttonPressed;
  ReadButtons();
  switch (buttonPressed)
  {
    case 3:
    case 1:
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

    case 4:
    case 2:
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
    case 5:
      startMotion = 1;
      state = 1;
      break;
    case 0:
      MoveLauncher();
      break;

  }
}
void TestReloader(void)
{
  int prevButtonPressed = buttonPressed;
  ReadButtons();
  switch (buttonPressed)
  {
    case 5: //select
      if (prevButtonPressed != buttonPressed)
      {
        if (state > 0)
        {
          Serial.println(F("Stuff is already happening.....idiot"));
        }
        else
        {
          state = 1;
        }
      }
      break;
  }
  switch (state)
  {
    case 1: //Command the reloader servo to the dispense angle
      //command the servo
      reloaderServo.write(dispenseAngle);
      Serial.println(F("DISPENSING"));
      // change the state, update the time
      state = 2;
      stateChangeTime = millis();
      break;
    case 2: // Delay, the command the reloader servo to the hold angle
      timeSinceLastStateChange = millis() - stateChangeTime;
      if (timeSinceLastStateChange > dispenseDelay)
      {
        // command the servo
        reloaderServo.write(holdAngle);
        Serial.println(F("HOLDING"));
        // change the state
        state = 0;
      }
      break;
  }
}

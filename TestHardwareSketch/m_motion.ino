void MoveLauncher(void)
{
  //  DebugPrint("Calling MoveLauncher; startMotion = ", startMotion);
  if (motorOn == true)
  {
    Moving();
  }
  else
  {
    if (startMotion)
    {
      PreparingToMove();
    }
    else
    {
      //NotMoving();
    }
  }
}

void PreparingToMove(void)
{
  // set desiredPosition
  // set motorRight
  if (desiredPosition > counts)
  {
    motorRight = 1;
  }
  else
  {
    motorRight = 0;
  }
  // turn motor on
  if (counts != desiredPosition)
  {
    TurnMotorOn();
    startMotion = 0;
  }
}

void Moving(void)
{
  //Count stripes
  CountStripes();
  //Stop at target
  if (counts == desiredPosition)
  {
    TurnMotorOff(10);
    CountStripes();
    Serial.print("Launcher at stripe ");
    Serial.println(counts);
  }
  //Read switches
  leftSwitchState = digitalRead(leftSwitchPin);
  rightSwitchState = digitalRead(rightSwitchPin);
  //Stop at home (moving left, left switch tripped)
  if ((motorRight == 0) & (leftSwitchState == 1))
  {
TurnMotorOff(10);
CountStripes();
counts = 5;
Serial.print("Launcher at home -- counts set to ");
Serial.println(counts);
  }
  //Stop at reloader (moving right, right switch tripped)
    if ((motorRight == 1) & (rightSwitchState == 1))
  {
TurnMotorOff(10);
CountStripes();
counts = 43;
Serial.print("Launcher at reloader -- counts set to ");
Serial.println(counts);
}
}

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
  

}

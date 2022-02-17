void TestSwitches(void)
{
  // Keep track of previous switch states for comparison
  int prevLeftSwitchState = leftSwitchState;
  int prevRightSwitchState = rightSwitchState;

  // Update the switch state variables
  int leftSwitchTempState = digitalRead(leftSwitchPin);
  int rightSwitchTempState = digitalRead(rightSwitchPin);

  // Left swtich debounce code
  if (leftSwitchTempState != prevLeftSwitchState)
  {
    timeSinceLastLeftSwitchChange = millis() - leftSwitchChangeTime;
    if (timeSinceLastLeftSwitchChange > switchDebounceTime)
    {
      leftSwitchChangeTime = millis();
      leftSwitchState = leftSwitchTempState;
    }
  }

  // Right switch debounce code
  if (rightSwitchTempState != prevRightSwitchState)
  {
    timeSinceLastRightSwitchChange = millis() - rightSwitchChangeTime;
    if (timeSinceLastRightSwitchChange > switchDebounceTime)
    {
      rightSwitchChangeTime = millis();
      rightSwitchState = rightSwitchTempState;
    }
  }

  // If appropriate, print a new message
  timeSinceLastPrint = millis() - printTime;
  if ((prevLeftSwitchState != leftSwitchState) || (prevRightSwitchState != rightSwitchState) || (timeSinceLastPrint > printDelay))
  {
    printTime = millis();
    char printArray [1000];
    sprintf(printArray, "Left switch state : %d ... Right switch state %d\n", leftSwitchState, rightSwitchState);
    Serial.print(printArray);
//    Serial.print("Left switch state: ");
//    Serial.print(leftSwitchState);
//    Serial.print(" ... Right switch state: ");
//    Serial.println(rightSwitchState);
  }
}

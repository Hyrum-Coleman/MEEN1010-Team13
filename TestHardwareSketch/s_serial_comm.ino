void GetDataFromMatlab(void)
{
  Serial.println("ready for data");
  String dataString1 = Serial.readStringUntil('\n');
  String dataString2 = Serial.readStringUntil('\n');
  int encoderStripeNum = dataString1.toInt();
  double targetDistance = dataString2.toDouble();
  Serial.print("Drive to stripe ");
  Serial.print(encoderStripeNum);
  Serial.print(" and aim for ");
  Serial.print(targetDistance, 3);
  Serial.println("m.");

}

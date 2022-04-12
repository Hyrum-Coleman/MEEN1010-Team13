void GetDataFromMatlab(void)
{
  Serial.println("ready for data");
  String dataString1 = Serial.readStringUntil('\n');
  String dataString2 = Serial.readStringUntil('\n');
  int myInt = dataString1.toInt();
  double myDouble = dataString2.toDouble();
  Serial.print("I recieved ");
  Serial.print(myInt);
  Serial.print(" and ");
  Serial.print(myDouble, 3);
  Serial.println(". Is that what you sent?");

}

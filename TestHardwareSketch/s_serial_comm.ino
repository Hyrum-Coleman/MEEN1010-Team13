void GetDataFromMatlab(void)
{
  Serial.println("ready for data");


  for (target = 0; target < 6; target++)
  {
    String dataString1 = Serial.readStringUntil('\n');
    String dataString2 = Serial.readStringUntil('\n');
    int encoderStripeNum = dataString1.toInt();
    float targetDistance = dataString2.toFloat();
    driveTo[target] = encoderStripeNum;
    xTargetVec[target] = targetDistance;
    Serial.print("For target ");
    Serial.print(target);
    Serial.print(", drive to stripe ");
    Serial.print(driveTo[target]);
    Serial.print(" and aim for ");
    Serial.print(xTargetVec[target], 3);
    Serial.println("m.");
  }
  target = 0;
  // get linkage parameters from matlab
  String paramString; 
  paramString = Serial.readStringUntil('\n');
  alpha = paramString.toFloat();
  paramString = Serial.readStringUntil('\n');
  beta = paramString.toFloat();
  paramString = Serial.readStringUntil('\n');
  thetaL0 = paramString.toFloat();
  Serial.print("alpha = ");
  Serial.print(alpha, 3);
  Serial.print("; beta = ");
  Serial.print(beta, 3);
  Serial.print("; thetaL0 = ");
  Serial.println(thetaL0, 3);
  // get velocity coefficients from matlab
  String coeffString;
  coeffString = Serial.readStringUntil('\n');
  k = coeffString.toFloat();
  coeffString = Serial.readStringUntil('\n');
  lambda = coeffString.toFloat();

 
  Serial.print("kappa = ");
  Serial.print(k, 4);
  Serial.print("; lambda = ");
  Serial.println(lambda, 4);
  

}

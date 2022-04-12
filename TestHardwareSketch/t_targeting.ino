void ComputeStuff(void)
{
  Serial.println("Performing targeting calculations");
   double d[] = {.0400, .1583, .0553};
   double H[] = {.1301, .0960, .0880, .0465};
   
   TargetServoAngles(d,k, lambda, H, alpha, beta, thetaL0, xTargetVec);
   for (int i = 0; i < 6; i++)
{
  Serial.print("To hit a target at ");
  Serial.print(xTargetVec[i]);
  Serial.print(" m, command the servo to ");
  Serial.print(writeToServo[i]);
  Serial.println(" deg");
}
}

double Deg2Rad(double angleDeg)
{
  return angleDeg * M_PI / 180;
}
double Rad2Deg(double angleRag)
{
  return angleRag * 180 / M_PI;
}

double Quadratic(double a, double b, double c, int plusOrMinus)
{
  return (-b + plusOrMinus * sqrt(pow(b, 2) - (4 * a * c))) / (2 * a);
}
double LandingDistance(double d[], double k, double lambda, double thetaL)
{

  double x0;
  double y0;
  double v0x;
  double v0y;
  double tLand;
  const double g = 9.81;
  double v0 = k + lambda * thetaL;

  x0 = (d[1] * cos(Deg2Rad(thetaL))) - (d[2] * sin(Deg2Rad(thetaL))); // calculating initial coordinates
  y0 = (d[0] + d[1] * sin(Deg2Rad(thetaL))) + (d[2] * cos(Deg2Rad(thetaL)));

  v0x = v0 * cos(Deg2Rad(thetaL)); // calculating velocity components
  v0y = v0 * sin(Deg2Rad(thetaL));

  tLand = Quadratic(-g / 2, v0y, y0, -1); // calculating tland using quadratic function

  return x0 + v0x * tLand; // returning xland

}

double RangeAngle(double d[], double k, double lambda)
{
  double thetaL = 0;
  double range = 0;
  double rangeAngle = 0;

  while (thetaL <= 90) { // loops while theta is less than 90, it starts at 0 so it will always loop at least once
    double xLand = LandingDistance(d, k, lambda, thetaL); // calls landing distance function for current theta and stores it in xLand

    if (xLand > range) { // if xLand is greater than range the if statements triggers, range starts at 0 so it will initially happen
      range = xLand; // range becomes xLand
      rangeAngle = thetaL; // range angle becomes theta
      //eventually the if will no longer apply and the max values will be stored in range and rangeAngle
    }
    thetaL = thetaL + .05; // increment theta
    // thetaL = thetaL + .05;
    // Serial.println(thetaL);
  }

  return rangeAngle;
}
double LaunchAngle(double d[], double k, double lambda, double xTarget)
{
  double thetaL = RangeAngle(d, k, lambda);
  double xLand = LandingDistance(d, k, lambda, thetaL);

  while (xLand > xTarget)
  {
    thetaL = thetaL + .05;
    xLand = LandingDistance(d, k, lambda, thetaL);
  }
  return thetaL;
}

double ThetaFour(double L[], double theta2)
{
  double L1 = L[0];
  double L2 = L[1];
  double L3 = L[2];
  double L4 = L[3];

  double K1 = L1 / L2;
  double K2 = L1 / L4;
  double K3 = (pow(L1, 2) + pow(L2, 2) - pow(L3, 2) + pow(L4, 2)) / (2 * L2 * L4);

  double A = cos(theta2) - K1 - (K2 * cos(theta2)) + K3;
  double B = -2 * sin(theta2);
  double C = K1 - ((K2 + 1) * cos(theta2)) + K3;

  double negRoot = Quadratic(A, B, C, -1);

  return 2 * atan(negRoot);
}
double ThetaServo(double H[], double thetaL, double alpha, double beta, double thetaL0)
{
  thetaL = Deg2Rad(thetaL);
  alpha = Deg2Rad(alpha);
  thetaL0 = Deg2Rad(thetaL0);
  double theta2 = thetaL - thetaL0;
  double theta4 = ThetaFour(H, theta2);

  return Rad2Deg((theta4 + alpha) / (1 - beta));
}

void TargetServoAngles(double d[], double k, double lambda, double H[], double alpha, double beta, double thetaL0, double xTargetVec[])
{
  double localLaunchVec[6];
  double localServoVec[6];
  for (int i = 0; i < 6; i++)
  {
    Serial.print("Computing target ");
    Serial.println(i);

    localLaunchVec[i] = LaunchAngle(d, k, lambda, xTargetVec[i]);
    localServoVec[i] = ThetaServo(H, localLaunchVec[i], alpha, beta, thetaL0);

    writeToServo[i] = int(round(localServoVec[i]));

//    Serial.print("xTarget [m] = ");
//    Serial.print(xTargetVec[i]);
//    Serial.print(" --> thetaL [deg] = ");
//    Serial.print(localLaunchVec[i]);
//    Serial.print(" --> thetaS [deg] = ");
//    Serial.print(localServoVec[i]);
//    Serial.print(" --> Rounded thetaS [deg] = ");
//    Serial.println(writeToServo[i]);

  }
}

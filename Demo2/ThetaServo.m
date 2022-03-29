function [thetaS] = ThetaServo(H, thetaL, params)
theta2 = thetaL - params(3);
theta4 = ThetaFour(H, theta2);
thetaS = (theta4 + params(1)) / (1 - params(2));
end
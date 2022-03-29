function [thetaL] = ThetaLaunch(L, thetaS, params)
% calculates thetaL
alpha = params(1);
beta = params(2);
thetaL0 = params(3);

thetaSC = alpha + beta * thetaS;
theta2 = 180 - thetaS + thetaSC;
theta4 = ThetaFour(L, theta2);
thetaL = 180 - theta4 + thetaL0;

if(nargout == 0)
    plot(thetaS, thetaL);
    title('Cannon Fourbar Kinematics');
    xlabel('Servomotor Angle [deg]');
    ylabel('Launch Angle [deg]');

end

end
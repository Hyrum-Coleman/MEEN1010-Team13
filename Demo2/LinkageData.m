function [thetaS,aveThetaL] = LinkageData(filename)
data = readmatrix(filename);
thetaS = data(:, 1);
experThetaL = data(:, 2:end);
aveThetaL = mean([experThetaL]')';

if(nargout == 0)
    plot(thetaS, aveThetaL, 'rx');
    title('Cannon Fourbar Kinematics');
    xlabel('Servo Angle [deg]');
    ylabel('Launch Angle [deg]');
end

end
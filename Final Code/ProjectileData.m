function [thetaL,aveXLand] = ProjectileData(filename)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
data = readmatrix(filename);
thetaL = data(:, 1);
xLand1 = data(:, 2:end);
% xLand2 = data(:, 3);
% xLand3 = data(:, 4);
aveXLand = mean(xLand1, 2);
aveXLand = aveXLand ./ 100;

if(nargout == 0)
    plot(thetaL, aveXLand, 'ro');
    title('Ping Pong Ball Projectile Data');
    xlabel('Launch Angle [deg]');
    ylabel('Horizontal Distance Travelled [m]');
end

end
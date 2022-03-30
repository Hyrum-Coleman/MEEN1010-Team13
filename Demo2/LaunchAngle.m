% Hyrum Coleman, u1365193, ME EN 1010, HW9a

function [steepThetaL] = LaunchAngle(d, v0, xTarget)


for i = 1:length(xTarget)
[range, rangeAngle] = ProjectileRange2(d, v0);
thetaL0 = linspace(rangeAngle, 90, 10000);

xLand = LandingDistance(d, v0, thetaL0);
absXDiff = abs(xLand - xTarget(i));

[minDiff, minDiffIndex] = min(absXDiff);
steepThetaL(i) = thetaL0(minDiffIndex);
end


end
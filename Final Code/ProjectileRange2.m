% Hyrum Coleman, u1365193, ME EN 1010, HW6b

function [range, rangeAngle] = ProjectileRange2(d, velCoeffs)

thetaL = 0:.01:90;
xLand = LandingDistance(d, velCoeffs, thetaL);
[range, rangeIndex] = max(xLand);
rangeAngle = thetaL(rangeIndex);

if (nargout == 0)
plot(thetaL,xLand);
end

end
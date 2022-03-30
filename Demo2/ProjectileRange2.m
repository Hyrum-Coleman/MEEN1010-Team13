% Hyrum Coleman, u1365193, ME EN 1010, HW6b

function [range, rangeAngle] = ProjectileRange2(d, v0)

thetaL = 0:.01:90;
xLand = LandingDistance(d, v0, thetaL);
[range, rangeIndex] = max(xLand);
rangeAngle = thetaL(rangeIndex);

if (nargout == 0)
plot(thetaL,xLand);
end

end
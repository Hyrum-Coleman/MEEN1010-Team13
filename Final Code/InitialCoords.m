% Hyrum Coleman, u365193, ME EN 1010, HW5b
function [x0, y0] = InitialCoords(d, theta) 
% Calculates the starting coordinates of a point
% Inputs: d     -- array with all 3 distances in it
%         theta -- array with all the angles
% Output: x0    -- starting x position
%         y0    -- starting y position
x0 = (d(2) .* cosd(theta)) - (d(3) .* sind(theta));
y0 = (d(1) + d(2) .* sind(theta)) + (d(3) .* cosd(theta));
end
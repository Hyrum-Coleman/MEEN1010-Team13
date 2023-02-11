% Hyrum Coleman, u365193, ME EN 1010, HW5b
function [v0x, v0y] = InitialVelocityComponents(v0, theta)
% seperates the starting velocity into its x and y components
% Inputs: v0 -- initial velocity
%         theta -- array with all the angles
% Output: v0x -- velocity in the x component
%         v0y -- velocity in the y component
v0x = v0 .* cosd(theta);
v0y = v0 .* sind(theta);
end     
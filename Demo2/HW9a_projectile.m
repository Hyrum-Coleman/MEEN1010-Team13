%%%%%%%%%%%%%%%%%%%%%
% Hyrum Coleman
% u1365193
% ME EN 1010 Lab Section #003
% HW 9a_projectile
% 03/22/22
%%%%%%%%%%%%%%%%%%%%%
clear; clc; close all;

%%

load d_vector.mat;
v0 = 3.2;
xTarget = [.9, 1.05, 1.20];

thetaL = LaunchAngle2(d, v0, xTarget);

for i = 1:length(xTarget)
fprintf("To hit a target at %.2f m the launch angle should be %.2f degrees\n", xTarget(i), thetaL(i));
end
%%%%%%%%%%%%%%%%%%%%%
% Hyrum Coleman
% u1365193
% ME EN 1010 Lab Section #003
% HW 9b
% 03/25/22
%%%%%%%%%%%%%%%%%%%%%
clear; clc; close all;

%%

load d_vector.mat
v0 = 3.25;
filename = 'Robot12_ProjectileData.xlsx';
[exp_thetaL, exp_xLand] = ProjectileData(filename);

SSE = CompareProjectileData(v0, d, exp_thetaL, exp_xLand);

fprintf("The SSE is %.4f\n", SSE);

%%

load d_vector.mat

filename = 'Robot12_ProjectileData.xlsx';
[exp_thetaL, exp_xLand] = ProjectileData(filename);
[optimal_v0, best_SSE] = fminbnd(@CompareProjectileData, 0, 5, [], d, exp_thetaL, exp_xLand);

fprintf("The best v0 is %.4f\nThe best SSE is %.4f\n", optimal_v0, best_SSE);

figure
ProjectileData(filename);
hold on
LandingDistance(d, optimal_v0, exp_thetaL);
legend('experiment', 'theory');
graphTxt = sprintf("The SSE is %.4f for an initial velocity of %.2f", best_SSE, optimal_v0);
text(25, .3, graphTxt);


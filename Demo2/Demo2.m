%%%%%%%%%%%%%%%%%%%%%
% Hyrum Coleman, Will Connors
% u1365193       u1351108
% ME EN 1010 Lab Section #003
% 03/30/22
%%%%%%%%%%%%%%%%%%%%%
clear; clc; close all;

%%
% General
clear; clc; close all;


% Initializing Varialbes
linkageFilename = 'Robot12_LinkageData.xlsx';
load L_vector.mat
load H_vector.mat
[thetaS_exper, thetaL_exper] = LinkageData(linkageFilename);

% Finding minimum value of params
[optimal_params, paramsSSE] = fminsearch(@CompareLinkageData, [0, 0, 0], [], L, thetaS_exper, thetaL_exper);

% Graphing the information
figure
LinkageData(linkageFilename);
hold on
ThetaLaunch(L, thetaS_exper, optimal_params);
legend('experiment', 'theory', 'Location', 'southeast');
graphTxt = sprintf("alpha = %.2f\nbeta = %.2f\nthetaL0 = %.2f\nSSE = %.4f", optimal_params(1), optimal_params(2), optimal_params(3), paramsSSE);
text(20, 70, graphTxt);

thetaL = [47, 54, 61, 68];
% thetaL = [45, 51, 57, 63]

thetaS = ThetaServo(H, thetaL, optimal_params);

for i=1:length(thetaS)
fprintf("Use a servo angle of %.2f deg to achieve a launch angle of %.2f deg\n", thetaS(i), thetaL(i));
end

load('d_vector.mat');

% Extracting the projectile data from the robot 12 spreadsheet
projectileFilename = 'Robot12_ProjectileData.xlsx';
[exp_thetaL, exp_xLand] = ProjectileData(projectileFilename);

% Finding the optimal SSE and v0
[optimal_v0, best_SSE] = fminbnd(@CompareProjectileData, 0, 5, [], d, exp_thetaL, exp_xLand);

% Creating a plot for displaying the experimental vs theory data
figure
ProjectileData(projectileFilename);
hold on
LandingDistance(d, optimal_v0, exp_thetaL);
legend('experiment', 'theory');
graphTxt = sprintf("The SSE is %.4f for an initial velocity of %.2f m/s", best_SSE, optimal_v0);
text(25, .3, graphTxt);

%%
% Linkage


%%
% Projectile


%%
% Targeting


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
linkageFilename = 'Robot18_LinkageData.xlsx';
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
projectileFilename = 'Robot18_ProjectileData.xlsx';
[exp_thetaL, exp_xLand] = ProjectileData(projectileFilename);

% Finding the optimal SSE and v0
[optimal_velCoeffs, best_SSE] = fminsearch(@CompareProjectileData, [3.2,0], [], d, exp_thetaL, exp_xLand);

% Creating a plot for displaying the experimental vs theory data
figure
ProjectileData(projectileFilename);
hold on
LandingDistance(d, optimal_velCoeffs, exp_thetaL);
legend('experiment', 'theory');
graphTxt = sprintf("The SSE is %.4f for kappa of %.2f and lamda of %.4f\n", best_SSE, optimal_velCoeffs(1), optimal_velCoeffs(2));
text(20, .3, graphTxt);

%xTarget = [0.70,0.85,1.00,1.15];
xTarget = [0.75,0.90,1.05,1.20];

%%
% Linkage


%%
% Projectile
% Ask alex if we should add clear, clc and close all

thetaL = LaunchAngle(d, optimal_velCoeffs, xTarget);
thetaS = ThetaServo(H, thetaL, optimal_params);

for i = 1:length(xTarget)
fprintf("To hit a target at %.2f m the launch angle should be %.2f degrees\n", xTarget(i), thetaL(i));
end

for i = 1:length(xTarget)
fprintf("To hit a target at %.2f m use a servo angle of %.2f degrees, to get a launch angle of %.2f degrees\n", xTarget(i), thetaS(i), thetaL(i));
end


%%
% Targeting


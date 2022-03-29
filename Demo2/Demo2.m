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
[thetaS, thetaL] = LinkageData(linkageFilename);

% Finding minimum value of params
[optimal_params, paramsSSE] = fminsearch(@CompareLinkageData, [0, 0, 0], [], L, thetaS, thetaL);

% Graphing the information
LinkageData(linkageFilename);
hold on
ThetaLaunch(L, thetaS, optimal_params);
legend('experiment', 'theory', 'Location', 'southeast');
graphTxt = sprintf("alpha = %.2f\nbeta = %.2f\nthetaL0 = %.2f\nSSE = %.4f", optimal_params(1), optimal_params(2), optimal_params(3), paramsSSE);
text(20, 70, graphTxt);


%%
% Linkage


%%
% Projectile



%%
% Targeting
%%%%%%%%%%%%%%%%%%%%%
% Hyrum Coleman, Will Connors
% u1365193       u1351108
% ME EN 1010 Lab Section #003
% 03/30/22
%%%%%%%%%%%%%%%%%%%%%
clear; clc; close all;

%%

params = [30, .08, 12];
load L_vector.mat
filename = 'Robot12_LinkageData.xlsx';
[thetaS, thetaL] = LinkageData(filename);
SSE = CompareLinkageData(params, L, thetaS, thetaL)

%%

load L_vector.mat
filename = 'Robot12_LinkageData.xlsx';
[thetaS, thetaL] = LinkageData(filename);

[optimal_params, paramsSSE] = fminsearch(@CompareLinkageData, [0, 0, 0], [], L, thetaS, thetaL)

LinkageData(filename);
hold on
ThetaLaunch(L, thetaS, optimal_params);
legend('experiment', 'theory', 'Location', 'southeast');
graphTxt = sprintf("alpha = %.2f\nbeta = %.2f\nthetaL0 = %.2f\nSSE = %.4f", params(1), params(2), params(3), SSE);
text(20, 70, graphTxt);




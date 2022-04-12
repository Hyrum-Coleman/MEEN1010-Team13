%%%%%%%%%%%%%%%%%%%%%
% Hyrum Coleman 
% u1365193
% ME EN 1010 Lab Section #003
% HW 11b
% 04/07/22
%%%%%%%%%%%%%%%%%%%%%
% clear; clc; close all;

%%

% RGBImage = imread("test_image1.bmp");
% [PixelRGB] = ColorPicker(RGBImage);

imageArray = imread("S22_PP_A1.bmp");
disp("Click on the peashooter to get color info!");
peaRGB = ColorPicker(imageArray);
Rtarget = 5 * peaRGB(3);
Gtarget = 5 * peaRGB(3);
Btarget = 4 * peaRGB(3);
targetRGB = [Rtarget, Gtarget, Btarget];

[centroidRowVec, centroidColVec, imageArray] = FindAllTargetCentroids(imageArray, targetRGB);

centroidColVec
centroidRowVec

figure
image(imageArray)
hold on
plot(centroidColVec, centroidRowVec, 'mo');
drawnow

stripeNum = (.2 * centroidRowVec) ./ 10
xTargetm = (650 + .2 * centroidColVec) ./ 1000



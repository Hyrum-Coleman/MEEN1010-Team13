%%%%%%%%%%%%%%%%%%%%%
% Hyrum Coleman, Will Connors
% u1365193       u1351108
% ME EN 1010 Lab Section #003
% 04/11/22
%%%%%%%%%%%%%%%%%%%%%
clear, clc, close all
%%

load('d_vector.mat');
load L_vector.mat;
linkageFilename = 'Robot18_LinkageData.xlsx';
projectileFilename = 'Robot18_ProjectileData2.xlsx';

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
hold off



%%
figure
imageArray = imread("S22_PP_B2.bmp");
disp("Click on the peashooter to get color info!");
peaRGB = ColorPicker(imageArray);
Rtarget = 5 * peaRGB(3);
Gtarget = 5 * peaRGB(3);
Btarget = 4 * peaRGB(3);
targetRGB = [Rtarget, Gtarget, Btarget];

[centroidRowVec, centroidColVec, imageArray] = FindAllTargetCentroids(imageArray, targetRGB);

centroidRowVec;

%sorting centroid row vec for optimal movement before sending to arduino

%shoot about 2 stripes before to game

sortedCentroidRowVec = sort(centroidRowVec, 'descend');
tempCentroidRowVec = sortedCentroidRowVec(end);
sortedCentroidRowVec(end) = sortedCentroidRowVec(1);
sortedCentroidRowVec(1) = tempCentroidRowVec;

tempCentroidRowVec = sortedCentroidRowVec(end);
sortedCentroidRowVec(end) = sortedCentroidRowVec(end-1);
sortedCentroidRowVec(end-1) = tempCentroidRowVec;
sortedCentroidRowVec;

[~,sortedCentroidIndex] = ismember(sortedCentroidRowVec,centroidRowVec);

centroidColVec;
sortedCentroidColVec = centroidColVec(sortedCentroidIndex);


figure
image(imageArray)
hold on
plot(centroidColVec, centroidRowVec, 'mo');
drawnow
% oldStripeNum = (.2 * centroidRowVec) ./ 10
stripeNum = (.2 * sortedCentroidRowVec) ./ 10
% oldxTargetm = (650 + .2 * centroidColVec) ./ 1000
xTargetm = (650 + .2 * sortedCentroidColVec) ./ 1000
%xTargetm = xTargetm - .02

%%

% serial communication setup
RomeoCOM = serialport('COM7',9600);
endCheck = "done";
dataCheck = "ready for data";

% key press detection setup
kbhit('init');
key = char(0);
prevKey = key;

while(1)
    % key press detection
    prevKey = key;
    key = kbhit;
    pause(1/6000) % seconds
    if key == 'q'
        disp('Matlab aborting! o7 soldiers')
        break
    elseif key ~= char(0)
        disp('sending letter to Arduino')
        writeline(RomeoCOM,key)
    end

    % serial communication
    if RomeoCOM.NumBytesAvailable > 0   
        message = readline(RomeoCOM);
        message = erase(message,sprintf('\r'));
        if strcmp(message,endCheck) == 1
            break;
        elseif strcmp(message, dataCheck) == 1
            %send data to arduino
            disp('sending data to romeo');
            % send target info to Romeo
            for target = 1:6
            % Try sending an integer value as a string to Romeo
            out1 = sprintf('%d',stripeNum(target));
            writeline(RomeoCOM,out1);
            out2 = sprintf('%.3f', xTargetm(target));
            writeline(RomeoCOM, out2);
            message = readline(RomeoCOM);
            message = erase(message,sprintf('\r'));
            disp(message);
            end
            % send linkage parameters to Romeo
            for i = 1:3
                out3 = sprintf('%.3f', optimal_params(i));
                writeline(RomeoCOM, out3);
                
            end
            message = readline(RomeoCOM);
                message = erase(message,sprintf('\r'));
                disp(message);
            % send velocity coefficients to Romeo
            for i = 1:2
                out4 = sprintf('%.4f', optimal_velCoeffs(i));
                writeline(RomeoCOM, out4);
            end
            message = readline(RomeoCOM);
                message = erase(message,sprintf('\r'));
                disp(message);
        else
            disp(message);
            
        end
    end
end

clear RomeoCOM
kbhit('stop');
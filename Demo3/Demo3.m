%%%%%%%%%%%%%%%%%%%%%
% Hyrum Coleman, Will Connors
% u1365193       u1351108
% ME EN 1010 Lab Section #003
% 04/11/22
%%%%%%%%%%%%%%%%%%%%%
clear, clc, close all
%%

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

%%

% serial communication setup
RomeoCOM = serialport('/dev/tty.usbmodem101',9600);
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
        end
    end
end

clear RomeoCOM
kbhit('stop');
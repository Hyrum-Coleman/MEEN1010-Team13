% header
clear, clc, close all

% serial communication setup
RomeoCOM = serialport('COM10',9600)
endCheck = "done";
dataCheck = "ready for data";

% key press detection setup
% kbhit('init');
% key = char(0);
% prevKey = key;

while(1)
    % key press detection
%     prevKey = key;
%     key = kbhit;
%     pause(1/6000)
%     if key ~= char(0)
%         disp('sending letter to Arduino')
%         writeline(RomeoCOM,key)
%     end

    % serial communication
    if RomeoCOM.NumBytesAvailable > 0   
        message = readline(RomeoCOM);
        % message = erase(message,sprintf('\r'));
        disp(message)
    end
end

clear RomeoCOM
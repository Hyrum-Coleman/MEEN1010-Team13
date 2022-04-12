% header
clear, clc, close all

% serial communication setup
RomeoCOM = serialport('/dev/tty.usbmodem1101',9600);
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
            % Try sending an integer value as a string to Romeo
            out1 = sprintf('%d',25);
            writeline(RomeoCOM,out1);
            out2 = sprintf('%.3f', 1.234);
            writeline(RomeoCOM, out2);
            message = readline(RomeoCOM);
            message = erase(message,sprintf('\r'));
        end
        disp(message)
    end
end

clear RomeoCOM
kbhit('stop');
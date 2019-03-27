% I2t current limit: user
% JFDuval, Dephy, Inc. 06/14/2017
% Update August 2018: Added non-linearity
% Update December 2018: Cleaner code and output

% Note: use this file to get your #define values. i2t_1.m can be used to test
% your values with different profiles.

clc;
close all;
clear all;
format short eng

% Period, i2t_compute() call:
dt = 100e-3;      %Every 100ms
Y_TIME_MAX = 20;  %Max time plotted, in seconds

disp('Program these values in i2t-current-limit.h:')
disp('============================================')

% The algorithm uses 8-bit values: we need to scale down the maximum current
% accordingly. It uses real units (mA). Ex.: ±30000mA sensor
% 30000/256 = 117 => shift 7 (div by 128). 30A will give us 234

% Pocket has a ±5A sensor. 5000/256 = 19.53 => shift by 5 (32)

I2T_SHIFT = 7             % Closest bitshift available
SCALE = 128;              % (Octave only, avoids bitwise operations)
NON_LIN_TRESH = 55000;    % mA

% Maximum average current you want to support:
maxAvgCurrent = 15000;     %mA
I2T_LEAK = (maxAvgCurrent / SCALE)^2

% Maximum peak current you want to support, and duration:
currentLimit = 50000;     %mA
currentLimitTime = 0.33;     %s
I2T_LIMIT = (currentLimitTime / dt) * ((currentLimit/SCALE)^2 - I2T_LEAK)

%At what fraction of the max to you want a warning? (0-1)
warn = 0.8;
I2T_WARNING = warn * I2T_LIMIT;

%8-bit non-lin:
I2T_NON_LINEAR_THRESHOLD = NON_LIN_TRESH / SCALE

% Plotting:
CURR = maxAvgCurrent:100:2.5*currentLimit;
CURR2 = (max(0,(CURR-NON_LIN_TRESH)));
tmp = (CURR./SCALE).^2;
tmpNL = ((CURR+10*CURR2)./SCALE).^2;
time = (I2T_LIMIT * dt) ./ ( tmp - I2T_LEAK );
timeNL = (I2T_LIMIT * dt) ./ ( tmpNL - I2T_LEAK );
figure()
plot(CURR, time)
title('Time before reaching the I2t limit')
xlabel('Current (mA)')
ylabel('Time (s)')
ylim([0,Y_TIME_MAX])
hold on
plot(CURR, timeNL, 'r')
legend('Original', 'Non-linear')

disp('')
disp('Time at given current (mA):')
CURR = 25000
CURR2 = (max(0,(CURR-NON_LIN_TRESH)));
tmp = (CURR./SCALE).^2;
tmpNL = ((CURR+10*CURR2)./SCALE).^2;
time = (I2T_LIMIT * dt) ./ ( tmp - I2T_LEAK )
timeNL = (I2T_LIMIT * dt) ./ ( tmpNL - I2T_LEAK )

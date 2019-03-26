clc;
close all;
clear all;
format short eng

tresh = 125;
g = 10;
currDigital = 125:1:150;
currNonLin = currDigital + g.*(max(0,currDigital-tresh))
amps = currNonLin * 128;

plot(currDigital)
figure()
plot(amps)
max(amps)
%% load data
data = load('Output/energy_autocorr.dat');

figure(3);
clf;
hold all;
plot(data(:,1),data(:,2));
plot([data(1,1),data(end,1)],exp(-2.0)*[1,1],'-r');
shg;
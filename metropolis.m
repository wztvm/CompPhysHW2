%% Load data
data = load('Output/metropolis.dat');
data
size(data)
%% Plot data
fs=struct('title',20,'label',16);

k = 14985/15;
I = (k*9):(k*10);
I = I'
size(I)

figure(1);
clf;
hold all

plot(I,data(I,1),'o');
plot([I(1),I(end)],-294.0*8000*[1,1]);
%plot([I(1),I(end)],-436.0*4000-113.0*4000*[1,1]);
legend({'Lattice energy','Minimal lattice energy'},...
    'fontsize',fs.label,'location','NorthEast');
xlabel('Iteration number','fontsize',fs.label);
ylabel('Energy','fontsize',fs.label);
title('Energy','fontsize',fs.title);
shg;

figure(2);
clf;
hold all
plot(I,data(I,2),'o');
plot(I,data(I,3),'o');
shg;
ylim([-0.1,1.1]);
legend({'Long Range Order','Short Range order'},'Location','SouthEast',...
    'fontsize',fs.label)
xlabel('Iteration number','fontsize',fs.label);
ylabel('Whatever','fontsize',fs.label);
title('Mehch!','fontsize',fs.title);
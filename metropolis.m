%% Load data
data = load('Output/metropolis.dat');

%% Plot data
fs=struct('title',20,'label',16);

I = 1:length(data(:,1))

size(I)
size(run)
figure(1);
clf;
hold all

plot(I,data(:,1),'o');
plot([1,I(end)],-294.0*8000*[1,1]);
plot([1,I(end)],-436.0*4000-113.0*4000*[1,1]);
legend({'Lattice energy','Minimal lattice energy','Maximal lattice energy'},...
    'fontsize',fs.label,'location','East');
xlabel('Iteration number','fontsize',fs.label);
ylabel('Energy','fontsize',fs.label);
title('Energy','fontsize',fs.title);
shg;

figure(2);
clf;
hold all
plot(I,data(:,2),'o');
plot(I,data(:,3),'o');
shg;
ylim([-0.1,1.1]);
legend({'Long Range Order','Short Range order'},'Location','SouthEast',...
    'fontsize',fs.label)
xlabel('Iteration number','fontsize',fs.label);
ylabel('Whatever','fontsize',fs.label);
title('Mehch!','fontsize',fs.title);
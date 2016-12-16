%% load data
data = load('Output/heat_capacity_averages.dat');
size(data)
data


%% plot data
fs=struct('title',20,'label',18);

temperature = data(:,1);
mean = data(:,2);
s_autocorr = data(:,3);
std_autocorr = data(:,4);
s_block = data(:,5);
std_block = data(:,6);

temperature = temperature .* (temperature>=0.0);
figure(10);
clf;
hold all;
errorbar(temperature,mean,std_block,'.-','markersize',20);
xlabel('Temperature [K]','fontsize',fs.label,'interpreter','latex');
ylabel('Heat Capacity [meV/K]','fontsize',fs.label,'interpreter','latex');
title('Mean Heat Capacity','fontsize',fs.title,'interpreter','latex');
xlim([100,1000])
a = get(gca,'XTickLabel');
set(gca,'XTickLabel',a,'fontsize',14)
legend({'Mean energy'},'fontsize',fs.label,'interpreter','latex','location','NorthEast')
shg;

figure(11);
clf;
hold all;
plot(temperature,100*std_autocorr./abs(mean));
plot(temperature,100*std_block./abs(mean));

a = get(gca,'XTickLabel');
set(gca,'XTickLabel',a,'fontsize',14)

xlabel('Temperature [K]','fontsize',fs.label,'interpreter','latex')
ylabel('$\sigma$ [\% of mean]','fontsize',fs.label,'interpreter','latex');
title('Heat Capacity standard deviation','fontsize',fs.title,'interpreter','latex');
legend({'Autocorrelation function','Block averaging'},'fontsize',fs.label,'location','SouthWest','interpreter','latex');
hold off;

shg;


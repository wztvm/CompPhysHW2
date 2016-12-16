%% load data
data = load('Output/long_range_order_averages.dat');
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
figure(6);
clf;
hold all;
errorbar(temperature,mean,std_block,'.-','markersize',20);
plot([0,1100],[0,0]);
xlabel('Temperature [K]','fontsize',fs.label,'interpreter','latex');
ylabel('P','fontsize',fs.label,'interpreter','latex');
title('Long range order','fontsize',fs.title,'interpreter','latex');
legend({'Long range order'},'fontsize',fs.label,'interpreter','latex');
xlim([100,1100])
a = get(gca,'XTickLabel');
set(gca,'XTickLabel',a,'fontsize',14)
shg;

figure(7);
clf;
hold all;
plot(temperature,100*std_autocorr./abs(mean));
plot(temperature,100*std_block./abs(mean));
xlabel('Temperature [K]','fontsize',fs.label,'interpreter','latex')
ylabel('$\sigma$ [\% of mean]','fontsize',fs.label,'interpreter','latex');
title('Long range order standard deviation','fontsize',fs.title,'interpreter','latex');
a = get(gca,'XTickLabel');
set(gca,'XTickLabel',a,'fontsize',14)
hold off;

legend({'Autocorrelation function','Block averaging'},'fontsize',fs.label,'location','NorthWest','interpreter','latex');
shg;


%% load data
data = load('Output/energy_averages.dat');
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
figure(4);
clf;
hold all;
errorbar(temperature,mean,std_block,'.-','markersize',20);
xlabel('Temperature [K]','fontsize',fs.label,'interpreter','latex');
ylabel('Energy [meV]','fontsize',fs.label,'interpreter','latex');
title('Mean Energy','fontsize',fs.title,'interpreter','latex');
plot(temperature([1,end]),-294.0*8000*[1,1]);
xlim([100,1000])
a = get(gca,'XTickLabel');
set(gca,'XTickLabel',a,'fontsize',14)
legend({'Mean energy'},'fontsize',fs.label,'interpreter','latex','location','East')
shg;

figure(5);
clf;
hold all;
plot(temperature,100*std_autocorr./abs(mean));
plot(temperature,100*std_block./abs(mean));

a = get(gca,'XTickLabel');
set(gca,'XTickLabel',a,'fontsize',14)

xlabel('Temperature [K]','fontsize',fs.label,'interpreter','latex')
ylabel('$\sigma$ [\% of mean]','fontsize',fs.label,'interpreter','latex');
title('Energy standard deviation','fontsize',fs.title,'interpreter','latex');
legend({'Autocorrelation function','Block averaging'},'fontsize',fs.label,'location','NorthWest','interpreter','latex');
hold off;

shg;


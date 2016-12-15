data = load('Output/metropolis.dat');

figure(1);
clf;
hold all
plot(data(:,1));
legend({'Energy'});
xlabel('Iteration number');
ylabel('Energy');
title('Energy');
shg;

figure(2);
clf;
hold all
plot(data(:,2));
plot(data(:,3));
shg;
legend({'Long Range Order','Short Range order'})
xlabel('Iteration number');
ylabel('Whatever');
title('Mehch!');
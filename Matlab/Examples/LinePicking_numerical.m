%
% LinePicking_numerical.m, (c) Matthew Roughan, 2012
%         
% Compute the Laplace transform ratio for the Waxman problem
% via simulation of points, and then, compare to the one found
% through numerical integration of the exact density.
%
% Copyright 2012 Matthew Roughan <matthew.roughan@adelaide.edu.au>
%     This program is free software: you can redistribute it and/or modify
%     it under the terms of the GNU General Public License as published by
%     the Free Software Foundation, either version 3 of the License, or
%     (at your option) any later version.
% 
%     This program is distributed in the hope that it will be useful,
%     but WITHOUT ANY WARRANTY; without even the implied warranty of
%     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
%     GNU General Public License for more details.
%
%     You should have received a copy of the GNU General Public License
%     along with this program.  If not, see <http://www.gnu.org/licenses/>.
% 
%
%
clear;
seeds = 30;
Ns=ceil(10.^[3:0.5:6.0]);
dt = 0.001;
t = -0.1:dt:2.1;
colors = [[1 0 0];
	  [1 0.5 0];
	  [1 1 0];
	  [0 1 0];
	  [0 1 1];
	  [0 0 1];
	  [0 0.5 0.5];
	  [0.5 0 0.5];
	 ];
device = '-depsc';
suffix = 'eps';
seed = 1;
set(0,'DefaultTextFontsize', 18); % not working
set(0,'DefaultAxesFontsize', 18); % not working
set(0,'DefaultLineLinewidth', 2);
plotdir = '../Plots';

% first do the density

% unit square density
[g_square] = LinePickingPDF(t, 0, 1);

figure(1)
hold off
plot(0,0)
hold on
legend_str(1,:) = sprintf('            ');

dt = 0.05;
d_bins = 0:dt:sqrt(2)+0.1;
for i=1:length(Ns)
  fprintf('N = %.0f\n', Ns(i));
  N = Ns(i);
  x1 = rand(N,1);
  x2 = rand(N,1);
  y1 = rand(N,1);
  y2 = rand(N,1);
  d = sqrt((x1-x2).^2 + (y1-y2).^2);
  [y] = hist(d, d_bins);
  y = y/(dt*sum(y));
  p1(i+1) = plot(d_bins, y,'color', colors(i,:), 'linewidth', 2);
  legend_str(i+1,:) = sprintf('N = %8.0f', N);
end
p1(1) = plot(t, g_square,'k--', 'linewidth', 2);

set(gca, 'xlim', [0 sqrt(2)]);
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
legend(p1, legend_str);
xlabel('t');
ylabel('g(t)');

% now compare ratio of Laplace transforms
t_min = 0;
t_max = 4;
Ss = [0:0.5:50];
figure(2)
hold off
plot(0,0)
hold on

 
tic
for i=1:length(Ss)
  s = Ss(i);
  g_square = @(t) exp(-s*t) .* LinePickingPDF(t, 0, 1);
  [q_square, errbnd] = quadgk(g_square, t_min, t_max);
  G_square(i) = q_square;

  g_square = @(t) t .* exp(-s*t) .* LinePickingPDF(t, 0, 1);
  [q_square, errbnd] = quadgk(g_square, t_min, t_max);
  Gd_square(i) = -q_square;
  
end
time_exact = toc;
y_exact = -Gd_square./G_square;
 
for k=1:seeds
  rand('state', k);
  for i=1:length(Ns)
    fprintf('N = %.0f\n', Ns(i));
    tic
    N = Ns(i);
    % x = rand(N,1);
    % y = rand(N,1);
    % [X,Y] = meshgrid(x,y);
    % D = sqrt((X-X').^2 + (Y-Y').^2);
    % d = reshape(D, N^2, 1);
    
    x1 = rand(N,1);
    x2 = rand(N,1);
    y1 = rand(N,1);
    y2 = rand(N,1);
    d = sqrt((x1-x2).^2 + (y1-y2).^2);
    
    for j=1:length(Ss)
      s = Ss(j);
      G_square_num(j) = sum( exp(-s*d ) )/N;
      Gd_square_num(j) = -sum( d.*exp(-s*d ) )/N;
    end
    time_numerical(k,i) = toc;
    y = -Gd_square_num./G_square_num;
    
    if (k==1 & mod(i,4)==1)
      p2(i+1) = plot(Ss, y, 'color', colors(i,:), 'linewidth', 2);
    end
    
    abs_error(k,i) = mean(abs(y - y_exact));
    rel_error(k,i) = mean(abs(y - y_exact)./y_exact);
  end
end

p2(1) = plot(Ss, y_exact,'k--', 'linewidth', 2);
set(gca, 'ylim', [0 0.8]);
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
legend(p2, legend_str);
xlabel('s');
ylabel('-G''(s)/G(s)');
print('-depsc', 'Plots/LinePicking_numerical_laplace_ratio.eps');


figure(3);
hold off
p3(1) = plot(Ns, mean(time_numerical)./time_exact, 'bo-', 'linewidth', 2);
hold on
% p3(2) = plot(Ns.^2, ones(size(Ns))*time_exact, 'r', 'linewidth', 2);
% set(gca, 'ylim', [0 0.8]);
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
% legend(p2, legend_str);
xlabel('number of simulated points');
ylabel('time relative to exact solution');
print('-depsc', 'Plots/LinePicking_numerical_time.eps');

figure(4);
hold off
p3(1) = loglog(Ns, mean(abs_error), 'bo-', 'linewidth', 2);
hold on
plot([Ns; Ns], [mean(abs_error)-1.96*std(abs_error)/sqrt(seeds); mean(abs_error)+1.96*std(abs_error)/sqrt(seeds)], 'b-', 'linewidth', 2);
% p3(2) = plot(Ns.^2, ones(size(Ns))*time_exact, 'r', 'linewidth', 2);
% set(gca, 'ylim', [0 0.8]);
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
% legend(p2, legend_str);
xlabel('number of simulated points');
ylabel('mean absolute error');
print('-depsc', 'Plots/LinePicking_numerical_error.eps');

figure(5);
hold off
p3(1) = loglog(Ns, 100*mean(rel_error), 'bo-', 'linewidth', 2);
hold on
plot([Ns; Ns], 100*[mean(rel_error)-1.96*std(rel_error)/sqrt(seeds); mean(rel_error)+1.96*std(rel_error)/sqrt(seeds)], 'b-', 'linewidth', 2);

P = polyfit(log10(Ns), log10(100*mean(rel_error)), 1);
% p3(2) = plot(Ns, 10^P(2) * 10.^(P(1)*log10(Ns)), 'r--', 'linewidth', 2);
p3(2) = plot(Ns, 10^P(2) * Ns.^P(1), 'r--', 'linewidth', 2);
set(gca, 'ylim', 10.^[-1 1]);
set(gca, 'ytick', 10.^[-1:1]);
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
legend(p3, 'measured error', sprintf('error ~ N^{%.1f}', P(1)));
xlabel('number of simulated points');
ylabel('mean relative error (%)');
print('-depsc', 'Plots/LinePicking_numerical_rel_error.eps');

 
%
% Generate nice plots for inclusion in the manscript.
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
clear;
path(path, '../');

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

% check that the geometries are what we think they should be 
LinePickingPrintAllProblems;


% compare ball-line picking in different dimensions:
%   see http://mathworld.wolfram.com/BallLinePicking.html
figure(5)
hold off
plot(0,0)
hold on
for n=1:8
  [g] = LinePickingPDF(t, 2, [n, 1]);
  p5(n) = plot(t,g,'color', colors(n,:));
  legend_str(n,:) = sprintf('n = %2d', n);
end
set(gca, 'xlim', [0 2.3]);
legend(p5, legend_str);
xlabel('t');
ylabel('g_n(t)');
filename = sprintf('%s/LinePicking_plot_nballs.%s', plotdir, suffix);
print(device, filename);
fprintf('Printed to %s\n', filename);

%
% do  plots comparing sphere, line, disk and square
%
%  scale so that all have same MAX(length)
[g_square] = LinePickingPDF(t, 0, 1/sqrt(2));
[g_disk] = LinePickingPDF(t, 1, 0.5);
[g_sphere] = LinePickingPDF(t, 2, [3,0.5]);
[g_rect] = LinePickingPDF(t, 3, [0.5,1]/sqrt(1.25));
[g_line] = LinePickingPDF(t, 4, 1);
[g_cube] = LinePickingPDF(t, 5, 1/sqrt(3));
figure(6)
hold off
plot(0,0)
hold on
p6(1) = plot(t, g_square,'color', colors(1,:));
p6(2) = plot(t, g_disk,'color', colors(2,:));
p6(3) = plot(t, g_sphere,'color', colors(4,:));
p6(4) = plot(t, g_rect,'color', colors(5,:));
p6(5) = plot(t, g_line,'color', colors(3,:));
p6(6) = plot(t, g_cube,'color', colors(6,:));
set(gca, 'xlim', [0 1]);
legend(p6, 'square', 'disk', 'sphere', 'rectangle(2:1)', 'line', 'cube');
xlabel('t');
ylabel('g(t)');
filename = sprintf('%s/LinePicking_plot_fix_max_len.%s', plotdir, suffix);
print(device, filename);
fprintf('Printed to %s\n', filename);


%  scale so that all have the same area
dt = 0.001;
t = -0.1:dt:3.1;
[g_square] = LinePickingPDF(t, 0, 1);
[g_disk] = LinePickingPDF(t, 1, 1/sqrt(pi));
[g_sphere] = LinePickingPDF(t, 2, [3,(3/(4*pi))^(1/3)]);
[g_rect] = LinePickingPDF(t, 3, [0.5,1]*2);
[g_line] = LinePickingPDF(t, 4, 1);
[g_cube] = LinePickingPDF(t, 5, 1);
figure(7)
hold off
plot(0,0)
hold on
p7(1) = plot(t, g_square,'color', colors(1,:));
p7(2) = plot(t, g_disk,'color', colors(2,:));
p7(3) = plot(t, g_sphere,'color', colors(4,:));
p7(4) = plot(t, g_rect,'color', colors(5,:));
p7(5) = plot(t, g_cube,'color', colors(6,:));
set(gca, 'xlim', [0 2.1]);
legend(p7, 'square', 'disk', 'sphere', 'rectangle(2:1)', 'cube');
xlabel('t');
ylabel('g(t)');
filename = sprintf('%s/LinePicking_plot_fix_area.%s', plotdir, suffix);
print(device, filename);
fprintf('Printed to %s\n', filename);



% 
% do  plot considering rectangles of various dimensions
%  fixing the max length
dt = 0.001;
t = -0.1:dt:3.1;
figure(8)
hold off
plot(0,0)
hold on
for n=1:8
  [g_rect] = LinePickingPDF(t, 3, [n,1]/sqrt(1+n^2));
  p8(n) = plot(t,g_rect,'color', colors(n,:));
  legend_str8(n,:) = sprintf('aspect ratio = 1:%d', n);
end
set(gca, 'xlim', [0 1]);
legend(p8, legend_str8);
xlabel('t');
ylabel('g_{a:b}(t)');
filename = sprintf('%s/LinePicking_plot_rect.%s', plotdir, suffix);
print(device, filename);
fprintf('Printed to %s\n', filename);

% also do a plot showing the different regions in the PDF
problem = 3;
dt = 0.001;
a = 1;
b = 1.2;
t = -0.1:dt:a+b+0.1;
k1 = find(t<=a);
k2 = find(t>a & t<=b);
k3 = find(t>b & t<=a+b);
t1 = t(k1);
t2 = t(k2);
t3 = t(k3);

figure(81)
hold off
plot(0,0)
hold on
[g] = LinePickingPDF(t, problem, [a b]);
fill([t1, fliplr(t1)], [g(k1),zeros(size(k1))], [0.9,1,1]);
fill([t2, fliplr(t2)], [g(k2),zeros(size(k2))], [1,0.9,1]);
fill([t3, fliplr(t3)], [g(k3),zeros(size(k3))], [1,1,0.9]);
plot(t,g,'b-');
set(gca, 'xlim', [-0.1 a+b+0.1]);
xlabel('t');
ylabel(sprintf('g_{%.1f:%.1f}(t)',a,b));
filename = sprintf('%s/LinePicking_plot_rect_regions.%s', plotdir, suffix);
print(device, filename);
fprintf('Printed to %s\n', filename);


% 
% do plot considering rectangles (with Manhattan distances) of various dimensions
%  fixing the max length
problem = 9;
dt = 0.001;
t = -0.1:dt:3.1;
figure(9)
hold off
plot(0,0)
hold on
for n=1:8
  [g_rect_man] = LinePickingPDF(t, problem, [n,1]/(1+n));
  p9(n) = plot(t,g_rect_man,'color', colors(n,:));
  legend_str9(n,:) = sprintf('aspect ratio = 1:%d', n);
end
set(gca, 'xlim', [0 1]);
legend(p9, legend_str9);
xlabel('t');
ylabel('g_{a:b}(t)');
filename = sprintf('%s/LinePicking_plot_rect_man.%s', plotdir, suffix);
print(device, filename);
fprintf('Printed to %s\n', filename);

% also do a plot showing the different regions in the PDF
problem = 9;
dt = 0.001;
a = 1;
b = 2.5;
t = -0.1:dt:a+b+0.1;
k1 = find(t<=a);
k2 = find(t>a & t<=b);
k3 = find(t>b & t<=a+b);
t1 = t(k1);
t2 = t(k2);
t3 = t(k3);

figure(91)
hold off
plot(0,0)
hold on
[g] = LinePickingPDF(t, problem, [a b]);
fill([t1, fliplr(t1)], [g(k1),zeros(size(k1))], [0.9,1,1]);
fill([t2, fliplr(t2)], [g(k2),zeros(size(k2))], [1,0.9,1]);
fill([t3, fliplr(t3)], [g(k3),zeros(size(k3))], [1,1,0.9]);
plot(t,g,'b-');
set(gca, 'xlim', [-0.1 a+b+0.1]);
xlabel('t');
ylabel(sprintf('g_{%.1f:%.1f}(t)',a,b));
filename = sprintf('%s/LinePicking_plot_rect_man_regions.%s', plotdir, suffix);
print(device, filename);
fprintf('Printed to %s\n', filename);

% 
% do  plot considering rectangles (with Max distances) of various dimensions
%  fixing the max length
problem = 10;
dt = 0.001;
t = -0.1:dt:3.1;
figure(10)
hold off
plot(0,0)
hold on
for n=1:8
  [g_rect_max] = LinePickingPDF(t, problem, [n,1]/n);
  p9(n) = plot(t,g_rect_max,'color', colors(n,:));
  legend_str9(n,:) = sprintf('aspect ratio = 1:%d', n);
end
set(gca, 'xlim', [0 1]);
legend(p9, legend_str9);
xlabel('t');
ylabel('g_{a:b}(t)');
filename = sprintf('%s/LinePicking_plot_rect_max.%s', plotdir, suffix);
print(device, filename);
fprintf('Printed to %s\n', filename);

% also do a plot showing the different regions in the PDF
problem = 10;
dt = 0.001;
a = 1;
b = 2.5;
t = -0.1:dt:a+b+0.1;
k1 = find(t<=a);
k2 = find(t>a & t<=b);
k3 = find(t>b & t<=a+b);
t1 = t(k1);
t2 = t(k2);
t3 = t(k3);

figure(101)
hold off
plot(0,0)
hold on
[g] = LinePickingPDF(t, problem, [a b]);
fill([t1, fliplr(t1)], [g(k1),zeros(size(k1))], [0.9,1,1]);
fill([t2, fliplr(t2)], [g(k2),zeros(size(k2))], [1,0.9,1]);
fill([t3, fliplr(t3)], [g(k3),zeros(size(k3))], [1,1,0.9]);
plot(t,g,'b-');
set(gca, 'xlim', [-0.1 a+b+0.1]);
xlabel('t');
ylabel(sprintf('g_{%.1f:%.1f}(t)',a,b));
filename = sprintf('%s/LinePicking_plot_rect_max_regions.%s', plotdir, suffix);
print(device, filename);
fprintf('Printed to %s\n', filename);



% 
% do  plot for cube
problem = 5;
L = 1/sqrt(3);
dt = 0.001;
t = -0.1:dt:3.1;
k1 = find(t<=L);
k2 = find(t>L & t<=L*sqrt(2));
k3 = find(t>L*sqrt(2)& t<=L*sqrt(3));
t1 = t(k1);
t2 = t(k2);
t3 = t(k3);
figure(11)
hold off
plot(0,0)
hold on
[g_cube] = LinePickingPDF(t, problem, L);
fill([t1, fliplr(t1)], [g_cube(k1),zeros(size(k1))], [0.9,1,1]);
fill([t2, fliplr(t2)], [g_cube(k2),zeros(size(k2))], [1,0.9,1]);
fill([t3, fliplr(t3)], [g_cube(k3),zeros(size(k3))], [1,1,0.9]);
plot(t,g_cube,'color', colors(n,:));
set(gca, 'xlim', [0 1]);
legend(p9, legend_str9);
xlabel('t');
ylabel('g^{\rm cube}(t)');
filename = sprintf('%s/LinePicking_plot_cube_regions.%s', plotdir, suffix);
print(device, filename);
fprintf('Printed to %s\n', filename);

% 
% do  plots for line
problem = 4;
L = 1;
dt = 0.001;
t = -0.1:dt:3.1;
k1 = find(t<=L);
k2 = find(t>L & t<=L*sqrt(2));
k3 = find(t>L*sqrt(2)& t<=L*sqrt(3));
t1 = t(k1);
t2 = t(k2);
t3 = t(k3);
figure(12)
hold off
plot(0,0)
hold on
[g_line] = LinePickingPDF(t, problem, L);
plot(t,g_line,'color', 'b');
set(gca, 'xlim', [0 1]);
xlabel('t');
ylabel('g^{\rm line}(t)');
filename = sprintf('%s/LinePicking_plot_line_pdf.%s', plotdir, suffix);
print(device, filename);
fprintf('Printed to %s\n', filename);

figure(13)
hold off
plot(0,0)
hold on
[G_line] = LinePickingCDF(t, problem, L);
plot(t,G_line,'color', 'b');
set(gca, 'xlim', [0 1]);
xlabel('t');
ylabel('G^{\rm line}(t)');
filename = sprintf('%s/LinePicking_plot_line_cdf.%s', plotdir, suffix);
print(device, filename);
fprintf('Printed to %s\n', filename);

% 
% do  plots for square
problem = 0;
L = 1;
dt = 0.001;
t = -0.1:dt:3.1;
k1 = find(t<=L);
k2 = find(t>L & t<=L*sqrt(2));
t1 = t(k1);
t2 = t(k2);
figure(14)
hold off
plot(0,0)
hold on
[g_square] = LinePickingPDF(t, problem, L);
fill([t1, fliplr(t1)], [g_square(k1),zeros(size(k1))], [0.9,1,1]);
fill([t2, fliplr(t2)], [g_square(k2),zeros(size(k2))], [1,0.9,1]);
plot(t,g_square,'color', 'b');
set(gca, 'xlim', [0 sqrt(2)]);
xlabel('t');
ylabel('g^{\rm square}(t)');
filename = sprintf('%s/LinePicking_plot_square_pdf.%s', plotdir, suffix);
print(device, filename);
fprintf('Printed to %s\n', filename);

figure(15)
hold off
plot(0,0)
hold on
[G_square] = LinePickingCDF(t, problem, L);
fill([t1, fliplr(t1)], [G_square(k1),zeros(size(k1))], [0.9,1,1]);
fill([t2, fliplr(t2)], [G_square(k2),zeros(size(k2))], [1,0.9,1]);
plot(t,G_square,'color', 'b');
set(gca, 'xlim', [0 sqrt(2)]);
xlabel('t');
ylabel('G^{\rm square}(t)');
filename = sprintf('%s/LinePicking_plot_square_cdf.%s', plotdir, suffix);
print(device, filename);
fprintf('Printed to %s\n', filename);

% compare sphere-line picking in different dimensions:
%   
figure(16)
hold off
plot(0,0)
hold on
for n=1:8
  [g] = LinePickingPDF(t, 11, [n, 1]);
  p16(n) = plot(t,g,'color', colors(n,:));
  legend_str(n,:) = sprintf('n = %2d', n);
end
set(gca, 'xlim', [0 2.3]);
set(gca, 'ylim', [0 3]);
legend(p16, legend_str,'location','NorthWest');
xlabel('t');
ylabel('g_n(t)');
filename = sprintf('%s/LinePicking_plot_nspheres.%s', plotdir, suffix);
print(device, filename);
fprintf('Printed to %s\n', filename);

% compare sphere-geodesic-line picking in different dimensions:
%   
figure(17)
hold off
plot(0,0)
hold on
for n=1:8
  [g] = LinePickingPDF(t, 12, [n, 1]);
  p17(n) = plot(t,g,'color', colors(n,:));
  legend_str(n,:) = sprintf('n = %2d', n);
end
set(gca, 'xlim', [0 pi]);
set(gca, 'ylim', [0 1.5]);
legend(p17, legend_str,'location','NorthWest');
xlabel('t');
ylabel('g_n(t)');
filename = sprintf('%s/LinePicking_plot_nspheres_geodesic.%s', plotdir, suffix);
print(device, filename);
fprintf('Printed to %s\n', filename);


%
% Test results, and generate nice plots
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
dt = 0.001;
t = -0.1:dt:2.1;


% compare ball-line picking in 1D, with line-line picking
[g1] = LinePickingPDF(t, 2, [1, 1]);
[g2] = LinePickingPDF(t, 4, 2);
figure(1)
hold off
p1 = plot(t, g1, 'linewidth', 2);
hold on
p2 = plot(t, g2, 'r--', 'linewidth', 2);
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
legend([p1 p2], '1D ball-line picking', 'line-line picking');
xlabel('t');
ylabel('g(t)');

% compare ball-line picking in 2D, with disk-line picking
[g1] = LinePickingPDF(t, 1, 1);
[g2] = LinePickingPDF(t, 2, [2, 1]);
figure(2)
hold off
p1 = plot(t, g1, 'linewidth', 2);
hold on
p2 = plot(t, g2, 'r--', 'linewidth', 2);
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
legend([p1 p2], 'disk-line picking', '2D ball-line picking');
xlabel('t');
ylabel('g(t)');

% compare rectangle (with square parameters) with square
[g1] = LinePickingPDF(t, 0, 1);
[g2] = LinePickingPDF(t, 3, [1, 1]);
figure(3)
hold off
p1 = plot(t, g1, 'linewidth', 2);
hold on
p2 = plot(t, g2, 'r--', 'linewidth', 2);
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
legend([p1 p2], 'square-line picking', '(square) rectangle-line picking');
xlabel('t');
ylabel('g(t)');

% compare long, thin rectangle with line
[g1] = LinePickingPDF(t, 4, 1);
[g2] = LinePickingPDF(t, 3, [0.00001, 1]);
figure(4)
hold off
p1 = plot(t, g1, 'linewidth', 2);
hold on
p2 = plot(t, g2, 'r--', 'linewidth', 2);
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
legend([p1 p2], 'line-line picking', '(long thin) rectangle-line picking');
xlabel('t');
ylabel('g(t)');

 

% compare ball-line picking in different dimensions:
%   see http://mathworld.wolfram.com/BallLinePicking.html
colors = [[1 0 0];
	  [1 0.5 0];
	  [1 1 0];
	  [0 1 0];
	  [0 1 1];
	  [0 0 1];
	  [0 0.5 0.5];
	  [0.5 0 0.5];
	 ];
figure(5)
hold off
plot(0,0)
hold on
for n=1:8
  [g] = LinePickingPDF(t, 2, [n, 1]);
  p5(n) = plot(t,g,'color', colors(n,:), 'linewidth', 2);
  legend_str(n,:) = sprintf('n = %2d', n);
end
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
set(gca, 'xlim', [0 2.3]);
legend(p5, legend_str);
xlabel('t');
ylabel('g_n(t)');
print('-depsc', 'Plots/LinePicking_test_balls.eps');


%
% do nice plots comparing sphere, line, disk and square
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
p6(1) = plot(t, g_square,'color', colors(1,:), 'linewidth', 2);
p6(2) = plot(t, g_disk,'color', colors(2,:), 'linewidth', 2);
p6(3) = plot(t, g_sphere,'color', colors(4,:), 'linewidth', 2);
p6(4) = plot(t, g_rect,'color', colors(5,:), 'linewidth', 2);
p6(5) = plot(t, g_line,'color', colors(3,:), 'linewidth', 2);
p6(6) = plot(t, g_cube,'color', colors(6,:), 'linewidth', 2);
set(gca, 'xlim', [0 1]);
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
legend(p6, 'square', 'disk', 'sphere', 'rectangle(2:1)', 'line', 'cube');
xlabel('t');
ylabel('g(t)');
print('-depsc', 'Plots/LinePicking_test_fix_max_len.eps');



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
p7(1) = plot(t, g_square,'color', colors(1,:), 'linewidth', 2);
p7(2) = plot(t, g_disk,'color', colors(2,:), 'linewidth', 2);
p7(3) = plot(t, g_sphere,'color', colors(4,:), 'linewidth', 2);
p7(4) = plot(t, g_rect,'color', colors(5,:), 'linewidth', 2);
p7(5) = plot(t, g_cube,'color', colors(6,:), 'linewidth', 2);
set(gca, 'xlim', [0 2.1]);
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
legend(p7, 'square', 'disk', 'sphere', 'rectangle(2:1)', 'cube');
xlabel('t');
ylabel('g(t)');
print('-depsc', 'Plots/LinePicking_test_fix_area.eps');




% 
% do nice plot considering rectangles of various dimensions
%  fixing the max length
dt = 0.001;
t = -0.1:dt:3.1;
figure(8)
hold off
plot(0,0)
hold on
for n=1:8
  [g_rect] = LinePickingPDF(t, 3, [n,1]/sqrt(1+n^2));
  p8(n) = plot(t,g_rect,'color', colors(n,:), 'linewidth', 2);
  legend_str8(n,:) = sprintf('aspect ratio = 1:%d', n);
end
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
set(gca, 'xlim', [0 1]);
legend(p8, legend_str8);
xlabel('t');
ylabel('g_{a/b}(t)');
print('-depsc', 'Plots/LinePicking_test_rect.eps');


% 
% do nice plot considering rectangles (with Manhattan distances) of various dimensions
%  fixing the max length
problem = 9;
dt = 0.001;
t = -0.1:dt:3.1;
figure(9)
hold off
plot(0,0)
hold on
for n=1:8
  [g_rect_man] = LinePickingPDF(t, problem, [1,n]/(1+n));
%  [g_rect_man] = LinePickingPDF(t, problem, [n,1]/sqrt(1+n^2));
  p9(n) = plot(t,g_rect_man,'color', colors(n,:), 'linewidth', 2);
  legend_str9(n,:) = sprintf('aspect ratio = 1:%d', n);
end
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
set(gca, 'xlim', [0 1]);
legend(p9, legend_str9);
xlabel('t');
ylabel('g_{a/b}(t)');
print('-depsc', 'Plots/LinePicking_test_rect_man.eps');

% also do a plot showing the different regions in the PDF


% test scaling with size for each type of distribution, 
%   by considering whether distribution sums to 1
dt = 0.001;
t = -0.1:dt:10.1;

[g1] = LinePickingPDF(t, 0, 1);
[g5] = LinePickingPDF(t, 0, 5);
sum_square_1 = (sum(g1) -(g1(1)+g1(end))/2 )*dt
sum_square_5 = (sum(g5) -(g5(1)+g5(end))/2 )*dt

[g1] = LinePickingPDF(t, 1, 1);
[g5] = LinePickingPDF(t, 1, 5);
sum_disk_1 = (sum(g1) -(g1(1)+g1(end))/2 )*dt
sum_disk_5 = (sum(g5) -(g5(1)+g5(end))/2 )*dt

[g1] = LinePickingPDF(t, 2, [3,1]);
[g5] = LinePickingPDF(t, 2, [3,5]);
sum__1 = sum(g1*dt)
sum_ball3_1 = (sum(g1) -(g1(1)+g1(end))/2 )*dt
sum_ball3_5 = (sum(g5) -(g5(1)+g5(end))/2 )*dt

[g1] = LinePickingPDF(t, 3, [0.5,1]);
[g5] = LinePickingPDF(t, 3, [2.5,5]);
sum_rect_1 = (sum(g1) -(g1(1)+g1(end))/2 )*dt
sum_rect_5 = (sum(g5) -(g5(1)+g5(end))/2 )*dt

[g1] = LinePickingPDF(t, 4, 1);
[g5] = LinePickingPDF(t, 4, 5);
sum_line_1 = (sum(g1) -(g1(1)+g1(end))/2 )*dt
sum_line_5 = (sum(g5) -(g5(1)+g5(end))/2 )*dt

[g1] = LinePickingPDF(t, 5, 1);
[g5] = LinePickingPDF(t, 5, 5);
sum_cube_1 = (sum(g1) -(g1(1)+g1(end))/2 )*dt
sum_cube_5 = (sum(g5) -(g5(1)+g5(end))/2 )*dt

[g1] = LinePickingPDF(t, 9, [0.5,1]);
[g5] = LinePickingPDF(t, 9, [2.5,5]);
sum_rect_man_1 = (sum(g1) -(g1(1)+g1(end))/2 )*dt
sum_rect_man_5 = (sum(g5) -(g5(1)+g5(end))/2 )*dt



% tests of common error conditions
%



% 
% compute Laplace transform and derivative of Laplace transform of the distributions
%

t_min = 0;
t_max = 4;
tolerance = 1.0e-9;
trace = 0;
Ss = [0:0.2:100];
% radius = 1/sqrt(pi) for disk with area 1
R = 1/sqrt(pi);
for i=1:length(Ss)
  s = Ss(i);
  g_square = @(t) exp(-s*t) .* LinePickingPDF(t, 0, 1);
  g_disk = @(t) exp(-s*t) .* LinePickingPDF(t, 1, R);
  g_sphere = @(t) exp(-s*t) .* LinePickingPDF(t, 2, [3,(3/(4*pi))^(1/3)]);
  g_rect = @(t) exp(-s*t) .* LinePickingPDF(t, 3, [0.5,1]*2);
  g_line = @(t) exp(-s*t) .* LinePickingPDF(t, 4, 1);
  g_cube = @(t) exp(-s*t) .* LinePickingPDF(t, 5, 1);
  [q_square, errbnd] = quadgk(g_square, t_min, t_max);
  [q_disk, errbnd] = quadgk(g_disk, t_min, t_max);
  [q_sphere, errbnd] = quadgk(g_sphere, t_min, t_max);
  [q_rect, errbnd] = quadgk(g_rect, t_min, t_max);
  [q_line, errbnd] = quadgk(g_line, t_min, t_max);
  [q_cube, errbnd] = quadgk(g_cube, t_min, t_max);
  [q_cube2, fn_count] = quad(g_cube, t_min, t_max, tolerance, trace);
  G_square(i) = q_square;
  G_disk(i) = q_disk;
  G_sphere(i) = q_sphere;
  G_rect(i) = q_rect;
  G_line(i) = q_line;
  G_cube(i) = q_cube;
  G_cube2(i) = q_cube2;
end
figure(20)
hold off
plot(0,0) 
hold on
p20(1) = plot(Ss, G_square,'color', colors(1,:), 'linewidth', 2);
p20(2) = plot(Ss, G_disk,'color', colors(2,:), 'linewidth', 2);
p20(3) = plot(Ss, G_sphere,'color', colors(4,:), 'linewidth', 2);
p20(4) = plot(Ss, G_rect,'color', colors(5,:), 'linewidth', 2);
p20(5) = plot(Ss, G_cube,'color', colors(6,:), 'linewidth', 2);
set(gca, 'xlim', [0 5]);
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
legend(p20, 'square', 'disk', 'sphere', 'rectangle(2:1)', 'cube');
xlabel('s');
ylabel('G(s)');
print('-depsc', 'Plots/LinePicking_test_laplace_tranforms.eps');

for i=1:length(Ss)
  s = Ss(i);
  g_square = @(t) t .* exp(-s*t) .* LinePickingPDF(t, 0, 1);
  g_disk = @(t) t .* exp(-s*t) .* LinePickingPDF(t, 1, R);
  g_sphere = @(t) t .* exp(-s*t) .* LinePickingPDF(t, 2, [3,(3/(4*pi))^(1/3)]);
  g_rect = @(t) t .* exp(-s*t) .* LinePickingPDF(t, 3, [0.5,1]*2);
  g_line = @(t) t .* exp(-s*t) .* LinePickingPDF(t, 4, 1);
  g_cube = @(t) t .* exp(-s*t) .* LinePickingPDF(t, 5, 1);
  [q_square, errbnd] = quadgk(g_square, t_min, t_max);
  [q_disk, errbnd] = quadgk(g_disk, t_min, t_max);
  [q_sphere, errbnd] = quadgk(g_sphere, t_min, t_max);
  [q_rect, errbnd] = quadgk(g_rect, t_min, t_max);
  [q_line, errbnd] = quadgk(g_line, t_min, t_max);
  [q_cube, errbnd] = quadgk(g_cube, t_min, t_max);
  [q_cube2, fn_count] = quad(g_cube, t_min, t_max, tolerance, trace);
  Gd_square(i) = -q_square;
  Gd_disk(i) = -q_disk;
  Gd_sphere(i) = -q_sphere;
  Gd_rect(i) = -q_rect;
  Gd_line(i) = -q_line;
  Gd_cube(i) = -q_cube;
  Gd_cube2(i) = -q_cube2;
end
 
figure(21)
hold off
plot(0,0)
hold on
p21(1) = plot(Ss, -Gd_square./G_square,'color', colors(1,:), 'linewidth', 2);
p21(2) = plot(Ss, -Gd_disk./G_disk,'color', colors(2,:), 'linewidth', 2);
p21(3) = plot(Ss, -Gd_sphere./G_sphere,'color', colors(4,:), 'linewidth', 2);
p21(4) = plot(Ss, -Gd_rect./G_rect,'color', colors(5,:), 'linewidth', 2);
p21(5) = plot(Ss, -Gd_cube./G_cube,'color', colors(6,:), 'linewidth', 2);
p21(6) = plot(Ss, 2./Ss, 'k-.', 'linewidth', 2);
p21(7) = plot(Ss, 3./Ss, 'k:', 'linewidth', 3);
set(gca, 'ylim', [0 0.8]);
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
legend(p21, 'square', 'disk', 'sphere', 'rectangle(2:1)', 'cube', '2/s', '3/s');
xlabel('s');
ylabel('-G''(s)/G(s)');
print('-depsc', 'Plots/LinePicking_test_laplace_ratio.eps');
 
figure(22)
hold off
plot(0,0)
hold on
p22(1) = plot(Ss, -Gd_cube./G_cube,'color', colors(6,:), 'linewidth', 2);
p22(2) = plot(Ss, -Gd_cube2./G_cube2,'y--', 'linewidth', 2);
set(gca, 'ylim', [0 0.8]);
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
legend(p22, 'cube using "quadgk"', 'cube using "quad"');
xlabel('s');
ylabel('-G''(s)/G(s)');
print('-depsc', 'Plots/LinePicking_test_quad.eps');
 
figure(23)
hold off
plot(0,0)
hold on
p23(1) = plot(Ss, -Gd_disk./G_disk, 'b-', 'linewidth', 2);
p23(2) = plot(Ss,  2./Ss,'r--', 'linewidth', 2);
p23(3) = plot(Ss,  2./Ss - 4./(pi*R*Ss.^2),'m--', 'linewidth', 2);
set(gca, 'ylim', [0 0.8]);
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
legend(p23, '-G''(s)/G(s)', '2/s', '2/s - 4/(\pi R s^2)');
xlabel('s');
ylabel('-G''(s)/G(s) approximation');
 

figure(24)
hold off
semilogy(0,1)
hold on
p24(1) = plot(Ss, + Gd_disk./G_disk + 2./Ss , 'b-', 'linewidth', 2);
p24(2) = plot(Ss, 4./(pi*R*Ss.^2) ,'r--', 'linewidth', 2);
%p23(3) = plot(Ss, 3*(8/(pi*R^3))./((2/R^2) - 8./(pi*R^3*Ss) )./Ss.^2,'g--', 'linewidth', 2);
%p23(4) = plot(Ss, 12*R./(pi*Ss.^2) ,'m--', 'linewidth', 2);
set(gca, 'ylim', [0 0.8]);
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
legend(p24, 'error', 'error approximation');
xlabel('s');
ylabel('-G''(s)/G(s) approximation error');
print('-depsc', 'Plots/LinePicking_approx_error.eps');

figure(25)
hold off
semilogy(0,1)
hold on
p25(1) = plot(Ss, (Gd_disk./G_disk + 2./Ss) ./ (-Gd_disk./G_disk) , 'b-', 'linewidth', 2);
p25(2) = plot(Ss, 2./(pi*R*Ss),'r--', 'linewidth', 2);
set(gca, 'ylim', [0 0.8]);
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
legend(p25, 'error', 'error approximation');
xlabel('s');
ylabel('-G''(s)/G(s) absolute relative approximation error');
print('-depsc', 'Plots/LinePicking_approx_rel_error.eps');


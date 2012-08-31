%
% 
% compute Laplace transform and derivative of Laplace transform of the distributions
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
colors = [[1 0 0];
	  [1 0.5 0];
	  [1 1 0];
	  [0 1 0];
	  [0 1 1];
	  [0 0 1];
	  [0 0.5 0.5];
	  [0.5 0 0.5];
	 ];



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


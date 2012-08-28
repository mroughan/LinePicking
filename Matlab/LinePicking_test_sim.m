%
% Test each geometry against a simulation
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
N = 30;
M = 10^6;
rand('state', 1);
randn('state', 1);

% check that the geometries are what we think they should be 
LinePickingAllModes;


%
% square picking
%
geometry = 0;
L = 1;
parameters = [L];
s = LinePickingSupport(geometry, parameters);
ds = diff(s)/N;
t = s(1):ds:s(2);
g = LinePickingPDF(t, geometry, parameters);
m = LinePickingMean(geometry, parameters);
v = LinePickingVar(geometry, parameters);

x1 = L*rand(M,1);
y1 = L*rand(M,1);
x2 = L*rand(M,1);
y2 = L*rand(M,1);
d = sqrt( (x1-x2).^2 + (y1-y2).^2);
n = histc(d, t);
prob = (n/M) / ds;

figure(geometry+1)
hold off
p1 = plot(0,0);
hold on
p1 = plot(t, g, 'r--', 'linewidth', 2);
p2 = plot(t+ds/2, prob, 'bo', 'linewidth', 2);
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
legend([p1 p2], 'exact', 'simulated');
xlabel('t');
ylabel('g(t)');
title('square-line picking density');
print('-deps','Plots/LinePicking_test_sim_square.eps');

figure(geometry+101)
hold off
plot([0 L L 0 0], [0 0 L L 0], 'k-', 'linewidth', 2);
hold on
m = 1:10;
plot([x1(m)'; x2(m)'], [y1(m)'; y2(m)'], 'bo-', 'linewidth', 2);
set(gca, 'xlim', [-0.1, L+0.1]);
set(gca, 'ylim', [-0.1, L+0.1]);
axis equal
axis off
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
title('square-line picking example');
print('-deps','Plots/LinePicking_test_sim_square_eg.eps');

%
% disk picking
%
geometry = 1;
R = 1;
parameters = [R];
s = LinePickingSupport(geometry, parameters);
ds = diff(s)/N;
t = s(1):ds:s(2);
g = LinePickingPDF(t, geometry, parameters);
m = LinePickingMean(geometry, parameters);
v = LinePickingVar(geometry, parameters);

x1 = 2*R*rand(M,1)-R;
y1 = 2*R*rand(M,1)-R;
x2 = 2*R*rand(M,1)-R;
y2 = 2*R*rand(M,1)-R;
k = find((x1.^2+y1.^2)<=R^2 & (x2.^2+y2.^2)<=R^2); 
d = sqrt( (x1(k)-x2(k)).^2 + (y1(k)-y2(k)).^2);
n = histc(d, t);
prob = (n/length(k)) / ds;

figure(geometry+1)
hold off
p1 = plot(0,0);
hold on
p1 = plot(t, g, 'r--', 'linewidth', 2);
p2 = plot(t+ds/2, prob, 'bo', 'linewidth', 2);
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
legend([p1 p2], 'exact', 'simulated');
xlabel('t');
ylabel('g(t)');
title('disk-line picking density');
print('-deps','Plots/LinePicking_test_sim_disk.eps');

figure(geometry+101)
hold off
theta = 0:pi/40:2*pi;
x_theta = R*cos(theta);
y_theta = R*sin(theta);
plot(x_theta, y_theta, 'k-', 'linewidth', 2);
hold on
m = 1:10;
plot([x1(k(m))'; x2(k(m))'], [y1(k(m))'; y2(k(m))'], 'bo-', 'linewidth', 2);
set(gca, 'xlim', [-R-0.1, R+0.1]);
set(gca, 'ylim', [-R-0.1, R+0.1]);
axis equal
axis off
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
title('disk-line picking example');
print('-deps','Plots/LinePicking_test_sim_disk_eg.eps');


%
% 3ball picking (to test hyperball)
%
geometry = 2;
R = 1;
parameters = [3, R];
s = LinePickingSupport(geometry, parameters);
ds = diff(s)/N;
t = s(1):ds:s(2);
g = LinePickingPDF(t, geometry, parameters);
m = LinePickingMean(geometry, parameters);
v = LinePickingVar(geometry, parameters);

x1 = 2*R*rand(M,1)-R;
y1 = 2*R*rand(M,1)-R;
z1 = 2*R*rand(M,1)-R;
x2 = 2*R*rand(M,1)-R;
y2 = 2*R*rand(M,1)-R;
z2 = 2*R*rand(M,1)-R;
k = find((x1.^2+y1.^2+z1.^2)<=R^2 & (x2.^2+y2.^2+z2.^2)<=R^2); 
d = sqrt( (x1(k)-x2(k)).^2 + (y1(k)-y2(k)).^2 + (z1(k)-z2(k)).^2);
n = histc(d, t);
prob = (n/length(k)) / ds;

figure(geometry+1)
hold off
p1 = plot(0,0);
hold on
p1 = plot(t, g, 'r--', 'linewidth', 2);
p2 = plot(t+ds/2, prob, 'bo', 'linewidth', 2);
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
legend([p1 p2], 'exact', 'simulated');
xlabel('t');
ylabel('g(t)');
title('3D ball-line picking density');
print('-deps','Plots/LinePicking_test_sim_3ball.eps');

figure(geometry+101)
hold off
theta = 0:pi/40:2*pi;
x_theta = R*cos(theta);
y_theta = R*sin(theta);
plot3(0,0,0);
hold on
plot3(x_theta, y_theta, zeros(size(theta)), 'k-', 'linewidth', 2);
plot3(x_theta, zeros(size(theta)), y_theta, 'k-', 'linewidth', 2);
plot3(zeros(size(theta)), x_theta, y_theta, 'k-', 'linewidth', 2);
m = 1:10;
plot3([x1(k(m))'; x2(k(m))'], [y1(k(m))'; y2(k(m))'], [z1(k(m))'; z2(k(m))'], 'bo-', 'linewidth', 2);
set(gca, 'xlim', [-R-0.1, R+0.1]);
set(gca, 'ylim', [-R-0.1, R+0.1]);
set(gca, 'zlim', [-R-0.1, R+0.1]);
axis equal
az = -120; el = 20;
view([az, el]);
% axis off
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
title('3D ball-line picking example');
print('-deps','Plots/LinePicking_test_sim_3ball_eg.eps');



%
% 4ball picking (to test hyperball)
%
geometry = 2;
R = 1;
parameters = [4, R];
s = LinePickingSupport(geometry, parameters);
ds = diff(s)/N;
t = s(1):ds:s(2);
g = LinePickingPDF(t, geometry, parameters);
m = LinePickingMean(geometry, parameters);
v = LinePickingVar(geometry, parameters);

x1 = 2*R*rand(M,1)-R;
y1 = 2*R*rand(M,1)-R;
z1 = 2*R*rand(M,1)-R;
w1 = 2*R*rand(M,1)-R;
x2 = 2*R*rand(M,1)-R;
y2 = 2*R*rand(M,1)-R;
z2 = 2*R*rand(M,1)-R;
w2 = 2*R*rand(M,1)-R;
k = find((x1.^2+y1.^2+z1.^2+w1.^2)<=R^2 & (x2.^2+y2.^2+z2.^2+w2.^2)<=R^2); 
d = sqrt( (x1(k)-x2(k)).^2 + (y1(k)-y2(k)).^2 + (z1(k)-z2(k)).^2 + (w1(k)-w2(k)).^2);
n = histc(d, t);
prob = (n/length(k)) / ds;

figure(geometry+21)
hold off
p1 = plot(0,0);
hold on
p1 = plot(t, g, 'r--', 'linewidth', 2);
p2 = plot(t+ds/2, prob, 'bo', 'linewidth', 2);
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
legend([p1 p2], 'exact', 'simulated');
xlabel('t');
ylabel('g(t)');
title('4D ball-line picking density');
print('-deps','Plots/LinePicking_test_sim_4ball.eps');


%
% rect picking
%
geometry = 3;
a = 1;
b = 2;
parameters = [a, b];
s = LinePickingSupport(geometry, parameters);
ds = diff(s)/N;
t = s(1):ds:s(2);
g = LinePickingPDF(t, geometry, parameters);
m = LinePickingMean(geometry, parameters);
v = LinePickingVar(geometry, parameters);

x1 = b*rand(M,1);
y1 = a*rand(M,1);
x2 = b*rand(M,1);
y2 = a*rand(M,1);
d = sqrt( (x1-x2).^2 + (y1-y2).^2);
n = histc(d, t);
prob = (n/M) / ds;

figure(geometry+1)
hold off
p1 = plot(0,0);
hold on
p1 = plot(t, g, 'r--', 'linewidth', 2);
p2 = plot(t+ds/2, prob, 'bo', 'linewidth', 2);
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
legend([p1 p2], 'exact', 'simulated');
xlabel('t');
ylabel('g(t)');
title('rect(2:1)-line picking density');
print('-deps','Plots/LinePicking_test_sim_rect.eps');

figure(geometry+101)
hold off
plot([0 b b 0 0], [0 0 a a 0], 'k-', 'linewidth', 2);
hold on
m = 1:10;
plot([x1(m)'; x2(m)'], [y1(m)'; y2(m)'], 'bo-', 'linewidth', 2);
set(gca, 'xlim', [-0.1, b+0.1]);
set(gca, 'ylim', [-0.1, a+0.1]);
axis equal
axis off
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
title('rect(2:1)-line picking example');
print('-deps','Plots/LinePicking_test_sim_rect_eg.eps');

%
% line-line picking
%
geometry = 4;
L = 1;
parameters = [L];
s = LinePickingSupport(geometry, parameters);
ds = diff(s)/N;
t = s(1):ds:s(2);
g = LinePickingPDF(t, geometry, parameters);
m = LinePickingMean(geometry, parameters);
v = LinePickingVar(geometry, parameters);

x1 = L*rand(M,1);
x2 = L*rand(M,1);
d = abs( (x1-x2) );
n = histc(d, t);
prob = (n/M) / ds;

figure(geometry+1)
hold off
p1 = plot(0,0);
hold on
p1 = plot(t, g, 'r--', 'linewidth', 2);
p2 = plot(t+ds/2, prob, 'bo', 'linewidth', 2);
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
legend([p1 p2], 'exact', 'simulated');
xlabel('t');
ylabel('g(t)');
title('line-line picking density');
print('-deps','Plots/LinePicking_test_sim_line.eps');


%
% cube picking
%
geometry = 5;
L = 1;
parameters = [L];
s = LinePickingSupport(geometry, parameters);
ds = diff(s)/N;
t = s(1):ds:s(2);
g = LinePickingPDF(t, geometry, parameters);
m = LinePickingMean(geometry, parameters);
v = LinePickingVar(geometry, parameters);

x1 = L*rand(M,1);
y1 = L*rand(M,1);
z1 = L*rand(M,1);
x2 = L*rand(M,1);
y2 = L*rand(M,1);
z2 = L*rand(M,1);
d = sqrt( (x1-x2).^2 + (y1-y2).^2 + (z1-z2).^2);
n = histc(d, t);
prob = (n/M) / ds;

figure(geometry+1)
hold off
p1 = plot(0,0);
hold on
p1 = plot(t, g, 'r--', 'linewidth', 2);
p2 = plot(t+ds/2, prob, 'bo', 'linewidth', 2);
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
legend([p1 p2], 'exact', 'simulated');
xlabel('t');
ylabel('g(t)');
title('cube-line picking density');
print('-deps','Plots/LinePicking_test_sim_cube.eps');

figure(geometry+101)
hold off
plot3(0,0,0);
hold on
plot3([0 L L 0 0], [0 0 L L 0], [0 0 0 0 0], 'k-', 'linewidth', 2);
plot3([0 L L 0 0], [0 0 L L 0], [L L L L L], 'k-', 'linewidth', 2);
plot3([0 L L 0 0], [0 0 0 0 0], [0 0 L L 0], 'k-', 'linewidth', 2);
plot3([0 L L 0 0], [L L L L L], [0 0 L L 0], 'k-', 'linewidth', 2);
m = 1:10;
plot3([x1(m)'; x2(m)'], [y1(m)'; y2(m)'], [z1(m)'; z2(m)'], 'bo-', 'linewidth', 2);
set(gca, 'xlim', [-0.1, L+0.1]);
set(gca, 'ylim', [-0.1, L+0.1]);
set(gca, 'zlim', [-0.1, L+0.1]);
axis equal
az = -50; el = 25;
view([az, el]);
% axis off
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
title('cube-line picking example');
print('-deps','Plots/LinePicking_test_sim_cube_eg.eps');


%
% sphere line picking
%
geometry = 6;
R = 1;
parameters = [R];
s = LinePickingSupport(geometry, parameters);
ds = diff(s)/N;
t = s(1):ds:s(2);
g = LinePickingPDF(t, geometry, parameters);
m = LinePickingMean(geometry, parameters);
v = LinePickingVar(geometry, parameters);

% random points on sphere
% http://mathworld.wolfram.com/SpherePointPicking.html
% http://en.wikipedia.org/wiki/N-sphere
v1 = R * randn(3,M);
r1 = v1./repmat(sqrt( sum( v1.^2 ) ), 3, 1);
x1 = r1(1,:)';
y1 = r1(2,:)';
z1 = r1(3,:)';
v2 = randn(3,M);
r2 = R * v2./repmat(sqrt( sum( v2.^2 ) ), 3, 1);
x2 = r2(1,:)';
y2 = r2(2,:)';
z2 = r2(3,:)';
d = sqrt( (x1-x2).^2 + (y1-y2).^2 + (z1-z2).^2);
n = histc(d, t);
prob = (n/M) / ds;

figure(geometry+1)
hold off
p1 = plot(0,0);
hold on
p1 = plot(t, g, 'r--', 'linewidth', 2);
p2 = plot(t+ds/2, prob, 'bo', 'linewidth', 2);
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
legend([p1 p2], 'exact', 'simulated');
xlabel('t');
ylabel('g(t)');
title('sphere-line picking density');
print('-deps','Plots/LinePicking_test_sim_geodesic.eps');

figure(geometry+101)
hold off
theta = 0:pi/40:2*pi;
x_theta = R*cos(theta);
y_theta = R*sin(theta);
plot3(0,0,0);
hold on
plot3(x_theta, y_theta, zeros(size(theta)), 'k-', 'linewidth', 2);
plot3(x_theta, zeros(size(theta)), y_theta, 'k-', 'linewidth', 2);
plot3(zeros(size(theta)), x_theta, y_theta, 'k-', 'linewidth', 2);
m = 1:10;
plot3([x1(m)'; x2(m)'], [y1(m)'; y2(m)'], [z1(m)'; z2(m)'], 'bo-', 'linewidth', 2);
set(gca, 'xlim', [-R-0.1, R+0.1]);
set(gca, 'ylim', [-R-0.1, R+0.1]);
set(gca, 'zlim', [-R-0.1, R+0.1]);
axis equal
az = -120; el = 20;
view([az, el]);
% axis off
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
title('sphere-line picking example');
print('-deps','Plots/LinePicking_test_sim_sphere_eg.eps');


%
% sphere geodesic picking
%
geometry = 7;
R = 1;
parameters = [R];
s = LinePickingSupport(geometry, parameters);
ds = diff(s)/N;
t = s(1):ds:s(2);
g = LinePickingPDF(t, geometry, parameters);
m = LinePickingMean(geometry, parameters);
v = LinePickingVar(geometry, parameters);

% random points on sphere
% http://mathworld.wolfram.com/SpherePointPicking.html
% http://en.wikipedia.org/wiki/N-sphere
u1 = rand(M,1);
v1 = rand(M,1);
theta1 = 2*pi*u1;
phi1 = acos(2*v1-1);
x1 = R*cos(phi1).*cos(theta1);
y1 = R*cos(phi1).*sin(theta1);
z1 = R*sin(phi1);
% implicitly assume one point is at the pole
%   to calculate the geodesic distance
d = R*phi1;

n = histc(d, t);
prob = (n/M) / ds;

figure(geometry+1)
hold off
p1 = plot(0,0);
hold on
p1 = plot(t, g, 'r--', 'linewidth', 2);
p2 = plot(t+ds/2, prob, 'bo', 'linewidth', 2);
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
legend([p1 p2], 'exact', 'simulated');
xlabel('t');
ylabel('g(t)');
title('sphere-geodesic-line picking density');
print('-deps','Plots/LinePicking_test_sim_sphere_geodesic.eps');

% figure(geometry+101)
% haven't implemented drawing this one yet
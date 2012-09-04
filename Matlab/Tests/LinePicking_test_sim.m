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
randn('state', 5);
device = '-depsc';
suffix = 'eps';

% probably should put error bars into the graphs ...


% check that the geometries are what we think they should be 
LinePickingAllProblems;

%
% square picking
%
problem = 0;
L = 1;
parameters = [L];
s = LinePickingSupport(problem, parameters);
ds = diff(s)/N;
t = s(1):ds:s(2);
g = LinePickingPDF(t, problem, parameters);
means(problem+1) = LinePickingMean(problem, parameters);
vars(problem+1) = LinePickingVar(problem, parameters);
name(problem+1) = {LinePickingProblemLookup(problem)};

x1 = L*rand(M,1);
y1 = L*rand(M,1);
x2 = L*rand(M,1);
y2 = L*rand(M,1);
d = sqrt( (x1-x2).^2 + (y1-y2).^2);
n = histc(d, t);
prob = (n/M) / ds;
est_means(problem+1) = mean(d);
est_var(problem+1) = var(d);

figure(problem+1)
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
filename = sprintf('Plots/LinePicking_test_sim_square.%s', suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('square-line picking density');

figure(problem+101)
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
filename = sprintf('Plots/LinePicking_test_sim_square_eg.%s', suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('square-line picking example');

%
% disk picking
%
problem = 1;
R = 1;
parameters = [R];
s = LinePickingSupport(problem, parameters);
ds = diff(s)/N;
t = s(1):ds:s(2);
g = LinePickingPDF(t, problem, parameters);
means(problem+1) = LinePickingMean(problem, parameters);
vars(problem+1) = LinePickingVar(problem, parameters);
name(problem+1) = {LinePickingProblemLookup(problem)};

x1 = 2*R*rand(M,1)-R;
y1 = 2*R*rand(M,1)-R;
x2 = 2*R*rand(M,1)-R;
y2 = 2*R*rand(M,1)-R;
k = find((x1.^2+y1.^2)<=R^2 & (x2.^2+y2.^2)<=R^2); 
d = sqrt( (x1(k)-x2(k)).^2 + (y1(k)-y2(k)).^2);
n = histc(d, t);
prob = (n/length(k)) / ds;
est_means(problem+1) = mean(d);
est_var(problem+1) = var(d);

figure(problem+1)
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
filename = sprintf('Plots/LinePicking_test_sim_disk.%s', suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('disk-line picking density');

figure(problem+101)
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
filename = sprintf('Plots/LinePicking_test_sim_disk_eg.%s', suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('disk-line picking example');


%
% 3ball picking (to test hyperball)
%
problem = 2;
R = 1;
parameters = [3, R];
s = LinePickingSupport(problem, parameters);
ds = diff(s)/N;
t = s(1):ds:s(2);
g = LinePickingPDF(t, problem, parameters);
means(problem+1) = LinePickingMean(problem, parameters);
vars(problem+1) = LinePickingVar(problem, parameters);
% name(problem+1) = {LinePickingProblemLookup(problem)};
name(problem+1) = {'3d hyperball'};

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
est_means(problem+1) = mean(d);
est_var(problem+1) = var(d);

figure(problem+1)
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
filename = sprintf('Plots/LinePicking_test_sim_3ball.%s', suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('3D ball-line picking density');

figure(problem+101)
hold off
n = 12;
[x,y,z] = sphere(n);
x = R*x;
y = R*y; 
z = R*z;
h = mesh(x+0,y+0,z+0);
colormap(0.5*[1 1 1]);
hidden off
hold on
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
filename = sprintf('Plots/LinePicking_test_sim_3ball_eg.%s', suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('3D ball-line picking example');



%
% 4ball picking (to test hyperball)
%
problem = 2;
R = 1;
parameters = [4, R];
s = LinePickingSupport(problem, parameters);
ds = diff(s)/N;
t = s(1):ds:s(2);
g = LinePickingPDF(t, problem, parameters);

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

figure(problem+21)
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
filename = sprintf('Plots/LinePicking_test_sim_4ball.%s', suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('4D ball-line picking density');


%
% rect picking
%
problem = 3;
a = 1;
b = 2;
parameters = [a, b];
s = LinePickingSupport(problem, parameters);
ds = diff(s)/N;
t = s(1):ds:s(2);
g = LinePickingPDF(t, problem, parameters);
means(problem+1) = LinePickingMean(problem, parameters);
vars(problem+1) = LinePickingVar(problem, parameters);
% name(problem+1) = {LinePickingProblemLookup(problem)};
name(problem+1) = {'1:2 rectangle'};

x1 = b*rand(M,1);
y1 = a*rand(M,1);
x2 = b*rand(M,1);
y2 = a*rand(M,1);
d = sqrt( (x1-x2).^2 + (y1-y2).^2);
n = histc(d, t);
prob = (n/M) / ds;
est_means(problem+1) = mean(d);
est_var(problem+1) = var(d);

figure(problem+1)
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
filename = sprintf('Plots/LinePicking_test_sim_rect.%s', suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('rect(2:1)-line picking density');

figure(problem+101)
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
filename = sprintf('Plots/LinePicking_test_sim_rect_eg.%s', suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('rect(2:1)-line picking example');

%
% line-line picking
%
problem = 4;
L = 1;
parameters = [L];
s = LinePickingSupport(problem, parameters);
ds = diff(s)/N;
t = s(1):ds:s(2);
g = LinePickingPDF(t, problem, parameters);
means(problem+1) = LinePickingMean(problem, parameters);
vars(problem+1) = LinePickingVar(problem, parameters);
name(problem+1) = {LinePickingProblemLookup(problem)};

x1 = L*rand(M,1);
x2 = L*rand(M,1);
d = abs( (x1-x2) );
n = histc(d, t);
prob = (n/M) / ds;
est_means(problem+1) = mean(d);
est_var(problem+1) = var(d);

figure(problem+1)
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
filename = sprintf('Plots/LinePicking_test_sim_line.%s', suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('line-line picking density');


%
% cube picking
%
problem = 5;
L = 1;
parameters = [L];
s = LinePickingSupport(problem, parameters);
ds = diff(s)/N;
t = s(1):ds:s(2);
g = LinePickingPDF(t, problem, parameters);
means(problem+1) = LinePickingMean(problem, parameters);
vars(problem+1) = LinePickingVar(problem, parameters);
name(problem+1) = {LinePickingProblemLookup(problem)};

x1 = L*rand(M,1);
y1 = L*rand(M,1);
z1 = L*rand(M,1);
x2 = L*rand(M,1);
y2 = L*rand(M,1);
z2 = L*rand(M,1);
d = sqrt( (x1-x2).^2 + (y1-y2).^2 + (z1-z2).^2);
n = histc(d, t);
prob = (n/M) / ds;
est_means(problem+1) = mean(d);
est_var(problem+1) = var(d);

figure(problem+1)
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
filename = sprintf('Plots/LinePicking_test_sim_cube.%s', suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('cube-line picking density');

figure(problem+101)
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
filename = sprintf('Plots/LinePicking_test_sim_cube_eg.%s', suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('cube-line picking example');


%
% sphere line picking
%
problem = 6;
R = 1;
parameters = [R];
s = LinePickingSupport(problem, parameters);
ds = diff(s)/N;
t = s(1):ds:s(2);
g = LinePickingPDF(t, problem, parameters);
means(problem+1) = LinePickingMean(problem, parameters);
vars(problem+1) = LinePickingVar(problem, parameters);
name(problem+1) = {LinePickingProblemLookup(problem)};

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
est_means(problem+1) = mean(d);
est_var(problem+1) = var(d);

figure(problem+1)
hold off
p1 = plot(0,0);
hold on
p1 = plot(t, g, 'r--', 'linewidth', 2);
p2 = plot(t+ds/2, prob, 'bo', 'linewidth', 2);
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
legend([p1 p2], 'exact', 'simulated', 'location','southeast');
xlabel('t');
ylabel('g(t)');
filename = sprintf('Plots/LinePicking_test_sim_sphere.%s', suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('sphere-line picking density');

figure(problem+101)
hold off
n = 12;
[x,y,z] = sphere(n);
x = R*x;
y = R*y;
z = R*z;
h = mesh(x+0,y+0,z+0);
colormap(0.5*[1 1 1]);
hidden off
hold on
m = 1:10;
of = 1.001; % make dots just outside sphere
plot3(of*x1(m), of*y1(m), of*z1(m), 'b.', 'markersize', 15);
plot3(of*x2(m), of*y2(m), of*z2(m), 'b.', 'markersize', 15);
plot3([x1(m)'; x2(m)'], [y1(m)'; y2(m)'], [z1(m)'; z2(m)'], 'b-', 'linewidth', 2);
set(gca, 'xlim', [-R-0.1, R+0.1]);
set(gca, 'ylim', [-R-0.1, R+0.1]);
set(gca, 'zlim', [-R-0.1, R+0.1]);
axis equal
az = -120; el = 20;
view([az, el]);
% axis off
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
filename = sprintf('Plots/LinePicking_test_sim_sphere_eg.%s', suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('sphere-line picking example');


%
% sphere geodesic picking
%
problem = 7;
R = 1;
parameters = [R];
s = LinePickingSupport(problem, parameters);
ds = diff(s)/N;
t = s(1):ds:s(2);
g = LinePickingPDF(t, problem, parameters);
means(problem+1) = LinePickingMean(problem, parameters);
vars(problem+1) = LinePickingVar(problem, parameters);
name(problem+1) = {LinePickingProblemLookup(problem)};

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
est_means(problem+1) = mean(d);
est_var(problem+1) = var(d);

figure(problem+1)
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
filename = sprintf('Plots/LinePicking_test_sim_sphere_geodesic.%s', suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('sphere-geodesic-line picking density');

figure(problem+101)
hold off
n = 12;
[x,y,z] = sphere(n);
x = R*x;
y = R*y; 
z = R*z;
h = mesh(x+0,y+0,z+0);
colormap(0.5*[1 1 1]);
hidden off
hold on
n=10;
points = randn(3,n);
normals = 1./sum(points.^2).^(1/2);
v1 = [normals.*points(1,:); normals.*points(2,:); normals.*points(3,:)];

points = randn(3,n);
normals = 1./sum(points.^2).^(1/2);
v2 = [normals.*points(1,:); normals.*points(2,:); normals.*points(3,:)];

of = 1.001; % make dots just outside sphere
d = 0.1;
little_sphere_x = d*x/R;
little_sphere_y = d*y/R;
little_sphere_z = d*z/R;
for i=1:size(v1,2)
  % surf(of*v1(1,i)+little_sphere_x,of*v1(2,i)+little_sphere_y,of*v1(3,i)+little_sphere_z);
  % seems to draw them better if we do it one by one
  plot3(of*v1(1,i),of*v1(2,i),of*v1(3,i),'b.', 'markersize', 15);
  plot3(of*v2(1,i),of*v2(2,i),of*v2(3,i),'b.', 'markersize', 15);
end


% draw the great circle lines 
[rows cols] = size(v1);
for i = 1:cols
  % v3 lies in plane of v1 & v2 and is orthog. to v1 
  v3 = cross(cross(v1(:,i),v2(:,i)),v1(:,i)); 
  v3 = v3/norm(v3); % Make v3 of length r
  % Let t range through the inner angle between v1 and v2
  t = linspace(0,atan2(norm(cross(v1(:,i),v2(:,i))),dot(v1(:,i),v2(:,i))));

  v = v1(:,i)*cos(t)+v3*sin(t); % v traces great circle path, relative to center
  plot3(of*v(1,:),of*v(2,:),of*v(3,:),'b-', 'linewidth', 2); % Plot it in 3D
end

set(gca, 'xlim', [-R-0.1, R+0.1]);
set(gca, 'ylim', [-R-0.1, R+0.1]);
set(gca, 'zlim', [-R-0.1, R+0.1]);
axis equal
az = -120; el = 20;
view([az, el]);
% axis off
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
filename = sprintf('Plots/LinePicking_test_sim_sphere_geodesic_eg.%s', suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('sphere-geodesic picking example');




%
% rect with Manhattan distance picking
%
problem = 9;
a = 1;
b = 2;
parameters = [a, b];
s = LinePickingSupport(problem, parameters);
ds = diff(s)/N;
t = s(1):ds:s(2);
g = LinePickingPDF(t, problem, parameters);
means(problem+1) = LinePickingMean(problem, parameters);
vars(problem+1) = LinePickingVar(problem, parameters);
% name(problem+1) = {LinePickingProblemLookup(problem)};
name(problem+1) = {'1:2 rectangle with Manhattan distances'};

x1 = b*rand(M,1);
y1 = a*rand(M,1);
x2 = b*rand(M,1);
y2 = a*rand(M,1);
d = abs(x1-x2) + abs(y1-y2);
n = histc(d, t);
prob = (n/M) / ds;
est_means(problem+1) = mean(d);
est_var(problem+1) = var(d);

figure(problem+1)
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
filename = sprintf('Plots/LinePicking_test_sim_rect_man.%s', suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('rect(2:1) with Manhattan distances-line picking density');

figure(problem+101)
hold off
plot([0 b b 0 0], [0 0 a a 0], 'k-', 'linewidth', 2);
hold on
m = 1:10;
plot([x1(m)'; x2(m)'; x2(m)'], [y1(m)'; y1(m)'; y2(m)'], 'b-', 'linewidth', 2);
plot([x1(m)'; x2(m)'], [y1(m)'; y2(m)'], 'bo', 'linewidth', 2);
set(gca, 'xlim', [-0.1, b+0.1]);
set(gca, 'ylim', [-0.1, a+0.1]);
axis equal
axis off
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
filename = sprintf('Plots/LinePicking_test_sim_rect_man_eg.%s', suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('rect(2:1) with Manhattan distances-line picking example');

%
% rect with Max distance picking
%
problem = 10;
a = 1;
b = 2;
parameters = [a, b];
s = LinePickingSupport(problem, parameters);
ds = diff(s)/N;
t = s(1):ds:s(2);
g = LinePickingPDF(t, problem, parameters);
means(problem+1) = LinePickingMean(problem, parameters);
vars(problem+1) = LinePickingVar(problem, parameters);
% name(problem+1) = {LinePickingProblemLookup(problem)};
name(problem+1) = {'1:2 rectangle with Max distances'};

x1 = b*rand(M,1);
y1 = a*rand(M,1);
x2 = b*rand(M,1);
y2 = a*rand(M,1);
d = max([abs(x1-x2),abs(y1-y2)]');
n = histc(d, t);
prob = (n/M) / ds;
est_means(problem+1) = mean(d);
est_var(problem+1) = var(d);

figure(problem+1)
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
filename = sprintf('Plots/LinePicking_test_sim_rect_max.%s', suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('rect(2:1) with Max distances-line picking density');


%
%
% output a table of results
%
% 
fprintf('  \\begin{tabular}{r|rrrr}\n');
fprintf('%20s & %8s & %14s & %8s & %14s \\\\\n', 'problem', 'mean', 'estimated mean', 'variance', 'estimated var');
fprintf('     \\hline \n');
for i=1:problem
  fprintf('%20s & %8.4f & %14.4f & %8.4f & %14.4f \\\\\n', ...
	  char(name(i)), means(i), est_means(i), vars(i), est_var(i));
end
fprintf('  \\end{tabular}\n');

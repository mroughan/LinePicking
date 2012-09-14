%
% Generate plots showing examples.
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

M = 10;
device = '-depsc';
suffix = 'eps';
seed = 1;
set(0,'DefaultTextFontsize', 18);
set(0,'DefaultAxesFontsize', 18);
set(0,'DefaultLineLinewidth', 2);
plotdir = '../Plots';

% check that the geometries are what we think they should be 
LinePickingPrintAllProblems;

%
% line-line picking
%
problem = LinePickingNameLookup('line');
L = 1;
parameters = [L];
name(problem+1) = {LinePickingProblemLookup(problem)};
points1 = LinePickingSimPoints(M, problem, parameters, seed);
points2 = LinePickingSimPoints(M, problem, parameters, seed+1);

figure(problem+1)
hold off
plot([0 L], [0 0], 'k-');
hold on
plot([0 0], [-0.04 0.04], 'k-');
plot([L L], [-0.04 0.04], 'k-');
plot([points1(1,:); points2(1,:)], [1:M; 1:M]*(0.3/M), 'bo-');
set(gca, 'xlim', [-0.1, L+0.1]);
set(gca, 'ylim', [-0.1, L+0.1]);
axis equal
axis off
filename = sprintf('%s/LinePicking_eg_line.%s', plotdir, suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('line-line picking example');

%
% square picking
%
problem = LinePickingNameLookup('square');
L = 1;
parameters = [L];
name(problem+1) = {LinePickingProblemLookup(problem)};
points1 = LinePickingSimPoints(M, problem, parameters, seed);
points2 = LinePickingSimPoints(M, problem, parameters, seed+1);

figure(problem+1)
hold off
plot([0 L L 0 0], [0 0 L L 0], 'k-');
hold on
plot([points1(1,:); points2(1,:)], [points1(2,:); points2(2,:)], 'bo-');
set(gca, 'xlim', [-0.1, L+0.1]);
set(gca, 'ylim', [-0.1, L+0.1]);
axis equal
axis off
filename = sprintf('%s/LinePicking_eg_square.%s', plotdir, suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('square-line picking example');

%
% disk picking
%
problem = LinePickingNameLookup('disk');
R = 1;
parameters = [R];
name(problem+1) = {LinePickingProblemLookup(problem)};
points1 = LinePickingSimPoints(M, problem, parameters, seed);
points2 = LinePickingSimPoints(M, problem, parameters, seed+1);

figure(problem+1)
hold off
theta = 0:pi/40:2*pi;
x_theta = R*cos(theta);
y_theta = R*sin(theta);
plot(x_theta, y_theta, 'k-');
hold on
plot([points1(1,:); points2(1,:)], [points1(2,:); points2(2,:)], 'bo-');
set(gca, 'xlim', [-R-0.1, R+0.1]);
set(gca, 'ylim', [-R-0.1, R+0.1]);
axis equal
axis off
filename = sprintf('%s/LinePicking_eg_disk.%s', plotdir, suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('disk-line picking example');

%
% 3ball picking
%
problem = LinePickingNameLookup('hyper-ball');
R = 1;
parameters = [3, R];
name(problem+1) = {'3d hyperball'};
points1 = LinePickingSimPoints(M, problem, parameters, seed);
points2 = LinePickingSimPoints(M, problem, parameters, seed+1);

figure(problem+1)
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
plot3([points1(1,:); points2(1,:)], [points1(2,:); points2(2,:)], [points1(3,:); points2(3,:)], 'bo-');
set(gca, 'xlim', [-R-0.1, R+0.1]);
set(gca, 'ylim', [-R-0.1, R+0.1]);
set(gca, 'zlim', [-R-0.1, R+0.1]);
axis equal
az = -120; el = 20;
view([az, el]);
filename = sprintf('%s/LinePicking_eg_3ball.%s', plotdir, suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('3D ball-line picking example');

%
% rect picking
%
problem = LinePickingNameLookup('rectangle');
a = 1;
b = 2;
parameters = [a, b];
name(problem+1) = {'1:2 rectangle'};
points1 = LinePickingSimPoints(M, problem, parameters, seed);
points2 = LinePickingSimPoints(M, problem, parameters, seed+1);

figure(problem+1)
hold off
plot([0 b b 0 0], [0 0 a a 0], 'k-', 'linewidth', 2);
hold on
plot([points1(1,:); points2(1,:)], [points1(2,:); points2(2,:)], 'bo-');
set(gca, 'xlim', [-0.1, b+0.1]);
set(gca, 'ylim', [-0.1, a+0.1]);
axis equal
axis off
filename = sprintf('%s/LinePicking_eg_rect.%s', plotdir, suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('rect(2:1)-line picking example');

%
% line-line picking
%    don't bother ...


%
% cube picking
%
problem = LinePickingNameLookup('cube');
L = 1;
parameters = [L];
name(problem+1) = {LinePickingProblemLookup(problem)};
points1 = LinePickingSimPoints(M, problem, parameters, seed);
points2 = LinePickingSimPoints(M, problem, parameters, seed+1);

figure(problem+1)
hold off
plot3(0,0,0);
hold on
plot3([0 L L 0 0], [0 0 L L 0], [0 0 0 0 0], 'k-', 'linewidth', 2);
plot3([0 L L 0 0], [0 0 L L 0], [L L L L L], 'k-', 'linewidth', 2);
plot3([0 L L 0 0], [0 0 0 0 0], [0 0 L L 0], 'k-', 'linewidth', 2);
plot3([0 L L 0 0], [L L L L L], [0 0 L L 0], 'k-', 'linewidth', 2);
plot3([points1(1,:); points2(1,:)], [points1(2,:); points2(2,:)], [points1(3,:); points2(3,:)], 'bo-');
set(gca, 'xlim', [-0.1, L+0.1]);
set(gca, 'ylim', [-0.1, L+0.1]);
set(gca, 'zlim', [-0.1, L+0.1]);
axis equal
az = -50; el = 25;
view([az, el]);
filename = sprintf('%s/LinePicking_eg_cube.%s', plotdir, suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('cube-line picking example');


problem = LinePickingNameLookup('hyper-cube max');
L = 1;
parameters = [3, L];
name(problem+1) = {LinePickingProblemLookup(problem)};
points1 = LinePickingSimPoints(M, problem, parameters, seed);
points2 = LinePickingSimPoints(M, problem, parameters, seed+1);
figure(problem+1)
hold off
plot3(0,0,0);
hold on
plot3([0 L L 0 0], [0 0 L L 0], [0 0 0 0 0], 'k-', 'linewidth', 2);
plot3([0 L L 0 0], [0 0 L L 0], [L L L L L], 'k-', 'linewidth', 2);
plot3([0 L L 0 0], [0 0 0 0 0], [0 0 L L 0], 'k-', 'linewidth', 2);
plot3([0 L L 0 0], [L L L L L], [0 0 L L 0], 'k-', 'linewidth', 2);


%  this all works to colour the longest section of the manhattan path red
% ie showing what is used for the max metric.

k = abs(points1 - points2)
j = k(1,:) == max(k)

plot3([points1(1,j); points2(1,j)], [points1(2,j); points1(2,j)], [points1(3,j); points1(3,j)],'r-');
j = k(1,:) < max(k)
plot3([points1(1,j); points2(1,j)], [points1(2,j); points1(2,j)], [points1(3,j); points1(3,j)],'b-');

j = k(2,:) == max(k)
plot3([points2(1,j); points2(1,j)], [points1(2,j); points2(2,j)], [points1(3,j); points1(3,j)], 'r-');
j = k(2,:) < max(k)
plot3([points2(1,j); points2(1,j)], [points1(2,j); points2(2,j)], [points1(3,j); points1(3,j)], 'b-');

j = k(3,:) == max(k)
plot3([points2(1,j); points2(1,j)], [points2(2,j); points2(2,j)], [points1(3,j); points2(3,j)], 'r-');
j = k(3,:) < max(k)
plot3([points2(1,j); points2(1,j)], [points2(2,j); points2(2,j)], [points1(3,j); points2(3,j)], 'b-');


plot3([points1(1,:); points1(1,:)], [points1(2,:); points1(2,:)], [points1(3,:); points1(3,:)], 'bo-');
plot3([points2(1,:); points2(1,:)], [points2(2,:); points2(2,:)], [points2(3,:); points2(3,:)], 'bo-');



set(gca, 'xlim', [-0.1, L+0.1]);
set(gca, 'ylim', [-0.1, L+0.1]);
set(gca, 'zlim', [-0.1, L+0.1]);
axis equal
az = -50; el = 25;
view([az, el]);
filename = sprintf('%s/LinePicking_eg_cubemax.%s', plotdir, suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('cubemax line picking example');


%
% sphere line picking
%
problem = LinePickingNameLookup('sphere');
R = 1;
parameters = [R];
name(problem+1) = {LinePickingProblemLookup(problem)};
points1 = LinePickingSimPoints(M, problem, parameters, seed);
points2 = LinePickingSimPoints(M, problem, parameters, seed+1);

figure(problem+1)
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
% of = 1.001; % make dots just outside sphere
% plot3(of*x1(m), of*y1(m), of*z1(m), 'b.', 'markersize', 15);
% plot3(of*x2(m), of*y2(m), of*z2(m), 'b.', 'markersize', 15);
plot3([points1(1,:); points2(1,:)], [points1(2,:); points2(2,:)], [points1(3,:); points2(3,:)], 'bo-');
set(gca, 'xlim', [-R-0.1, R+0.1]);
set(gca, 'ylim', [-R-0.1, R+0.1]);
set(gca, 'zlim', [-R-0.1, R+0.1]);
axis equal
az = -120; el = 20;
view([az, el]);
filename = sprintf('%s/LinePicking_eg_sphere.%s', plotdir, suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('sphere-line picking example');

%
% sphere geodesic picking
%
problem = LinePickingNameLookup('sphere geodesic');
R = 1;
parameters = [R];
points1 = LinePickingSimPoints(M, problem, parameters, seed);
points2 = LinePickingSimPoints(M, problem, parameters, seed+1);

figure(problem+1)
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
v1 = points1;
v2 = points2;

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
filename = sprintf('%s/LinePicking_eg_sphere_geodesic.%s', plotdir, suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('sphere-geodesic picking example');




%
% rect with Manhattan distance picking
%
problem = LinePickingNameLookup('rectangle Manhattan');
a = 1;
b = 2;
parameters = [a, b];
name(problem+1) = {'1:2 rectangle with Manhattan distances'};
points1 = LinePickingSimPoints(M, problem, parameters, seed);
points2 = LinePickingSimPoints(M, problem, parameters, seed+1);

figure(problem+101)
hold off
plot([0 b b 0 0], [0 0 a a 0], 'k-', 'linewidth', 2);
hold on
plot([points1(1,:); points2(1,:); points2(1,:)], [points1(2,:); points1(2,:); points2(2,:)], 'b-');
plot([points1(1,:); points2(1,:)], [points1(2,:); points2(2,:)], 'bo');
set(gca, 'xlim', [-0.1, b+0.1]);
set(gca, 'ylim', [-0.1, a+0.1]);
axis equal
axis off
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
filename = sprintf('%s/LinePicking_eg_rect_man.%s', plotdir, suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('rect(2:1) with Manhattan distances-line picking example');

%
% rect with Max distance picking
%    don't bother


%
% circle line picking (using hypersphere, with n=1)
%
problem = 11;
problem = LinePickingNameLookup('hyper-sphere');
R = 1;
parameters = [1,R];
name(problem+1) = {LinePickingProblemLookup(problem)};
points1 = LinePickingSimPoints(M, problem, parameters, seed);
points2 = LinePickingSimPoints(M, problem, parameters, seed+1);

figure(problem+1)
hold off
theta = 0:pi/40:2*pi;
x_theta = R*cos(theta);
y_theta = R*sin(theta);
plot(x_theta, y_theta, 'k-');
hold on
plot([points1(1,:); points2(1,:)], [points1(2,:); points2(2,:)], 'bo-');
set(gca, 'xlim', [-R-0.1, R+0.1]);
set(gca, 'ylim', [-R-0.1, R+0.1]);
axis equal
axis off
filename = sprintf('%s/LinePicking_eg_circle.%s', plotdir, suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('circle-line picking example');


%
% hypersphere geodesic (general case) 
%    don't bother



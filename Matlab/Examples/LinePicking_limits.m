%
% Look at limits for n-ball and n-sphere
%
% Q: 
%     Are they asymptotically normal? If so, with what parameters
%     Do they converge to a delta?
%     Do the nsphere an nball coverge to the same distribution?
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
set(0,'DefaultTextFontsize', 18);
set(0,'DefaultAxesFontsize', 18);
set(0,'DefaultLineLinewidth', 2);
plotdir = '../Plots';

% check that the geometries are what we think they should be 
LinePickingPrintAllProblems;

step = 20;

% look at n-ball for large n
problem = LinePickingNameLookup('hyper-ball');
figure(5)
hold off
plot(0,0)
hold on
for n=1:8
  [g_ball] = LinePickingPDF(t, 2, [n*step, 1]);
  p5(n) = plot(t,g_ball,'color', colors(n,:));
  legend_str(n,:) = sprintf('n = %3d', n*step);
end
set(gca, 'xlim', [0 2.3]);
legend(p5, legend_str,'location','NorthWest');
xlabel('t');
ylabel('g_n(t)');
filename = sprintf('%s/LinePicking_limit_nballs.%s', plotdir, suffix);
print(device, filename);
fprintf('Printed to %s\n', filename);

% look at n-sphere for large n
%   
problem = LinePickingNameLookup('hyper-sphere');
figure(16)
hold off
plot(0,0)
hold on
for n=1:8
  [g_sphere] = LinePickingPDF(t, 11, [n*step, 1]);
  p16(n) = plot(t,g_sphere,'color', colors(n,:));
  legend_str(n,:) = sprintf('n = %3d', n*step);
end
set(gca, 'xlim', [0 2.3]);
legend(p16, legend_str,'location','NorthWest');
xlabel('t');
ylabel('g_n(t)');
filename = sprintf('%s/LinePicking_limit_nspheres.%s', plotdir, suffix);
print(device, filename);
fprintf('Printed to %s\n', filename);

% compare sphere-geodesic-line picking in different dimensions:
%   
problem = LinePickingNameLookup('hyper-sphere geodesic');
figure(17)
hold off
plot(0,0)
hold on
for n=1:8
  [g] = LinePickingPDF(t, 12, [n*step, 1]);
  p17(n) = plot(t,g,'color', colors(n,:));
  legend_str(n,:) = sprintf('n = %3d', n*step);
end
set(gca, 'xlim', [0 pi]);
legend(p17, legend_str,'location','NorthWest');
xlabel('t');
ylabel('g_n(t)');
filename = sprintf('%s/LinePicking_limit_nspheres_geodesic.%s', plotdir, suffix);
print(device, filename);
fprintf('Printed to %s\n', filename);


figure(100)
hold off
plot(0,0)
hold on
p100(1) = plot(t,g_ball,'b');
p100(2) = plot(t,g_sphere,'r--');
legend(p100, 'n-ball', 'n-sphere', 'location','NorthWest');
set(gca, 'xlim', [0 2.3]);
xlabel('t');
ylabel('g_n(t)');
filename = sprintf('%s/LinePicking_limit_compare.%s', plotdir, suffix);
print(device, filename);
fprintf('Printed to %s\n', filename);


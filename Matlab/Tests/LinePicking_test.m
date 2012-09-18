%
% Compare some of the overlapping cases.
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

 
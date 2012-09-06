%
% Test each problem against a simulation
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

N = 30;   % number of bins for PDFs
M = 10^6; % number of simulations to run
K = 1000; % number of points for the PDF and CDF
seed = 1;

dt = 0.01;
colors = [[1 0 0];
	  [1 0.5 0];
	  [1 1 0];
	  [0 1 0];
	  [0 1 1];
	  [0 0 1];
	  [0 0.5 0.5];
	  [0.5 0 0.5];
	 ];
set(0,'DefaultTextFontsize', 18); 
set(0,'DefaultAxesFontsize', 18);
set(0,'DefaultLineLinewidth', 2);
plotdir = '../Plots';
device = '-depsc';
suffix = 'eps';

% list of test problems in the form
%    {name, parameters, title (to use in figs)}
% arrange parameters so that support of each has identical support
L1 = 1;         % length of line
L2 = 1/sqrt(2); % side of square
L3 = 1/sqrt(3); % side of cube
R = 1/2;        % radius for balls
a = 1;          % rectangle height
b = 2;          % rectangle width
a = 1/sqrt(a^2 + b^2); b=1/sqrt(a^2 + b^2);
test_problems = [...
    {'square', [L2], 'square', 'square'};
    {'disk', [R], 'disk (2-ball)', 'disk'};
    {'hyper-ball', [3, R], '3-ball', '3ball'};
    {'hyper-ball', [4, R], '4-ball', '4ball'};
    {'rectangle', [a, b], 'rectangle (1:2)', 'rect'};
    {'line', [L1], 'line', 'line'};
    {'cube', [L3], 'cube', 'cube'};
    {'sphere', [R], '2-sphere', '2-sphere'};
    {'hyper-sphere', [1, R], 'circle', 'circle'};
    {'hyper-sphere', [3, R], '3-sphere', '3sphere'};
    {'sphere geodesic', [R], 'sphere geodesic', 'sphere_geodesic'};
    {'hyper-sphere geodesic', [1 R], 'circle geodesic', 'circle_geodesic'};
    {'hyper-sphere geodesic', [3 R], '3-sphere geodesic', '3sphere_geodesic'};
    {'rectangle Manhattan', [a, b], 'rectangle Manhattan (1:2)', 'rect_manhattan'};
    {'rectangle max', [a, b], 'rectangle max (1:2)', 'rectangle_max'};
    {'prism geodesic', [1, 1], 'prism geodesic', 'prism_geodesic'};
		];

% could porobably add a check of scaling in here as well

% reminder of the problems
LinePickingPrintAllProblems

for i=1:length(test_problems)
% for i=5:5
  name = char(test_problems(i,1));
  parameters = cell2mat(test_problems(i,2));
  title_str = char(test_problems(i,3));
  file_str = char(test_problems(i,4));
  problem = LinePickingNameLookup(name);
  fprintf('problem=%2d, name=%-24s\n', problem, name);
  
  % get the mean, variance, PDF and CDF
  calc_means(i) = LinePickingMean(problem, parameters);
  calc_vars(i) = LinePickingVar(problem, parameters);
  s = LinePickingSupport(problem, parameters);
  ds = diff(s)/K;
  t = s(1):ds:s(2);
  g = LinePickingPDF(t, problem, parameters);
  G = LinePickingCDF(t, problem, parameters);
  
  % compute the sum of the PDF
  sum_pdf(i) = sum(g)*ds;
  
  % simulate
  distances = LinePickingSimDistances(M, problem, parameters, seed);
  ds_sim = diff(s)/N;
  t_sim = s(1):ds_sim:s(2);
  n = histc(distances, t_sim);
  prob = (n/M)/ds_sim;
  est_means(i) = mean(distances);
  est_var(i) = var(distances);

  % plot the PDF
  figure(i)
  hold off
  plot(0,0);
  hold on
  p(i,1) = plot(t, g, 'r--');
  p(i,2) = plot(t_sim+ds_sim/2, prob, 'bo');
  legend(p(i,:), 'exact', 'simulated');
  xlabel('t');
  ylabel('g(t)');
  filename = sprintf('%s/LinePicking_test_sim_%s.%s', plotdir, file_str, suffix);
  print(device,filename);
  fprintf('   printed to %s\n', filename);
  title(title_str);

  % test values
  
end

%
%
% output a table of means and variance estimates
%
% 
fprintf('\n\n\n');
fprintf('  \\begin{tabular}{r|rrrr}\n');
fprintf('%25s & %8s & %14s & %8s & %14s \\\\\n', 'problem', 'mean', 'estimated mean', 'variance', 'estimated var');
fprintf('     \\hline \n');
for i=1:length(test_problems)
  fprintf('%25s & %8.4f & %14.4f & %8.4f & %14.4f \\\\\n', ...
	  char(test_problems(i,3)), calc_means(i), est_means(i), calc_vars(i), est_var(i));
end
fprintf('  \\end{tabular}\n');


%
%
% output a table of PDF sums
%
% 
fprintf('\n\n\n');
fprintf('  \\begin{tabular}{r|r}\n');
fprintf('%25s & %8s & %14s \\\\\n', 'problem', 'PDF sum');
fprintf('     \\hline \n');
for i=1:length(test_problems)
  fprintf('%25s & %8.5f \\\\\n', ...
	  char(test_problems(i,3)), sum_pdf(i));
end
fprintf('  \\end{tabular}\n');


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

% list of test problems
test_cases;

% reminder of the problems
LinePickingPrintAllProblems

for i=1:length(test_problems)
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
  % if (any(g<0))
  %   k = find(g < 0);
  %   t(k)
  %   stop
  % end
  
  % compute the sum of the PDF
  % sum_pdf(i) = sum(g)*ds;
  gt = @(t) LinePickingPDF(t, problem, parameters);
  [q_square, errbnd] = quadgk(gt, s(1), s(2));
  sum_pdf(i) = q_square;
  
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

  % plot CDFs and test values
  
end


%%%
%    create a .tex file with some stuff in it for the paper
%%%
fid = fopen('LinePicking_test_sim.tex', 'w');

%
%
% output two figures to import directly into LaTex document
%
% 
fprintf(fid,'\n\n\n');
fprintf(fid,'\\begin{figure}[tbp]\n');
fprintf(fid,'  \\begin{center}\n');
for i=1:12
  file_str = char(test_problems(i,4));
  filename = sprintf('LinePicking_test_sim_%s.%s', file_str, suffix);
  fprintf(fid,'        \\subfloat[%s]{\\includegraphics[width=0.32\\columnwidth]{../Matlab/Plots/%s}}\n', ...
	  char(test_problems(i,3)), filename);
  if (mod(i,3) == 0)
    fprintf(fid,'\n');
  end
end
fprintf(fid,'    \\caption{\\label{fig:sim_vs_exact}Comparisons of exactly calculated\n');
fprintf(fid,'      distributions and the distributions obtained by simulation. \n');
fprintf(fid,'      %.0f simulated lines were used to draw the estimated PDF,\n', M);
fprintf(fid,'      which are binned into %0.f equally spaced bins.}\n', N);
fprintf(fid,'  \\end{center} \n');
fprintf(fid,'\\vspace{-4mm}\n');
fprintf(fid,'\\end{figure}\n');

fprintf(fid,'\n\n\n');
fprintf(fid,'\\begin{figure}[tbp]\n');
fprintf(fid,'  \\begin{center}\n');
for i=13:length(test_problems)
  file_str = char(test_problems(i,4));
  filename = sprintf('LinePicking_test_sim_%s.%s', file_str, suffix);
  fprintf(fid,'        \\subfloat[%s]{\\includegraphics[width=0.32\\columnwidth]{../Matlab/Plots/%s}}\n', ...
	  char(test_problems(i,3)), filename);
  if (mod(i,3) == 0)
    fprintf(fid,'\n');
  end
end
fprintf(fid,'    \\caption{\\label{fig:sim_vs_exact2}Comparisons of exactly calculated\n');
fprintf(fid,'      distributions and the distributions obtained by simulation. \n');
fprintf(fid,'      %.0f simulated lines were used to draw the estimated PDF,\n', M);
fprintf(fid,'      which are binned into %0.f equally spaced bins.}\n', N);
fprintf(fid,'  \\end{center} \n');
fprintf(fid,'\\vspace{-4mm}\n');
fprintf(fid,'\\end{figure}\n');

%
%
% output a table of means and variance estimates
%
% 
fprintf(fid,'\n\n\n');
fprintf(fid,'\\begin{table}[ht]\n');
fprintf(fid,'  \\centering\n');
fprintf(fid,'  \\begin{tabular}{r|rrrr}\n');
fprintf(fid,'%25s & %8s & %14s & %8s & %14s \\\\\n', 'problem', 'mean', 'estimated mean', 'variance', 'estimated var');
fprintf(fid,'     \\hline \n');
for i=1:length(test_problems)
  fprintf(fid,'%25s & %8.4f & %14.4f & %8.4f & %14.4f \\\\\n', ...
	  char(test_problems(i,3)), calc_means(i), est_means(i), calc_vars(i), est_var(i));
end
fprintf(fid,'  \\end{tabular}\n');
fprintf(fid,'  \\caption{Means and variances calculated exactly, and approximated by simulation.}\n');
fprintf(fid,'  \\label{tab:mean_var_estimates}\n');
fprintf(fid,'\\end{table}\n');


%
%
% output a table of PDF sums
%
% 
fprintf(fid,'\n\n\n');
fprintf(fid,'\n\n\n');
fprintf(fid,'\\begin{table}[ht]\n');
fprintf(fid,'  \\centering\n');
fprintf(fid,'  \\begin{tabular}{r|r}\n');
fprintf(fid,'%25s & %12s \\\\\n', 'problem', 'PDF integral');
fprintf(fid,'     \\hline \n');
for i=1:length(test_problems)
  fprintf(fid,'%25s & %12.10f \\\\\n', ...
	  char(test_problems(i,3)), sum_pdf(i));
end
fprintf(fid,'  \\end{tabular}\n');
fprintf(fid,'  \\caption{Numerically integrated PDFs (integrated using Matlab''s {\\tt quadgk} function)}\n');
fprintf(fid,'  \\label{tab:numerical_pdf_sum}\n');
fprintf(fid,'\\end{table}\n');

fclose(fid);

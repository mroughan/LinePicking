%
% created: 	Mon Sep 17 2012 
% author:  	Matthew Roughan 
% email:   	matthew.roughan@adelaide.edu.au
% 
% TEST_INVERSE_CDF 
%      Test that the inverse CDF outputs results that match the CDF
%


clear;
path(path, '../');

N = 100;   % number of points to compare CDF and Inverse CDF
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
  
  % get  CDF
  s = LinePickingSupport(problem, parameters);
  ds = diff(s)/N;
  t = s(1):ds:s(2);
  G = LinePickingCDF(t, problem, parameters);
  ti = LinePickingInverseCDF(G, problem, parameters);
  
  % plot the CDF, and inverse CDF
  figure(i)
  hold off
  plot(0,0);
  hold on
  p(i,1) = plot(t, G, 'b-');
  p(i,2) = plot(ti, G, 'r--');
  legend(p(i,:), 'G(t)', 'G^{-1}(s)','location', 'southeast');
  xlabel('t');
  ylabel('G(t)');
  filename = sprintf('%s/LinePicking_test_inverse_%s.%s', plotdir, file_str, suffix);
  print(device,filename);
  fprintf('   printed to %s\n', filename);
  title(title_str);
  
  % RMS error
  rms(i) = sqrt( mean( (t-ti).^2 ) );
  fprintf('   RMS error for %-24s is %g\n', char(test_problems(i,3)), rms(i));
end


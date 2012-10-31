%
% test_median.m, (c) Matthew Roughan, 2012
%
% created: 	Tue Sep 18 2012 
% author:  	Matthew Roughan 
% email:   	matthew.roughan@adelaide.edu.au
% 
% TEST_MEDIAN 
%   Do some tests to make sure the Median is returning sensible values.
%         
%         
%
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
  median = LinePickingMedian(problem, parameters);
  G = LinePickingCDF(median, problem, parameters);
  
  % error
  error_val(i) = abs(0.5-G);
  fprintf('   error for %-24s is %g\n', char(test_problems(i,3)), error_val(i));
end

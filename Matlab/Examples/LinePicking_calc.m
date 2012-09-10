%
% LinePicking_calc.m, (c) Matthew Roughan, 2012
%
% created: 	Wed Aug 22 2012 
% author:  	Matthew Roughan 
% email:   	matthew.roughan@adelaide.edu.au
% 
% Written to numerically calculate the mean and variance of each from their PDFs.    
%         
clear;
path(path, '../')

tolerance = 1.0e-14;
trace = 0;
n = 15;
R = 1;

% helped by
% http://isc.carma.newcastle.edu.au/
% http://oldweb.cecm.sfu.ca/projects/ISC/ISCmain.html
Cahen = 0.64341054629; % Cahens constant, http://en.wikipedia.org/wiki/Cahen%27s_constant
guess = zeros(n);
guess(1) = (pi/(2*sqrt(3)))^2;
guess(3) = guess(1) - 1/2;
guess(5) = guess(3) - 1/8;
guess(7) = guess(5) - 1/18;
guess(9) = guess(7) - 1/32;
guess(11) = guess(9) - 1/50;
guess(13) = guess(11) - 1/72;
guess(15) = guess(13) - 1/98;

% http://oeis.org/search?q=2%2C+8%2C18%2C32%2C50%2C72%2C98&language=english&go=Search
%   online sequence 2,8,18,32,50,72,98
%       Number of edges of the complete bipartite graph of order 3n
%   ((2n+3+(-1)^n)^2)/8 (for odd n)
%   Maximum number of electrons in an atomic shell with total quantum number n
%   Arithmetic mean of triangular numbers in pairs: (1+3)/2, (6+10)/2,(15+21)/2
%   a(n) = A176271(n,k) + A176271(n,n-k+1), 1<=k<=n.
%   Even squares divided by 2
% maybe last one makes most sense, as we are only doing these for odd i
% 
guess(2) = (pi/2)^2 - 2;
guess(4) = guess(2) - 2/9;
guess(6) = guess(4) - 2/25;
guess(8) = guess(6) - 2/49;
guess(10) = guess(8) - 2/81;
guess(12) = guess(10) - 2/121;
guess(14) = guess(12) - 2/169;



problem = LinePickingNameLookup('hyper-sphere geodesic');
for i=1:n
  if (i>2)
    guess(i) = guess(i-2) - (2/(i-1)^2);
  end
  parameters = [i,R];
  s = LinePickingSupport(problem, parameters);
  g_nsphere_geo = @(t) t .* LinePickingPDF(t, problem, parameters);
  [meanb, fn_count] = quad(g_nsphere_geo, s(1), s(2), tolerance, trace);
  mean_nsphere_geo(i) = meanb;
  g_nsphere_geo2 = @(t) t.^2 .* LinePickingPDF(t, problem, parameters);
  [mu2, fn_count] = quad(g_nsphere_geo2, s(1), s(2), tolerance, trace);
  var_nsphere_geo(i) = mu2 - meanb.^2;
  fprintf('%3dD ball has mean=%.15f and var=%.15f guess=%.15f\n', ...
	  i, mean_nsphere_geo(i), var_nsphere_geo(i), guess(i));
end



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

t_min = 0;
t_max = 4; % just use an upper bound guaranteed to be outside support in all cases
tolerance = 1.0e-14;
trace = 0;

g_line = @(t) t .* LinePicking(t, 4, 1);
g_square = @(t) t .* LinePicking(t, 0, 1);
g_cube = @(t) t .* LinePicking(t, 5, 1);
g_rect21 = @(t) t .* LinePicking(t, 3, [2,1]);

[mean_line, fn_count] = quad(g_line, t_min, t_max, tolerance, trace);
[mean_square, fn_count] = quad(g_square, t_min, t_max, tolerance, trace);
[mean_cube, fn_count] = quad(g_cube, t_min, t_max, tolerance, trace);
[mean_rect21, fn_count] = quad(g_rect21, t_min, t_max, tolerance, trace);

g_line = @(t) t.^2 .* LinePicking(t, 4, 1);
g_square = @(t) t.^2 .* LinePicking(t, 0, 1);
g_cube = @(t) t.^2 .* LinePicking(t, 5, 1);
g_rect21 = @(t) t.^2 .* LinePicking(t, 3, [2,1]);
[mu2_line, fn_count] = quad(g_line, t_min, t_max, tolerance, trace);
[mu2_square, fn_count] = quad(g_square, t_min, t_max, tolerance, trace);
[mu2_cube, fn_count] = quad(g_cube, t_min, t_max, tolerance, trace);
[mu2_rect21, fn_count] = quad(g_rect21, t_min, t_max, tolerance, trace);
  
var_line = mu2_line - mean_line.^2;
var_square = mu2_square - mean_square.^2;
var_cube = mu2_cube - mean_cube.^2;
var_rect21 = mu2_rect21 - mean_rect21.^2;


fprintf('line      has mean=%.12f and var=%.12f\n', mean_line, var_line);
fprintf('square    has mean=%.12f and var=%.12f\n', mean_square, var_square);
fprintf('cube      has mean=%.12f and var=%.12f\n', mean_cube, var_cube);
fprintf('rect(2,1) has mean=%.12f and var=%.12f\n', mean_rect21, var_rect21);

for i=1:10
  g_ball = @(t) t .* LinePicking(t, 2, [i,1]);
  [meanb, fn_count] = quad(g_ball, t_min, t_max, tolerance, trace);
  mean_ball(i) = meanb;
  g_ball = @(t) t.^2 .* LinePicking(t, 2, [i,1]);
  [mu2, fn_count] = quad(g_ball, t_min, t_max, tolerance, trace);
  var_ball(i) = mu2 - meanb.^2;
  fprintf('%3dD ball has mean=%.12f and var=%.12f\n', i, mean_ball(i), var_ball(i));
end


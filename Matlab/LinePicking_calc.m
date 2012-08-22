%
% LinePicking_calc.m, (c) Matthew Roughan, 2012
%
% created: 	Wed Aug 22 2012 
% author:  	Matthew Roughan 
% email:   	matthew.roughan@adelaide.edu.au
% 
% Written to calculate the mean and variance of each of the distributions numerically.    
%         


t_min = 0;
t_max = 4; % just use an upper bound guaranteed to be outside support in all cases
tolerance = 1.0e-14;
trace = 0;

g_square = @(t) t .* LinePicking(t, 0, 1);
g_disk = @(t) t .* LinePicking(t, 1, 1);
g_sphere = @(t) t .* LinePicking(t, 2, [3,1]);
g_rect = @(t) t .* LinePicking(t, 3, [0.5,1]*2);
g_line = @(t) t .* LinePicking(t, 4, 1);
g_cube = @(t) t .* LinePicking(t, 5, 1);

[mean_square, fn_count] = quad(g_square, t_min, t_max, tolerance, trace)
[mean_disk, fn_count] = quad(g_disk, t_min, t_max, tolerance, trace)
[mean_sphere, fn_count] = quad(g_sphere, t_min, t_max, tolerance, trace)
[mean_rect, fn_count] = quad(g_rect, t_min, t_max, tolerance, trace)
[mean_line, fn_count] = quad(g_line, t_min, t_max, tolerance, trace)
[mean_cube, fn_count] = quad(g_cube, t_min, t_max, tolerance, trace)
  

g_square = @(t) t.^2 .* LinePicking(t, 0, 1);
g_disk = @(t) t.^2 .* LinePicking(t, 1, 1);
g_sphere = @(t) t.^2 .* LinePicking(t, 2, [3,1]);
g_rect = @(t) t.^2 .* LinePicking(t, 3, [0.5,1]*2);
g_line = @(t) t.^2 .* LinePicking(t, 4, 1);
g_cube = @(t) t.^2 .* LinePicking(t, 5, 1);
[mu2_square, fn_count] = quad(g_square, t_min, t_max, tolerance, trace);
[mu2_disk, fn_count] = quad(g_disk, t_min, t_max, tolerance, trace);
[mu2_sphere, fn_count] = quad(g_sphere, t_min, t_max, tolerance, trace);
[mu2_rect, fn_count] = quad(g_rect, t_min, t_max, tolerance, trace);
[mu2_line, fn_count] = quad(g_line, t_min, t_max, tolerance, trace);
[mu2_cube, fn_count] = quad(g_cube, t_min, t_max, tolerance, trace);
  
var_square = mu2_square - mean_square.^2
var_disk = mu2_disk - mean_disk.^2
var_sphere = mu2_sphere - mean_sphere.^2
var_rect = mu2_rect - mean_rect.^2
var_cube = mu2_cube - mean_cube.^2


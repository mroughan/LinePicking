%
% test_cases.m, (c) Matthew Roughan, 2012
%
% created: 	Tue Sep 18 2012 
% author:  	Matthew Roughan 
% email:   	matthew.roughan@adelaide.edu.au
% 
% The set of common test cases to use in our test routines
%         
%
%


% list of test problems in the form
%    {name, parameters, title (to use in figs)}
% arrange parameters so that support of each has identical support
L1 = 1;         % length of line
L2 = 1/sqrt(2); % side of square
L3 = 1/sqrt(3); % side of cube
R = 1/2;        % radius for balls
a = 1;          % rectangle height
b = 2;          % rectangle width
test_problems = [...
    {'line', [L1], 'line', 'line'};
    {'square', [L2], 'square', 'square'};
    {'cube', [L3], 'cube', 'cube'};
    {'rectangle', [a, b]/sqrt(a^2 + b^2), 'rectangle (1:2)', 'rect'};
    {'rectangle Manhattan', [a, b]/(a+b), 'rectangle Manhattan (1:2)', 'rect_manhattan'};
    {'rectangle max', [a, b]/max(a,b), 'rectangle max (1:2)', 'rectangle_max'};
    {'disk', [R], 'disk (2-ball)', 'disk'};
    {'hyper-ball', [3, R], '3-ball', '3ball'};
    {'hyper-ball', [4, R], '4-ball', '4ball'};
    {'hyper-sphere', [1, R], 'circle (1-sphere)', 'circle'};
    {'sphere', [R], '2-sphere', '2-sphere'};
    {'hyper-sphere', [3, R], '3-sphere', '3sphere'};
    {'hyper-sphere geodesic', [1 R], 'circle geodesic', 'circle_geodesic'};
    {'sphere geodesic', [R], 'sphere geodesic', 'sphere_geodesic'};
    {'hyper-sphere geodesic', [3 R], '3-sphere geodesic', '3sphere_geodesic'};
    {'prism geodesic', [b, a]/sqrt(b^2+(a/2)^2), 'prism geodesic', 'prism_geodesic'};
    {'cylindrical surface', [b, R]/sqrt(b^2+(R * 2)^2), 'cylindrical surface', 'cylindrical_surface'};
    {'cylindrical surface geodesic', [b, R]/sqrt(b^2+(R * pi)^2), 'cylindrical surface geodesic', 'cylindrical_surface_geodesic'};
    {'cylinder', [b, R]/sqrt(b^2+(R * 2)^2), 'cylinder', 'cylinder'};             
    {'cube max metric', [L1], 'cube max', 'cube_max'};
    {'hyper-cube max', [4, L1], '4-cube max', '4-cube_max'};
		];


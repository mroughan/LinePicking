%
% Test proposed PDF for the Manhattan distances on a rectangle
%
%    
%         
%
%
clear;

a = 1;
b = 2.5;
parameters = [a, b];
s = [0 a+b];
t = s(1):0.01:s(2);
suffix = 'eps';
device = '-depsc';

k1 = find(t<=a);
k2 = find(t>a & t<=b);
k3 = find(t>b & t<=a+b);
t1 = t(k1);
t2 = t(k2);
t3 = t(k3);
temp = @(t) (4/(a*b)) * t  -  (2*(b+a)/(a^2*b^2)) * t.^2  +  (2/(3*a^2*b^2)) * t.^3; 
g(k1) = temp(t1);
% g1_a =( 4/b - 2*(b-a)/b^2 - 4*a/(3*b^2) );
g1_a =( (6*b+2*a)/(3*b^2) );
g(k2) = g1_a  - (2/b^2)*t2;
g(k3) = g1_a  - (2/b^2)*t3 - temp(t3-b); 
g2_b = 2/a - (4*b)/(3*a^2)
g(k3) = g2_b;  

M = 1000000;
problem = 1;
x1 = b*rand(M,1);
y1 = a*rand(M,1);
x2 = b*rand(M,1);
y2 = a*rand(M,1);
d = abs(x1-x2) + abs(y1-y2);
N = 30;
ds = diff(s)/N;
ts = s(1):ds:s(2);
n = histc(d, ts);
prob = (n/M) / ds;
est_means(problem+1) = mean(d);
est_var(problem+1) = var(d);

figure(problem+1)
hold off
p1 = plot(0,0);
hold on
fill([t1, fliplr(t1)], [g(k1),zeros(size(k1))], [0.9,1,1]);
fill([t2, fliplr(t2)], [g(k2),zeros(size(k2))], [1,0.9,1]);
fill([t3, fliplr(t3)], [g(k3),zeros(size(k3))], [1,1,0.9]);
p1 = plot(t, g, 'r--', 'linewidth', 2);
p2 = plot(ts+ds/2, prob, 'bo', 'linewidth', 2);

set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
legend([p1 p2], 'exact', 'simulated');
xlabel('t');
ylabel('g(t)');
filename = sprintf('Plots/LinePicking_test_sim_rect_manhattan.%s', suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('rect-manhattan-line picking density');




% symbolic calculation
syms a b s t f
f  = 4*( (1-t/b)*s + (1/b-1/a+t/(a*b))*s^2/2 - s^3/(3*a*b))/(a*b);
expand(subs(f, s, t))
expand(subs(f, s, a))


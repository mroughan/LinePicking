%
% test_nball_cdf.m, (c) Matthew Roughan, 2012
%
% test the derived form of the n-ball CDF      
%         
%
%


R = 1/2;
R = 3;
dt = R/100;
t = 0:dt:2*R;

n = 4;
p = (n+1)/2;
q = 1/2;

% PDF 
x = 1 - t.^2 / (4*R^2);
g = n * t.^(n-1) .* betainc(x,p,q) / R^n;
figure(1)
hold off
plot(t, g, 'b-');
g2 = LinePickingPDF(t, 2, [n,R]);
hold on
plot(t, g2, 'r--');

% CDF
Gd = cumsum(g)*dt;
figure(2)
hold off
plot(t, Gd, 'b-');

G = 2^n * ( (t/(2*R)).^n .* betainc(x,p,q) ...
	    + betainc(1-x,q+n/2,p) * beta(q+n/2,p)/beta(p,q) ...
	  );
hold on
plot(t, G, 'r--');
G2 = LinePickingCDF(t, 2, [n,R]);
plot(t, G2, 'g:', 'linewidth', 3);


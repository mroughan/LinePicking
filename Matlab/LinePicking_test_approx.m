%         
% Test the approximation results for the hyperball in particular         
%
%
clear;
R = 1;
N = 100;
mode = 2; % hyperball
parameters = [1,R];
s = LinePickingSupport(mode, parameters);
dt = diff(s)/N;
t = s(1):dt:s(2);

for n=1:5
  figure(n)
  hold off
  plot(0,0)
  hold on
  
  [g1] = LinePickingPDF(t, 2, [n, R]);

  c1 = +1;
  c2 = +1 / beta(1/2,(n+1)/2);
  c3 = (1/4) * ...
       ( ...
	   (n+1)/2 - beta(1.5,1)/beta(n/2+1,1) ...
	) / beta(1/2,(n+1)/2)
  a1 = + (n*c1*t.^(n-1)/R^(n));
  a2 = - (n*c2*t.^(n)  /R^(n+1));
  a3 = + (n*c3*t.^(n+2)/R^(n+3));
  
  p1 = plot(t, g1, 'linewidth', 2);
  p2 = plot(t, a1, 'r--', 'linewidth', 2);
  p3 = plot(t, a1+a2, 'g-.', 'linewidth', 2);
  p4 = plot(t, a1+a2+a3, 'm:', 'linewidth', 4);

  set(gca, 'linewidth', 2);
  set(gca, 'fontsize', 16);
  legend([p1 p2 p3 p4], sprintf('exact',n), ...
	 '1 term approx.', '2 term approx.', '3 term approx.', ...
	 'Location', 'NorthWest');
  set(gca,'ylim', [0, 2]);
  xlabel('t');
  ylabel('g_n(t)');
  title(sprintf('%dD ball', n));
  print('-depsc', sprintf('Plots/LinePicking_test_approx_ball_%1d.eps', n));

  
  % NB: 2nd order lies below, and 3rd order lies above for all plotted cases
  %       could prove they provide bounds
end



%         
% Test the approximation results for the hyperball in particular         
%
%
clear;
dt = 0.01;
t = 0:dt:2.0;
R = 1;

for n=1:5
  figure(n)
  hold off
  plot(0,0)
  hold on
  
  [g1] = LinePickingPDF(t, 2, [n, R]);

  a1 = + (n*t.^(n-1)/R^(n));
  a2 = - (n*t.^(n)  /R^(n+1))  / beta(1/2,(n+1)/2);
  a3 = + (n*t.^(n+1)/R^(n+2)) * (1/4) * ( ...
      (n+1)/2 - beta(1.5,1)/beta(n/2+1,1) ...
      );
  
  p1 = plot(t, g1, 'linewidth', 2);
  p2 = plot(t, a1, 'r--', 'linewidth', 2);
  p3 = plot(t, a1+a2, 'g-.', 'linewidth', 2);
  p4 = plot(t, a1+a2+a3, 'm:', 'linewidth', 4);

  set(gca, 'linewidth', 2);
  set(gca, 'fontsize', 16);
  legend([p1 p2 p3 p4], sprintf('%d ball-line picking',n), ...
	 '1st order approximation', '2nd order approximation', '3rd order approximation');
  set(gca,'ylim', [0, 2]);
  xlabel('t');
  ylabel('g_n(t)');
  print('-depsc', sprintf('Plots/LinePicking_test_approx_ball_%1d.eps', n));

end



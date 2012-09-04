%
% test_hypersphere.m PDF against simulations
%
%         
%
%
N = 40;
M = 1000000;

%
% 2-sphere picking
%
problem = 11;
R = 1;
parameters = [3, R]; % parameter[0] is dimension of the embedding space
s = LinePickingSupport(problem, parameters);
ds = diff(s)/N;
t = s(1):ds:s(2);
g = LinePickingPDF(t, problem, parameters);
means(problem+1) = LinePickingMean(problem, parameters)
vars(problem+1) = LinePickingVar(problem, parameters)
name(problem+1) = {LinePickingProblemLookup(problem)};

seed = 1;
parameters1 = parameters;
parameters1(1) = parameters1(1)+1;
d = LinePickingSimDistances(M, problem, parameters1, seed);
n = histc(d, t);
prob = (n/length(d)) / ds;
est_means(problem+1) = mean(d)
est_var(problem+1) = var(d)

figure(problem+1)
hold off
p1 = plot(0,0);
hold on
p1 = plot(t, g, 'r--', 'linewidth', 2);
p2 = plot(t+ds/2, prob, 'bo', 'linewidth', 2);
set(gca, 'linewidth', 2);
set(gca, 'fontsize', 16);
legend([p1 p2], 'exact', 'simulated', 'Location', 'NorthWest');
xlabel('t');
ylabel('g(t)');
filename = sprintf('Plots/LinePicking_test_sim_2sphere.%s', suffix);
print(device,filename);
fprintf('printed to %s\n', filename);
title('2-sphere-line picking density');

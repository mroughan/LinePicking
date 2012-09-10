library("LinePicking")

context("Check numerical integration of pdf's")
tmp <- LinePickingAllProblems(print=FALSE)
for (i in 1:length(tmp)){
  problem <- i - 1  
  parameters<-as.numeric(tmp[[i]]$parameters)
  support <- LinePickingSupport(problem=problem,parameters=parameters)
  num.int <- integrate(f=LinePickingPDF,
                       lower=support[1],upper=support[2],
                       problem=problem,parameters=parameters)
  expect_that(num.int$value,equals(1,tolerance=1e-5))
}

context("Check means and variances")

for (i in 1:length(tmp)){
  problem <- i - 1  
  parameters<- tmp[[i]]$parameters
  support <- LinePickingSupport(problem=problem,parameters=parameters)
  sim.mean <- mean(LinePickingSimDistances(N=10000,problem=problem,
                                           parameters=parameters,seed=5644))
  sim <- LinePickingSimDistances(N=10000,problem=problem,
                                           parameters=parameters,seed=5644)
  sim.mean <- mean(sim)
  sim.var <- var(sim)
  analytic.mean <- LinePickingMean(problem=problem,parameters=parameters)
  analytic.var <- LinePickingVar(problem=problem,parameters=parameters)
  expect_that(sim.mean,equals(analytic.mean,tolerance=0.1))
  expect_that(sim.var,equals(analytic.var,tolerance=0.1))
  print(analytic.var)
}
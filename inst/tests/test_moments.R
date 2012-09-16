library("LinePicking")

context("Check LinePicking means and variances")

test_that("Simulation mean equals LinePickingMean", {
  tmp <- LinePickingAllProblems(print=FALSE)
  problems <- sapply(tmp,function(x)x$problem)
  N <- 10000
  for (i in problems){
    index <- which(problems==i)
    parameters<-as.numeric(tmp[[index]]$parameters)
    LP.mean <- LinePickingMean(problem=i,parameters=parameters)
    sim.mean <- mean(LinePickingSimDistances(N,problem=i,
                                             parameters=parameters,
                                             seed=1121))
    expect_that(LP.mean,equals(sim.mean,tolerance=0.01))
  }
})

test_that("Simulation var equals LinePickingVar", {
  tmp <- LinePickingAllProblems(print=FALSE)
  problems <- sapply(tmp,function(x)x$problem)
  N <- 100000
  for (i in problems){
    index <- which(problems==i)
    parameters<-as.numeric(tmp[[index]]$parameters)
    LP.var <- LinePickingVar(problem=i,parameters=parameters)
    sim.var <- var(LinePickingSimDistances(N,problem=i,
                                           parameters=parameters,seed=1121))
    expect_that(LP.var,equals(sim.var,tolerance=0.01))
  }
})
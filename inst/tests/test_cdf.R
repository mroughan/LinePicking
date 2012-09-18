library("LinePicking")

context("Check LinePicking CDF")

test_that("CDF less than lower support is 0", {
  epi <- 1
  tmp <- LinePicking::LinePickingAllProblems(print=FALSE)
  problems <- sapply(tmp,function(x)x$problem)
  for (i in problems){
    index <- which(problems==i)
    parameters<-as.numeric(tmp[[index]]$parameters)
    support <- LinePickingSupport(problem=i,parameters=parameters)
    cdf.lower <- LinePickingCDF(t=support[1]-epi,problem=i,
                                parameters=parameters)
    expect_that(cdf.lower,equals(0))
  }
})

test_that("CDF greater than upper support is 1", {
  epi <- 0.1
  tmp <- LinePickingAllProblems(print=FALSE)
  problems <- sapply(tmp,function(x)x$problem)
  for (i in problems){
    index <- which(problems==i)
    parameters<-as.numeric(tmp[[index]]$parameters)
    support <- LinePickingSupport(problem=i,parameters=parameters)
    cdf.lower <- LinePickingCDF(t=support[2]+epi,problem=i,
                                parameters=parameters)
    expect_that(cdf.lower,equals(1))
  }
})

test_that("Numerical cdf is equal to cdf", {
  tmp <- LinePickingAllProblems(print=FALSE)
  problems <- sapply(tmp,function(x)x$problem)
  for (i in problems){
    index <- which(problems==i)
    parameters<-as.numeric(tmp[[index]]$parameters)
    support <- LinePickingSupport(problem=i,parameters=parameters)
    t <- seq(support[1],support[2],l=10)
    analytic.cdf <- LinePickingCDF(t=t,problem=i,
                                parameters=parameters)
    num.cdf <- GetNumCDF(problem=i,parameters=parameters,t=t)
    diff <- sum((analytic.cdf - num.cdf)^2)
    expect_that(diff, equals(1,tol=10-5))
  }
})
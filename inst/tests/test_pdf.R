library("LinePicking")

context("Check LinePicking pdf")

test_that("pdfs numerically integrate to one over support", {
  tmp <- LinePickingAllProblems(print=FALSE)
  problems <- sapply(tmp,function(x)x$problem)
  for (i in problems){
    index <- which(problems==i)
    parameters<-as.numeric(tmp[[index]]$parameters)
    support <- LinePickingSupport(problem=i,parameters=parameters)
    num.int <- integrate(f=LinePickingPDF,
                         lower=support[1],upper=support[2],
                         problem=i,parameters=parameters)
    expect_that(num.int$value,equals(1,tolerance=1e-4))
  }
})

test_that("pdf >= 0 over support",{
    tmp <- LinePickingAllProblems(print=FALSE)
    N <- 100
    problems <- sapply(tmp,function(x)x$problem)
    for (i in problems){
      index <- which(problems==i)
      parameters<-as.numeric(tmp[[index]]$parameters)
      support <- LinePickingSupport(problem=i,parameters=parameters)
      t <- seq(support[1],support[2],length=N)
      pdf <- LinePickingPDF(t=t,problem=i,parameters=parameters)
      negatives <- sum(na.omit(pdf)<0)
      expect_that(negatives, equals(0))
      }
})


test_that("pdfs compared to simulated data", {
  tmp <- LinePickingAllProblems(print=FALSE)
  N <- 10000
  problems <- sapply(tmp,function(x)x$problem)
  for (i in problems){
    index <- which(problems==i)
    parameters<-as.numeric(tmp[[index]]$parameters)
    support <- LinePickingSupport(problem=i,parameters=parameters)
    t <- seq(support[1],support[2],length=100)
    sim.data <- LinePickingSimDistances(N=N,
                                        problem=i,
                                        parameters=parameters,
                                        seed=1023)
#     TODO change to quantiles
    obs <- table(cut(sim.data,breaks=t))
    expected <- LinePickingCDF(t=t,problem=i,parameters=parameters)
    expected <- diff(expected)
    expected <- expected / sum(expected)
    expect_that(chisq.test(obs,p=expected)$p.value > 0.05, is_true())
    if(chisq.test(obs,p=expected)$p.value <= 0.05){
      print(i)
      print(chisq.test(obs,p=expected))
      data <- rbind(prop.table(obs),expected)
      print(data)
    }
  }
})

# TODO add check that cdf >=0
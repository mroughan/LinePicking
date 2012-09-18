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
  N <- 100000
  problems <- sapply(tmp,function(x)x$problem)
  p <- seq(0,1,by=0.1)
  for (i in problems){
    index <- which(problems==i)
    parameters<-as.numeric(tmp[[index]]$parameters)
    sim.data <- LinePickingSimDistances(N=N,
                                        problem=i,
                                        parameters=parameters,
                                        seed=1023)
    cuts <- LinePickingInverseCDF(t=p,problem=i,parameters=parameters)
    obs <- table(cut(x=sim.data,breaks=cuts))
    expected <- diff(p)
    chi.pvalue <- chisq.test(obs,p=expected)$p.value
    if(chi.pvalue <= 0.05){
      print(tmp[[index]])
      print(chisq.test(obs,p=expected))
      hist(sim.data,freq=FALSE)
      x <- LinePickingSupport(problem=i,parameters=parameters)
      x <- seq(x[1],x[2],l=100)
      lines(x,LinePickingPDF(t=x,problem=i,parameters=parameters))
    }
    expect_that(chisq.test(obs,p=expected)$p.value > 0.05, is_true())
  }
})

# TODO add check that cdf >=0
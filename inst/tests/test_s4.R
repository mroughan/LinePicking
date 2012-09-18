library("LinePicking")

context("Check LinePicking objects")

test_that("Objects can be printed and plotted", {
  tmp <- LinePickingAllProblems(print=FALSE)
  problems <- sapply(tmp,function(x)x$problem)
  for (i in problems){
    index <- which(problems==i)
    parameters<-as.numeric(tmp[[index]]$parameters)
    LP <- CreateLinePicking(problem=i,parameters=parameters)
    plot(LP)
    plot(LP,dist='CDF')
  }
})

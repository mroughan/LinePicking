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
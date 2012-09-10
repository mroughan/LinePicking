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

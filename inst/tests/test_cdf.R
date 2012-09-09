library("LinePicking")

context("Nothing as yet: TODO")
tmp <- LinePickingAllProblems()
for (i in 1:length(tmp)){
 problem <- i -1  
 parameters<-as.numeric(tmp[[i]]$parameters)
 support <- LinePickingSupport(problem=problem,parameters=parameters)
 print(support)
 pdf <- function(x) LinePickingPDF(x, problem, parameters)
 curve(pdf, support[[1]], support[[2]], n = 101, add = TRUE, type = "l")
}
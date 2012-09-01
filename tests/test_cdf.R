library("LinePicking")
problem <- 11
para <- c(4,5)
integrate(LinePickingPDF,
          lower=LinePickingSupport(problem=problem,para=para)[1],
          upper=LinePickingSupport(problem=problem,para=para)[2],
          problem=problem, para=para)


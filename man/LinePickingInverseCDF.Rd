\name{LinePickingInverseCDF}
\alias{LinePickingInverseCDF}
\title{Get inverse cdf for distance between two random points}
\usage{
  LinePickingInverseCDF(t, problem = 0, parameters,
    trace = FALSE)
}
\description{
  Get inverse cdf for distance between two random points
}
\note{
  September 17 2012
}
\examples{
t <- seq(0,1,l=1000)
y <- InverseLinePickingCDF(t=t,problem=0,para=1)
plot(t,y,type='l')
}
\author{
  Eric Parsonage
}


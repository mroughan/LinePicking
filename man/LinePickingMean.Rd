\name{LinePickingMean}
\alias{LinePickingMean}
\title{Get expected value for given problem and parameters}
\usage{
  LinePickingMean(problem = 0, parameters)
}
\arguments{
  \item{problem}{see \code{\link{LinePickingPDF}}}

  \item{parameters}{the parameter necessary to describe the
  space given by problem.}
}
\value{
  expected value
}
\description{
  For a given problem and parameters gives the expected
  value
}
\note{
  August 25 2012
}
\examples{
LinePickingMean(problem=0,parameters=10)
}
\author{
  Eric Parsonage, Matt Roughan, Jono Tuke
}


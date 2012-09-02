\name{LinePickingVar}
\alias{LinePickingVar}
\title{Get variance for given problem and parameters}
\usage{
  LinePickingVar(problem = 0, parameters)
}
\arguments{
  \item{problem}{see \code{\link{LinePickingPDF}}}

  \item{parameters}{the parameter necessary to describe the
  space given by problem.}
}
\value{
  variance
}
\description{
  For a given problem and parameters gives the variance
}
\note{
  August 25 2012
}
\examples{
LinePickingVar(problem=0,parameters=10)
}
\author{
  Eric Parsonage, Matt Roughan, Jono Tuke
}


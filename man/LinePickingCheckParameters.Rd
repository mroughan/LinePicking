\name{LinePickingCheckParameters}
\alias{LinePickingCheckParameters}
\title{Check that a problem and a set of parameters are valid}
\usage{
  LinePickingCheckParameters(problem = 0, parameters)
}
\arguments{
  \item{problem}{see \code{\link{LinePickingPDF}}}

  \item{parameters}{numeric vector of parameter describing
  problem}
}
\value{
  exit code \itemize{ \item 0: parameters are valid \item
  1: unsupported problem \item 2: parameters out of range.
  \item 3: not enough parameters were entered. \item 4:
  other error. }
}
\description{
  Problems are integers describing possible geometries for
  the line picking problem. This function takes a problem
  and a parameter vector and checks if valid
}
\note{
  August 25 2012
}
\examples{
LinePickingCheckParameters(problem=0, parameters=c(10))
LinePickingCheckParameters(problem=99,parameters=c(10))
LinePickingCheckParameters(problem=0, parameters=c(1,2))
LinePickingCheckParameters(problem=3, parameters=c(1))
}
\author{
  Eric Parsonage, Matt Roughan, Jono Tuke
}


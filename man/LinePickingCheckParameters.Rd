\name{LinePickingCheckParameters}
\alias{LinePickingCheckParameters}
\title{Check that a mode and a set of parameters are valid}
\usage{
  LinePickingCheckParameters(mode = 0, parameters)
}
\arguments{
  \item{mode}{see \code{\link{LinePickingPDF}}}

  \item{parameters}{numeric vector of parameter describing
  mode}
}
\value{
  exit code \itemize{ \item 0: parameters are valid \item
  1: unsupported mode \item 2: parameters out of range.
  \item 3: not enough parameters were entered. \item 4:
  other error. }
}
\description{
  Modes are integers describing possible geometries for the
  line picking problem. This function takes a mode and a
  parameter vector and checks if valid
}
\note{
  August 25 2012
}
\examples{
LinePickingCheckParameters(mode=0, parameters=c(10))
LinePickingCheckParameters(mode=99,parameters=c(10))
LinePickingCheckParameters(mode=0, parameters=c(1,2))
LinePickingCheckParameters(mode=3, parameters=c(1))
}
\author{
  Eric Parsonage, Matt Roughan, Jono Tuke
}


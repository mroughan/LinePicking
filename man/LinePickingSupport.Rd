\name{LinePickingSupport}
\alias{LinePickingSupport}
\title{Returns support for pdf for given problem and parameters}
\usage{
  LinePickingSupport(problem = 0, parameters)
}
\arguments{
  \item{problem}{see \code{\link{LinePickingPDF}}}

  \item{parameters}{the parameter necessary to describe the
  space given by problem.}
}
\value{
  min and max values of support
}
\description{
  Given a problem see \link{LinePickingPDF} and parameters
  gives the range distance t such that the pdf is non-zero
}
\note{
  August 25 2012
}
\examples{
LinePickingSupport(problem=0,parameters=10)
}
\author{
  Eric Parsonage, Matt Roughan, Jono Tuke
}


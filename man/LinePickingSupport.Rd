\name{LinePickingSupport}
\alias{LinePickingSupport}
\title{Returns support for pdf for given mode and parameters}
\usage{
  LinePickingSupport(mode = 0, parameters)
}
\arguments{
  \item{mode}{see \code{\link{LinePickingPDF}}}

  \item{parameters}{the parameter necessary to describe the
  space given by mode.}
}
\value{
  min and max values of support
}
\description{
  Given a mode see \link{LinePickingPDF} and parameters
  gives the range distance t such that the pdf is non-zero
}
\note{
  August 25 2012
}
\examples{
LinePickingSupport(mode=0,parameters=10)
}
\author{
  Eric Parsonage, Matt Roughan, Jono Tuke
}


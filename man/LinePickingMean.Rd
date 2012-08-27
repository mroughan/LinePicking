\name{LinePickingMean}
\alias{LinePickingMean}
\title{Get expected value for given mode and parameters}
\usage{
  LinePickingMean(mode = 0, para)
}
\arguments{
  \item{mode}{see \code{\link{LinePickingPDF}}}

  \item{para}{the parameter necessary to describe the space
  given by mode.}
}
\value{
  expected value
}
\description{
  For a given mode and parameters gives the expected value
}
\note{
  August 25 2012
}
\examples{
LinePickingMean(mode=0,para=10)
}
\author{
  Eric Parsonage, Matt Roughan, Jono Tuke
}


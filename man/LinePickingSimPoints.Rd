\name{LinePickingSimPoints}
\alias{LinePickingSimPoints}
\title{Get simulated points on region}
\usage{
  LinePickingSimPoints(NPoints, problem, parameters, seed)
}
\arguments{
  \item{NPoints}{the number of points to generate.}

  \item{problem}{see \code{\link{LinePickingPDF}}.}

  \item{parameters}{numeric vector of parameters describing
  problem.}

  \item{seed}{a seed for the random number generator}
}
\value{
  vector of N points.
}
\description{
  Give the number of points required and the shape (square,
  disk, ...) and parameters defining the shape, and a seed
  for the random number generator this function will return
  a list of points.
}
\note{
  September 9 2012
}
\examples{
t <- LinePickingSimDistances(10, 0 , list(1), 67)
}
\author{
  Eric Parsonage
}


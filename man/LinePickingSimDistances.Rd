\name{LinePickingSimDistances}
\alias{LinePickingSimDistances}
\title{Get simulated distances between two random points}
\usage{
  LinePickingSimDistances(N, problem, parameters, seed)
}
\arguments{
  \item{N}{the number of distances to generate.}

  \item{problem}{see \code{\link{LinePickingPDF}}.}

  \item{parameters}{numeric vector of parameter describing
  problem.}

  \item{seed}{a seed for the random number generator}
}
\value{
  vector of N distances.
}
\description{
  Give the number of distances required
}
\details{
  and the shape (square, disk, ...) and parameters defining
  the shape, and a seed for the random number generator
  this function will return a list of distances.
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


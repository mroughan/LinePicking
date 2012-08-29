\name{LinePickingPDF}
\alias{LinePickingPDF}
\title{Get pdf for distance between two random points}
\usage{
  LinePickingPDF(t, problem = 0, para)
}
\arguments{
  \item{t}{vector of points to calculate pdf for.}

  \item{problem}{\itemize{ \item 0 Square, with side length
  parameters[0] \item 1 Disk, with radius parameters[0]
  \item 2 Hyper-ball, dimension parameters[0], radius
  parameters[1] \item 3 Rectangle, side lengths
  parameters[0], parameters[1] \item 4 Line, length
  parameters[0] \item 5 Cube, side length parameters[0]
  \item 6 Sphere, with radius parameters[0] \item 7
  SphereGeodesic, with radius parameters[0] \item 8
  PrismGeodesic, TBA }}

  \item{para}{the parameter necessary to describe the space
  given by problem.}
}
\value{
  vector of probability density function values for each
  element in t.
}
\description{
  Give a shape (square, disk, ...) and parameters defining
  the shape, this function will give a the probability
  density function for the distances between two Poisson
  distributed points in the space.
}
\note{
  August 25 2012
}
\examples{
t <- seq(0,1,l=1000)
y <- LinePickingPDF(t=t,problem=0,para=1)
plot(t,y,type='l')
}
\author{
  Eric Parsonage, Matt Roughan, Jono Tuke
}


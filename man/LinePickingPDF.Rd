\name{LinePickingPDF}
\alias{LinePickingPDF}
\title{Get pdf for distance between two random points}
\usage{
  LinePickingPDF(t, mode = 0, para)
}
\arguments{
  \item{t}{vector of points to calculate pdf for.}

  \item{mode}{\itemize{ \item 0 square, with side length
  parameters[0] \item 1 disk, with radius parameters[0]
  \item 2 hyper-ball, dimension parameters[0], radius
  parameters[1] \item 3 rectangle, side lengths
  parameters[0], parameters[1] \item 4 line, length
  parameters[0] \item 5 cube, side length parameters[0] }}

  \item{para}{the parameter necessary to describe the space
  given by mode.}
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
  August 17 2012
}
\examples{
t <- seq(0,1,l=1000)
y <- LinePickingPDF(t=t,mode=0,para=1)
plot(t,y,type='l')
}
\author{
  Matt Roughan, Jono Tuke
}


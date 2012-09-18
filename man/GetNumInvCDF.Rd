\name{GetNumInvCDF}
\alias{GetNumInvCDF}
\title{Gets numerical inverse CDF}
\usage{
  GetNumInvCDF(problem, parameters, t)
}
\arguments{
  \item{problem}{see \link{LinePickingCDF}}

  \item{parameters}{}

  \item{t}{probabilities}
}
\value{
  points x such that P(X <= x)=t
}
\description{
  For the cases where c code does not return an inverse
  CDF. This uses uniroot to find an approximation.
}
\note{
  September 18 2012
}
\author{
  Eric Parsonage, Matt Roughan, Jono Tuke
}
\keyword{internal}


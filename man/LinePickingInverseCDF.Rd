\name{LinePickingInverseCDF}
\alias{LinePickingInverseCDF}
\title{Get inverse CDF for LinePicking problems}
\usage{
  LinePickingInverseCDF(t, problem = 0, parameters,
    trace = FALSE)
}
\arguments{
  \item{t}{number between 0 and 1, can also be a vector}

  \item{problem}{see \link{LinePickingCDF}}

  \item{parameters}{values to describe the problem}

  \item{trace}{boolean, if true gives some extra info.
  Default is false}
}
\value{
  points x
}
\description{
  Takes a point, t, between 0 and 1 and returns point x
  such that P(X <= x) = t
}
\note{
  September 18 2012
}
\examples{
t <- seq(0,1,by=0.1)
LinePickingInverseCDF(t = t, problem = 0,parameters=1)
}
\author{
  Eric Parsonage, Matt Roughan, Jono Tuke
}


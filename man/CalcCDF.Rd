\name{CalcCDF}
\alias{CalcCDF}
\title{Calculates the cdf for a given distance and \code{linepicking} object}
\arguments{
  \item{x}{A \code{linepicking} object}

  \item{t}{a distance}
}
\value{
  cumulative density function
}
\description{
  Given a \code{linepicking} object and a distance t
  returns the cumulative density function
}
\examples{
tmp <- CreateLinePicking(mode=0,para=10)
CalcCDF(tmp,t=5)
}
\author{
  Eric Parsonage, Matt Roughan, Jono Tuke
}


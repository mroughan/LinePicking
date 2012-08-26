\name{linepicking-class}
\alias{linepicking-class}
\title{Create a class for LinePicking}
\value{
  an object of class \code{linepicking}
}
\description{
  Easy way to play with linepicking. Define and space and
  this object has most of the features of the space
}
\section{Slots}{
  \itemize{ \item Mode: type of space \item parameters:
  parameters to define space \item support: range of values
  pdf if non-zero \item t: points in support for pdf and
  cdf \item pdf: probability density function for values t
  \item cdf: cumulative density function for values t \item
  mean: expected value of pdf \item var: variance of pdf }
}
\examples{
getSlots("linepicking")
}
\author{
  Eric Parsonage, Matt Roughan, Jono Tuke
}


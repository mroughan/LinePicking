\name{CalcPDF}
\alias{CalcPDF}
\title{Calculates the pdf for a given distance and \code{linepicking} object}
\arguments{
  \item{x}{A \code{linepicking} object}

  \item{t}{a distance}
}
\value{
  probability density function
}
\description{
  Given a \code{linepicking} object and a distance t
  returns the probability density function
}
\examples{
tmp <- CreateLinePicking(mode=0,para=10)
pdf(tmp,t=5)
}
\author{
  Eric Parsonage, Matt Roughan, Jono Tuke
}


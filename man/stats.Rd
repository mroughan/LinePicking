\name{stats}
\alias{stats}
\title{Gets mean and variance for \code{linepicking} object}
\arguments{
  \item{x}{A \code{linepicking} object}
}
\value{
  value from slot
}
\description{
  Returns the mean and variance for \code{linepicking}
  object rather than using @
}
\examples{
tmp <- CreateLinePicking(mode=0,para=10)
stats(tmp)
}
\author{
  Eric Parsonage, Matt Roughan, Jono Tuke
}


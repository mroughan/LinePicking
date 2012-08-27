\name{para}
\alias{para}
\title{Get para for \code{linepicking} object}
\arguments{
  \item{x}{A \code{linepicking} object}
}
\value{
  value from slot
}
\description{
  Returns the para for \code{linepicking} object rather
  than using @
}
\examples{
tmp <- CreateLinePicking(mode=0,para=10)
para(tmp)
}
\author{
  Eric Parsonage, Matt Roughan, Jono Tuke
}


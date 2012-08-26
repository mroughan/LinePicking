\name{space}
\alias{space}
\title{Get mode for \code{linepicking} object}
\arguments{
  \item{x}{A \code{linepicking} object}
}
\value{
  value from slot
}
\description{
  Returns the mode for \code{linepicking} object rather
  than using @
}
\examples{
tmp <- CreateLinePicking(mode=0,para=10)
space(tmp)
}
\author{
  Eric Parsonage, Matt Roughan, Jono Tuke
}


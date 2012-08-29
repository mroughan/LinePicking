\name{support}
\alias{support}
\title{Get support for \code{linepicking} object}
\arguments{
  \item{x}{A \code{linepicking} object}
}
\value{
  value from slot
}
\description{
  Returns the support for \code{linepicking} object rather
  than using @
}
\examples{
tmp <- CreateLinePicking(problem=0,para=10)
support(tmp)
para(tmp)
}
\author{
  Eric Parsonage, Matt Roughan, Jono Tuke
}


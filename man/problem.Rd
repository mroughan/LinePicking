\name{problem}
\alias{problem}
\title{Get problem for \code{linepicking} object}
\arguments{
  \item{x}{A \code{linepicking} object}
}
\value{
  value from slot
}
\description{
  Returns the problem for \code{linepicking} object rather
  than using @
}
\examples{
tmp <- CreateLinePicking(problem=0,para=10)
problem(tmp)
}
\author{
  Eric Parsonage, Matt Roughan, Jono Tuke
}


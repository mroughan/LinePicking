\docType{methods}
\name{accessors}
\alias{accessors}
\alias{para}
\alias{para,linepicking-method}
\alias{problem}
\alias{problem,linepicking-method}
\alias{stats}
\alias{stats,linepicking-method}
\alias{support}
\alias{support,linepicking-method}
\title{Get slot values for \code{linepicking} object}
\arguments{
  \item{x}{A \code{linepicking} object}
}
\value{
  value from slot
}
\description{
  Returns the slot value for \code{linepicking} object
  rather than using @
}
\examples{
tmp <- CreateLinePicking(problem=0,para=10)
problem(tmp)
}
\author{
  Eric Parsonage, Matt Roughan, Jono Tuke
}


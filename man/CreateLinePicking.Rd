\name{CreateLinePicking}
\alias{CreateLinePicking}
\title{Creates a linepicking object from problem and parameters}
\usage{
  CreateLinePicking(problem, para, n = 1000)
}
\arguments{
  \item{problem}{see \code{\link{LinePickingPDF}}}

  \item{para}{parameters for problem.}

  \item{n}{number of points for plots.}
}
\value{
  an instance of \code{linepicking} class
}
\description{
  Problemss are integers describing possible geometries for
  the line picking problem. Each has appropraite parameters
}
\note{
  August 25 2012
}
\examples{
tmp <- CreateLinePicking(problem=0,para=10)
print(tmp)
}
\author{
  Matt Roughan, Jono Tuke, Eric Parsonage
}


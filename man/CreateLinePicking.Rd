\name{CreateLinePicking}
\alias{CreateLinePicking}
\title{Creates a linepicking object from mode and parameters}
\usage{
  CreateLinePicking(mode, para, n = 1000)
}
\arguments{
  \item{mode}{see \code{\link{LinePickingPDF}}}

  \item{para}{parameters for mode.}

  \item{n}{number of points for plots.}
}
\value{
  an instance of \code{linepicking} class
}
\description{
  Modes are integers describing possible geometries for the
  line picking problem. Each has appropraite parameters
}
\note{
  August 25 2012
}
\examples{
tmp <- CreateLinePicking(mode=0,para=10)
print(tmp)
}
\author{
  Matt Roughan, Jono Tuke, Eric Parsonage
}


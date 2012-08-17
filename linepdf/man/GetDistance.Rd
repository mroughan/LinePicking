\name{GetDistance}
\alias{GetDistance}
\title{Get pdf for distance between two random points}
\usage{
  GetDistance(t, mode = 0, para)
}
\arguments{
  \item{t}{vector of points to calculate pdf for.}

  \item{mode}{\itemize{ \item 0 square, with side length
  parameters[0] \item 1 disk, with radius parameters[0]
  \item 2 hyper-ball, dimension parameters[0], radius
  parameters[1] \item 3 rectangle, side lengths
  parameters[0], parameters[1] \item 4 line, length
  parameters[0] \item 5 cube, side length parameters[0] }}
}
\value{
  data
}
\description{
  to do sum of them
}
\note{
  August 17 2012
}
\examples{
GetDistance(t=1:100,mode=0,para=50)
}
\author{
  Matt Roughan, Jono Tuke
}


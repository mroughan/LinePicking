\name{LinePickingAllProblems}
\alias{LinePickingAllProblems}
\title{Gets list of all problems}
\usage{
  LinePickingAllProblems(short_tab = TRUE)
}
\arguments{
  \item{short_tab}{boolean is false gives description as
  well.}
}
\value{
  Data frame with \itemize{ \item problems: problem number
  see \code{\link{LinePickingPDF}} \item names: list of the
  problem names \item description: brief description of
  each space }
}
\description{
  Problems are integers describing possible geometries for
  the line picking problem. This function prints all
  possible problems.
}
\note{
  August 25 2012
}
\examples{
LinePickingAllProblems()
}
\author{
  Eric Parsonage, Matt Roughan, Jono Tuke
}


#' Creates a linepicking object from problem and parameters
#'
#' Problemss are integers describing possible geometries for the line picking
#' problem. Each has appropraite parameters
#' 
#' @param problem see \code{\link{LinePickingPDF}}
#' @param para parameters for problem.
#' @param n number of points for plots.
#' @return an instance of \code{linepicking} class
#' @author Matt Roughan, Jono Tuke, Eric Parsonage
#' @export
#' @useDynLib LinePicking
#' @note August 25 2012
#' @examples
#' tmp <- CreateLinePicking(problem=0,para=10)
#' print(tmp)
CreateLinePicking <- function(problem, para, n=1000){
  # Check possible space
  exit <- LinePickingCheckParameters(problem=problem, parameters=para)
  if(exit == 1){
    cat("Possible problems are :\n")
    LinePickingAllProblems()
    return(NULL)
  }
  if(exit > 1) return(NULL)
  support <- LinePickingSupport(problem=problem,parameters=para)
  t <- seq(support[1],support[2],length=n)
  new("linepicking", 
      problem = problem, 
      parameters = para,
      support = LinePickingSupport(problem=problem,parameters=para), 
      t = t,
      pdf = LinePickingPDF(t=t,problem=problem,para=para),
      cdf = LinePickingCDF(t=t,problem=problem,para=para),
      mean = LinePickingMean(problem=problem,para=para),
      var = LinePickingVar(problem=problem,para=para))
}

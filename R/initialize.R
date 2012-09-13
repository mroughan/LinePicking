#' Creates a linepicking object from problem and parameters
#'
#' Problemss are integers describing possible geometries for the line picking
#' problem. Each has appropraite parameters
#' 
#' @param problem see \code{\link{LinePickingPDF}}
#' @param parameters parameters for problem.
#' @param n number of points for plots.
#' @return an instance of \code{linepicking} class
#' @author Matt Roughan, Jono Tuke, Eric Parsonage
#' @export
#' @useDynLib LinePicking
#' @note August 25 2012
#' @examples
#' tmp <- CreateLinePicking(problem=0,parameters=10)
#' print(tmp)
CreateLinePicking <- function(problem, parameters, n=1000){
  # Check possible space
  exit <- LinePickingCheckParameters(problem=problem, 
                                     parameters=parameters)
  if(exit == 1){
    cat("Possible problems are :\n")
    print(LinePickingAllProblems())
    return(NULL)
  }
  if(exit > 1) return(NULL)
  support <- LinePickingSupport(problem=problem,parameters=parameters)
  t <- seq(support[1],support[2],length=n)
  new("linepicking", 
      problem = problem, 
      parameters = parameters,
      support = LinePickingSupport(problem=problem,
                                   parameters=parameters), 
      t = t,
      pdf = LinePickingPDF(t=t,problem=problem,parameters=parameters),
      cdf = LinePickingCDF(t=t,problem=problem,parameters=parameters),
      mean = LinePickingMean(problem=problem,parameters=parameters),
      var = LinePickingVar(problem=problem,parameters=parameters))
}

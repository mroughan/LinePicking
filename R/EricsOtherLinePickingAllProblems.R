#' Gets list of all problems
#'
#' Problems are integers describing possible geometries for the line picking
#' problem. This function prints all implemented problems.
#' 
#' @param short_tab boolean is false gives description as well.
#' @return Data frame with information on each problem
#' @author Eric Parsonage
#' @export
#' @useDynLib LinePicking
#' @note September 8 2012
#' @examples
#' EricsOtherLinePickingAllProblems()

  
EricsOtherLinePickingAllProblems <- function()
{    
    tmp <- .Call("EricsOtherLinePickingAllProblems")
    return(tmp)
}

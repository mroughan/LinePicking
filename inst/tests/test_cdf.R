library("LinePicking")

NumCDF <- function(problem, parameters){
  tmp <- LinePickingSupport(problem=problem,parameters=parameters)
  int.num <- integrate(LinePickingPDF,
                       lower=tmp[1],upper=tmp[2],
                       problem=problem,parameters=parameters)$value
  return(int.num)
}
test_that("PDF integrate to 1 over support",{
  expect_that(NumCDF(1,5), equals(1, tolerance=1e-5))
  expect_that(NumCDF(2,c(5,5)), equals(1, tolerance=1e-5))
  expect_that(NumCDF(3,c(5,5)), equals(1, tolerance=1e-5))
  expect_that(NumCDF(4,5), equals(1, tolerance=1e-5))
  expect_that(NumCDF(5,5), equals(1, tolerance=1e-5))
  expect_that(NumCDF(6,5), equals(1, tolerance=1e-5))
  expect_that(NumCDF(7,5), equals(1, tolerance=1e-5))
  expect_that(NumCDF(8,c(5,5)), equals(1, tolerance=1e-5))
  expect_that(NumCDF(9,c(5,5)), equals(1, tolerance=1e-5))
  expect_that(NumCDF(10,c(5,5)), equals(1, tolerance=1e-5))
})

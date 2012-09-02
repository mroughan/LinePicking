###########
# Functions
###########
ComparePlots <- function(t=seq(-0.1,2.1,0.001),
                         model1,model2){
  g1 <- LinePickingPDF(t,problem=model1[1],parameters=model1[-1])
  g2 <- LinePickingPDF(t,problem=model2[1],parameters=model2[-1])
  plot(t,g1,lty=1,type='l')
  lines(t,g2,lty=2)
  names <- c(LinePickingProblemLookup(model1[1])$name,
             LinePickingProblemLookup(model2[1])$name)
  legend("topright",legend=names,lty=1:2)
}
##########
# Analysis
##########
library("LinePicking")
ComparePlots(model1=c(2,1,1),model2=c(4,2))
ComparePlots(model1=c(1,1),model2=c(2,2,1))
ComparePlots(model1=c(0,1),model2=c(3,1,1))
ComparePlots(model1=c(4,1),model2=c(3,0.00001,1))

plot(0,0,xlim=c(-0.1,2.1),ylim=c(0,2),
     type='n',ylab='f(t)',xlab='t')
for( n in 1:8){
  t <- seq(-0.1,2.1,by=0.001)
  g <- LinePickingPDF(t,2,c(n,1))
  lines(t,g,col=n)
}
legend("topright",legend=paste("n =",1:8),col=1:8,lty=1)

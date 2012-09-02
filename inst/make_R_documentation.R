library('devtools')
pkg <- as.package("~/Dropbox/LinePicking/")
document(pkg)

install(pkg)
check(pkg)
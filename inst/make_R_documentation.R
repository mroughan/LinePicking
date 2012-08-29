library('devtools')
pkg <- as.package("~/Dropbox/LinePicking/")
document(pkg)

install(pkg)
Sys.setenv(http_proxy="http://a1078881:bob4ever+2@www-proxy.adelaide.edu.au:8080")
check(pkg)
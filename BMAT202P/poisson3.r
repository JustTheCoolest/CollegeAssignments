probability <- function(x, n, func) {
    P <- 0
    if(n == 0) {
        return(1)
    }
    for(i in x:0) {
        P <- P + func(i) * probability(x-i, n-1, func)
    }
    return(P)
}

L <- 2
print(probability(4, 3, function(x) {dpois(x, L)}))
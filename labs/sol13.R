
n <- 500
m <- 784

A <- matrix(rnorm(m*n), m, n)
B <- matrix(rnorm(m*n), m+5, n)

dist <- function(a, b){
  sum((a-b)^2)
}

# scalar compute
pdist1 <- function(A, B){
  D <- matrix(0, dim(A)[1], dim(B)[1])
  for (i in 1:dim(A)[1]){ 
    for (j in 1:dim(B)[1]){ 
      s <- 0
      for (k in 1:dim(A)[2]){ 
        s <- s + (A[i, k] - B[j, k])^2
      }
      D[i, j] <- s
    }
  }
  return(D)
}

start <- Sys.time() #timing

D1 <- pdist1(A, B)

end <- Sys.time()
print(end - start)

# vectorising the computation of D_ij
pdist2 <- function(A,B){
  D <- matrix(0, dim(A)[1], dim(B)[1])
  for (i in 1:dim(A)[1]){ 
    for (j in 1:dim(B)[1]){ 
      D[i, j] <- dist(A[i,], B[j,])
    }
  }
  return(D)
}

start <- Sys.time() #timing

D2 <- pdist2(A, B)

end <- Sys.time()
print(end - start)

# vectorising the computation of D_i, the i-th row of D
pdist3 <- function(A,B){
  D <- matrix(0, dim(A)[1], dim(B)[1])
  for (i in 1:dim(A)[1]){ 
    D[i,] <- sum(A[i, ]^2) - 2*A[i,]%*%t(B) + rowSums(B^2)
  }
  return(D)
}

start <- Sys.time() #timing

D3 <- pdist3(A, B)

end <- Sys.time()
print(end - start)

# fully vectorised version
pdist4 <- function(A,B){
  o1 <- matrix(1, 1, dim(B)[1])
  o2 <- matrix(1, dim(A)[1], 1)
  
  D <- rowSums(A^2) %*% o1 - 2 * A%*%t(B) + o2%*%t(rowSums(B^2))
  return(D)
}

start <- Sys.time() #timing

D4 <- pdist4(A, B)

end <- Sys.time()
print(end - start)



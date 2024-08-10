# Set seed for reproducibility
set.seed(123)

# Generate the data
data <- data.frame(
    X = rnorm(20, mean=20, sd=2),
    Y = rnorm(20, mean=40, sd=2),
    Z = rnorm(20, mean=60, sd=4)
)

# (a) Find the regression line of Z on X and Y
model1 <- lm(Z ~ X + Y, data=data)
print(summary(model1))

# (b) Find the regression lines of Z on X and Z on Y
model2 <- lm(Z ~ X, data=data)
model3 <- lm(Z ~ Y, data=data)
print(summary(model2))
print(summary(model3))

# (c) Find the multiple regression of Z on X and Y
# This is the same as (a)
print(summary(model1))

# (d) Find the correlation between X, Y, and Z
correlation <- cor(data)
# Ignore the diagonal elements by setting them to 0
diag(correlation) <- 0
# Find the indices of the maximum correlation
indices <- which(abs(correlation) == max(abs(correlation)), arr.ind = TRUE)
# Get the names of the most correlated columns
most_correlated <- rownames(indices)
print(paste("The most correlated columns are: ", paste(most_correlated, collapse = " and ")))

# (e) Plot the distribution function of the three normal distributions
par(mfrow=c(3,1))  # set up the graphics
hist(data$X, freq=FALSE, main="Distribution of X", xlab="X")
lines(density(data$X))
hist(data$Y, freq=FALSE, main="Distribution of Y", xlab="Y")
lines(density(data$Y))
hist(data$Z, freq=FALSE, main="Distribution of Z", xlab="Z")
lines(density(data$Z))

# (f) Find the median of the three distributions
medians <- sapply(data, median)
print(medians)
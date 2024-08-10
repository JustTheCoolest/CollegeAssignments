# Set seed for reproducibility
set.seed(123)

# Generate the data
data <- data.frame(
    X = rbinom(15, size=50, prob=0.4),
    Y = rpois(15, lambda=20),
    Z = rbinom(15, size=40, prob=0.5)
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

# Calculate the correlation matrix
correlation <- cor(data)

# Ignore the diagonal elements by setting them to 0
diag(correlation) <- 0

# Find the indices of the maximum correlation
indices <- which(abs(correlation) == max(abs(correlation)), arr.ind = TRUE)

# Get the names of the most correlated columns
most_correlated <- rownames(indices)

print(paste("The most correlated columns are: ", paste(most_correlated, collapse = " and ")))

# (e) Find first, second and third quartile values of X,Y,Z
quartiles <- sapply(data, quantile)
print(quartiles)
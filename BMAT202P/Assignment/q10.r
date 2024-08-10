# Define the observed frequencies
x <- 0:6
f_observed <- c(314, 335, 204, 86, 29, 9, 3)

# Calculate the mean of the Poisson distribution
lambda <- sum(x * f_observed) / sum(f_observed)

# Calculate the expected frequencies
f_expected <- dpois(x, lambda) * sum(f_observed)

# Create a data frame with the values of x, observed frequencies, and expected frequencies
df <- data.frame(x = x, f_observed = f_observed, f_expected = round(f_expected))
print(df)
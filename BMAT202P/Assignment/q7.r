# (a) Test the claim that mosquito nets were installed in 70% of the flats
# The null hypothesis is p = 0.7 and the alternative hypothesis is p != 0.7
# This is a binomial test
mosquito_nets <- binom.test(8, 15, p = 0.7, alternative = "two.sided", conf.level = 0.90)
print(mosquito_nets)

# Define the sample statistics
sample_mean <- 27463
population_mean <- 28000
sample_sd <- 1348
n <- 40

# Calculate the z-score
z <- (sample_mean - population_mean) / (sample_sd / sqrt(n))

# Calculate the p-value
p_value <- pnorm(z)

# Print the z-score and p-value
print(paste("z-score: ", z))
print(paste("p-value: ", p_value))

# Define the significance level
alpha <- 0.01

# Determine whether the hypothesis is accepted or not
if (p_value < alpha) {
    print("The guarantee can not be accepted.")
} else {
    print("The guarantee can be accepted.")
}
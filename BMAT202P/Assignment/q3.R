# Define the parameters
n <- 60  # number of trials (questions)
p <- 0.25  # probability of success (guessing a question correctly)

# (i) Probability that he guesses exactly 20 questions correctly
prob_20 <- dbinom(20, size=n, prob=p)
print(paste("Probability of guessing exactly 20 questions correctly: ", prob_20))

# (ii) Probability that he guesses no answers correctly
prob_0 <- dbinom(0, size=n, prob=p)
print(paste("Probability of guessing no answers correctly: ", prob_0))

# (iii) Probability that he guesses at least 10 questions correctly
# This is 1 - P(guessing less than 10 questions correctly)
prob_10_or_more <- 1 - pbinom(9, size=n, prob=p)
print(paste("Probability of guessing at least 10 questions correctly: ", prob_10_or_more))

# (iv) Expected number of questions that he will answer correctly
expected <- n * p
print(paste("Expected number of questions answered correctly: ", expected))

# (v) Variance of this probability distribution
variance <- n * p * (1 - p)
print(paste("Variance of the probability distribution: ", variance))

# (vi) Visualize the probability distribution
x <- 0:n
probabilities <- dbinom(x, size=n, prob=p)
plot(x, probabilities, type="h", main="Probability Distribution", xlab="Number of Correct Answers", ylab="Probability")
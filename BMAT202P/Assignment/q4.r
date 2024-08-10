# Define the data
classes <- c(62.5, 67.5, 72.5, 77.5, 82.5, 87.5, 92.5, 97.5)  # midpoints of the classes
frequencies <- c(3, 21, 150, 335, 326, 135, 26, 4)  # frequencies

# Calculate the mean
mean <- weighted.mean(classes, frequencies)
print(paste("Mean: ", mean))

# Calculate the quartiles
data <- rep(classes, frequencies)
quartiles <- quantile(data, probs = c(0.25, 0.5, 0.75))
names(quartiles) <- c("Q1", "Q2", "Q3")
print("Quartiles: ")
print(quartiles)

# Calculate the variance and standard deviation
variance <- var(data)
std_dev <- sd(data)
print(paste("Variance: ", variance))
print(paste("Standard Deviation: ", std_dev))
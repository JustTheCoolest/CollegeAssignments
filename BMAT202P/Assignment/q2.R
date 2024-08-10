# Define the data
scores <- c(60, 62, 65, 70, 72, 48, 53, 73, 65, 82)
productivity <- c(68, 60, 62, 80, 85, 40, 52, 62, 60, 81)

# Calculate the correlation coefficient
correlation <- cor(scores, productivity)
print(paste("Correlation coefficient: ", correlation))

# Fit linear regression models
model1 <- lm(scores ~ productivity)
print(model1);
model2 <- lm(productivity ~ scores)
print(model2);

# Calculate the slope and intercept for the second model in the scores vs. productivity space
intercept2 <- coef(model2)[1] / coef(model2)[2]
slope2 <- 1 / coef(model2)[2]

# Plot the regression lines
plot(scores, productivity, main="Regression Lines", xlab="Scores", ylab="Productivity")
abline(model1, col="blue")
abline(intercept2, slope2, col="red") # use the calculated intercept and slope

# Estimate the productivity corresponding to the score of 50
predicted_productivity <- predict(model2, newdata=data.frame(scores=50))
print(paste("Estimated productivity for score 50: ", predicted_productivity))
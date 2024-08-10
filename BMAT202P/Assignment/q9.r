# Define the parameters of the normal distribution
mean_life <- 1000
sd_life <- 200
n_lamps <- 10000

# (i) Find how many lamps might be expected to fail in the first 800 burning hours
p_fail_800 <- pnorm(800, mean = mean_life, sd = sd_life)
n_fail_800 <- p_fail_800 * n_lamps
print(paste("Expected number of lamps to fail in the first 800 hours: ", round(n_fail_800)))

# (ii) Find how many lamps might be expected to fail between 800 and 1200 burning hours
p_fail_800_1200 <- pnorm(1200, mean = mean_life, sd = sd_life) - p_fail_800
n_fail_800_1200 <- p_fail_800_1200 * n_lamps
print(paste("Expected number of lamps to fail between 800 and 1200 hours: ", round(n_fail_800_1200)))

# (iii) Find after how many burning hours 10% of the lamps are expected to fail
burn_hours_10_fail <- qnorm(0.10, mean = mean_life, sd = sd_life)
print(paste("Burning hours after which 10% of the lamps are expected to fail: ", round(burn_hours_10_fail)))

# (iv) Find after how many burning hours 10% of the lamps are expected to be still burning
burn_hours_10_burning <- qnorm(0.90, mean = mean_life, sd = sd_life)
print(paste("Burning hours after which 10% of the lamps are expected to be still burning: ", round(burn_hours_10_burning)))
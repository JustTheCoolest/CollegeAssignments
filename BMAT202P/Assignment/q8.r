# (a) Test the claim that less number of undergraduates are smokers than the postgraduates
# The null hypothesis is p1 >= p2 and the alternative hypothesis is p1 < p2
# This is a two-proportion z-test
smokers <- prop.test(c(248, 180), c(1600, 900), alternative = "less")
print(smokers)

# (b) Test the claim that men are taller than women
# The null hypothesis is mu1 <= mu2 and the alternative hypothesis is mu1 > mu2
# This is a two-sample t-test
heights <- data.frame(
    gender = c(rep("Male", 1600), rep("Female", 6400)),
    height = c(rnorm(1600, mean=172, sd=6.3), rnorm(6400, mean=170, sd=6.3))
)
t_test_01 <- t.test(height ~ gender, data = heights, alternative = "greater", conf.level = 0.99)
t_test_05 <- t.test(height ~ gender, data = heights, alternative = "greater", conf.level = 0.95)
print(t_test_01)
print(t_test_05)
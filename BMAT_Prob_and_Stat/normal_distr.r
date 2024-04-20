m = 20;
s = 5;

print(paste("Less than 15 minutes: ", pnorm(15, 20, 5)));
print(paste("More than 25 minutes: ", 1-pnorm(25, 20, 5)));
print(paste("Between 15 and 25 minutes: ", pnorm(25, 20, 5)-pnorm(15, 20, 5)));

x = 0:50
plot(x, dnorm(x, m, s));

print(data.frame(x, dnorm(x, m, s)));



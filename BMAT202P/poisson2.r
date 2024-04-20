L = 0.06;

print(paste("No defect: ", dpois(0, L)));
print(paste("Two or less defects: ", ppois(2, L)));
print(paste("One or more defects ", 1 - dpois(0, L)));

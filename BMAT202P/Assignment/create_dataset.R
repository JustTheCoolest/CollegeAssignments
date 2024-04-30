# Configuration
marks_columns_range = 3:5
subjects = c('A', 'B', 'C')

library(readxl)
students = read_excel("/home/goto/Projects/CollegeAssignments/BMAT202P/Assignment/students.xlsx")

print("Original dataset")
students[,marks_columns_range] = as.data.frame(lapply(students[, marks_columns_range], as.numeric))
print(students)

n = nrow(students)
# students <- students[, c(ncol(students), 1:(ncol(students)-1))]
# students_ID <- 1:n
# students <- data.frame(students_ID, students)
students$ID = seq(n)
print("Dataset with ID")
print(students)

students$Gender = factor(students$Gender, labels = c("Male", "Female"), levels=c('M', 'F'))
print("Dataset after making Gender as factor data")
print(students)

for(i in marks_columns_range){
    marks = students[,i]
    marks <- unlist(marks)
    subject <- colnames(students)[i]
    print(paste("Subject: ", subject))
    print(paste("-- Mean: ", mean(marks)))
    print(paste("-- SD: ", sd(marks)))
}

quantiles = c(0.25, 0.5, 0.75, 0.99)
quantiles_table = data.frame(
    Quantile = c("First Quartile", "Second Quartile", "Third Quartile", "99 Percentile")
)
for(i in marks_columns_range){
    marks = students[,i]
    marks <- unlist(marks)
    percentiles = quantile(marks, quantiles)
    # percentiles = unname(percentiles)
    subject_name = colnames(students)[i]
    quantiles_table[[subject_name]] = percentiles
}

print(quantiles_table)

marks_columns_range_in_quantiles_table = 2:(2+length(marks_columns_range)-1)

for(subject in subjects){
    cut_off = quantiles_table[[4, subject]]; # [[]]
    print("Students who are in the top 1% in subject: ", subject)
    # Possible imporvement: Sort by rank
    # print([student for student in students where students[subject] >= cut_off])
    student_indices = which(students[[subject]] >= cut_off) # >= or >
    for(i in student_indices){
        print(students[[i, "Name"]])
    }
    print();
}

max_coorealtion = -2;
max_correlation_subjects; #declare
for (subject1 in subjects){
    for (subject2 in subjects){ # rewrite inner loop to continue after outer loop
        if(subject1 == subject2){
            continue;
        }
        correlation = rank.corr(subject1, subject2)
        if(correlation > max_coorealtion){
            max_coorealtion = correlation
            max_correlation_subjects = c(subject1, subject2)
        }
        # Bug : Equal correlations are not handled
    }
}
print(paste("The performance is most similar between ", max_correlation_subjects, " with correlation value: ", max_coorealtion))


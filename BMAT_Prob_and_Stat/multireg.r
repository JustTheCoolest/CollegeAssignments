x1 = c(4, 6, 7, 9, 13, 15);
x2 = c(15, 12, 8, 6, 4, 3);
x3 = c(30, 24, 20, 14, 10, 4);
regmodel = lm(x1~x2+x3);
scatterplot3d::scatterplot3d(x1, x2, x3)$plane3d(regmodel);
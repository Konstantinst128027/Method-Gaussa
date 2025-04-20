/* Berezkin Konstantin Evgenievich
./tests st128027@student.spbu.ru*/
#include <gtest/gtest.h>
#include "function.h"
// Матрица выраженная
TEST(checking_matrix_Test, MGTest_1) {
    Eigen::MatrixXd AC(2, 3);
    AC << 1, 2, 3,
          2.5, 5, 6;

    EXPECT_EQ(checking_matrix(AC), false);
}
// Матрица невыраженная
TEST(checking_matrix_Test, MGTest_2) {
    Eigen::MatrixXd AC(2, 3);
    AC << 1, 2, 3,
          2, 5, 6;

    EXPECT_EQ(checking_matrix(AC), true);
}
// проверка checking_gm (правильно ли решает)
TEST(checking_gm_Test, MGTest_3) {
    Eigen::MatrixXd AC(2, 3);
    AC << 1, 2, 3,
          2, 5, 6;
          
    Eigen::MatrixXd A = AC.leftCols(AC.cols() - 1); 
    Eigen::MatrixXd C = AC.rightCols(1); 
    Eigen::MatrixXd B(AC.rows(), 1);
    gaussian_method(AC, B);
   
    EXPECT_EQ(checking_gm(A, B, C), true);
}
// проверка checking_gm (правильно ли решает)
TEST(checking_gm_Test, MGTest_4) {
    Eigen::MatrixXd AC(2, 3);
    AC << 1, 2, 3,
          2, 5, 6;
    
    Eigen::MatrixXd A = AC.leftCols(AC.cols() - 1);
    Eigen::MatrixXd C = AC.rightCols(1);    
    Eigen::MatrixXd B(AC.rows(), 1);
    B << 2,
         1;
   
    EXPECT_EQ(checking_gm(A, B, C), false);
}
// 3 x 3
TEST(gaussian_method_Test, MGTest_5) {
    Eigen::MatrixXd AC(3, 4);
    AC << 4, 2, -1, 1,
          5, 3, -2, 2,
          3, 2, -3, 0;
    
    Eigen::MatrixXd A = AC.leftCols(AC.cols() - 1);  
    Eigen::MatrixXd C = AC.rightCols(1);   
    Eigen::MatrixXd B(AC.rows(), 1);
    gaussian_method(AC, B);
   
    EXPECT_EQ(checking_gm(A, B, C), true);
}
// 4 x 4
TEST(gaussian_method_Test, MGTest_6) {
    Eigen::MatrixXd AC(4, 5);
    AC << 2, 5, 4, 1, 20,
          1, 3, 2, 1, 11,
          2, 10, 9, 7, 40,
          3, 8, 9, 2, 37; 
     
    Eigen::MatrixXd A = AC.leftCols(AC.cols() - 1);    
    Eigen::MatrixXd C = AC.rightCols(1); 
    Eigen::MatrixXd B(AC.rows(), 1);
    gaussian_method(AC, B);
   
    EXPECT_EQ(checking_gm(A, B, C), true);
}


/* Berezkin Konstantin Evgenievich
./tests st128027@student.spbu.ru*/
#include <gtest/gtest.h>
#include "function.h"
// 10 x 10
TEST(GM_Test, MGTest_random_1) {
    Eigen::MatrixXd AC = generetion_random_AC(10, 100);
    Eigen::MatrixXd A = AC.leftCols(AC.cols() - 1);
    
    while (!checking_matrix(AC)) {
        AC = generetion_random_AC(10, 100);
    }
       
    Eigen::MatrixXd C = AC.rightCols(1);
    Eigen::MatrixXd B(10, 1);
    gaussian_method(AC, B);
    EXPECT_EQ(checking_gm(A, B, C), true);
}

// 15 x 15
TEST(GM_Test, MGTest_random_2) {
    Eigen::MatrixXd AC = generetion_random_AC(15, 100);
    Eigen::MatrixXd A = AC.leftCols(AC.cols() - 1);
    
    while (!checking_matrix(AC)) {
        AC = generetion_random_AC(10, 100);
    }
       
    Eigen::MatrixXd C = AC.rightCols(1);
    Eigen::MatrixXd B(15, 1);
    gaussian_method(AC, B);
    EXPECT_EQ(checking_gm(A, B, C), true);
}
// 100 x 100
TEST(GM_Test, MGTest_random_3) {
    Eigen::MatrixXd AC = generetion_random_AC(100, 100);
    Eigen::MatrixXd A = AC.leftCols(AC.cols() - 1);
    
    while (!checking_matrix(AC)) {
        AC = generetion_random_AC(100, 100);
    }
       
    Eigen::MatrixXd C = AC.rightCols(1);
    Eigen::MatrixXd B(100, 1);
    gaussian_method(AC, B);
    EXPECT_EQ(checking_gm(A, B, C), true);
}

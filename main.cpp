/* Berezkin Konstantin Evgenievich
./main st128027@student.spbu.ru*/
#include "function.h"

int main() {
    try {
        Eigen::MatrixXd AC = read_csv_in_matrix("AB.csv");
        Eigen::MatrixXd A = AC.leftCols(AC.cols()-1);
        Eigen::MatrixXd C = AC.rightCols(1);
        if (checking_matrix(AC)) {
            Eigen::MatrixXd B(AC.rows(), 1);
            gaussian_method(AC, B);
            if (checking_gm(A, B, C)) {
                std::cout << "all_right" << std::endl;
                std::string result = "result.csv";
                matrix_To_CSV(result, B);
            }
            else {
                std::cout << "the Gauss method solved incorrectly" << std::endl;
            }
        }
        else {
            std::cout << "The determinant of this matrix is = 0 => it is not solved by the Gauss method" << std::endl;
        }
        return 0;
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}

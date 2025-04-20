/* Berezkin Konstantin Evgenievich
./main or ./tests st128027@student.spbu.ru*/
#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <string>
#include <vector>
#include "lazycsv.hpp"
#include <Eigen/Dense>
#include <stdexcept>
#include <cmath>
#include <fstream>
#include <random>

Eigen::MatrixXd read_csv_in_matrix(std::string Name_File);
bool checking_matrix(Eigen::MatrixXd& AC);
void gaussian_method(Eigen::MatrixXd& AC, Eigen::MatrixXd& B);
bool checking_gm(Eigen::MatrixXd& A, Eigen::MatrixXd& B, Eigen::MatrixXd& C);
void matrix_To_CSV(std::string& filename, Eigen::MatrixXd& matrix);
Eigen::MatrixXd generetion_random_AC(int n, double x);
#endif

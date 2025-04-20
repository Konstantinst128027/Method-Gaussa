/* Berezkin Konstantin Evgenievich
./main or ./tests st128027@student.spbu.ru*/
#include "function.h"

Eigen::MatrixXd read_csv_in_matrix(std::string Name_File) {

    std::vector<std::vector<double>> rcsv;
    lazycsv::parser parser{Name_File};
    
    auto header_row = parser.header();
    std::vector<double> header_cell;    
    
    int number_of_row = 0;
    
    for (auto cell : header_row){
        std::string cell_str(cell.raw());
        
        if (!cell_str.empty()) {
            try {
                header_cell.push_back(std::stod(cell_str));
            }
            catch (...) {
                throw std::runtime_error("Невозможно преобразовать " + cell_str + " в число типа double");
            }
        }
    }
    
    if (!header_cell.empty()) {
            number_of_row++;
            rcsv.push_back(header_cell);
    }
    
    for (auto row : parser) {
        std::vector<double> r;
        for (auto cell : row) {
            std::string cell_str(cell.raw());
            
            if (!cell_str.empty()) {
                try {
                    r.push_back(std::stod(cell_str));
                }
                catch (...) {
                    throw std::runtime_error("Невозможно преобразовать " + cell_str + " в число типа double");
                }
            }
            
        }
        
        if (!r.empty()) {
            rcsv.push_back(r);
            number_of_row++;
            
        } 
        
        // Проверка на количество элементов в строке
        if (number_of_row > 1) {
            if (rcsv[number_of_row-1].size() != rcsv[number_of_row-2].size()) {
                throw std::runtime_error("Несовпадение количества столбцов");
            }
        }       
    }
    
    if (rcsv.empty()) {
        throw std::runtime_error("Mатрица пустая");
    }

    size_t rows = rcsv.size();
    size_t cols = rcsv[0].size(); 
    Eigen::MatrixXd matrix(rows, cols);

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            matrix(i, j) = rcsv[i][j];
        }
    }

    return matrix;
}

// Проверка на вырожденность
bool checking_matrix(Eigen::MatrixXd& AC) {
    if (std::abs(AC.leftCols(AC.cols()-1).determinant()) < 1e-10) {
        return false;
    }
    else {
        return true;
    }
}

void gaussian_method(Eigen::MatrixXd& AC, Eigen::MatrixXd& B) {
    
    int n = AC.rows();
    int m = AC.cols();
    
    // Цикл, который приводит матрицу к треугольному виду (после главной диагонали все нули)
    for (int k = 0; k < std::min(n, m); ++k) {
        int max_row = k;
        for (int i = k + 1; i < n; ++i) {
            if (std::abs(AC(i, k)) > std::abs(AC(max_row, k))) {
            max_row = i;
            }
        }
        
        if (max_row != k) {
        AC.row(k).swap(AC.row(max_row));
        }
        
        if (std::abs(AC(k, k)) < 1e-10) // 1 в -10 степени
        {
            continue; // Пропуск, если max элемент в столбце ~0
        }
        
        for (int i = k + 1; i < n; ++i) {
            double factor = AC(i, k) / AC(k, k);
            AC.row(i) -= factor * AC.row(k);
        }
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (std::abs(AC(i, j)) < 1e-10) // 1 в -10 степени
                {
                    AC(i, j) = 0.0;
                }
            }
        }    
    }
        
    // Приведение к нормированному виду (единичному) матрицы А
    for (int k = std::min(n, m) - 1; k >= 0; --k) {
        if (std::abs(AC(k, k)) < 1e-10) { 
            continue;
        }
        AC.row(k) /= AC(k, k);
        
        for (int i = 0; i < k; ++i) {
            AC.row(i) -= AC(i, k) * AC.row(k);
        }
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (std::abs(AC(i, j)) < 1e-10) // 1 в -10 степени
                {
                    AC(i, j) = 0.0;
                }
            }
        }    
    }
    // Формирование матрицы B
    for (int i = 0; i < n; ++i) {
        B(i, 0) = AC(i, m - 1);    
    }
}

bool checking_gm(Eigen::MatrixXd& A, Eigen::MatrixXd& B, Eigen::MatrixXd& C) {
    Eigen::MatrixXd AB_C = A * B - C;
    double summ_all = 0;
    for (int i = 0; i < AB_C.rows(); i++) {
        for (int j = 0; j < AB_C.cols(); j++) {
            summ_all += std::round(AB_C(i,j) * 1000)/1000;
        }
    }
    if (summ_all == 0) {
        return true;
    }
    else {
        return false;
    }
}

void matrix_To_CSV(std::string& filename, Eigen::MatrixXd& matrix) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл " + filename);
    }
    
    for (int i = 0; i < matrix.rows(); ++i) {
        for (int j = 0; j < matrix.cols(); ++j) {
            file << matrix(i, j);
            if (j != matrix.cols() - 1) {
                file << ",";  // Разделитель - запятая
            }
        }
        file << "\n";
    }
    
    file.close();
}

Eigen::MatrixXd generetion_random_AC(int n, double x) // m - диапазон чисел, которые добавляются в матрицу
    {
    // Инициализация генератора случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(-x, x); // Диапазон от -10 до 10
    
    // Создание матрицы
    Eigen::MatrixXd AC(n, n+1);
    
    // Заполнение случайными числами с округлением
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n+1; ++j) {
            // Генерация числа и округление до 2 знаков
            double value = dist(gen);
            value = std::round(value * 100) / 100; // Округление до 2 знаков
            AC(i, j) = value;
        }
    }
    
    return AC;
}


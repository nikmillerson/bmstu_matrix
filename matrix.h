//
// Created by nikit on 26.04.2023.
//

#ifndef MAINCLION_MATRIX_H
#define MAINCLION_MATRIX_H
#include <iostream>
#include <vector>
namespace bmstu {
    template<typename T>
    class matrix {
    public:
        matrix() : data_(1), rows_(1), columns_(1) {
            representation_ = {{&data_[0]}};
        }

        matrix(size_t rows, size_t columns) : data_(rows * columns), rows_(rows), columns_(columns) {
            for (int i = 0; i < rows_; i++) {
                std::vector<T *> vtmp(columns_);
                for (int j = 0; j < columns_; j++) {
                    vtmp[j] = &(data_[i * columns_ + j]);
                }
                representation_.push_back(std::move(vtmp)); // конструктор копирования из даты в репрезентейшн
            }
        }

        matrix(std::initializer_list<T> i_list, size_t rows, size_t columns) : rows_(rows), columns_(columns) {
            if ((rows_ * columns_) == i_list.size()) {
                data_.resize(i_list.size());
                std::move(i_list.begin(), i_list.end(), data_.data());
                for (int i = 0; i < rows_; i++) {
                    std::vector<T *> vtmp(columns_);
                    for (int j = 0; j < columns_; j++) {
                        vtmp[j] = &(data_[i * columns_ + j]);
                    }
                    representation_.push_back(std::move(vtmp));
                }
            } else {
                throw std::logic_error("Rows or/and columns don't match i_list size");
            }    // конструктор копирования из ай_листа в дату, а потом в репрезентейшн
        }

        T &operator()(size_t row, size_t column) { // оператор возврата ссылки на определенный элемент матрицы
            return *representation_[row][column];
        }

        T operator()(size_t row, size_t column) const {  // оператор возврата определенного элемента матрицы
            return *representation_[row][column];
        }

        std::vector<T *> operator[](size_t i) {     // оператор возврата строки из указателей
            return representation_[i];
        }

        std::vector<T> operator[](size_t i) const { // оператор возврата строки из элементов
            std::vector<T> result(columns_);
            for (size_t j = 0; j < columns_; ++j) {
                result[j] = *representation_[i][j];
            }
            return result;
        }

        T det() {
            if (columns_ == rows_) {
                T result = T();
                std::vector<size_t> indexes(columns_);
                int sign = 1;
                for (size_t i = 0; i < columns_; ++i) {
                    indexes[i] = i;
                }
                permute(indexes, indexes.size(), result, sign); // пермут дописать
                return result;
            } else { throw std::logic_error("matrix must be square"); }
        }

        friend std::ostream &operator<<(std::ostream &ovs, const matrix<T> &obj) {
            for (int i = 0; i < obj.rows_; ++i) {
                for (int j = 0; j < obj.columns_; ++j) {
                    ovs << obj(i, j) << ' ';
                }
                ovs << "\r\n";
            }
            return ovs;
        }

        friend matrix<T> operator*(const matrix<T> &l, const matrix<T> &r) {
            if (l.columns_ == r.rows_) {
                matrix result(l.rows_, l.columns_);
                for (int i = 0; i < l.rows_; i++) {
                    for (int j = 0; j < r.columns_; j++) {
                        result(i, j) = 0;
                        for (int k = 0; k < l.columns_; k++) {
                            result(i, j) += (l(i, k) * r(k, j));
                        }
                    }
                }
                return result;
            } else { throw std::logic_error("Rows and columns must match"); }
        }

        friend matrix<T> operator+(const matrix<T> &l, const matrix<T> &r) {
            if ((l.rows_ == r.rows_) && (l.columns_ == r.columns_)) {
                matrix result(l.rows_, l.columns_);
                for (int i = 0; i < l.rows_; i++) {
                    for (int j = 0; j < l.columns_; j++) {
                        result(i, j) = l(i, j) + r(i, j);
                    }
                }
                return result;
            } else { throw std::logic_error("Rows and columns must match"); }
        }

        friend matrix<T> operator-(const matrix<T> &l, const matrix<T> &r) {
            if ((l.rows_ == r.rows_) && (l.columns_ == r.columns_)) {
                matrix result(l.rows_, l.columns_);
                for (int i = 0; i < l.rows_; i++) {
                    for (int j = 0; j < l.columns_; j++) {
                        result(i, j) = l(i, j) - r(i, j);
                    }
                }
                return result;
            } else { throw std::logic_error("Rows and columns must match"); }
        }

        friend matrix<T> operator*(const matrix<T> &l, const T value) {
            matrix result(l.rows_, l.columns_);
            for (int i = 0; i < l.rows_; i++) {
                for (int j = 0; j < l.columns_; j++) {
                    result(i, j) = l(i, j) * value;
                }
            }
            return result;
        }

        void transpose() {
            std::vector<T> tmpdata;
            for (int j = 0; j < columns_; j++) {
                for (int i = 0; i < rows_; i++) {
                    tmpdata.push_back(data_[i * columns_ + j]);
                }
            }

            std::swap(rows_, columns_);
            data_ = std::move(tmpdata);
            representation_.clear();

            for (int i = 0; i < rows_; i++) {
                std::vector<T *> vtmp(columns_);
                for (int j = 0; j < columns_; j++) {
                    vtmp[j] = &(data_[i * columns_ + j]);
                }
                representation_.push_back(std::move(vtmp)); // конструктор копирования из даты в репрезентейшн
            }
        }

        matrix<T> get_minor_matrix(size_t row, size_t column) {
            if (row < rows_ && column < columns_) {
                matrix result(rows_ - 1, columns_ - 1);
                int rownum = 0;
                for (int i = 0; i < rows_; i++) {
                    if (i == row) { continue; }
                    int columnnum = 0;
                    for (int j = 0; j < columns_; j++) {
                        if (j == column) { continue; }
                        result(rownum, columnnum) = *representation_[i][j];
                        columnnum += 1;
                    }
                    rownum += 1;
                }
                return result;
            } else { throw std::out_of_range("Row or/and column of minor > rows or/and columns of initial matrix"); }
        }

        matrix<T> adj() {
            if (rows_ == columns_) {
                matrix<T> result(rows_, columns_);
                int sign = 1;
                for (int i = 0; i < rows_; i++) {
                    for (int j = 0; j < columns_; j++) {
                        result(i, j) = (this->get_minor_matrix(i, j)).det() * sign;
                        sign *= -1;
                    }
                }
                result.transpose();
                return result;
            } else { throw std::logic_error("matrix must be square"); }
        }

        matrix<double> reverse() {
            if ((rows_ == columns_) && (this->det() != 0)) {
                matrix result(rows_, columns_);
                matrix adjugate_matrix = this->adj();
                for (int i = 0; i < rows_; i++) {
                    for (int j = 0; j < columns_; j++) {
                        result(i, j) = adjugate_matrix(i, j) / this->det();
                    }
                }
                return result;
            } else { throw std::logic_error("matrix must be square and det not 0"); }
        }

    private:
        void permute(std::vector<size_t> &arr, size_t pos, T &value, int &sign) {
            if (pos == 1) {
                T tmprow = T(1);
                for (size_t i = 0; i < columns_; ++i) {
                    tmprow *= *representation_[i][arr[i]];
                }
                value += (tmprow * sign);
            } else {
                for (size_t i = 0; i < pos; ++i) {
                    permute(arr, pos - 1, value, sign);
                    if (pos % 2) {
                        std::swap(arr[0], arr[pos - 1]);
                    } else {
                        std::swap(arr[i], arr[pos - 1]);
                        sign *= (-1);
                    }
                }
            }
        }

        std::vector<T> data_;
        std::vector<std::vector<T *>> representation_;
        size_t rows_;
        size_t columns_;

    };
}
#endif //MAINCLION_MATRIX_H


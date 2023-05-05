#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "matrix.h"

using namespace bmstu;
TEST(Constructor, Default){
    matrix<int> test_matrix;
    ASSERT_EQ(test_matrix(0, 0), 0);
}

TEST(Constructor, Parameter){
    matrix<int> test_matrix(3, 6);
    for (int i=0; i<3; i++) {
        for (int j=0; j<6; j++){
            ASSERT_EQ(test_matrix(i,j), 0);
        }
    }
}

TEST(Constructor, i_list){
    matrix<int> test_matrix({1, 2, 3, 4, 5, 6, 7, 8}, 2, 4);
    for (int i=0; i<2; i++) {
        for (int j=0; j<4; j++){
            ASSERT_EQ(test_matrix(i,j), i*4 + j + 1);
        }
    }
}

TEST(Method, GetMinorMatrix){
    matrix<int> big_matrix({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);
    matrix<int> minor_matrix({5, 6, 8, 9}, 2, 2);
    matrix<int> test_matrix = big_matrix.get_minor_matrix(0, 0);
    for (int i=0; i<2; i++) {
        for (int j=0; j<2; j++){
            ASSERT_EQ(test_matrix(i,j), minor_matrix(i,j));
        }
    }
}

TEST(Method, Adjugate){
    matrix<int> begin_matrix({-3, 2, -5, -1, 0, -2, 3, -4, 1}, 3, 3);
    matrix<int> adjugate_matrix({-8, 18, -4, -5, 12, -1, 4, -6, 2}, 3, 3);
    matrix<int> test_matrix = begin_matrix.adj();
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++){
            ASSERT_EQ(test_matrix(i,j), adjugate_matrix(i,j));
        }
    }
}

TEST(Method, Reverse){
    matrix<double> begin_matrix({1, -2, 0, 3, 4, 2, -1, 3, 1}, 3, 3);
    matrix<double> reverse_matrix({-0.25, 0.25, -0.5, -0.625, 0.125, -0.25, 1.625, -0.125, 1.25}, 3, 3);
    matrix<double> test_matrix = begin_matrix.reverse();
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++){
            ASSERT_EQ(test_matrix(i,j), reverse_matrix(i,j));
        }
    }
}
TEST(Method, Determinant){
    matrix<int> begin_matrix({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);
    ASSERT_EQ(begin_matrix.det(), 0);
}

TEST(Method, Transpose){
    matrix<int> test_matrix({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);
    test_matrix.transpose();
    matrix<int> transposed_matrix({1, 4, 7, 2, 5, 8, 3, 6, 9}, 3, 3);
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            ASSERT_EQ(transposed_matrix(i,j), test_matrix(i,j));
        }
    }
}

TEST(Operator, ReturnSpecificElement){
    matrix<int> first_matrix({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3 ,3);
    int correct_element = 5;
    int test_element = first_matrix(1, 1);
    ASSERT_EQ(correct_element, test_element);
}

TEST(Operator, ReturnSpecificRow){
    matrix<int> first_matrix({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3 ,3);
    std::vector<int> correct_row = {1, 2, 3};
    std::vector<int*> test_row = first_matrix[0];
    for (int i=0; i<3; i++){
        ASSERT_EQ(correct_row[i], *test_row[i]);
    }
}

TEST(Operator, OStream){
    matrix<int> begin_matrix({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);
    std::stringstream ss;
    ss << begin_matrix;
    ASSERT_STREQ(ss.str().c_str(), "1 2 3 \r\n4 5 6 \r\n7 8 9 \r\n");
}

TEST(Operator, MatrixMultiplication){
    matrix<int> first_matrix({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3 ,3);
    matrix<int> second_matrix({2, 3, 4, 5, 6, 7, 8, 9, 10}, 3, 3);
    matrix<int> multiplied_matrix({36, 42, 48, 81, 96, 111, 126, 150, 174}, 3 ,3);
    matrix<int> test_matrix = first_matrix * second_matrix;
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            ASSERT_EQ(test_matrix(i,j), multiplied_matrix(i,j));
        }
    }
}

TEST(Operator, Multiplication){
    matrix<int> first_matrix({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3 ,3);
    matrix<int> multiplied_matrix({2, 4, 6, 8, 10, 12, 14, 16, 18}, 3 ,3);
    matrix<int> test_matrix = first_matrix * 2;
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            ASSERT_EQ(test_matrix(i,j), multiplied_matrix(i,j));
        }
    }
}

TEST(Operator, Summ){
    matrix<int> first_matrix({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3 ,3);
    matrix<int> second_matrix({2, 3, 4, 5, 6, 7, 8, 9, 10}, 3, 3);
    matrix<int> summ_matrix({3, 5, 7, 9, 11, 13, 15, 17, 19}, 3, 3);
    matrix<int> test_matrix = first_matrix + second_matrix;
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            ASSERT_EQ(test_matrix(i,j), summ_matrix(i,j));
        }
    }
}

TEST(Operator, Subs){
    matrix<int> first_matrix({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3 ,3);
    matrix<int> second_matrix({10, 13, 24, 45, 56, 87, 98, 999, 1000}, 3, 3);
    matrix<int> subs_matrix({-9, -11, -21, -41, -51, -81, -91, -991, -991 }, 3, 3);
    matrix<int> test_matrix = first_matrix - second_matrix;
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            ASSERT_EQ(test_matrix(i,j), subs_matrix(i,j));
        }
    }
}

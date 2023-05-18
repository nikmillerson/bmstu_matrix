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

    try {
        matrix<int> bad_matrix({1, 2, 3}, 2, 4);
    } catch (std::out_of_range const& error) {
        EXPECT_EQ(error.what(), std::string("Rows or/and columns don't match i_list size"));
    }

    try {
        matrix<char> bad_matrix({'a', 'b', 'c'}, 1, 3);
    } catch (std::logic_error const& error) {
        EXPECT_EQ(error.what(), std::string("Type must be a number"));
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
    try {
        matrix<int> bad_minor_matrix = big_matrix.get_minor_matrix(999, 999);
    } catch (std::out_of_range const& error) {
        ASSERT_EQ(error.what(), std::string("Row or/and column of minor must not be > rows or/and columns of initial matrix"));
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
    matrix<int> another_test_matrix({10, 12, 13, 14}, 2, 2);
    try {
        matrix<int> bad_matrix = another_test_matrix.adj();
    } catch (std::logic_error const& error) {
        EXPECT_EQ(error.what(), std::string("Matrix must be square"));
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
    matrix<double> test_matrix_square_with_det_0({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3 ,3);
    matrix<double> test_matrix_not_square({1, 2, 3, 4}, 2, 2);
    try {
        matrix<double> bad_matrix = test_matrix_square_with_det_0.adj();
    } catch (std::logic_error const& error) {
        EXPECT_EQ(error.what(), std::string("Matrix must be square and det not 0"));
    }
    try {
        matrix<double> another_bad_matrix = test_matrix_not_square.adj();
    } catch (std::logic_error const& error) {
        EXPECT_EQ(error.what(), std::string("Matrix must be square and det not 0"));
    }
}
TEST(Method, Determinant){
    matrix<int> begin_matrix({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);
    ASSERT_EQ(begin_matrix.det(), 0);
    matrix<int> bad_matrix({1, 2, 3, 4, 5, 6}, 2, 3);
    try {
        int bad_determinant = bad_matrix.det();
    } catch(std::logic_error const& error) {
        EXPECT_EQ(error.what(), std::string("Matrix must be square"));
    }
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
    try {
        int bad_element = first_matrix(999, 999);
    } catch (std::out_of_range const& error) {
        EXPECT_EQ(error.what(), std::string("Input row or/and column is out of range"));
    }
}

TEST(Operator, ReturnSpecificRow){
    matrix<int> first_matrix({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3 ,3);
    std::vector<int> correct_row = {1, 2, 3};
    std::vector<int*> test_row = first_matrix[0];
    for (int i=0; i<3; i++){
        ASSERT_EQ(correct_row[i], *test_row[i]);
    }
    try {
        std::vector<int*> bad_row = first_matrix[999];
    } catch (std::out_of_range const& error) {
        EXPECT_EQ(error.what(), std::string("Input row is out of range"));
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

    matrix<int> another_test_matrix = second_matrix * first_matrix;
    matrix<int> another_multiplied_matrix({42, 51, 60, 78, 96, 114, 114, 141, 168}, 3 ,3);
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            ASSERT_EQ(another_test_matrix(i,j), another_multiplied_matrix(i,j));
        }
    }


    matrix<int> bad_matrix({1, 2, 3, 4}, 2, 2);
    try {
        matrix<int> bad_multiplied_matrix = bad_matrix * second_matrix;
    } catch(std::logic_error const& error){
        EXPECT_EQ(error.what(), std::string("Rows and columns must match"));
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
    matrix<int> third_matrix({1, 2, 3, 4}, 2 ,2);
    try {
        matrix<int> bad_matrix = first_matrix + third_matrix;
    } catch (std::logic_error const& error) {
        EXPECT_EQ(error.what(), std::string("Rows and columns must match"));
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
    matrix<int> third_matrix({1, 2, 3, 4}, 2 ,2);
    try {
        matrix<int> bad_matrix = first_matrix - third_matrix;
    } catch (std::logic_error const& error) {
        EXPECT_EQ(error.what(), std::string("Rows and columns must match"));
    }
}

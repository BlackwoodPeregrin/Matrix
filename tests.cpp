#include <gtest/gtest.h>

#include "matrix.hpp"

void setValueMatrix(Matrix<double> *matrix, int value) {
  for (int i = 0; i < matrix->get_rows(); i++)
    for (int j = 0; j < matrix->get_columns(); j++)
      (*matrix)(i, j) = (double)value++;
}

TEST(CheckTest, CheckConstructor1) {
  Matrix<double> matrix(3, 3);
  setValueMatrix(&matrix, 10);

  Matrix<double> result(3, 3);
  setValueMatrix(&result, 10);

  ASSERT_TRUE(matrix == result);
  ASSERT_EQ(result.get_rows(), matrix.get_rows());
  ASSERT_EQ(result.get_columns(), matrix.get_columns());
}

TEST(CheckTest, CheckConstructor2) {
  Matrix<double> matrix(2, 2);
  setValueMatrix(&matrix, 10);

  Matrix<double> result(2, 2);
  result(0, 0) = 10.0;
  result(0, 1) = 11.0;
  result(1, 0) = 12.0;
  result(1, 1) = 13.0;

  ASSERT_TRUE(matrix == result);
  ASSERT_EQ(result.get_rows(), matrix.get_rows());
  ASSERT_EQ(result.get_columns(), matrix.get_columns());
}

TEST(CheckTest, CheckConstructor3) {
  Matrix<double> matrix(2, 2);
  setValueMatrix(&matrix, 10);

  Matrix<double> my_result(matrix);

  Matrix<double> result(2, 2);
  result(0, 0) = 10.0;
  result(0, 1) = 11.0;
  result(1, 0) = 12.0;
  result(1, 1) = 13.0;

  ASSERT_TRUE(my_result == result);
  ASSERT_EQ(my_result.get_rows(), result.get_rows());
  ASSERT_EQ(my_result.get_columns(), result.get_columns());
}

TEST(CheckTest, CheckConstructor4) {
  Matrix<double> matrix(2, 2);
  setValueMatrix(&matrix, 1);

  Matrix<double> my_result(std::move(matrix));

  Matrix<double> result(2, 2);
  result(0, 0) = 1.0;
  result(0, 1) = 2.0;
  result(1, 0) = 3.0;
  result(1, 1) = 4.0;

  ASSERT_EQ(matrix.get_rows(), 0);
  ASSERT_EQ(matrix.get_columns(), 0);
  ASSERT_TRUE(my_result == result);
  ASSERT_EQ(my_result.get_rows(), result.get_rows());
  ASSERT_EQ(my_result.get_columns(), result.get_columns());
}

TEST(CheckTest, CheckEq) {
  Matrix<double> matrixFirst(2, 2);
  Matrix<double> matrixSecond(2, 2);
  setValueMatrix(&matrixFirst, 1);
  setValueMatrix(&matrixSecond, 1);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      ASSERT_EQ(matrixFirst(i, j), matrixSecond(i, j));
    }
  }
}

TEST(CheckTest, SumMatrix) {
  Matrix<double> matrixFirst(2, 2);
  Matrix<double> matrixSecond(2, 2);
  setValueMatrix(&matrixFirst, 1);
  setValueMatrix(&matrixSecond, 1);
  matrixFirst.sum_matrix(matrixSecond);

  Matrix<double> result(2, 2);
  result(0, 0) = 2.0;
  result(0, 1) = 4.0;
  result(1, 0) = 6.0;
  result(1, 1) = 8.0;

  ASSERT_TRUE(matrixFirst == result);
}

TEST(CheckTest, SubMatrix) {
  Matrix<double> matrixFirst(2, 2);
  Matrix<double> matrixSecond(2, 2);
  setValueMatrix(&matrixFirst, 1);
  setValueMatrix(&matrixSecond, 1);
  matrixFirst.sub_matrix(matrixSecond);

  Matrix<double> result(2, 2);
  result(0, 0) = 0.0;
  result(0, 1) = 0.0;
  result(1, 0) = 0.0;
  result(1, 1) = 0.0;

  ASSERT_TRUE(matrixFirst == result);
}

TEST(CheckTest, MultNumMatrix) {
  Matrix<double> matrixFirst(2, 2);
  setValueMatrix(&matrixFirst, 1);

  matrixFirst.mul_number(12.0);

  Matrix<double> result(2, 2);
  result(0, 0) = 12.0;
  result(0, 1) = 24.0;
  result(1, 0) = 36.0;
  result(1, 1) = 48.0;

  ASSERT_TRUE(matrixFirst == result);
}

TEST(CheckTest, MultMatrix) {
  Matrix<double> a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;
  Matrix<double> b(2, 3);
  b(0, 0) = 1;
  b(0, 1) = 1;
  b(0, 2) = 1;
  b(1, 0) = 1;
  b(1, 1) = 1;
  b(1, 2) = 1;
  a.mul_matrix(b);
  Matrix<double> result(2, 3);
  result(0, 0) = 3.0;
  result(0, 1) = 3.0;
  result(0, 2) = 3.0;
  result(1, 0) = 7.0;
  result(1, 1) = 7.0;
  result(1, 2) = 7.0;

  ASSERT_TRUE(a == result);
}

TEST(CheckTest, Transpose) {
  Matrix<double> a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  Matrix<double> b(a.Transpose());

  Matrix<double> result(2, 2);
  result(0, 0) = 1.0;
  result(0, 1) = 3.0;
  result(1, 0) = 2.0;
  result(1, 1) = 4.0;

  ASSERT_TRUE(b == result);
}

TEST(CheckTest, OperatorEquel) {
  Matrix<double> a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  Matrix<double> b(3, 3);
  b = a;

  Matrix<double> result(2, 2);
  result(0, 0) = 1.0;
  result(0, 1) = 2.0;
  result(1, 0) = 3.0;
  result(1, 1) = 4.0;

  ASSERT_TRUE(b == result);
}

TEST(CheckTest, OperatorPlus) {
  Matrix<double> a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;
  Matrix<double> b(a);
  Matrix<double> myRes(1, 1);
  myRes = a + b;
  Matrix<double> result(2, 2);
  result(0, 0) = 2.0;
  result(0, 1) = 4.0;
  result(1, 0) = 6.0;
  result(1, 1) = 8.0;

  ASSERT_TRUE(myRes == result);
}

TEST(CheckTest, OperatorMinus) {
  Matrix<double> a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;
  Matrix<double> b(a);
  Matrix<double> myRes(2, 2);
  myRes = a - b;
  Matrix<double> result(2, 2);
  result(0, 0) = 0.0;
  result(0, 1) = 0.0;
  result(1, 0) = 0.0;
  result(1, 1) = 0.0;

  ASSERT_TRUE(myRes == result);
}

TEST(CheckTest, OperatorMultNumber) {
  Matrix<double> a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;
  a.mul_number(12.0);
  Matrix<double> result(2, 2);
  result(0, 0) = 12.0;
  result(0, 1) = 24.0;
  result(1, 0) = 36.0;
  result(1, 1) = 48.0;

  ASSERT_TRUE(a == result);
}

TEST(CheckTest, OperatorMult) {
  Matrix<double> a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;
  Matrix<double> b(2, 3);
  b(0, 0) = 1;
  b(0, 1) = 1;
  b(0, 2) = 1;
  b(1, 0) = 1;
  b(1, 1) = 1;
  b(1, 2) = 1;
  Matrix<double> myRes(a * b);
  Matrix<double> result(2, 3);
  result(0, 0) = 3.0;
  result(0, 1) = 3.0;
  result(0, 2) = 3.0;
  result(1, 0) = 7.0;
  result(1, 1) = 7.0;
  result(1, 2) = 7.0;
  ASSERT_TRUE(myRes == result);
}

TEST(CheckTest, OperatorPlusEquel) {
  Matrix<double> a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;
  Matrix<double> b(2, 2);
  b(0, 0) = 1;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 4;
  a += b;
  Matrix<double> result(2, 2);
  result(0, 0) = 2.0;
  result(0, 1) = 4.0;
  result(1, 0) = 6.0;
  result(1, 1) = 8.0;
  ASSERT_TRUE(a == result);
}

TEST(CheckTest, OperatorMinusEquel) {
  Matrix<double> a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;
  Matrix<double> b(2, 2);
  b(0, 0) = 1;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 4;
  a -= b;
  Matrix<double> result(2, 2);
  result(0, 0) = 0.0;
  result(0, 1) = 0.0;
  result(1, 0) = 0.0;
  result(1, 1) = 0.0;
  ASSERT_TRUE(a == result);
}

TEST(CheckTest, OperatorMultNumberEquel) {
  Matrix<double> a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;
  a *= 12.0;
  Matrix<double> result(2, 2);
  result(0, 0) = 12.0;
  result(0, 1) = 24.0;
  result(1, 0) = 36.0;
  result(1, 1) = 48.0;
  ASSERT_TRUE(a == result);
}

TEST(CheckTest, OperatorMultrEquel) {
  Matrix<double> a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;
  Matrix<double> b(2, 3);
  b(0, 0) = 1;
  b(0, 1) = 1;
  b(0, 2) = 1;
  b(1, 0) = 1;
  b(1, 1) = 1;
  b(1, 2) = 1;
  a *= b;
  Matrix<double> result(2, 3);
  result(0, 0) = 3.0;
  result(0, 1) = 3.0;
  result(0, 2) = 3.0;
  result(1, 0) = 7.0;
  result(1, 1) = 7.0;
  result(1, 2) = 7.0;
  ASSERT_TRUE(a == result);
}

TEST(CheckTest, OperatorBreckets) {
  Matrix<double> a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  ASSERT_EQ(a(0, 0), 1);
  ASSERT_EQ(a(0, 1), 2);
  ASSERT_EQ(a(1, 0), 3);
  ASSERT_EQ(a(1, 1), 4);
  a(1, 1) = 9;
  ASSERT_EQ(a(1, 1), 9);
}

TEST(CheckTest, constructor) {
  Matrix<double> a(3, 3);
  ASSERT_EQ(a(0, 0), 0);
  ASSERT_EQ(a(0, 1), 0);
  ASSERT_EQ(a(0, 2), 0);
  ASSERT_EQ(a(1, 0), 0);
  ASSERT_EQ(a(1, 1), 0);
  ASSERT_EQ(a(1, 2), 0);
  ASSERT_EQ(a(2, 0), 0);
  ASSERT_EQ(a(2, 1), 0);
  ASSERT_EQ(a(2, 2), 0);
  Matrix<double> b(2, 2);
  ASSERT_EQ(b.get_rows(), 2);
  ASSERT_EQ(b.get_columns(), 2);
  ASSERT_EQ(b(0, 0), 0);
  ASSERT_EQ(b(0, 1), 0);
  ASSERT_EQ(b(1, 0), 0);
  ASSERT_EQ(b(1, 1), 0);
  Matrix<double> c(b);
  ASSERT_EQ(c.get_rows(), 2);
  ASSERT_EQ(c.get_columns(), 2);
  ASSERT_EQ(c(0, 0), 0);
  ASSERT_EQ(c(0, 1), 0);
  ASSERT_EQ(c(1, 0), 0);
  ASSERT_EQ(c(1, 1), 0);
  Matrix<double> d(std::move(b));
  ASSERT_EQ(d.get_rows(), 2);
  ASSERT_EQ(d.get_columns(), 2);
  ASSERT_EQ(d(0, 0), 0);
  ASSERT_EQ(d(0, 1), 0);
  ASSERT_EQ(d(1, 0), 0);
  ASSERT_EQ(d(1, 1), 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_matrix.h"
void init_matrix(matrix_t *A, double number) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = number;
    }
  }
}
void init_matrix_2(matrix_t *A) {
  int x = 1;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = x;
      x++;
    }
  }
}
void init_matrix_3(matrix_t *A) {
  int x = 1;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (i == 0 && j > 0)
        A->matrix[i][j] = 3;
      else
        A->matrix[i][j] = x;
      x++;
    }
  }
}

START_TEST(create_matrix_test_1) {
  matrix_t mat = {0};
  ck_assert_int_eq(s21_create_matrix(-1, 0, &mat), ERROR_SIZE);
  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(create_matrix_test_2) {
  matrix_t mat = {0};
  ck_assert_int_eq(s21_create_matrix(3, 5, &mat), OK);
  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(create_matrix_test_3) {
  matrix_t mat = {0};
  ck_assert_int_eq(s21_create_matrix(0, 6, &mat), ERROR_SIZE);
  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(create_matrix_test_4) {
  matrix_t mat = {0};
  ck_assert_int_eq(s21_create_matrix(1, 3, &mat), OK);
  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(create_matrix_test_5) {
  matrix_t mat = {0};
  ck_assert_int_eq(s21_create_matrix(1, 1, &mat), OK);
  s21_remove_matrix(&mat);
}
END_TEST
START_TEST(create_matrix_test_6) {
  matrix_t matrix = {0};
  ck_assert_int_eq(s21_create_matrix(5, 5, NULL), 1);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(eq_matrix_test_1) {
  matrix_t mat_1 = {0};
  matrix_t mat_2 = {0};
  s21_create_matrix(3, 3, &mat_1);
  s21_create_matrix(3, 3, &mat_2);
  init_matrix(&mat_1, 48.4);
  init_matrix(&mat_2, 48.4);
  ck_assert_int_eq(s21_eq_matrix(&mat_1, &mat_2), SUCCESS);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
}
END_TEST

START_TEST(eq_matrix_test_2) {
  matrix_t mat_1 = {0};
  matrix_t mat_2 = {0};
  s21_create_matrix(3, 3, &mat_1);
  s21_create_matrix(3, 3, &mat_2);
  init_matrix(&mat_1, 48.5);
  init_matrix(&mat_2, 48.4);
  ck_assert_int_eq(s21_eq_matrix(&mat_1, &mat_2), FAILURE);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
}
END_TEST

START_TEST(eq_matrix_test_3) {
  matrix_t mat_1 = {0};
  matrix_t mat_2 = {0};
  s21_create_matrix(2, 3, &mat_1);
  s21_create_matrix(3, 3, &mat_2);
  init_matrix(&mat_1, 48.4);
  init_matrix(&mat_2, 48.4);
  ck_assert_int_eq(s21_eq_matrix(&mat_1, &mat_2), FAILURE);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
}
END_TEST

START_TEST(eq_matrix_test_4) {
  matrix_t mat_1 = {0};
  matrix_t mat_2 = {0};
  s21_create_matrix(-1, 3, &mat_1);
  s21_create_matrix(3, 3, &mat_2);
  init_matrix(&mat_1, 12348.4);
  init_matrix(&mat_2, 12348.4);
  ck_assert_int_eq(s21_eq_matrix(&mat_1, &mat_2), FAILURE);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
}
END_TEST

START_TEST(eq_matrix_test_5) {
  matrix_t mat_1 = {0};
  matrix_t mat_2 = {0};
  s21_create_matrix(5, 5, &mat_2);
  init_matrix(&mat_1, 18.44561);
  mat_1.rows = 5;
  mat_1.columns = 5;
  mat_1.matrix = NULL;
  init_matrix(&mat_2, 18.44561);
  ck_assert_int_eq(s21_eq_matrix(&mat_1, &mat_2), FAILURE);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
}
END_TEST

START_TEST(sum_matrix_test_1) {
  matrix_t mat_1 = {0};
  matrix_t mat_2 = {0};
  matrix_t sum = {0};
  matrix_t dop = {0};
  s21_create_matrix(5, 5, &mat_1);
  s21_create_matrix(5, 5, &mat_2);
  s21_create_matrix(5, 5, &dop);
  init_matrix(&mat_1, 18.4);
  init_matrix(&mat_2, 15.0);
  init_matrix(&dop, 33.4);
  ck_assert_int_eq(s21_sum_matrix(&mat_1, &mat_2, &sum), OK);
  ck_assert_int_eq(s21_eq_matrix(&sum, &dop), SUCCESS);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
  s21_remove_matrix(&sum);
  s21_remove_matrix(&dop);
}
END_TEST

START_TEST(sum_matrix_test_2) {
  matrix_t mat_1 = {0};
  matrix_t mat_2 = {0};
  matrix_t sum = {0};
  s21_create_matrix(3, 5, &mat_1);
  s21_create_matrix(5, 5, &mat_2);
  init_matrix(&mat_1, 18.4);
  init_matrix(&mat_2, 15.0);
  ck_assert_int_eq(s21_sum_matrix(&mat_1, &mat_2, &sum), ERROR_CALC);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
  s21_remove_matrix(&sum);
}
END_TEST

START_TEST(sum_matrix_test_3) {
  matrix_t mat_1 = {0};
  matrix_t mat_2 = {0};
  matrix_t sum = {0};
  s21_create_matrix(-6, 5, &mat_1);
  s21_create_matrix(-5, 5, &mat_2);
  init_matrix(&mat_1, 18.4);
  init_matrix(&mat_2, 15.0);
  ck_assert_int_eq(s21_sum_matrix(&mat_1, &mat_2, &sum), ERROR_SIZE);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
  s21_remove_matrix(&sum);
}
END_TEST

START_TEST(sum_matrix_test_4) {
  matrix_t mat_1 = {0};
  matrix_t mat_2 = {0};
  matrix_t sum = {0};
  matrix_t dop = {0};
  s21_create_matrix(2, 5, &mat_1);
  s21_create_matrix(2, 5, &mat_2);
  s21_create_matrix(2, 5, &dop);
  init_matrix(&mat_1, -122222.0);
  init_matrix(&mat_2, 15.0);
  init_matrix(&dop, -122207.0);
  ck_assert_int_eq(s21_sum_matrix(&mat_1, &mat_2, &sum), OK);
  ck_assert_int_eq(s21_eq_matrix(&sum, &dop), SUCCESS);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
  s21_remove_matrix(&sum);
  s21_remove_matrix(&dop);
}
END_TEST

START_TEST(sub_matrix_test_1) {
  matrix_t mat_1 = {0};
  matrix_t mat_2 = {0};
  matrix_t sub = {0};
  s21_create_matrix(1, 2, &mat_1);
  s21_create_matrix(2, 2, &mat_2);
  init_matrix(&mat_1, 124556.8);
  init_matrix(&mat_2, 15.0);
  ck_assert_int_eq(s21_sub_matrix(&mat_1, &mat_2, &sub), ERROR_CALC);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
  s21_remove_matrix(&sub);
}
END_TEST

START_TEST(sub_matrix_test_2) {
  matrix_t mat_1 = {0};
  matrix_t mat_2 = {0};
  matrix_t sub = {0};
  matrix_t dop = {0};
  s21_create_matrix(4, 4, &mat_1);
  s21_create_matrix(4, 4, &mat_2);
  s21_create_matrix(4, 4, &dop);
  init_matrix(&mat_1, 124556.8);
  init_matrix(&mat_2, 0);
  init_matrix(&dop, 124556.8);
  ck_assert_int_eq(s21_sub_matrix(&mat_1, &mat_2, &sub), OK);
  ck_assert_int_eq(s21_eq_matrix(&sub, &dop), SUCCESS);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
  s21_remove_matrix(&sub);
  s21_remove_matrix(&dop);
}
END_TEST

START_TEST(sub_matrix_test_3) {
  matrix_t mat_1 = {0};
  matrix_t mat_2 = {0};
  matrix_t sub = {0};
  s21_create_matrix(-1, 4, &mat_1);
  s21_create_matrix(4, 4, &mat_2);
  init_matrix(&mat_1, 124556.8);
  init_matrix(&mat_2, 0);
  ck_assert_int_eq(s21_sub_matrix(&mat_1, &mat_2, &sub), ERROR_SIZE);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
  s21_remove_matrix(&sub);
}
END_TEST

START_TEST(sub_matrix_test_4) {
  matrix_t mat_1 = {0};
  matrix_t mat_2 = {0};
  matrix_t sub = {0};
  matrix_t dop = {0};
  s21_create_matrix(4, 4, &mat_1);
  s21_create_matrix(4, 4, &mat_2);
  s21_create_matrix(4, 4, &dop);
  init_matrix(&mat_1, -124556.80000000);
  init_matrix(&mat_2, -124556.8);
  init_matrix(&dop, 0);
  ck_assert_int_eq(s21_sub_matrix(&mat_1, &mat_2, &sub), OK);
  ck_assert_int_eq(s21_eq_matrix(&sub, &dop), SUCCESS);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
  s21_remove_matrix(&sub);
  s21_remove_matrix(&dop);
}
END_TEST

START_TEST(mult_number_test_1) {
  matrix_t mat = {0};
  matrix_t mult = {0};
  matrix_t dop = {0};
  s21_create_matrix(4, 4, &mat);
  s21_create_matrix(4, 4, &dop);
  init_matrix(&mat, -124556.80000000);
  init_matrix(&dop, -124556.80000000 * 12000);
  ck_assert_int_eq(s21_mult_number(&mat, 12000, &mult), OK);
  ck_assert_int_eq(s21_eq_matrix(&mult, &dop), SUCCESS);
  s21_remove_matrix(&mat);
  s21_remove_matrix(&mult);
  s21_remove_matrix(&dop);
}
END_TEST

START_TEST(mult_number_test_2) {
  matrix_t mat = {0};
  matrix_t mult = {0};
  s21_create_matrix(0, 4, &mat);
  init_matrix(&mat, -124556.80000000);
  ck_assert_int_eq(s21_mult_number(&mat, 12000, &mult), ERROR_SIZE);
  s21_remove_matrix(&mat);
  s21_remove_matrix(&mult);
}
END_TEST

START_TEST(mult_matrix_test_1) {
  matrix_t mat_1 = {0};
  matrix_t mat_2 = {0};
  matrix_t mult = {0};
  matrix_t dop = {0};
  s21_create_matrix(5, 4, &mat_1);
  s21_create_matrix(4, 6, &mat_2);
  s21_create_matrix(5, 6, &dop);
  init_matrix(&mat_1, -1);
  init_matrix(&mat_2, 4);
  init_matrix(&dop, 124556.8);
  ck_assert_int_eq(s21_mult_matrix(&mat_1, &mat_2, &mult), OK);
  ck_assert_int_eq(s21_eq_matrix(&mult, &dop), FAILURE);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
  s21_remove_matrix(&mult);
  s21_remove_matrix(&dop);
}
END_TEST

START_TEST(mult_matrix_test_2) {
  matrix_t mat_1 = {0};
  matrix_t mat_2 = {0};
  matrix_t mult = {0};
  matrix_t dop = {0};
  s21_create_matrix(5, 4, &mat_1);
  s21_create_matrix(4, 6, &mat_2);
  s21_create_matrix(5, 6, &dop);
  init_matrix(&mat_1, -1);
  init_matrix(&mat_2, 4);
  init_matrix(&dop, -16);
  ck_assert_int_eq(s21_mult_matrix(&mat_1, &mat_2, &mult), OK);
  ck_assert_int_eq(s21_eq_matrix(&mult, &dop), SUCCESS);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
  s21_remove_matrix(&mult);
  s21_remove_matrix(&dop);
}
END_TEST

START_TEST(mult_matrix_test_3) {
  matrix_t mat_1 = {0};
  matrix_t mat_2 = {0};
  matrix_t mult = {0};
  s21_create_matrix(4, 4, &mat_1);
  s21_create_matrix(5, 3, &mat_2);
  init_matrix(&mat_1, -1);
  init_matrix(&mat_2, 4);
  ck_assert_int_eq(s21_mult_matrix(&mat_1, &mat_2, &mult), ERROR_CALC);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
  s21_remove_matrix(&mult);
}
END_TEST

START_TEST(transpose_test_1) {
  matrix_t mat = {0};
  matrix_t res = {0};
  matrix_t dop = {0};
  s21_create_matrix(7, 3, &mat);
  s21_create_matrix(3, 7, &dop);
  init_matrix(&mat, -1);
  init_matrix(&dop, -1);
  ck_assert_int_eq(s21_transpose(&mat, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&res, &dop), SUCCESS);
  s21_remove_matrix(&mat);
  s21_remove_matrix(&res);
  s21_remove_matrix(&dop);
}
END_TEST

START_TEST(transpose_test_2) {
  matrix_t mat = {0};
  matrix_t res = {0};
  matrix_t dop = {0};
  s21_create_matrix(7, 3, &mat);
  s21_create_matrix(3, 7, &dop);
  init_matrix(&mat, -1);
  init_matrix(&dop, -1);
  mat.matrix[5][1] = 1000;
  dop.matrix[1][5] = 1000;
  ck_assert_int_eq(s21_transpose(&mat, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&res, &dop), SUCCESS);
  s21_remove_matrix(&mat);
  s21_remove_matrix(&res);
  s21_remove_matrix(&dop);
}
END_TEST

START_TEST(transpose_test_3) {
  matrix_t mat = {0};
  matrix_t res = {0};
  s21_create_matrix(-5, 3, &mat);
  ck_assert_int_eq(s21_transpose(&mat, &res), ERROR_SIZE);
  s21_remove_matrix(&mat);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(calc_complements_test_1) {
  matrix_t mat = {0};
  matrix_t res = {0};
  s21_create_matrix(5, 4, &mat);
  ck_assert_int_eq(s21_calc_complements(&mat, &res), ERROR_CALC);
  s21_remove_matrix(&mat);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(calc_complements_test_2) {
  matrix_t mat = {0};
  matrix_t res = {0};
  matrix_t dop = {0};
  s21_create_matrix(3, 3, &mat);
  s21_create_matrix(3, 3, &dop);
  init_matrix_2(&mat);
  dop.matrix[0][0] = -3.0;
  dop.matrix[0][1] = 6.0;
  dop.matrix[0][2] = -3.0;
  dop.matrix[1][0] = 6.0;
  dop.matrix[1][1] = -12;
  dop.matrix[1][2] = 6;
  dop.matrix[2][0] = -3;
  dop.matrix[2][1] = 6;
  dop.matrix[2][2] = -3;
  ck_assert_int_eq(s21_calc_complements(&mat, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&res, &dop), SUCCESS);
  s21_remove_matrix(&mat);
  s21_remove_matrix(&res);
  s21_remove_matrix(&dop);
}
END_TEST

START_TEST(calc_complements_test_3) {
  matrix_t mat = {0};
  matrix_t res = {0};
  matrix_t dop = {0};
  s21_create_matrix(2, 2, &mat);
  s21_create_matrix(2, 2, &dop);
  init_matrix_2(&mat);
  dop.matrix[0][0] = 4.0;
  dop.matrix[0][1] = -3.0;
  dop.matrix[1][0] = -2.0;
  dop.matrix[1][1] = 1;
  ck_assert_int_eq(s21_calc_complements(&mat, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&res, &dop), SUCCESS);
  s21_remove_matrix(&mat);
  s21_remove_matrix(&res);
  s21_remove_matrix(&dop);
}
END_TEST

START_TEST(determinant_test_1) {
  matrix_t mat = {0};
  double res = 0;
  s21_create_matrix(5, 4, &mat);
  ck_assert_int_eq(s21_determinant(&mat, &res), ERROR_CALC);
  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(determinant_test_2) {
  matrix_t mat = {0};
  double res = 0;
  s21_create_matrix(3, 3, &mat);
  init_matrix_2(&mat);
  ck_assert_int_eq(s21_determinant(&mat, &res), OK);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(determinant_test_3) {
  matrix_t mat = {0};
  double res = 0;
  s21_create_matrix(3, 3, &mat);
  init_matrix_3(&mat);
  ck_assert_int_eq(s21_determinant(&mat, &res), OK);
  ck_assert_int_eq(res, 6);
  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(inverse_matrix_test_1) {
  matrix_t mat = {0};
  matrix_t res = {0};
  s21_create_matrix(3, 3, &mat);
  init_matrix_2(&mat);
  ck_assert_int_eq(s21_inverse_matrix(&mat, &res), ERROR_CALC);
  s21_remove_matrix(&mat);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(inverse_matrix_test_2) {
  matrix_t mat = {0};
  matrix_t res = {0};
  s21_create_matrix(3, 3, &mat);
  init_matrix_2(&mat);
  ck_assert_int_eq(s21_inverse_matrix(&mat, &res), ERROR_CALC);
  s21_remove_matrix(&mat);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(inverse_matrix_test_3) {
  matrix_t mat = {0};
  matrix_t res = {0};
  matrix_t dop = {0};
  s21_create_matrix(3, 3, &mat);
  s21_create_matrix(3, 3, &dop);
  init_matrix_3(&mat);
  dop.matrix[0][0] = -1.0 / 2.0;
  dop.matrix[0][1] = -1.0 / 2.0;
  dop.matrix[0][2] = 1.0 / 2.0;
  dop.matrix[1][0] = 1.0;
  dop.matrix[1][1] = -2.0;
  dop.matrix[1][2] = 1.0;
  dop.matrix[2][0] = -1.0 / 2.0;
  dop.matrix[2][1] = 13.0 / 6.0;
  dop.matrix[2][2] = -7.0 / 6.0;
  ck_assert_int_eq(s21_inverse_matrix(&mat, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&res, &dop), SUCCESS);
  s21_remove_matrix(&mat);
  s21_remove_matrix(&res);
  s21_remove_matrix(&dop);
}
END_TEST

START_TEST(inverse_matrix_test_4) {
  matrix_t mat = {0};
  matrix_t res = {0};
  s21_create_matrix(1, 1, &mat);
  mat.matrix[0][0] = 1;
  ck_assert_int_eq(s21_inverse_matrix(&mat, &res), OK);
  s21_remove_matrix(&mat);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(inverse_matrix_test_5) {
  matrix_t mat = {0};
  matrix_t res = {0};
  s21_create_matrix(1, 1, &mat);
  mat.matrix[0][0] = 0;
  ck_assert_int_eq(s21_inverse_matrix(&mat, &res), ERROR_CALC);
  s21_remove_matrix(&mat);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(inverse_matrix_test_6) {
  matrix_t mat = {0};
  matrix_t res = {0};
  s21_create_matrix(3, 4, &mat);
  init_matrix_3(&mat);
  ck_assert_int_eq(s21_inverse_matrix(&mat, &res), ERROR_CALC);
  s21_remove_matrix(&mat);
  s21_remove_matrix(&res);
}
END_TEST

Suite *main_suite(void) {
  Suite *suite = suite_create("Main");
  TCase *tc_create_matrix = tcase_create("create_matrix");
  TCase *tc_eq_matrix = tcase_create("eq_matrix");
  TCase *tc_sum_matrix = tcase_create("sum_matrix");
  TCase *tc_sub_matrix = tcase_create("sub_matrix");
  TCase *tc_mult_number = tcase_create("mult_number");
  TCase *tc_mult_matrix = tcase_create("mult_matrix");
  TCase *tc_transpose = tcase_create("transpose");
  TCase *tc_calc_complements = tcase_create("calc_complements");
  TCase *tc_determinant = tcase_create("determinant");
  TCase *tc_inverse_matrix = tcase_create("inverse_matrix");

  suite_add_tcase(suite, tc_create_matrix);
  suite_add_tcase(suite, tc_eq_matrix);
  suite_add_tcase(suite, tc_sum_matrix);
  suite_add_tcase(suite, tc_sub_matrix);
  suite_add_tcase(suite, tc_mult_number);
  suite_add_tcase(suite, tc_mult_matrix);

  suite_add_tcase(suite, tc_transpose);
  suite_add_tcase(suite, tc_calc_complements);
  suite_add_tcase(suite, tc_determinant);
  suite_add_tcase(suite, tc_inverse_matrix);

  tcase_add_test(tc_create_matrix, create_matrix_test_1);
  tcase_add_test(tc_create_matrix, create_matrix_test_2);
  tcase_add_test(tc_create_matrix, create_matrix_test_3);
  tcase_add_test(tc_create_matrix, create_matrix_test_4);
  tcase_add_test(tc_create_matrix, create_matrix_test_5);
  tcase_add_test(tc_create_matrix, create_matrix_test_6);

  tcase_add_test(tc_eq_matrix, eq_matrix_test_1);
  tcase_add_test(tc_eq_matrix, eq_matrix_test_2);
  tcase_add_test(tc_eq_matrix, eq_matrix_test_3);
  tcase_add_test(tc_eq_matrix, eq_matrix_test_4);
  tcase_add_test(tc_eq_matrix, eq_matrix_test_5);

  tcase_add_test(tc_sum_matrix, sum_matrix_test_1);
  tcase_add_test(tc_sum_matrix, sum_matrix_test_2);
  tcase_add_test(tc_sum_matrix, sum_matrix_test_3);
  tcase_add_test(tc_sum_matrix, sum_matrix_test_4);

  tcase_add_test(tc_sub_matrix, sub_matrix_test_1);
  tcase_add_test(tc_sub_matrix, sub_matrix_test_2);
  tcase_add_test(tc_sub_matrix, sub_matrix_test_3);
  tcase_add_test(tc_sub_matrix, sub_matrix_test_4);

  tcase_add_test(tc_mult_number, mult_number_test_1);
  tcase_add_test(tc_mult_number, mult_number_test_2);

  tcase_add_test(tc_mult_matrix, mult_matrix_test_1);
  tcase_add_test(tc_mult_matrix, mult_matrix_test_2);
  tcase_add_test(tc_mult_matrix, mult_matrix_test_3);

  tcase_add_test(tc_transpose, transpose_test_1);
  tcase_add_test(tc_transpose, transpose_test_2);
  tcase_add_test(tc_transpose, transpose_test_3);

  tcase_add_test(tc_calc_complements, calc_complements_test_1);
  tcase_add_test(tc_calc_complements, calc_complements_test_2);
  tcase_add_test(tc_calc_complements, calc_complements_test_3);

  tcase_add_test(tc_determinant, determinant_test_1);
  tcase_add_test(tc_determinant, determinant_test_2);
  tcase_add_test(tc_determinant, determinant_test_3);

  tcase_add_test(tc_inverse_matrix, inverse_matrix_test_1);
  tcase_add_test(tc_inverse_matrix, inverse_matrix_test_2);
  tcase_add_test(tc_inverse_matrix, inverse_matrix_test_3);
  tcase_add_test(tc_inverse_matrix, inverse_matrix_test_4);
  tcase_add_test(tc_inverse_matrix, inverse_matrix_test_5);
  tcase_add_test(tc_inverse_matrix, inverse_matrix_test_6);

  return suite;
}

int main() {
  Suite *suite = main_suite();
  int fails = 0;

  SRunner *runner;
  runner = srunner_create(suite);
  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);

  fails = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (fails == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

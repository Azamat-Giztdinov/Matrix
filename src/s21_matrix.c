#include "s21_matrix.h"

// Создание матриц (create_matrix)
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = result ? OK : ERROR_SIZE;
  if (rows > 0 && columns > 0 && res == OK) {
    result->matrix = NULL;
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix) {
      for (int i = 0; i < rows && res == OK; i++) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
        if (result->matrix[i]) {
        } else {
          i--;
          while (i >= 0) {
            free(result->matrix[i]);
            i--;
          }
          free(result->matrix);
          result->matrix = NULL;
          res = ERROR_SIZE;
        }
      }
    }
  } else {
    res = ERROR_SIZE;
  }
  return res;
}

// Очистка матриц (remove_matrix)
void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
  }
  A->matrix = NULL;
}

// Сравнение матриц (eq_matrix)
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res =
      correct_matrix(A) == OK && correct_matrix(B) == OK ? SUCCESS : FAILURE;
  double accuracy = 0;
  if (equal_matrix(*A, *B) && res == SUCCESS) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns && res == SUCCESS; j++) {
        accuracy = A->matrix[i][j] - B->matrix[i][j];
        if (accuracy > ACCURACY || accuracy < -ACCURACY) {
          res = FAILURE;
        }
      }
    }
  } else {
    res = FAILURE;
  }
  return res;
}

// Сложение (sum_matrix) и вычитание матриц (sub_matrix)
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = correct_matrix(A) || correct_matrix(B);
  if (equal_matrix(*A, *B) && res == OK) {
    s21_create_matrix(A->rows, A->columns, result);
    double sum = 0;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns && res == OK; j++) {
        sum = A->matrix[i][j] + B->matrix[i][j];
        if (sum < INFINITY && sum > -INFINITY) {
          result->matrix[i][j] = sum;
        } else {
          res = ERROR_CALC;
        }
      }
    }
  } else if (res == OK) {
    res = ERROR_CALC;
  }
  return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = correct_matrix(A) || correct_matrix(B);
  if (equal_matrix(*A, *B) && res == OK) {
    s21_create_matrix(A->rows, A->columns, result);
    double sub = 0;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns && res == OK; j++) {
        sub = A->matrix[i][j] - B->matrix[i][j];
        if (sub < INFINITY && sub > -INFINITY) {
          result->matrix[i][j] = sub;
        } else {
          res = ERROR_CALC;
        }
      }
    }
  } else if (res == OK) {
    res = ERROR_CALC;
  }
  return res;
}

// Умножение матрицы на число (mult_number). Умножение двух матриц (mult_matrix)
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = correct_matrix(A);
  if (res == OK && s21_create_matrix(A->rows, A->columns, result) == OK) {
    double sub = 0;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns && res == OK; j++) {
        sub = A->matrix[i][j] * number;
        if (sub < INFINITY && sub > -INFINITY) {
          result->matrix[i][j] = sub;
        } else {
          res = ERROR_CALC;
        }
      }
    }
  }
  return res;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = correct_matrix(A) || correct_matrix(B);
  if (equal_mul_matrix(*A, *B) && res == OK) {
    double sub = 0;
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns && res == OK; j++) {
        sub = 0;
        for (int k = 0; k < A->columns; k++) {
          sub += A->matrix[i][k] * B->matrix[k][j];
        }
        if (sub < INFINITY && sub > -INFINITY) {
          result->matrix[i][j] = sub;
        } else {
          res = ERROR_CALC;
        }
      }
    }
  } else if (res == OK) {
    res = ERROR_CALC;
  }
  return res;
}

// Транспонирование матрицы (transpose)
int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = correct_matrix(A);
  if (res == OK && !s21_create_matrix(A->columns, A->rows, result)) {
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  } else {
    res = ERROR_SIZE;
  }
  return res;
}

// Минор матрицы и матрица алгебраических дополнений (calc_complements)
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = correct_matrix(A);
  double M = 0;
  if (A->rows == A->columns && A->rows > 1 && res == OK) {
    s21_create_matrix(A->rows, A->columns, result);
    matrix_t dop = {0};
    s21_create_matrix(A->rows - 1, A->columns - 1, &dop);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns && res == OK; j++) {
        s21_dop_determ(i, j, *A, &dop);
        res = s21_determinant(&dop, &M);
        if (res == OK) result->matrix[i][j] = pow(-1, i + j) * M;
      }
    }
    s21_remove_matrix(&dop);
  } else if ((A->rows != A->columns || A->rows == 1) && res == OK) {
    res = ERROR_CALC;
  } else {
    res = ERROR_SIZE;
  }
  return res;
}

// Определитель матрицы (determinant)
int s21_determinant(matrix_t *A, double *result) {
  *result = 0;
  int res = correct_matrix(A);
  if (A->rows == A->columns && res == OK) {
    matrix_t dop = {0};
    s21_create_matrix(A->rows - 1, A->rows - 1, &dop);
    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else if (A->rows == 2) {
      double sub =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
      if (sub < INFINITY && sub > -INFINITY) {
        *result = sub;
      } else {
        res = ERROR_CALC;
      }
    } else if (A->rows > 2) {
      double M = 0;
      for (int i = 0; i < A->rows && res == OK; i++) {
        s21_dop_determ(i, 0, *A, &dop);
        res = s21_determinant(&dop, &M);
        *result += +pow(-1, i) * A->matrix[i][0] * M;
      }
    }
    s21_remove_matrix(&dop);
  } else if (res == OK) {
    res = ERROR_CALC;
  }
  return res;
}

void s21_dop_determ(int row, int column, matrix_t A, matrix_t *result) {
  for (int i = 0, g = 0; i < A.rows && g < result->rows; i++, g++) {
    if (i == row) i++;
    for (int j = 0, k = 0; j < A.rows && k < result->rows; j++, k++) {
      if (j == column) j++;
      result->matrix[g][k] = A.matrix[i][j];
    }
  }
}

// Обратная матрица (inverse_matrix)
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = correct_matrix(A);
  if (A->rows == A->columns && res == OK) {
    if (A->rows == 1) {
      if (A->matrix[0][0]) {
        s21_create_matrix(A->rows, A->columns, result);
        result->matrix[0][0] = 1 / A->matrix[0][0];
      } else {
        res = ERROR_CALC;
      }
    } else {
      double a;
      s21_determinant(A, &a);
      // printf("\t a = %f\n", a);
      if (a) {
        matrix_t dop = {0};
        matrix_t T = {0};
        s21_calc_complements(A, &dop);
        s21_transpose(&dop, &T);
        s21_mult_number(&T, 1 / a, result);
        s21_remove_matrix(&T);
        s21_remove_matrix(&dop);
      } else {
        res = ERROR_CALC;
      }
    }
  } else if (res == OK && A->rows != A->columns) {
    res = ERROR_CALC;
  }

  return res;
}

// совпадение размеров матриц для сложение и вычетание
int equal_matrix(matrix_t A, matrix_t B) {
  int res = SUCCESS;
  if (A.rows != B.rows || A.columns != B.columns) {
    res = FAILURE;
  }
  return res;
}

// совпадение размеров матриц для умножение
int equal_mul_matrix(matrix_t A, matrix_t B) {
  int res = SUCCESS;
  if (A.columns != B.rows) {
    res = FAILURE;
  }
  return res;
}

int correct_matrix(matrix_t *A) {
  int res = A->matrix && A ? OK : ERROR_SIZE;
  if (A->rows <= 0 || A->columns <= 0) {
    res = ERROR_SIZE;
  } else if (res == OK) {
    for (int i = 0; i < A->rows && res == OK; i++) {
      res = A->matrix[i] ? OK : ERROR_SIZE;
    }
  }
  return res;
}

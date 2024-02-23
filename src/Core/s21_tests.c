#include <check.h>

#include "../Core/s21_SmartCalc_v1_0.h"

START_TEST(math_test_1) {
  char *in = "-11+23*(2-2)";
  int err = ERROR_ABSENT;
  char *rev_not = reverse_not(in, &err);
  double res = -11.;
  ck_assert_double_eq(res, calculation(rev_not, NULL));
}

END_TEST;

START_TEST(math_test_2) {
  char *in = "2345/6.55/3/2*(9-100+(-200))";
  int err = ERROR_ABSENT;
  char *rev_not = reverse_not(in, &err);
  double res = -17363.7404580;
  ck_assert_double_eq_tol(res, calculation(rev_not, NULL), 1e-7);
}

END_TEST;

START_TEST(math_test_3) {
  char *in = "2*2+1+1+1*2^2*2+2^3+1+1";
  int err = ERROR_ABSENT;
  char *rev_not = reverse_not(in, &err);
  double res = 24.;
  ck_assert_double_eq(res, calculation(rev_not, NULL));
}

END_TEST;

START_TEST(math_test_4) {
  char *in = "15%x";
  int err = ERROR_ABSENT;
  char *rev_not = reverse_not(in, &err);
  double x = 3;
  double res = 0.;
  ck_assert_double_eq(res, calculation(rev_not, &x));
}

END_TEST;

START_TEST(math_test_5) {
  char *in = "cos(12.4)";
  int err = ERROR_ABSENT;
  char *rev_not = reverse_not(in, &err);
  double res = 0.9861923;
  ck_assert_double_eq_tol(res, calculation(rev_not, NULL), 1e-7);
}

END_TEST;

START_TEST(math_test_6) {
  char *in = "sin(123-100*8^5%2/10+904.25)";
  int err = ERROR_ABSENT;
  char *rev_not = reverse_not(in, &err);
  double res = 0.0507759;
  ck_assert_double_eq_tol(res, calculation(rev_not, NULL), 1e-7);
}

END_TEST;

START_TEST(math_test_7) {
  char *in = "tan(tan(x))";
  int err = ERROR_ABSENT;
  char *rev_not = reverse_not(in, &err);
  double res = -0.2435748;
  double x = 5;
  ck_assert_double_eq_tol(res, calculation(rev_not, &x), 1e-7);
}

END_TEST;

START_TEST(math_test_8) {
  char *in = "acos(1-0.25)";
  int err = ERROR_ABSENT;
  char *rev_not = reverse_not(in, &err);
  double res = 0.7227342;
  ck_assert_double_eq_tol(res, calculation(rev_not, NULL), 1e-7);
}

END_TEST;

START_TEST(math_test_9) {
  char *in = "asin(0.69)-asin(0.69)";
  int err = ERROR_ABSENT;
  char *rev_not = reverse_not(in, &err);
  double res = 0.;
  ck_assert_double_eq_tol(res, calculation(rev_not, NULL), 1e-7);
}

END_TEST;

START_TEST(math_test_10) {
  char *in = "atan(6+77/6*(7-8-(9%6-10)+100))";
  int err = ERROR_ABSENT;
  char *rev_not = reverse_not(in, &err);
  double res = 1.5700644;
  ck_assert_double_eq_tol(res, calculation(rev_not, NULL), 1e-7);
}

END_TEST;

START_TEST(math_test_11) {
  char *in = "sqrt(77-8-sqrt(88))+sqrt(2.34)";
  int err = ERROR_ABSENT;
  char *rev_not = reverse_not(in, &err);
  double res = 9.2510508;
  ck_assert_double_eq_tol(res, calculation(rev_not, NULL), 1e-7);
}

END_TEST;

START_TEST(math_test_12) {
  char *in = "ln(345.6+567.8-567.3)";
  int err = ERROR_ABSENT;
  char *rev_not = reverse_not(in, &err);
  double res = 5.8467278;
  ck_assert_double_eq_tol(res, calculation(rev_not, NULL), 1e-7);
}

END_TEST;

START_TEST(math_test_13) {
  char *in = "+30 + 2 * (+10 - 1)";
  int err = ERROR_ABSENT;
  char *rev_not = reverse_not(in, &err);
  double res = 48.;
  ck_assert_double_eq_tol(res, calculation(rev_not, NULL), 1e-7);
}

START_TEST(math_test_14) {
  char *in = "28*37-123";
  int err = ERROR_ABSENT;
  char *rev_not = reverse_not(in, &err);
  double res = 913;
  ck_assert_double_eq_tol(res, calculation(rev_not, NULL), 1e-07);
}

END_TEST;

START_TEST(math_test_15) {
  char *in = "-28*37-123";
  int err = ERROR_ABSENT;
  char *rev_not = reverse_not(in, &err);
  double res = -1159;
  ck_assert_double_eq_tol(res, calculation(rev_not, NULL), 1e-07);
}

END_TEST;

Suite *math() {
  Suite *suite = suite_create("MATH OPERATIONS");
  TCase *tCase = tcase_create("MATH");

  tcase_add_test(tCase, math_test_1);
  tcase_add_test(tCase, math_test_2);
  tcase_add_test(tCase, math_test_3);
  tcase_add_test(tCase, math_test_4);
  tcase_add_test(tCase, math_test_5);
  tcase_add_test(tCase, math_test_6);
  tcase_add_test(tCase, math_test_7);
  tcase_add_test(tCase, math_test_8);
  tcase_add_test(tCase, math_test_9);
  tcase_add_test(tCase, math_test_10);
  tcase_add_test(tCase, math_test_11);
  tcase_add_test(tCase, math_test_12);
  tcase_add_test(tCase, math_test_13);
  tcase_add_test(tCase, math_test_14);
  tcase_add_test(tCase, math_test_15);

  suite_add_tcase(suite, tCase);

  return suite;
}

void run_test(Suite *suite) {
  SRunner *sRunner = srunner_create(suite);
  srunner_set_fork_status(sRunner, CK_NOFORK);
  srunner_run_all(sRunner, CK_NORMAL);
  srunner_free(sRunner);
}

void run_suite() {
  Suite *list[] = {math(), NULL};
  for (Suite **current = list; *current != NULL; ++current) {
    run_test(*current);
  }
}

int main() {
  run_suite();
  return 0;
}
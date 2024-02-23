#include "s21_SmartCalc_v1_0.h"

/**
 * @brief Проверяет валидность строки
 *
 * @param s Строка для проверки
 * @param error Указатель на переменную для сохранения кода ошибки
 */
void str_valid(char *s, int *error) {
  int count = 0;

  if (*s == '\0' || strlen(s) > STACKSIZE)
    *error = INPUT_ERROR;

  if (s[0] == ')' || s[0] == '%' || s[0] == '.' || s[0] == '*' || s[0] == '/' ||
      s[0] == '^')
    *error = INPUT_ERROR;

  for (int i = 0; s[i]; ++i) {
    if (s[i] == '+' && s[i + 1] == '\0')
      *error = INPUT_ERROR;

    if (s[i] == 'n' && s[i + 1] == '\0')
      *error = INPUT_ERROR;

    if (s[i] == 's' && s[i + 1] == '\0')
      *error = INPUT_ERROR;

    if (s[i] == '-' && s[i + 1] == '\0')
      *error = INPUT_ERROR;

    if (s[i] == 'r' && s[i + 2] == '\0')
      *error = INPUT_ERROR;

    if (check_binary(&s[i]) && s[i + 1] == '\0')
      *error = INPUT_ERROR;

    if (check_digit(&s[i]) && s[i + 1] == '.' && s[i + 2] == '.')
      *error = INPUT_ERROR;

    if (check_digit(&s[i]) && s[i + 1] == '.' && s[i - 1] == '.')
      *error = INPUT_ERROR;

    if (check_digit(&s[i]) && s[i - 1] == '.' && s[i - 2] == '.')
      *error = INPUT_ERROR;

    if (check_binary(&s[i]) && (s[i - 1] == '.' || s[i + 1] == '.'))
      *error = INPUT_ERROR;

    if (check_binary(&s[i]) &&
        (check_binary(&s[i + 1]) || check_binary(&s[i - 1])))
      *error = INPUT_ERROR;

    if (check_binary(&s[i]) && check_binary(&s[i + 1]))
      *error = INPUT_ERROR;

    if ((check_digit(&s[i]) || s[i] == 'x' || s[i] == '.') &&
        check_unary(&s[i + 1]))
      *error = INPUT_ERROR;

    if (s[i] == 'x' && (check_digit(&s[i + 1]) || check_digit(&s[i - 1])))
      *error = INPUT_ERROR;

    if ((s[i] == '(') &&
        (check_digit(&s[i - 1]) || s[i - 1] == '.' || s[i - 1] == 'x'))
      *error = INPUT_ERROR;

    if ((s[i] == ')') &&
        (check_digit(&s[i + 1]) || s[i + 1] == '.' || s[i + 1] == 'x')) {
      *error = INPUT_ERROR;
      --count;
    }
  }
  if (count != 0)
    *error = INPUT_ERROR;
}

/**
 * @brief Инвертирует знак числа и генерирует обратную польскую запись
 *
 * @param s Входная строка
 * @param error Указатель на переменную для сохранения кода ошибки
 * @return Указатель на массив символов с обратной польской записью
 */
char *reverse_not(char *s, int *error) {
  *error = ERROR_ABSENT;
  operator_stack *op_s = NULL;
  char *out = malloc(sizeof(char) * strlen(s) * 2);
  char *res = out;

  str_valid(s, error);

  if (res != NULL) {
    for (int i = 0; s[i]; ++i) {
      check_unary_plus_or_minus(&s[i], &i, &op_s);

      if (s[i] == '(')
        op_s = push_op(op_s, s[i]);

      else if (s[i] == ')') {
        while (op_s != NULL && check_op(op_s) != '(') {
          *(out++) = check_op(op_s);
          *(out++) = ' ';
          op_s = pop_op(op_s);
        }
        op_s = pop_op(op_s);
      }

      else if (check_digit(&s[i]) || s[i] == '.' || s[i] == 'x') {
        *(out++) = s[i];
        if (!(check_digit(&s[i + 1]) || s[i + 1] == '.'))
          *(out++) = ' ';
      }

      else if (check_binary(&s[i]))
        get_binary(&s[i], &op_s, &out);

      else if (check_unary(&s[i]))
        get_unary(&s[i], &op_s);
    }
  }

  else
    *error = MEMORY_ERROR;

  while (op_s != NULL && *error == ERROR_ABSENT) {
    if (count_stecksize(op_s) == 1) {
      *(out++) = check_op(op_s);
      op_s = pop_op(op_s);
    } else {
      *(out++) = check_op(op_s);
      *(out++) = ' ';
      op_s = pop_op(op_s);
    }
    if (op_s == NULL)
      *(out++) = '\0';
  }

  if (*error != ERROR_ABSENT) {
    free(res);
    res = NULL;
  }
  free(op_s);
  return res;
}

/**
 * @brief Выполняет вычисление математического выражения
 *
 * @param s Обратная польская запись
 * @param num Указатель на переменную числа "x"
 * @return Результат вычисления
 */
double calculation(char *s, double *num) {
  double res = 0.;
  operand_stack *op_s = NULL;
  char *entry = s;
  double value_1 = 0.;
  double value_2 = 0.;

  for (int i = 0; s[i]; ++i) {
    if (s[i] == ' ')
      continue;

    else if (s[i] == '~') {
      value_1 = check_num(op_s);
      op_s = pop_num(op_s);
      op_s = push_num(op_s, (-1) * value_1);
    }

    else if (s[i] == '#') {
      value_1 = check_num(op_s);
      op_s = pop_num(op_s);
      op_s = push_num(op_s, (+1) * value_1);
    }

    else if (s[i] == 'x')
      op_s = push_num(op_s, *num);

    else if (check_digit(&s[i])) {
      if (check_digit(&s[i + 1]) && (i == 0 || (i >= 1 && s[i - 1] == ' '))) {
        value_1 = s21_atof(&s[i]);
        op_s = push_num(op_s, value_1);
      } else if (i == 0 || (i >= 1 && s[i - 1] == ' ')) {
        value_1 = s21_atof(&s[i]);
        op_s = push_num(op_s, value_1);
      }
    }
    if (check_binary(&s[i]))
      calculation_binary(&op_s, &s[i], value_1, value_2, res);

    if (check_unary(&s[i]))
      calculation_unary(&op_s, &s[i], value_1, res);
  }

  while (op_s != NULL) {
    res = check_num(op_s);
    op_s = pop_num(op_s);
  }

  free(op_s);
  free(entry);

  if (res - (int)res == 0)
    return (int)res;
  else
    return res;
}

/**
 * @brief Проверяет наличие унарных операторов "+" и "-"
 *
 * @param c Указатель на текущий символ
 * @param indx Указатель на текущий индекс символа
 * @param operator_s Стек операторов
 */
void check_unary_plus_or_minus(char *c, int *indx,
                               operator_stack **operator_s) {
  int index = *indx;

  if (*c == '-' && (index == 0 || (index >= 1 && *(c - 1) == '('))) {
    *operator_s = push_op(*operator_s, '~');
    ++index;
  }

  else if (*c == '+' && (index == 0 || (index >= 1 && *(c - 1) == '('))) {
    *operator_s = push_op(*operator_s, '#');
    ++index;
  }
  *indx = index;
}

/**
 * @brief Проверяет, является ли символ цифрой
 *
 * @param c Указатель на текущий символ
 * @return 1, если символ - цифра, иначе 0
 */
int check_digit(char *c) { return *c >= '0' && *c <= '9'; }

/**
 * @brief Проверяет, является ли символ бинарным оператором
 *
 * @param c Указатель на текущий символ
 * @return 1, если символ - бинарный оператор, иначе 0
 */
int check_binary(char *c) {
  return *c == '+' || *c == '-' || *c == '*' || *c == '/' || *c == '^' ||
         *c == '%';
}

/**
 * @brief Проверяет, является ли символ унарным оператором
 *
 * @param c Указатель на текущий символ
 * @return 1, если символ - унарный оператор, иначе 0
 */
int check_unary(char *c) {
  return *c == 's' || *c == 'c' || *c == 't' || *c == 'g' || *c == 'a' ||
         *c == 'l' || *c == 'S' || *c == 'C' || *c == 'T' || *c == 'q';
}

/**
 * @brief Обрабатывает бинарный оператор
 *
 * @param _operator Символ бинарного оператора
 * @param op_s Стек операторов
 * @param out Указатель на выходную строку
 */
void get_binary(char *_operator, operator_stack **op_s, char **out) {
  char *tmp = *out;
  if (*op_s == NULL)
    *op_s = push_op(*op_s, *_operator);
  else if (set_op_priority(*_operator) <= set_op_priority(check_op(*op_s))) {
    while (*op_s != NULL &&
           set_op_priority(*_operator) <= set_op_priority(check_op(*op_s))) {
      *(tmp++) = check_op(*op_s);
      *(tmp++) = ' ';
      *op_s = pop_op(*op_s);
    }
    *op_s = push_op(*op_s, *_operator);
  } else
    *op_s = push_op(*op_s, *_operator);

  *out = tmp;
}

/**
 * @brief Обрабатывает унарный оператор
 *
 * @param _operator Символ унарного оператора
 * @param op_s Стек операторов
 */
void get_unary(char *_operator, operator_stack **op_s) {
  if (*_operator == 'c' && *(_operator + 1) == 'o' && *(_operator - 1) != 'a')
    *op_s = push_op(*op_s, 'c');
  else if (*_operator == 's' && *(_operator + 1) == 'i' &&
           *(_operator - 1) != 'a')
    *op_s = push_op(*op_s, 's');
  else if (*_operator == 't' && *(_operator + 1) == 'a' &&
           *(_operator - 1) != 'a')
    *op_s = push_op(*op_s, 't');
  else if (*_operator == 'a' && *(_operator + 1) == 'c')
    *op_s = push_op(*op_s, 'C');
  else if (*_operator == 'a' && *(_operator + 1) == 's')
    *op_s = push_op(*op_s, 'S');
  else if (*_operator == 'a' && *(_operator + 1) == 't')
    *op_s = push_op(*op_s, 'T');
  else if (*_operator == 's' && *(_operator + 1) == 'q')
    *op_s = push_op(*op_s, 'q');
  else if (*_operator == 'l' && *(_operator + 1) == 'n')
    *op_s = push_op(*op_s, 'l');
}

/**
 * @brief Устанавливает приоритет оператора
 *
 * @param operation Символ оператора
 * @return Значение приоритета
 */
int set_op_priority(char operation) {
  int ret = 0;

  if (operation == '+' || operation == '-')
    ret = 1;

  else if (operation == '*' || operation == '/' || operation == '%')
    ret = 2;

  else if (operation == '^')
    ret = 3;

  else if (operation == '~' || operation == '#')
    ret = 4;

  else if (operation == 'c' || operation == 'C' || operation == 't' ||
           operation == 'T' || operation == 's' || operation == 'S' ||
           operation == 'q' || operation == 'l' || operation == 'g')
    ret = 5;

  return ret;
}

/**
 * @brief Преобразует строку в число с плавающей точкой
 *
 * @param str Строка для преобразования
 * @return Результат преобразования
 */
double s21_atof(char *str) {
  char *tmp = malloc(sizeof(char) * strlen(str) + 1);
  char *next = tmp;
  char *ptr = next;
  int count = 0;
  double res = 0;

  for (int i = 0; str[i]; ++i) {
    if (check_digit(&str[i]) || str[i] == '.')
      *tmp++ = str[i];
    else {
      *tmp++ = '\0';
      continue;
    }
  }

  for (int i = 0; next[i]; ++i) {
    if (count >= 1)
      count *= 10;
    if (next[i] == '.')
      count = 1;
  }

  while (*next != '\0') {
    if (*next == '.') {
      ++next;
      continue;
    }
    res *= 10;
    res += *next - '0';
    ++next;
  }

  free(ptr);
  if (count == 0)
    ++count;
  return res / count;
}

/**
 * @brief Выполняет унарные операции
 *
 * @param operand_s Стек операндов
 * @param _operator Символ унарного оператора
 * @param value Значение для выполнения операции
 * @param result Результат операции
 */
void calculation_unary(operand_stack **operand_s, char *_operator, double value,
                       double result) {
  value = check_num(*operand_s);
  *operand_s = pop_num(*operand_s);
  if (*_operator == 'c') {
    result = cos(value);
    *operand_s = push_num(*operand_s, result);
  }
  if (*_operator == 's') {
    result = sin(value);
    *operand_s = push_num(*operand_s, result);
  }
  if (*_operator == 't') {
    result = tan(value);
    *operand_s = push_num(*operand_s, result);
  }
  if (*_operator == 'C') {
    result = acos(value);
    *operand_s = push_num(*operand_s, result);
  }
  if (*_operator == 'S') {
    result = asin(value);
    *operand_s = push_num(*operand_s, result);
  }
  if (*_operator == 'T') {
    result = atan(value);
    *operand_s = push_num(*operand_s, result);
  }
  if (*_operator == 'q') {
    result = sqrt(value);
    *operand_s = push_num(*operand_s, result);
  }
  if (*_operator == 'l') {
    result = log(value);
    *operand_s = push_num(*operand_s, result);
  }
  if (*_operator == 'g') {
    result = log10(value);
    *operand_s = push_num(*operand_s, result);
  }
}

/**
 * @brief Выполняет бинарные операции
 *
 * @param operand Стек операндов
 * @param operator Символ бинарного оператора
 * @param value_1 Первый операнд
 * @param value_2 Второй операнд
 * @param result Результат операции
 */
void calculation_binary(operand_stack **operand, char *operator, double value_1,
                        double value_2, double result) {
  value_1 = check_num(*operand);
  *operand = pop_num(*operand);
  value_2 = check_num(*operand);
  *operand = pop_num(*operand);

  if (*operator== '+') {
    result = value_1 + value_2;
    *operand = push_num(*operand, result);
  }
  if (*operator== '-') {
    result = value_2 - value_1;
    *operand = push_num(*operand, result);
  }
  if (*operator== '*') {
    result = value_1 * value_2;
    *operand = push_num(*operand, result);
  }
  if (*operator== '/') {
    result = value_2 / value_1;
    *operand = push_num(*operand, result);
  }
  if (*operator== '^') {
    result = pow(value_2, value_1);
    *operand = push_num(*operand, result);
  }
  if (*operator== '%') {
    result = fmod(value_2, value_1);
    *operand = push_num(*operand, result);
  }
}

/**
 * @brief Возвращает количество элементов в стеке операторов
 *
 * @param last Указатель на вершину стека
 * @return Количество элементов в стеке
 */
size_t count_stecksize(operator_stack *last) {
  size_t res = 0;
  while (last) {
    ++res;
    last = last->next;
  }
  return res;
}

/**
 * @brief Инициализирует новый элемент стека операндов
 *
 * @param num Значение операнда
 * @return Указатель на новый элемент стека
 */
operand_stack *init_num(double num) {
  operand_stack *tmp = (operand_stack *)malloc(sizeof(operand_stack));
  tmp->val = num;
  tmp->next = NULL;
  return tmp;
}

/**
 * @brief Инициализирует новый элемент стека операторов
 *
 * @param op Символ оператора
 * @return Указатель на новый элемент стека
 */
operator_stack *init_op(char op) {
  operator_stack *tmp = (operator_stack *)malloc(sizeof(operator_stack));
  tmp->val = op;
  tmp->next = NULL;
  return tmp;
}

/**
 * @brief Добавляет элемент в стек операндов
 *
 * @param last Указатель на вершину стека
 * @param num Значение операнда
 * @return Указатель на новую вершину стека
 */
operand_stack *push_num(operand_stack *last, double num) {
  operand_stack *tmp = init_num(num);
  tmp->next = last;
  return tmp;
}

/**
 * @brief Добавляет элемент в стек операторов
 *
 * @param last Указатель на вершину стека
 * @param op Символ оператора
 * @return Указатель на новую вершину стека
 */
operator_stack *push_op(operator_stack *last, char op) {
  operator_stack *tmp = init_op(op);
  tmp->next = last;
  return tmp;
}

/**
 * @brief Возвращает значение оператора на вершине стека
 *
 * @param last Указатель на вершину стека
 * @return Значение оператора
 */
char check_op(operator_stack *last) { return last->val; }

/**
 * @brief Возвращает значение операнда на вершине стека
 *
 * @param last Указатель на вершину стека
 * @return Значение операнда
 */
double check_num(operand_stack *last) { return last->val; }

/**
 * @brief Удаляет верхний элемент из стека операндов
 *
 * @param last Указатель на вершину стека
 * @return Указатель на новую вершину стека
 */
operand_stack *pop_num(operand_stack *last) {
  operand_stack *tmp = NULL;
  if (last != NULL) {
    tmp = last->next;
    free(last);
  }
  return tmp;
}

/**
 * @brief Удаляет верхний элемент из стека операторов
 *
 * @param last Указатель на вершину стека
 * @return Указатель на новую вершину стека
 */
operator_stack *pop_op(operator_stack *last) {
  operator_stack *tmp = NULL;

  if (last != NULL) {
    tmp = last->next;
    free(last);
  }
  return tmp;
}

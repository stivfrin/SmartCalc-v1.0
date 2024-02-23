#ifndef CORE_S21_SMART_CALC_V1_0_H
#define CORE_S21_SMART_CALC_V1_0_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_ABSENT 0 /**< Код отсутствия ошибки */
#define INPUT_ERROR 1  /**< Код ошибки ввода */
#define MEMORY_ERROR 2 /**< Код ошибки памяти */
#define STACKSIZE 255  /**< Размер стека */

/**
 * @brief Структура для элемента стека операндов
 */
typedef struct operand_stack {
  double val; /**< Значение операнда */
  struct operand_stack
      *next; /**< Указатель на следующий элемент стека операндов */
} operand_stack;

/**
 * @brief Структура для элемента стека операторов
 */
typedef struct operator_stack {
  char val; /**< Значение оператора */
  struct operator_stack
      *next; /**< Указатель на следующий элемент стека операторов */
} operator_stack;

/**
 * @brief Проверяет валидность строки
 *
 * @param s Строка для проверки
 * @param error Указатель на переменную для сохранения кода ошибки
 */
void str_valid(char *s, int *error);

/**
 * @brief Инвертирует знак числа и генерирует обратную польскую запись
 *
 * @param s Входная строка
 * @param error Указатель на переменную для сохранения кода ошибки
 * @return Указатель на массив символов с обратной польской записью
 */
char *reverse_not(char *s, int *error);

/**
 * @brief Выполняет вычисление математического выражения
 *
 * @param s Обратная польская запись
 * @param num Указатель на переменную числа "x"
 * @return Результат вычисления
 */
double calculation(char *s, double *num);

/**
 * @brief Проверяет наличие унарных операторов "+" и "-"
 *
 * @param c Указатель на текущий символ
 * @param indx Указатель на текущий индекс символа
 * @param operator_s Стек операторов
 */
void check_unary_plus_or_minus(char *c, int *indx, operator_stack **operator_s);

/**
 * @brief Проверяет, является ли символ цифрой
 *
 * @param c Указатель на текущий символ
 * @return 1, если символ - цифра, иначе 0
 */
int check_digit(char *c);

/**
 * @brief Проверяет, является ли символ бинарным оператором
 *
 * @param c Указатель на текущий символ
 * @return 1, если символ - бинарный оператор, иначе 0
 */
int check_binary(char *c);

/**
 * @brief Проверяет, является ли символ унарным оператором
 *
 * @param c Указатель на текущий символ
 * @return 1, если символ - унарный оператор, иначе 0
 */
int check_unary(char *c);

/**
 * @brief Обрабатывает бинарный оператор
 *
 * @param _operator Символ бинарного оператора
 * @param op_s Стек операторов
 * @param out Указатель на выходную строку
 */
void get_binary(char *_operator, operator_stack **op_s, char **out);

/**
 * @brief Обрабатывает унарный оператор
 *
 * @param _operator Символ унарного оператора
 * @param op_s Стек операторов
 */
void get_unary(char *_operator, operator_stack **op_s);

/**
 * @brief Устанавливает приоритет оператора
 *
 * @param operation Символ оператора
 * @return Значение приоритета
 */
int set_op_priority(char operation);

/**
 * @brief Преобразует строку в число с плавающей точкой
 *
 * @param str Строка для преобразования
 * @return Результат преобразования
 */
double s21_atof(char *str);

/**
 * @brief Выполняет унарные операции
 *
 * @param operand_s Стек операндов
 * @param _operator Символ унарного оператора
 * @param value Значение для выполнения операции
 * @param result Результат операции
 */
void calculation_unary(operand_stack **operand_s, char *_operator, double value,
                       double result);

/**
 * @brief Выполняет бинарные операции
 *
 * @param operand Стек операндов
 * @param operator Символ бинарного оператора
 * @param value_1 Первый операнд
 * @param value_2 Второй операнд
 * @param result Результат операции
 */
void calculation_binary(operand_stack **op_s, char *op, double value_1,
                        double value_2, double result);
/**
 * @brief Подсчитывает количество элементов в стеке
 *
 * @param last Указатель на последний элемент стека
 * @return Количество элементов в стеке
 */
size_t count_stecksize(operator_stack *last);

/**
 * @brief Инициализирует новый элемент стека операндов
 *
 * @param num Значение операнда
 * @return Указатель на новый элемент стека
 */
operand_stack *init_num(double num);

/**
 * @brief Инициализирует новый элемент стека операторов
 *
 * @param op Значение оператора
 * @return Указатель на новый элемент стека
 */
operator_stack *init_op(char op);

/**
 * @brief Добавляет новый элемент в стек операндов
 *
 * @param last Указатель на последний элемент стека
 * @param num Значение операнда
 * @return Указатель на новый элемент стека
 */
operand_stack *push_num(operand_stack *last, double num);

/**
 * @brief Добавляет новый элемент в стек операторов
 *
 * @param last Указатель на последний элемент стека
 * @param op Значение оператора
 * @return Указатель на новый элемент стека
 */
operator_stack *push_op(operator_stack *last, char op);

/**
 * @brief Возвращает значение последнего оператора в стеке
 *
 * @param last Указатель на последний элемент стека
 * @return Значение последнего оператора
 */
char check_op(operator_stack *last);

/**
 * @brief Возвращает значение последнего операнда в стеке
 *
 * @param last Указатель на последний элемент стека
 * @return Значение последнего операнда
 */
double check_num(operand_stack *last);

/**
 * @brief Удаляет последний элемент из стека операндов
 *
 * @param last Указатель на последний элемент стека
 * @return Указатель на новый стек
 */
operand_stack *pop_num(operand_stack *last);

/**
 * @brief Удаляет последний элемент из стека операторов
 *
 * @param last Указатель на последний элемент стека
 * @return Указатель на новый стек
 */
operator_stack *pop_op(operator_stack *last);

#endif // CORE_S21_SMART_CALC_V1_0_H

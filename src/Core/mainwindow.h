#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qcustomplot.h"
#include <QMainWindow>
#include <QVector> // добавил

extern "C" {
#include "s21_SmartCalc_v1_0.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  QVector<double> x, y; /* added */

private slots:
  void concat(QString str);
  void on_pushButton_0_clicked();
  void on_pushButton_1_clicked();
  void on_pushButton_2_clicked();
  void on_pushButton_3_clicked();
  void on_pushButton_4_clicked();
  void on_pushButton_5_clicked();
  void on_pushButton_6_clicked();
  void on_pushButton_equal_clicked();
  void on_pushButton_7_clicked();
  void on_pushButton_8_clicked();
  void on_pushButton_9_clicked();
  void on_pushButton_dot_clicked();
  void on_pushButton_fmod_clicked();
  void on_pushButton_div_clicked();
  void on_pushButton_mult_clicked();
  void on_pushButton_plus_clicked();
  void on_pushButton_minus_clicked();
  void on_pushButton_pow_clicked();
  void on_pushButton_lb_clicked();
  void on_pushButton_rb_clicked();
  void on_pushButton_x_clicked();
  void on_pushButton_sin_clicked();
  void on_pushButton_cos_clicked();
  void on_pushButton_tan_clicked();
  void on_pushButton_log_clicked();
  void on_pushButton_sqrt_clicked();
  void on_pushButton_asin_clicked();
  void on_pushButton_acos_clicked();
  void on_pushButton_atan_clicked();
  void on_pushButton_ln_clicked();
  void on_pushButton_clear_clicked();
  void on_pushButton_AC_clicked();
  void on_pushButton_plus_minus_clicked();
  void on_pushButton_print_clicked();
};
#endif // MAINWINDOW_H

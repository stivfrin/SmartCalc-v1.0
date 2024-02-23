#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::concat(QString str) {
  QString text = ui->result_window->text();

  if (static_cast<int>(text.length()) == 1 &&
      *text.toLocal8Bit().constData() == '0' &&
      *str.toLocal8Bit().constData() != '.')
    ui->result_window->clear();

  ui->result_window->setText(ui->result_window->text() + str);
}

void MainWindow::on_pushButton_0_clicked() { concat("0"); }

void MainWindow::on_pushButton_1_clicked() { concat("1"); }

void MainWindow::on_pushButton_2_clicked() { concat("2"); }

void MainWindow::on_pushButton_3_clicked() { concat("3"); }

void MainWindow::on_pushButton_4_clicked() { concat("4"); }

void MainWindow::on_pushButton_5_clicked() { concat("5"); }

void MainWindow::on_pushButton_6_clicked() { concat("6"); }

void MainWindow::on_pushButton_7_clicked() { concat("7"); }

void MainWindow::on_pushButton_8_clicked() { concat("8"); }

void MainWindow::on_pushButton_9_clicked() { concat("9"); }

void MainWindow::on_pushButton_dot_clicked() { concat("."); }

void MainWindow::on_pushButton_fmod_clicked() { concat("%"); }

void MainWindow::on_pushButton_div_clicked() { concat("/"); }

void MainWindow::on_pushButton_mult_clicked() { concat("*"); }

void MainWindow::on_pushButton_plus_clicked() { concat("+"); }

void MainWindow::on_pushButton_minus_clicked() { concat("-"); }

void MainWindow::on_pushButton_pow_clicked() { concat("^"); }

void MainWindow::on_pushButton_lb_clicked() { concat("("); }

void MainWindow::on_pushButton_rb_clicked() { concat(")"); }

void MainWindow::on_pushButton_x_clicked() { concat("x"); }

void MainWindow::on_pushButton_sin_clicked() { concat("sin"); }

void MainWindow::on_pushButton_cos_clicked() { concat("cos"); }

void MainWindow::on_pushButton_tan_clicked() { concat("tan"); }

void MainWindow::on_pushButton_log_clicked() { concat("log"); }

void MainWindow::on_pushButton_sqrt_clicked() { concat("sqrt"); }

void MainWindow::on_pushButton_asin_clicked() { concat("asin"); }

void MainWindow::on_pushButton_acos_clicked() { concat("acos"); }

void MainWindow::on_pushButton_atan_clicked() { concat("atan"); }

void MainWindow::on_pushButton_ln_clicked() { concat("ln"); }

void MainWindow::on_pushButton_equal_clicked() {
  std::string str = ui->result_window->text().toStdString();
  char *ptr = &str[0];
  int error = 0;
  QString str_x = ui->result_window->text();
  double x = str_x.toDouble();
  char *polish = reverse_not(ptr, &error);

  if (error == 0) {
    double res = calculation(polish, &x);
    QString p = QString::number(res);
    ui->result_window->setText(p);
  } else
    ui->result_window->setText("ERROR!");
}

void MainWindow::on_pushButton_AC_clicked() {
  QString s = ui->result_window->text();

  if (s.length() > 0) {
    QString newtext = s.remove(s.length() - 1, 1);
    ui->result_window->setText(newtext);
  }
}

void MainWindow::on_pushButton_plus_minus_clicked() {
  double res = 0.;
  QString tmp;
  if (ui->pushButton_plus_minus->text() == "+/-") {
    res = (ui->result_window->text()).toDouble();
    res *= -1;
    tmp = QString::number(res, 'g', 15);
  }
  ui->result_window->setText(tmp);
}

void MainWindow::on_pushButton_print_clicked() {
  ui->widget->clearGraphs();
  x.clear();
  y.clear();

  QString str_xBegin = ui->lineEdit_xBegin->text();
  QString str_xEnd = ui->lineEdit_xEnd->text();
  QString str_step = ui->lineEdit_Step->text();

  double xStart = str_xBegin.toDouble();
  double xEnd = str_xEnd.toDouble();
  double step = str_step.toDouble();

  QString str_xMax = ui->lineEdit_xMax->text();
  QString str_xMin = ui->lineEdit_xMin->text();

  double xMax = str_xMax.toDouble();
  double xMin = str_xMin.toDouble();

  QString str_yMax = ui->lineEdit_yMax->text();
  QString str_yMin = ui->lineEdit_yMin->text();

  double yMax = str_yMax.toDouble();
  double yMin = str_yMin.toDouble();

  ui->widget->xAxis->setRange(xMin, xMax);
  ui->widget->yAxis->setRange(yMin, yMax);

  std::string str = ui->result_window->text().toStdString();
  char *ptr = &str[0];
  int error = 0;

  for (double tmp = xStart; tmp <= xEnd; tmp += step) {
    char *polish = reverse_not(ptr, &error);
    x.push_back(tmp);
    y.push_back(calculation(polish, &tmp));
  }

  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
}

void MainWindow::on_pushButton_clear_clicked() { ui->result_window->clear(); }

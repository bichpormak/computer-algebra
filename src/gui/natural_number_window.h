#ifndef NATURAL_WINDOW_H
#define NATURAL_WINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QScreen>
#include <QApplication>
#include <QLabel>
#include <QLineEdit>

#include "model/natural_number.h"



class NaturalNumberWindow : public QWidget {
    Q_OBJECT

public:
    NaturalNumberWindow(QWidget *parent = Q_NULLPTR);

private slots:
    void add_clicked();
    void subtract_clicked();
    void multiply_clicked();
    void compare_clicked();
    void is_zero_clicked();
    void add_one_clicked();
    void multiply_by_digit_clicked();
    void multiply_by_ten_in_power_clicked();
    void subtract_with_multiply_digit_clicked();
    void get_first_digit_after_division_number_on_ten_in_power_clicked();
    void division_numbers_with_remainder_clicked();
    void calculating_remainder_after_division_clicked();
    void calculate_gcd_clicked();
    void calculate_lcm_clicked();

private:
    QPushButton *compare_;
    QPushButton *is_zero_;
    QPushButton *add_;
    QPushButton *subtract_;
    QPushButton *multiply_;
    QPushButton *add_one_;
    QPushButton *multiply_by_digit_;
    QPushButton *multiply_by_ten_in_power_;
    QPushButton *subtract_with_multiply_digit_;
    QPushButton *get_first_digit_after_division_number_;
    QPushButton *division_numbers_with_remainder_;
    QPushButton *calculating_remainder_;
    QPushButton *calculate_gcd_;
    QPushButton *calculate_lcm_;

    QLabel *label_first_number_;
    QLabel *label_second_number_;
    QLabel *label_digit_;
    QLabel *label_result_;

    QLineEdit *lineedit_first_number_;
    QLineEdit *lineedit_second_number_;
    QLineEdit *lineedit_digit_;
    QLineEdit *lineedit_result_;

};


#endif
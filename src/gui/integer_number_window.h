#ifndef INTEGER_NUMBER_WINDOW_H
#define INTEGER_NUMBER_WINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QApplication>
#include <QScreen>


class IntegerNumberWindow : public QWidget {
    Q_OBJECT

public:
    IntegerNumberWindow(QWidget *parent = Q_NULLPTR);

private slots:
    void add_clicked();
    void subtract_clicked();
    void multiply_clicked();
    void get_absolute_value_clicked();
    void change_sign_clicked();
    void is_number_positive_clicked();
    void converting_natural_to_integer_clicked();
    void converting_positive_integer_to_natural_clicked();
    void calculating_quotient_clicked();
    void calculating_remainder_after_division_clicked();

private:
    QPushButton *add_;
    QPushButton *subtract_;
    QPushButton *multiply_;
    QPushButton *get_absolute_value_;
    QPushButton *change_sign_;
    QPushButton *is_number_positive_;
    QPushButton *converting_natural_to_integer_;
    QPushButton *converting_positive_integer_to_natural_;
    QPushButton *calculating_quotient_;
    QPushButton *calculating_remainder_after_division_;

    QLabel *label_first_number_;
    QLabel *label_second_number_;
    QLabel *label_result_;

    QLineEdit *lineedit_first_number_;
    QLineEdit *lineedit_second_number_;
    QLineEdit *lineedit_result_;

};



#endif
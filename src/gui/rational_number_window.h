#ifndef RATIONAL_NUMBER_WINDOW_H
#define RATIONAL_NUMBER_WINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QScreen>
#include <QGuiApplication>
#include <QMessageBox>
#include <QList>
#include <memory>

#include "fraction_input.h"
#include "model/rational_numbers.h"

class RationalNumberWindow : public QWidget
{
    Q_OBJECT
public:
    explicit RationalNumberWindow(QWidget *parent = nullptr);

private slots:
    void add_clicked();
    void subtract_clicked();
    void multiply_clicked();
    void divide_clicked();
    void convert_integer_to_fraction_clicked();
    void convert_reduced_fraction_to_integer_clicked();
    void reduce_fraction_clicked();
    void is_integer_clicked();

private:
    void performBinaryOperation(
        std::function<std::unique_ptr<RationalNumber>(RationalNumber&, RationalNumber&)> operation);
    void performUnaryOperation(
        std::function<std::unique_ptr<RationalNumber>(RationalNumber&)> operation);
    void performUnaryOperationInteger(
        std::function<std::unique_ptr<IntegerNumber>(RationalNumber&)> operation);

    FractionInput *fraction_input1_;
    FractionInput *fraction_input2_;
    FractionInput *fraction_result_;

    QPushButton *add_;
    QPushButton *subtract_;
    QPushButton *multiply_;
    QPushButton *divide_;
    QPushButton *convert_integer_to_fraction_;
    QPushButton *convert_reduced_fraction_to_integer_;
    QPushButton *reduce_fraction_;
    QPushButton *is_integer_;
};

#endif // RATIONAL_NUMBER_WINDOW_H

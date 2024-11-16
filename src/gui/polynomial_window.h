#ifndef POLYNOMIAL_WINDOW_H
#define POLYNOMIAL_WINDOW_H

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

#include "polynomial_input.h"
#include "model/polynomial.h"

class PolynomialWindow : public QWidget
{
    Q_OBJECT
public:
    explicit PolynomialWindow(QWidget *parent = nullptr);

private slots:
    void add_clicked();
    void subtract_clicked();
    void multiply_clicked();
    void multiply_by_rational_clicked();
    void multiply_by_x_power_clicked();
    void leading_coefficient_clicked();
    void degree_clicked();
    void divide_clicked();
    void derivative_clicked();
    void simplify_roots_clicked();
    void normalize_clicked();
    void remainder_clicked();
    void gcd_clicked();

private:
    void performBinaryOperation(
        std::function<std::unique_ptr<Polynomial>(const Polynomial&, const Polynomial&)> operation);
    void performUnaryOperation(
        std::function<std::unique_ptr<Polynomial>(const Polynomial&)> operation);

    PolynomialInput *polynomial_input1_;
    PolynomialInput *polynomial_input2_;
    PolynomialInput *polynomial_result_;

    QPushButton *add_;
    QPushButton *subtract_;
    QPushButton *multiply_;
    QPushButton *divide_;
    QPushButton *derivative_;
    QPushButton *simplify_roots_;
    QPushButton *multiply_by_rational_;
    QPushButton *multiply_by_x_power_;
    QPushButton *leading_coefficient_;
    QPushButton *degree_;
    QPushButton *normalize_;
    QPushButton *remainder_clicked_;
    QPushButton *gcd_;

    void displayPolynomial(const std::unique_ptr<Polynomial>& poly);
};

#endif // POLYNOMIAL_WINDOW_H

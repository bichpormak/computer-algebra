#ifndef POLYNOMIAL_INPUT_H
#define POLYNOMIAL_INPUT_H

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <memory>
#include "model/polynomial.h"

class PolynomialInput : public QWidget
{
    Q_OBJECT
public:
    explicit PolynomialInput(QWidget *parent = nullptr);

    // Получение объекта Polynomial из введенного текста
    std::unique_ptr<Polynomial> getPolynomial() const;

    // Установка текста многочлена
    void setPolynomialText(const QString &text);

    // Сделать поле только для чтения
    void setReadOnly(bool readOnly);

private:
    QLineEdit *polynomial_edit_;
};

#endif // POLYNOMIAL_INPUT_H

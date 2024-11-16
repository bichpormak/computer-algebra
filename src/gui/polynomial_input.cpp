#include "polynomial_input.h"
#include <regex>
#include <stdexcept>

PolynomialInput::PolynomialInput(QWidget *parent)
    : QWidget(parent)
{
    polynomial_edit_ = new QLineEdit(this);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(polynomial_edit_);
    setLayout(layout);
}

std::unique_ptr<Polynomial> PolynomialInput::getPolynomial() const
{
    QString text = polynomial_edit_->text().trimmed();
    if (text.isEmpty()) {
        return nullptr;
    }

    try {
        return Polynomial::fromString(text.toStdString());
    } catch (const std::exception &e) {
        // Если парсинг не удался, возвращаем nullptr
        return nullptr;
    }
}

void PolynomialInput::setPolynomialText(const QString &text)
{
    polynomial_edit_->setText(text);
}

void PolynomialInput::setReadOnly(bool readOnly)
{
    polynomial_edit_->setReadOnly(readOnly);
}

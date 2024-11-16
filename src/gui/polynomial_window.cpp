// polynomial_window.cpp

#include "polynomial_window.h"
#include "polynomial_input.h"
#include <QInputDialog>     // Добавлено для использования QInputDialog
#include <QMessageBox>     // Добавлено для использования QMessageBox
#include <regex>
#include <stdexcept>

PolynomialWindow::PolynomialWindow(QWidget *parent)
    : QWidget(parent)
{
    polynomial_input1_ = new PolynomialInput(this);
    polynomial_input2_ = new PolynomialInput(this);
    polynomial_result_ = new PolynomialInput(this);
    polynomial_result_->setReadOnly(true); // Результат только для чтения

    QGridLayout *inputLayout = new QGridLayout;
    inputLayout->addWidget(polynomial_input1_, 0, 0);
    inputLayout->addWidget(polynomial_input2_, 0, 1);
    inputLayout->addWidget(polynomial_result_, 0, 2);

    add_ = new QPushButton("Сложение", this);
    subtract_ = new QPushButton("Вычитание", this);
    multiply_ = new QPushButton("Умножение", this);
    divide_ = new QPushButton("Деление", this);
    derivative_ = new QPushButton("Производная", this);
    simplify_roots_ = new QPushButton("Кратные корни", this);
    multiply_by_rational_ = new QPushButton("Умножение на рациональное", this);
    multiply_by_x_power_ = new QPushButton("Умножение на x^k", this);
    leading_coefficient_ = new QPushButton("Старший коэффициент", this);
    degree_ = new QPushButton("Старшая степень", this);
    normalize_ = new QPushButton("Деление на старший коэффициент", this);
    remainder_clicked_ = new QPushButton("Остаток", this);
    gcd_ = new QPushButton("НОД", this);

    QList<QPushButton*> buttons = {add_, subtract_, multiply_,
                                   divide_, derivative_, simplify_roots_,
                                   multiply_by_rational_, leading_coefficient_, multiply_by_x_power_,
                                   degree_, normalize_, remainder_clicked_, gcd_};

    for(auto &button : buttons) {
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

    QGridLayout *buttonsLayout = new QGridLayout;
    buttonsLayout->addWidget(add_, 0, 0);
    buttonsLayout->addWidget(subtract_, 0, 1);
    buttonsLayout->addWidget(multiply_, 1, 0);
    buttonsLayout->addWidget(divide_, 1, 1);
    buttonsLayout->addWidget(derivative_, 2, 0);
    buttonsLayout->addWidget(simplify_roots_, 2, 1);
    buttonsLayout->addWidget(multiply_by_rational_, 3, 0);
    buttonsLayout->addWidget(leading_coefficient_, 3, 1);
    buttonsLayout->addWidget(multiply_by_x_power_, 4, 0);
    buttonsLayout->addWidget(degree_, 4, 1);
    buttonsLayout->addWidget(normalize_, 5, 0);
    buttonsLayout->addWidget(remainder_clicked_, 5, 1);
    buttonsLayout->addWidget(gcd_, 6, 0);

    buttonsLayout->setSpacing(10);
    buttonsLayout->setContentsMargins(10, 10, 10, 10);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);

    setWindowTitle("Многочлены");
    setFixedSize(800, 800);

    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen) {
        QRect screenGeometry = screen->availableGeometry();
        int x = (screenGeometry.width() - width()) / 2;
        int y = (screenGeometry.height() - height()) / 2;
        move(x, y);
    }

    // Подключение кнопок к соответствующим слотам
    connect(add_, &QPushButton::clicked, this, &PolynomialWindow::add_clicked);
    connect(subtract_, &QPushButton::clicked, this, &PolynomialWindow::subtract_clicked);
    connect(multiply_, &QPushButton::clicked, this, &PolynomialWindow::multiply_clicked);
    connect(divide_, &QPushButton::clicked, this, &PolynomialWindow::divide_clicked);
    connect(derivative_, &QPushButton::clicked, this, &PolynomialWindow::derivative_clicked);
    connect(simplify_roots_, &QPushButton::clicked, this, &PolynomialWindow::simplify_roots_clicked);
    connect(multiply_by_rational_, &QPushButton::clicked, this, &PolynomialWindow::multiply_by_rational_clicked);
    connect(leading_coefficient_, &QPushButton::clicked, this, &PolynomialWindow::leading_coefficient_clicked);
    connect(multiply_by_x_power_, &QPushButton::clicked, this, &PolynomialWindow::multiply_by_x_power_clicked); // Исправлено
    connect(degree_, &QPushButton::clicked, this, &PolynomialWindow::degree_clicked);
    connect(normalize_, &QPushButton::clicked, this, &PolynomialWindow::normalize_clicked);
    connect(remainder_clicked_, &QPushButton::clicked, this, &PolynomialWindow::remainder_clicked);
    connect(gcd_, &QPushButton::clicked, this, &PolynomialWindow::gcd_clicked);
}

void PolynomialWindow::performBinaryOperation(
    std::function<std::unique_ptr<Polynomial>(const Polynomial&, const Polynomial&)> operation)
{
    try {
        std::unique_ptr<Polynomial> poly1 = polynomial_input1_->getPolynomial();
        std::unique_ptr<Polynomial> poly2 = polynomial_input2_->getPolynomial();

        if (!poly1 || !poly2) {
            throw std::invalid_argument("Неверный формат многочлена.");
        }

        std::unique_ptr<Polynomial> result = operation(*poly1, *poly2);

        displayPolynomial(result);
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void PolynomialWindow::performUnaryOperation(
    std::function<std::unique_ptr<Polynomial>(const Polynomial&)> operation)
{
    try {
        std::unique_ptr<Polynomial> poly1 = polynomial_input1_->getPolynomial();

        if (!poly1) {
            throw std::invalid_argument("Неверный формат многочлена.");
        }

        std::unique_ptr<Polynomial> result = operation(*poly1);

        displayPolynomial(result);
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void PolynomialWindow::add_clicked()
{
    performBinaryOperation([](const Polynomial& a, const Polynomial& b) -> std::unique_ptr<Polynomial> {
        return a.add(b);
    });
}

void PolynomialWindow::subtract_clicked()
{
    performBinaryOperation([](const Polynomial& a, const Polynomial& b) -> std::unique_ptr<Polynomial> {
        return a.subtract(b);
    });
}

void PolynomialWindow::multiply_clicked()
{
    performBinaryOperation([](const Polynomial& a, const Polynomial& b) -> std::unique_ptr<Polynomial> {
        return a.multiply(b);
    });
}

void PolynomialWindow::divide_clicked()
{
    try {
        std::unique_ptr<Polynomial> poly1 = polynomial_input1_->getPolynomial();
        std::unique_ptr<Polynomial> poly2 = polynomial_input2_->getPolynomial();

        if (!poly1 || !poly2) {
            throw std::invalid_argument("Неверный формат многочлена.");
        }

        std::unique_ptr<Polynomial> remainder;
        std::unique_ptr<Polynomial> quotient = poly1->divide(*poly2, remainder);

        QString resultStr = "Частное: " + QString::fromStdString(quotient->toString()) +
                            "\nОстаток: " + QString::fromStdString(remainder->toString());

        polynomial_result_->setPolynomialText(resultStr);
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void PolynomialWindow::derivative_clicked()
{
    performUnaryOperation([](const Polynomial& a) -> std::unique_ptr<Polynomial> {
        return a.derivative();
    });
}

void PolynomialWindow::simplify_roots_clicked()
{
    performUnaryOperation([](const Polynomial& a) -> std::unique_ptr<Polynomial> {
        return a.simplify_roots();
    });
}

void PolynomialWindow::multiply_by_rational_clicked() {
    try {
        // Запросить у пользователя рациональное число
        bool ok;
        QString text = QInputDialog::getText(this, "Умножение на рациональное",
                                             "Введите рациональное число (например, 3/2):", QLineEdit::Normal, "", &ok);
        if (!ok || text.trimmed().isEmpty()) {
            return; // Пользователь отменил ввод или ввел пустую строку
        }

        // Парсинг рационального числа
        std::string rationalStr = text.toStdString();
        std::regex rationalRegex(R"(([+-]?\d+)(?:/(\d+))?)");
        std::smatch match;
        if (!std::regex_match(rationalStr, match, rationalRegex)) {
            throw std::invalid_argument("Неверный формат рационального числа.");
        }

        int numerator = std::stoi(match[1].str());
        int denominator = 1;
        if (match[2].matched) {
            denominator = std::stoi(match[2].str());
            if (denominator == 0) {
                throw std::invalid_argument("Знаменатель не может быть равен нулю.");
            }
        }

        // Исправлено: Используем фигурные скобки для инициализации
        RationalNumber scalar{IntegerNumber(numerator), NaturalNumber(denominator)};

        // Получить первый многочлен
        std::unique_ptr<Polynomial> poly1 = polynomial_input1_->getPolynomial();
        if (!poly1) {
            throw std::invalid_argument("Неверный формат первого многочлена.");
        }

        // Умножить на рациональное число
        std::unique_ptr<Polynomial> result = poly1->multiply_by_rational(scalar);
        result->normalize();

        displayPolynomial(result);
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void PolynomialWindow::multiply_by_x_power_clicked() {
    try {
        // Запросить степень k у пользователя
        bool ok;
        int k = QInputDialog::getInt(this, "Умножение на x^k",
                                     "Введите степень k:", 1, 0, 100, 1, &ok);
        if (!ok) {
            return; // Пользователь отменил ввод
        }

        // Получить первый многочлен
        std::unique_ptr<Polynomial> poly1 = polynomial_input1_->getPolynomial();
        if (!poly1) {
            throw std::invalid_argument("Неверный формат первого многочлена.");
        }

        // Умножить на x^k
        std::unique_ptr<Polynomial> result = poly1->multiply_by_x_power(k);
        result->normalize();

        displayPolynomial(result);
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void PolynomialWindow::leading_coefficient_clicked() {
    try {
        // Получить первый многочлен
        std::unique_ptr<Polynomial> poly1 = polynomial_input1_->getPolynomial();
        if (!poly1) {
            throw std::invalid_argument("Неверный формат многочлена.");
        }

        if (poly1->getCoefficients().empty()) {
            throw std::invalid_argument("Многочлен не имеет коэффициентов.");
        }

        const RationalNumber& leading_coeff = poly1->leading_coefficient();

        QString coeffStr;
        int num = leading_coeff.get_numerator().get_number();
        int den = leading_coeff.get_denominator().get_number();

        if (den != 1) {
            coeffStr = QString::number(num) + "/" + QString::number(den);
        } else {
            coeffStr = QString::number(num);
        }

        QMessageBox::information(this, "Старший коэффициент", "Старший коэффициент: " + coeffStr);
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void PolynomialWindow::degree_clicked() {
    try {
        // Получить первый многочлен
        std::unique_ptr<Polynomial> poly1 = polynomial_input1_->getPolynomial();
        if (!poly1) {
            throw std::invalid_argument("Неверный формат многочлена.");
        }

        if (poly1->getCoefficients().empty()) {
            throw std::invalid_argument("Многочлен не имеет степени.");
        }

        int deg = poly1->degree();

        QMessageBox::information(this, "Старшая степень", "Старшая степень: " + QString::number(deg));
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void PolynomialWindow::normalize_clicked() {
    try {
        // Получить первый многочлен
        std::unique_ptr<Polynomial> poly1 = polynomial_input1_->getPolynomial();
        if (!poly1) {
            throw std::invalid_argument("Неверный формат многочлена.");
        }

        // Получить старший коэффициент
        if (poly1->getCoefficients().empty()) {
            throw std::invalid_argument("Многочлен не имеет коэффициентов.");
        }

        RationalNumber leading_coeff = poly1->leading_coefficient();

        // Проверка, не равен ли старший коэффициент нулю
        if (leading_coeff.get_numerator().get_number() == 0) {
            throw std::invalid_argument("Старший коэффициент равен нулю.");
        }

        // Деление многочлена на старший коэффициент
        std::map<int, RationalNumber> new_coeffs;
        for (const auto& [degree, coeff] : poly1->getCoefficients()) {
            RationalNumber new_coeff = coeff / leading_coeff;
            new_coeffs[degree] = new_coeff;
        }

        std::unique_ptr<Polynomial> normalized_poly = std::make_unique<Polynomial>(new_coeffs);
        normalized_poly->normalize();

        displayPolynomial(normalized_poly);
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void PolynomialWindow::remainder_clicked() {
    try {
        std::unique_ptr<Polynomial> poly1 = polynomial_input1_->getPolynomial();
        std::unique_ptr<Polynomial> poly2 = polynomial_input2_->getPolynomial();

        if (!poly1 || !poly2) {
            throw std::invalid_argument("Неверный формат многочлена.");
        }

        std::unique_ptr<Polynomial> remainder;
        poly1->divide(*poly2, remainder);

        QString resultStr = "Остаток: " + QString::fromStdString(remainder->toString());

        QMessageBox::information(this, "Остаток", resultStr);
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void PolynomialWindow::gcd_clicked() {
    try {
        std::unique_ptr<Polynomial> poly1 = polynomial_input1_->getPolynomial();
        std::unique_ptr<Polynomial> poly2 = polynomial_input2_->getPolynomial();

        if (!poly1 || !poly2) {
            throw std::invalid_argument("Неверный формат многочлена.");
        }

        std::unique_ptr<Polynomial> gcd_poly = Polynomial::gcd(*poly1, *poly2);
        gcd_poly->normalize();

        QString resultStr = "НОД: " + QString::fromStdString(gcd_poly->toString());

        QMessageBox::information(this, "НОД", resultStr);
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void PolynomialWindow::displayPolynomial(const std::unique_ptr<Polynomial>& poly)
{
    if (poly) {
        polynomial_result_->setPolynomialText(QString::fromStdString(poly->toString()));
    } else {
        polynomial_result_->setPolynomialText("0");
    }
}

#include "rational_number_window.h"

RationalNumberWindow::RationalNumberWindow(QWidget *parent)
    : QWidget(parent)
{
    fraction_input1_ = new FractionInput(this);
    fraction_input2_ = new FractionInput(this);
    fraction_result_ = new FractionInput(this);
    fraction_result_->setEnabled(false); // Результат только для чтения

    QGridLayout *inputLayout = new QGridLayout;
    inputLayout->addWidget(fraction_input1_, 0, 0);
    inputLayout->addWidget(fraction_input2_, 0, 1);
    inputLayout->addWidget(fraction_result_, 0, 2);

    add_ = new QPushButton("Сложение", this);
    subtract_ = new QPushButton("Вычитание", this);
    multiply_ = new QPushButton("Умножение", this);
    divide_ = new QPushButton("Деление", this);
    convert_integer_to_fraction_ = new QPushButton("Целое в дробь", this);
    convert_reduced_fraction_to_integer_ = new QPushButton("Дробь в целое", this);
    reduce_fraction_ = new QPushButton("Сократить дробь", this);
    is_integer_ = new QPushButton("Проверить на целое", this);

    QList<QPushButton*> buttons = {add_, subtract_, multiply_,
                                   divide_, convert_integer_to_fraction_,
                                   convert_reduced_fraction_to_integer_,
                                   reduce_fraction_, is_integer_};

    for(auto &button : buttons) {
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

    QGridLayout *buttonsLayout = new QGridLayout;
    buttonsLayout->addWidget(add_, 0, 0);
    buttonsLayout->addWidget(subtract_, 0, 1);
    buttonsLayout->addWidget(multiply_, 1, 0);
    buttonsLayout->addWidget(divide_, 1, 1);
    buttonsLayout->addWidget(convert_integer_to_fraction_, 2, 0);
    buttonsLayout->addWidget(convert_reduced_fraction_to_integer_, 2, 1);
    buttonsLayout->addWidget(reduce_fraction_, 3, 0);
    buttonsLayout->addWidget(is_integer_, 3, 1);

    buttonsLayout->setSpacing(10);
    buttonsLayout->setContentsMargins(10, 10, 10, 10);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);

    setWindowTitle("Рациональные числа");
    setFixedSize(600, 600);

    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen) {
        QRect screenGeometry = screen->availableGeometry();
        int x = (screenGeometry.width() - width()) / 2;
        int y = (screenGeometry.height() - height()) / 2;
        move(x, y);
    }

    connect(add_, &QPushButton::clicked, this, &RationalNumberWindow::add_clicked);
    connect(subtract_, &QPushButton::clicked, this, &RationalNumberWindow::subtract_clicked);
    connect(multiply_, &QPushButton::clicked, this, &RationalNumberWindow::multiply_clicked);
    connect(divide_, &QPushButton::clicked, this, &RationalNumberWindow::divide_clicked);
    connect(convert_integer_to_fraction_, &QPushButton::clicked, this, &RationalNumberWindow::convert_integer_to_fraction_clicked);
    connect(convert_reduced_fraction_to_integer_, &QPushButton::clicked, this, &RationalNumberWindow::convert_reduced_fraction_to_integer_clicked);
    connect(is_integer_, &QPushButton::clicked, this, &RationalNumberWindow::is_integer_clicked);
    connect(reduce_fraction_, &QPushButton::clicked, this, &RationalNumberWindow::reduce_fraction_clicked);
}

void RationalNumberWindow::performBinaryOperation(
    std::function<std::unique_ptr<RationalNumber>(RationalNumber&, RationalNumber&)> operation)
{
    bool ok1, ok2, ok3, ok4;
    int64_t num1 = fraction_input1_->numeratorText().toLong(&ok1);
    int64_t denom1 = fraction_input1_->denominatorText().toLong(&ok2);
    int64_t num2 = fraction_input2_->numeratorText().toLong(&ok3);
    int64_t denom2 = fraction_input2_->denominatorText().toLong(&ok4);

    if (!ok1 || !ok2 || !ok3 || !ok4 || denom1 == 0 || denom2 == 0) {
        QMessageBox::warning(this, "Ошибка ввода", "Пожалуйста, введите корректные числа и знаменатель не равный нулю");
        return;
    }

    try {
        RationalNumber rat1{IntegerNumber(num1), NaturalNumber(denom1)};
        RationalNumber rat2{IntegerNumber(num2), NaturalNumber(denom2)};

        std::unique_ptr<RationalNumber> result = operation(rat1, rat2);

        fraction_result_->setNumeratorText(QString::number(result->get_integer()->get_number()));
        fraction_result_->setDenominatorText(QString::number(result->get_natural()->get_number()));
    } catch (const std::invalid_argument &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void RationalNumberWindow::performUnaryOperation(
    std::function<std::unique_ptr<RationalNumber>(RationalNumber&)> operation)
{
    bool ok1, ok2;
    int64_t num1 = fraction_input1_->numeratorText().toLong(&ok1);
    int64_t denom1 = fraction_input1_->denominatorText().toLong(&ok2);

    if (!ok1 || !ok2 || denom1 == 0) {
        QMessageBox::warning(this, "Ошибка ввода", "Пожалуйста, введите корректные числа и знаменатель не равный нулю");
        return;
    }

    try {
        RationalNumber rat1{IntegerNumber(num1), NaturalNumber(denom1)};

        std::unique_ptr<RationalNumber> result = operation(rat1);

        fraction_result_->setNumeratorText(QString::number(result->get_integer()->get_number()));
        fraction_result_->setDenominatorText(QString::number(result->get_natural()->get_number()));
    } catch (const std::invalid_argument &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void RationalNumberWindow::performUnaryOperationInteger(
    std::function<std::unique_ptr<IntegerNumber>(RationalNumber&)> operation)
{
    bool ok1, ok2;
    int64_t num1 = fraction_input1_->numeratorText().toLong(&ok1);
    int64_t denom1 = fraction_input1_->denominatorText().toLong(&ok2);

    if (!ok1 || !ok2 || denom1 == 0) {
        QMessageBox::warning(this, "Ошибка ввода", "Пожалуйста, введите корректные числа и знаменатель не равный нулю");
        return;
    }

    try {
        RationalNumber rat1{IntegerNumber(num1), NaturalNumber(denom1)};

        std::unique_ptr<IntegerNumber> result = operation(rat1);

        fraction_result_->setNumeratorText(QString::number(result->get_number()));
        fraction_result_->setDenominatorText("");
    } catch (const std::invalid_argument &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void RationalNumberWindow::add_clicked()
{
    performBinaryOperation([](RationalNumber& a, RationalNumber& b) {
        return a.add(b);
    });
}

void RationalNumberWindow::subtract_clicked()
{
    performBinaryOperation([](RationalNumber& a, RationalNumber& b) {
        return a.subtract(b);
    });
}

void RationalNumberWindow::multiply_clicked()
{
    performBinaryOperation([](RationalNumber& a, RationalNumber& b) {
        return a.multiply(b);
    });
}

void RationalNumberWindow::divide_clicked()
{
    performBinaryOperation([](RationalNumber& a, RationalNumber& b) {
        return a.divide(b);
    });
}

void RationalNumberWindow::reduce_fraction_clicked()
{
    performUnaryOperation([](RationalNumber& a) {
        return a.reduce_fraction();
    });
}

void RationalNumberWindow::convert_reduced_fraction_to_integer_clicked()
{
    performUnaryOperationInteger([](RationalNumber& a) {
        return a.convert_reduced_fraction_to_integer();
    });
}

void RationalNumberWindow::is_integer_clicked()
{
    bool ok1, ok2;
    int64_t num1 = fraction_input1_->numeratorText().toLong(&ok1);
    int64_t denom1 = fraction_input1_->denominatorText().toLong(&ok2);

    if (!ok1 || !ok2 || denom1 == 0) {
        QMessageBox::warning(this, "Ошибка ввода", "Пожалуйста, введите корректные числа и знаменатель не равный нулю");
        return;
    }

    try {
        RationalNumber rat1{IntegerNumber(num1), NaturalNumber(denom1)};
        bool result = rat1.is_integer();

        fraction_result_->setNumeratorText(result ? "Да" : "Нет");
        fraction_result_->setDenominatorText("");
    } catch (const std::invalid_argument &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void RationalNumberWindow::convert_integer_to_fraction_clicked()
{
    bool ok;
    int64_t integerNumber = fraction_input1_->numeratorText().toLong(&ok);

    if (!ok) {
        QMessageBox::warning(this, "Ошибка ввода", "Пожалуйста, введите корректное целое число");
        return;
    }

    try {
        IntegerNumber intNumber(integerNumber);
        RationalNumber rat{IntegerNumber(0), NaturalNumber(0)};
        std::unique_ptr<RationalNumber> result = rat.convert_integer_to_fraction(intNumber);

        fraction_result_->setNumeratorText(QString::number(result->get_integer()->get_number()));
        fraction_result_->setDenominatorText(QString::number(result->get_natural()->get_number()));
    } catch (const std::invalid_argument &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}
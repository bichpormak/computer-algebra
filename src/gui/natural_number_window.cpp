#include "natural_number_window.h"

NaturalNumberWindow::NaturalNumberWindow(QWidget *parent)
    : QWidget(parent)
{
    label_first_number_ = new QLabel("Первое число:", this);
    label_second_number_ = new QLabel("Второе число(если надо):", this);
    label_digit_ = new QLabel("Цифра(если надо):", this);
    label_result_ = new QLabel("Результат:", this);

    lineedit_first_number_ = new QLineEdit(this);
    lineedit_second_number_ = new QLineEdit(this);
    lineedit_digit_ = new QLineEdit(this);
    lineedit_result_ = new QLineEdit(this);
    lineedit_result_->setReadOnly(true);

    QGridLayout *inputLayout = new QGridLayout;
    inputLayout->addWidget(label_first_number_, 0, 0);
    inputLayout->addWidget(lineedit_first_number_, 1, 0);
    inputLayout->addWidget(label_second_number_, 0, 1);
    inputLayout->addWidget(lineedit_second_number_, 1, 1);
    inputLayout->addWidget(label_digit_, 0, 2);
    inputLayout->addWidget(lineedit_digit_, 1, 2);
    inputLayout->addWidget(label_result_, 0, 3);
    inputLayout->addWidget(lineedit_result_, 1, 3);

    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    compare_ = new QPushButton("Сравнение чисел", this);
    is_zero_ = new QPushButton("Проверка на ноль", this);
    add_ = new QPushButton("Сложение", this);
    subtract_ = new QPushButton("Вычитание", this);
    multiply_ = new QPushButton("Умножение", this);
    add_one_ = new QPushButton("Добавить 1", this);
    multiply_by_digit_ = new QPushButton("Умножить на цифру", this);
    multiply_by_ten_in_power_ = new QPushButton("Умножить на 10^k", this);
    subtract_with_multiply_digit_ = new QPushButton("Вычитание с умножением на цифру", this);
    get_first_digit_after_division_number_ = new QPushButton("Первая цифра при делении", this);
    division_numbers_with_remainder_ = new QPushButton("Деление с остатком", this);
    calculating_remainder_ = new QPushButton("Вычисление остатка", this);
    calculate_gcd_ = new QPushButton("НОД", this);
    calculate_lcm_ = new QPushButton("НОК", this);

    QList<QPushButton*> buttons = {compare_, is_zero_, add_, subtract_, multiply_,
                                   add_one_, multiply_by_digit_, multiply_by_ten_in_power_,
                                   subtract_with_multiply_digit_, get_first_digit_after_division_number_,
                                   division_numbers_with_remainder_, calculating_remainder_,
                                   calculate_gcd_, calculate_lcm_};

    for(auto &button : buttons) {
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

    QGridLayout *buttonsLayout = new QGridLayout;
    buttonsLayout->addWidget(compare_, 0, 0);
    buttonsLayout->addWidget(is_zero_, 0, 1);
    buttonsLayout->addWidget(add_, 1, 0);
    buttonsLayout->addWidget(subtract_, 1, 1);
    buttonsLayout->addWidget(multiply_, 2, 0);
    buttonsLayout->addWidget(add_one_, 2, 1);
    buttonsLayout->addWidget(multiply_by_digit_, 3, 0);
    buttonsLayout->addWidget(multiply_by_ten_in_power_, 3, 1);
    buttonsLayout->addWidget(subtract_with_multiply_digit_, 4, 0);
    buttonsLayout->addWidget(get_first_digit_after_division_number_, 4, 1);
    buttonsLayout->addWidget(division_numbers_with_remainder_, 5, 0);
    buttonsLayout->addWidget(calculating_remainder_, 5, 1);
    buttonsLayout->addWidget(calculate_gcd_, 6, 0);
    buttonsLayout->addWidget(calculate_lcm_, 6, 1);

    buttonsLayout->setSpacing(10);
    buttonsLayout->setContentsMargins(10, 10, 10, 10);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);

    setWindowTitle("Натуральные числа");
    setFixedSize(800, 800);

    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen) {
        QRect screenGeometry = screen->availableGeometry();
        int x = (screenGeometry.width() - width()) / 2;
        int y = (screenGeometry.height() - height()) / 2;
        move(x, y);
    }

    connect(compare_, &QPushButton::clicked, this, &NaturalNumberWindow::compare_clicked);
    connect(is_zero_, &QPushButton::clicked, this, &NaturalNumberWindow::is_zero_clicked);
    connect(add_, &QPushButton::clicked, this, &NaturalNumberWindow::add_clicked);
    connect(subtract_, &QPushButton::clicked, this, &NaturalNumberWindow::subtract_clicked);
    connect(multiply_, &QPushButton::clicked, this, &NaturalNumberWindow::multiply_clicked);
    connect(add_one_, &QPushButton::clicked, this, &NaturalNumberWindow::add_one_clicked);
    connect(multiply_by_digit_, &QPushButton::clicked, this, &NaturalNumberWindow::multiply_by_digit_clicked);
    connect(multiply_by_ten_in_power_, &QPushButton::clicked, this, &NaturalNumberWindow::multiply_by_ten_in_power_clicked);
    connect(subtract_with_multiply_digit_, &QPushButton::clicked, this, &NaturalNumberWindow::subtract_with_multiply_digit_clicked);
    connect(get_first_digit_after_division_number_, &QPushButton::clicked, this, &NaturalNumberWindow::get_first_digit_after_division_number_on_ten_in_power_clicked);
    connect(division_numbers_with_remainder_, &QPushButton::clicked, this, &NaturalNumberWindow::division_numbers_with_remainder_clicked);
    connect(calculating_remainder_, &QPushButton::clicked, this, &NaturalNumberWindow::calculating_remainder_after_division_clicked);
    connect(calculate_gcd_, &QPushButton::clicked, this, &NaturalNumberWindow::calculate_gcd_clicked);
    connect(calculate_lcm_, &QPushButton::clicked, this, &NaturalNumberWindow::calculate_lcm_clicked);
}

void NaturalNumberWindow::add_clicked() {

    bool ok1;
    bool ok2;
    int64_t num1 = lineedit_first_number_->text().toLong(&ok1);
    int64_t num2 = lineedit_second_number_->text().toLong(&ok2);

    if (!ok1 || !ok2) {
        QMessageBox::warning(this, "Ошибка ввода", "Пожалуйста, введите корректные натуральные числа");
        return;
    }

    try {
        NaturalNumber first_natural_number(num1);
        NaturalNumber second_natural_number(num2);

        std::unique_ptr<Number> result = first_natural_number.add(second_natural_number);

        QString result_text = QString::number(result->get_number());

        lineedit_result_->setText(result_text);
    } catch (const std::invalid_argument &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }

}

void NaturalNumberWindow::subtract_clicked() {

    bool ok1;
    bool ok2;
    int64_t num1 = lineedit_first_number_->text().toLong(&ok1);
    int64_t num2 = lineedit_second_number_->text().toLong(&ok2);

    if (!ok1 || !ok2) {
        QMessageBox::warning(this, "Ошибка ввода", "Пожалуйста, введите корректные натуральные числа");
        return;
    }

    try {
        NaturalNumber first_natural_number(num1);
        NaturalNumber second_natural_number(num2);

        std::unique_ptr<Number> result = first_natural_number.subtract(second_natural_number);

        QString result_text = QString::number(result->get_number());

        lineedit_result_->setText(result_text);
    } catch (const std::invalid_argument &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }

}

void NaturalNumberWindow::multiply_clicked() {

    bool ok1;
    bool ok2;
    int64_t num1 = lineedit_first_number_->text().toLong(&ok1);
    int64_t num2 = lineedit_second_number_->text().toLong(&ok2);

    if (!ok1 || !ok2) {
        QMessageBox::warning(this, "Ошибка ввода", "Пожалуйста, введите корректные натуральные числа");
        return;
    }

    try {
        NaturalNumber first_natural_number(num1);
        NaturalNumber second_natural_number(num2);

        std::unique_ptr<Number> result = first_natural_number.multiply(second_natural_number);

        QString result_text = QString::number(result->get_number());

        lineedit_result_->setText(result_text);
    } catch (const std::invalid_argument &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }

}


void NaturalNumberWindow::compare_clicked() {

    bool ok1;
    bool ok2;
    int64_t num1 = lineedit_first_number_->text().toLong(&ok1);
    int64_t num2 = lineedit_second_number_->text().toLong(&ok2);

    if (!ok1 || !ok2) {
        QMessageBox::warning(this, "Ошибка ввода", "Пожалуйста, введите корректные натуральные числа");
        return;
    }

    try {
        NaturalNumber natural1(num1);
        NaturalNumber natural2(num2);

        uint8_t comparison_result = natural1.compare(natural2);

        QString result_text;
        switch (comparison_result) {
            case 1:
                result_text = "Второе число больше первого.";
            break;
            case 2:
                result_text = "Первое число больше второго.";
            break;
            default:
                result_text = "Числа равны.";
            break;
        }

        lineedit_result_->setText(result_text);
    } catch (const std::invalid_argument &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void NaturalNumberWindow::is_zero_clicked() {

    bool ok1;
    int64_t num1 = lineedit_first_number_->text().toLong(&ok1);

    if (!ok1) {
        QMessageBox::warning(this, "Ошибка ввода", "Пожалуйста, введите корректные натуральные числа");
        return;
    }

    try {
        NaturalNumber first_natural_number(num1);

        bool result = first_natural_number.is_zero();

        QString result_text;
        if (result) {
            result_text = "Да, число 0";
        } else {
            result_text = "Нет, число не 0";
        }

        lineedit_result_->setText(result_text);
    } catch (const std::invalid_argument &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }

}

void NaturalNumberWindow::add_one_clicked() {
    bool ok1;
    int64_t num1 = lineedit_first_number_->text().toLong(&ok1);

    if (!ok1) {
        QMessageBox::warning(this, "Ошибка ввода", "Пожалуйста, введите корректные натуральные числа");
        return;
    }

    try {
        NaturalNumber first_natural_number(num1);

        std::unique_ptr<Number> result = first_natural_number.add_one();

        QString result_text = QString::number(result->get_number());

        lineedit_result_->setText(result_text);
    } catch (const std::invalid_argument &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void NaturalNumberWindow::multiply_by_digit_clicked() {
    bool ok1;
    bool ok2;
    int64_t num1 = lineedit_first_number_->text().toLong(&ok1);
    int64_t num2 = lineedit_digit_->text().toLong(&ok2);
    if (!ok1 || !ok2) {
        QMessageBox::warning(this, "Ошибка ввода", "Пожалуйста, введите корректное натуральное число и цифру");
        return;
    }

    try {
        NaturalNumber first_natural_number(num1);

        std::unique_ptr<Number> result = first_natural_number.multiply_by_digit(num2);

        QString result_text = QString::number(result->get_number());

        lineedit_result_->setText(result_text);
    } catch (const std::invalid_argument &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void NaturalNumberWindow::multiply_by_ten_in_power_clicked() {
    bool ok1;
    bool ok2;
    int64_t num1 = lineedit_first_number_->text().toLong(&ok1);
    int64_t num2 = lineedit_digit_->text().toLong(&ok2);

    if (!ok1) {
        QMessageBox::warning(this, "Ошибка ввода", "Пожалуйста, введите корректное натуральное число и цифру");
        return;
    }

    try {
        NaturalNumber first_natural_number(num1);

        std::unique_ptr<Number> result = first_natural_number.multiply_by_ten_in_power(num2);

        QString result_text = QString::number(result->get_number());

        lineedit_result_->setText(result_text);
    } catch (const std::invalid_argument &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void NaturalNumberWindow::subtract_with_multiply_digit_clicked() {

    bool ok1;
    bool ok2;
    bool ok3;
    int64_t num1 = lineedit_first_number_->text().toLong(&ok1);
    int64_t num2 = lineedit_second_number_->text().toLong(&ok2);
    int64_t num3 = lineedit_digit_->text().toLong(&ok3);

    if (!ok1 || !ok2 || !ok3) {
        QMessageBox::warning(this, "Ошибка ввода", "Пожалуйста, введите корректное натуральное число и цифру");
        return;
    }

    try {
        NaturalNumber first_natural_number(num1);
        NaturalNumber second_natural_number(num2);

        std::unique_ptr<Number> result = first_natural_number.subtract_with_multiply_digit(second_natural_number, num3);

        QString result_text = QString::number(result->get_number());

        lineedit_result_->setText(result_text);
    } catch (const std::invalid_argument &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }

}

void NaturalNumberWindow::get_first_digit_after_division_number_on_ten_in_power_clicked() {

    bool ok1;
    bool ok2;
    bool ok3;
    int64_t num1 = lineedit_first_number_->text().toLong(&ok1);
    int64_t num2 = lineedit_second_number_->text().toLong(&ok2);
    int64_t num3 = lineedit_digit_->text().toLong(&ok3);

    if (!ok1 || !ok2 || !ok3) {
        QMessageBox::warning(this, "Ошибка ввода", "Пожалуйста, введите корректное натуральное число и цифру");
        return;
    }

    try {
        NaturalNumber first_natural_number(num1);
        NaturalNumber second_natural_number(num2);

        std::unique_ptr<Number> result = first_natural_number.get_first_digit_after_division_number_on_ten_in_power(second_natural_number, num3);

        QString result_text = QString::number(result->get_number());

        lineedit_result_->setText(result_text);
    } catch (const std::invalid_argument &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }

}

void NaturalNumberWindow::division_numbers_with_remainder_clicked() {

    bool ok1;
    bool ok2;
    int64_t num1 = lineedit_first_number_->text().toLong(&ok1);
    int64_t num2 = lineedit_second_number_->text().toLong(&ok2);

    if (!ok1) {
        QMessageBox::warning(this, "Ошибка ввода", "Пожалуйста, введите корректное натуральное число и цифру");
        return;
    }

    try {
        NaturalNumber first_natural_number(num1);
        NaturalNumber second_natural_number(num2);

        std::unique_ptr<Number> result = first_natural_number.division_numbers_with_remainder(second_natural_number);

        QString result_text = QString::number(result->get_number());

        lineedit_result_->setText(result_text);
    } catch (const std::invalid_argument &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void NaturalNumberWindow::calculating_remainder_after_division_clicked() {

    bool ok1;
    bool ok2;
    int64_t num1 = lineedit_first_number_->text().toLong(&ok1);
    int64_t num2 = lineedit_second_number_->text().toLong(&ok2);

    if (!ok1) {
        QMessageBox::warning(this, "Ошибка ввода", "Пожалуйста, введите корректное натуральное число и цифру");
        return;
    }

    try {
        NaturalNumber first_natural_number(num1);
        NaturalNumber second_natural_number(num2);

        std::unique_ptr<Number> result = first_natural_number.calculating_remainder_after_division(second_natural_number);

        QString result_text = QString::number(result->get_number());

        lineedit_result_->setText(result_text);
    } catch (const std::invalid_argument &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }

}

void NaturalNumberWindow::calculate_gcd_clicked() {

    bool ok1;
    bool ok2;
    int64_t num1 = lineedit_first_number_->text().toLong(&ok1);
    int64_t num2 = lineedit_second_number_->text().toLong(&ok2);

    if (!ok1) {
        QMessageBox::warning(this, "Ошибка ввода", "Пожалуйста, введите корректное натуральное число и цифру");
        return;
    }

    try {
        NaturalNumber first_natural_number(num1);
        NaturalNumber second_natural_number(num2);

        std::unique_ptr<Number> result = first_natural_number.calculate_gcd(second_natural_number);

        QString result_text = QString::number(result->get_number());

        lineedit_result_->setText(result_text);
    } catch (const std::invalid_argument &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }

}

void NaturalNumberWindow::calculate_lcm_clicked() {

    bool ok1;
    bool ok2;
    int64_t num1 = lineedit_first_number_->text().toLong(&ok1);
    int64_t num2 = lineedit_second_number_->text().toLong(&ok2);

    if (!ok1) {
        QMessageBox::warning(this, "Ошибка ввода", "Пожалуйста, введите корректное натуральное число и цифру");
        return;
    }

    try {
        NaturalNumber first_natural_number(num1);
        NaturalNumber second_natural_number(num2);

        std::unique_ptr<Number> result = first_natural_number.calculate_lcm(second_natural_number);

        QString result_text = QString::number(result->get_number());

        lineedit_result_->setText(result_text);
    } catch (const std::invalid_argument &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }

}
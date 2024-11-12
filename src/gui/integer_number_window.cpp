#include "integer_number_window.h"

#include "natural_number_window.h"


IntegerNumberWindow::IntegerNumberWindow(QWidget *parent)
    : QWidget(parent)
{
    label_first_number_ = new QLabel("Первое число:", this);
    label_second_number_ = new QLabel("Второе число(если надо):", this);
    label_result_ = new QLabel("Результат:", this);

    lineedit_first_number_ = new QLineEdit(this);
    lineedit_second_number_ = new QLineEdit(this);
    lineedit_result_ = new QLineEdit(this);
    lineedit_result_->setReadOnly(true);

    QGridLayout *inputLayout = new QGridLayout;
    inputLayout->addWidget(label_first_number_, 0, 0);
    inputLayout->addWidget(lineedit_first_number_, 1, 0);
    inputLayout->addWidget(label_second_number_, 0, 1);
    inputLayout->addWidget(lineedit_second_number_, 1, 1);
    inputLayout->addWidget(label_result_, 0, 2);
    inputLayout->addWidget(lineedit_result_, 1, 2);

    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    add_ = new QPushButton("Сложение", this);;
    subtract_ = new QPushButton("Вычитание", this);
    multiply_ = new QPushButton("Умножение", this);
    get_absolute_value_ = new QPushButton("Получить абсолютное значение", this);
    change_sign_ = new QPushButton("Изменить знак", this);
    is_number_positive_ = new QPushButton("Проверка на положительность", this);
    converting_natural_to_integer_ = new QPushButton("Конвертация из натурального в целое", this);
    converting_positive_integer_to_natural_ = new QPushButton("Конвертация из целого в натуральное", this);
    calculating_quotient_ = new QPushButton("Найти частное от деления", this);
    calculating_remainder_after_division_ = new QPushButton("Найти остаток от деления", this);

    QList<QPushButton*> buttons = {add_, subtract_, multiply_,
                                   get_absolute_value_, change_sign_,
                                   is_number_positive_, converting_natural_to_integer_,
                                   converting_positive_integer_to_natural_, calculating_quotient_,
                                   calculating_remainder_after_division_};

    for(auto &button : buttons) {
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

    QGridLayout *buttonsLayout = new QGridLayout;
    buttonsLayout->addWidget(add_, 0, 0);
    buttonsLayout->addWidget(subtract_, 0, 1);
    buttonsLayout->addWidget(multiply_, 1, 0);
    buttonsLayout->addWidget(get_absolute_value_, 1, 1);
    buttonsLayout->addWidget(change_sign_, 2, 0);
    buttonsLayout->addWidget(is_number_positive_, 2, 1);
    buttonsLayout->addWidget(converting_natural_to_integer_, 3, 0);
    buttonsLayout->addWidget(converting_positive_integer_to_natural_, 3, 1);
    buttonsLayout->addWidget(calculating_quotient_, 4, 0);
    buttonsLayout->addWidget(calculating_remainder_after_division_, 4, 1);

    buttonsLayout->setSpacing(10);
    buttonsLayout->setContentsMargins(10, 10, 10, 10);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);

    setWindowTitle("Целые числа");
    setFixedSize(800, 800);

    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen) {
        QRect screenGeometry = screen->availableGeometry();
        int x = (screenGeometry.width() - width()) / 2;
        int y = (screenGeometry.height() - height()) / 2;
        move(x, y);
    }

    connect(add_, &QPushButton::clicked, this, &IntegerNumberWindow::add_clicked);
    connect(subtract_, &QPushButton::clicked, this, &IntegerNumberWindow::subtract_clicked);
    connect(multiply_, &QPushButton::clicked, this, &IntegerNumberWindow::multiply_clicked);
    connect(get_absolute_value_, &QPushButton::clicked, this, &IntegerNumberWindow::get_absolute_value_clicked);
    connect(change_sign_, &QPushButton::clicked, this, &IntegerNumberWindow::change_sign_clicked);
    connect(is_number_positive_, &QPushButton::clicked, this, &IntegerNumberWindow::is_number_positive_clicked);
    connect(converting_natural_to_integer_, &QPushButton::clicked, this, &IntegerNumberWindow::converting_natural_to_integer_clicked);
    connect(converting_positive_integer_to_natural_, &QPushButton::clicked, this, &IntegerNumberWindow::converting_positive_integer_to_natural_clicked);
    connect(calculating_quotient_, &QPushButton::clicked, this, &IntegerNumberWindow::calculating_quotient_clicked);
    connect(calculating_remainder_after_division_, &QPushButton::clicked, this, &IntegerNumberWindow::calculating_remainder_after_division_clicked);
}

void IntegerNumberWindow::add_clicked() {

}

void IntegerNumberWindow::subtract_clicked() {

}

void IntegerNumberWindow::multiply_clicked() {

}

void IntegerNumberWindow::get_absolute_value_clicked() {

}

void IntegerNumberWindow::change_sign_clicked() {

}

void IntegerNumberWindow::is_number_positive_clicked() {

}

void IntegerNumberWindow::converting_natural_to_integer_clicked() {

}

void IntegerNumberWindow::converting_positive_integer_to_natural_clicked() {

}

void IntegerNumberWindow::calculating_quotient_clicked() {

}

void IntegerNumberWindow::calculating_remainder_after_division_clicked() {

}
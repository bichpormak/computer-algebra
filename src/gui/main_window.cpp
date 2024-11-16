#include "main_window.h"


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    natural_numbers_button_ = new QPushButton("Натуральные числа", this);
    integers_button_ = new QPushButton("Целые числа", this);
    rational_numbers_button_ = new QPushButton("Рациональные числа", this);
    polynomials_button_ = new QPushButton("Многочлены", this);

    natural_numbers_button_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    integers_button_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    rational_numbers_button_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    polynomials_button_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(natural_numbers_button_, 0, 0);
    layout->addWidget(integers_button_, 0, 1);
    layout->addWidget(rational_numbers_button_, 1, 0);
    layout->addWidget(polynomials_button_, 1, 1);

    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    setLayout(layout);

    setFixedSize(400, 400);

    setWindowTitle("Меню");

    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen) {
        QRect screenGeometry = screen->availableGeometry();
        int x = (screenGeometry.width() - width()) / 2;
        int y = (screenGeometry.height() - height()) / 2;
        move(x, y);
    }

    connect(natural_numbers_button_, &QPushButton::clicked, this, &MainWindow::on_natural_numbers_clicked);
    connect(integers_button_, &QPushButton::clicked, this, &MainWindow::on_integers_clicked);
    connect(rational_numbers_button_, &QPushButton::clicked, this, &MainWindow::on_rational_numbers_clicked);
    connect(polynomials_button_, &QPushButton::clicked, this, &MainWindow::on_polynomials_clicked);
}

void MainWindow::on_natural_numbers_clicked() {
    NaturalNumberWindow *natural_number_window = new NaturalNumberWindow();
    natural_number_window->setAttribute(Qt::WA_DeleteOnClose);
    natural_number_window->setWindowFlags(Qt::Window);
    natural_number_window->show();
}

void MainWindow::on_integers_clicked() {
    IntegerNumberWindow *integer_number_window = new IntegerNumberWindow();
    integer_number_window->setAttribute(Qt::WA_DeleteOnClose);
    integer_number_window->setWindowFlags(Qt::Window);
    integer_number_window->show();
}

void MainWindow::on_rational_numbers_clicked() {
    RationalNumberWindow *rational_number_window = new RationalNumberWindow();
    rational_number_window->setAttribute(Qt::WA_DeleteOnClose);
    rational_number_window->setWindowFlags(Qt::Window);
    rational_number_window->show();
}

void MainWindow::on_polynomials_clicked() {
    PolynomialWindow *polynomial_window = new PolynomialWindow();
    polynomial_window->setAttribute(Qt::WA_DeleteOnClose);
    polynomial_window->setWindowFlags(Qt::Window);
    polynomial_window->show();
}

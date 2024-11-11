#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QScreen>
#include <QApplication>

#include "natural_number_window.h"


class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void on_natural_numbers_clicked();
    void on_integers_clicked();
    void on_rational_numbers_clicked();
    void on_polynomials_clicked();

private:
    QPushButton *natural_numbers_button_;
    QPushButton *integers_button_;
    QPushButton *rational_numbers_button_;
    QPushButton *polynomials_button_;
};

#endif
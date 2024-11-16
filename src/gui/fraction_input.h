#ifndef FRACTIONINPUT_H
#define FRACTIONINPUT_H

#include <QWidget>
#include <QLineEdit>

class FractionInput : public QWidget
{
    Q_OBJECT
public:
    explicit FractionInput(QWidget *parent = nullptr);

    QString numeratorText() const;
    QString denominatorText() const;

    void setNumeratorText(const QString &text);
    void setDenominatorText(const QString &text);

private:
    QLineEdit *numerator_;
    QLineEdit *denominator_;
};

#endif
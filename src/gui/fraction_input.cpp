#include "fraction_input.h"
#include <QVBoxLayout>
#include <QFrame>

FractionInput::FractionInput(QWidget *parent) : QWidget(parent)
{
    numerator_ = new QLineEdit(this);
    denominator_ = new QLineEdit(this);

    numerator_->setAlignment(Qt::AlignCenter);
    denominator_->setAlignment(Qt::AlignCenter);

    QFrame *line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->setLineWidth(1);
    line->setMidLineWidth(1);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(numerator_);
    layout->addWidget(line);
    layout->addWidget(denominator_);
    layout->setSpacing(0);
    layout->setContentsMargins(5, 5, 5, 5);

    setLayout(layout);
}

QString FractionInput::numeratorText() const
{
    return numerator_->text();
}

QString FractionInput::denominatorText() const
{
    return denominator_->text();
}

void FractionInput::setNumeratorText(const QString &text)
{
    numerator_->setText(text);
}

void FractionInput::setDenominatorText(const QString &text)
{
    denominator_->setText(text);
}

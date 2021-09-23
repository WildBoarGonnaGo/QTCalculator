#ifndef CALCULATOR_HPP
# define CALCULATOR_HPP

#include <QtWidgets/QWidget>
#include <QVector>
#include <QLCDNumber>
#include <QPushButton>

class Calculator : public QWidget {
    Q_OBJECT
public:
    Calculator(QWidget *pwgt = nullptr);
    QPushButton         *createButton(QString const &rhs);
    void                calculate();
private:
    QLCDNumber          *_plcd;
    QString             _strDisplay;
    QVector<QString>    _strVector;
public slots:
    void                buttonClicked();
    void                keyPressed();
};

#endif

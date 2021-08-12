#include <calculator.hpp>
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication    app(argc, argv);
    Calculator  *obj = new Calculator;
    obj->resize(230, 200);
    obj->setWindowTitle("QtCalculator");
    obj->show();

    return (app.exec());
}

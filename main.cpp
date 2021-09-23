#include <mainwindow.h>

int main(int argc, char *argv[]) {
    QApplication    app(argc, argv);
	MainWindow      mainObj;
    /*QMenu           *itemCheckMenu = new QMenu("&Menu");
    QMenuBar        mbar;
    QWidget         finWidget;

    QAction         *calcSimpleCheckPtr = itemCheckMenu->addAction("&Simple");
    calcSimpleCheckPtr->setCheckable(true);
    calcSimpleCheckPtr->setChecked(true);

    QAction         *calcNumSysCheckPtr = itemCheckMenu->addAction("&Numeral System");
    calcNumSysCheckPtr->setCheckable(true);
    calcNumSysCheckPtr->setChecked(false);

    itemCheckMenu->addSeparator();
    itemCheckMenu->addAction("&Exit", &app, SLOT(quit()));

    mbar.addMenu(itemCheckMenu);

    Calculator  *obj = new Calculator;
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(&mbar);
    vbox->addWidget(obj);
    vbox->setContentsMargins(0, 0, 0, 0);
    vbox->setSpacing(0);

    obj->resize(230, 200);
    obj->setWindowTitle("QtCalculator");
    obj->show();

    finWidget.setLayout(vbox);
    finWidget.resize(210, 320);
    finWidget.setWindowTitle("Calculator");
    finWidget.setContentsMargins(0, 0, 0, 5);
    finWidget.show();*/

	mainObj.setQApplication(&app);
	mainObj.show();

    return (app.exec());
}

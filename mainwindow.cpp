#include <mainwindow.h>
#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *wgtptr) : QWidget(wgtptr), _secWgtPtr(nullptr),
    _sysCalcWgtPtr(new numSysCalcWgt()), _calcWgtPtr(new Calculator()) {
    QMenu       *itemCheckMenu = new QMenu("&Menu");
    QMenuBar    *mbar = new QMenuBar();

    QAction         *calcSimpleCheckPtr = itemCheckMenu->addAction("&Simple");
    calcSimpleCheckPtr->setCheckable(true);
    calcSimpleCheckPtr->setChecked(true);

    QAction         *calcNumSysCheckPtr = itemCheckMenu->addAction("&Numeral System");
    calcNumSysCheckPtr->setCheckable(true);
    calcNumSysCheckPtr->setChecked(false);

    itemCheckMenu->addSeparator();
    itemCheckMenu->addAction("&Exit", &_mainApp, SLOT(quit()));

    mbar->addMenu(itemCheckMenu);
    _secWgtPtr = _sysCalcWgtPtr;
    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->addWidget(mbar);
    vbox->addWidget(_secWgtPtr);
    vbox->setContentsMargins(0, 0, 0, 0);
    vbox->setSpacing(0);

    connect(calcSimpleCheckPtr, SIGNAL(triggered(bool)), this, SLOT(menuCheckLinesVerify()));
    connect(calcNumSysCheckPtr, SIGNAL(triggered(bool)), this, SLOT(menuCheckLinesVerify()));

    setWindowTitle("Calculator");
    setLayout(vbox);
}

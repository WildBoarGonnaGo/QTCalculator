#include <mainwindow.h>
#include <QMenu>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *wgtptr) : QWidget(wgtptr), _secWgtPtr(nullptr),
    _sysNumWgtPtr(new numSysCalcWgt()), _calcWgtPtr(new Calculator()) {
    QMenu       *itemCheckMenu = new QMenu("&Menu");
    QMenuBar    *mbar = new QMenuBar();
	_mainApp = nullptr;

    _calcSimpleCheckPtr = itemCheckMenu->addAction("&Simple");
    _calcSimpleCheckPtr->setCheckable(true);
    _calcSimpleCheckPtr->setChecked(false);

    _calcNumSysCheckPtr = itemCheckMenu->addAction("&Numeral System");
    _calcNumSysCheckPtr->setCheckable(true);
    _calcNumSysCheckPtr->setChecked(true);

    itemCheckMenu->addSeparator();
    itemCheckMenu->addAction("&Exit", this, SLOT(quit()));

    mbar->addMenu(itemCheckMenu);
    _secWgtPtr = _sysNumWgtPtr;
    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->addWidget(mbar);
    vbox->addWidget(_secWgtPtr);
    vbox->setContentsMargins(0, 0, 0, 0);
    vbox->setSpacing(0);
	_tmpPtr = vbox;

    connect(_calcSimpleCheckPtr, SIGNAL(triggered(bool)), this, SLOT(menuCheckLinesVerify()));
    connect(_calcNumSysCheckPtr, SIGNAL(triggered(bool)), this, SLOT(menuCheckLinesVerify()));

    setWindowTitle("Calculator");
    setLayout(vbox);
	setContentsMargins(0, 0, 0, 0);
}

void                MainWindow::setQApplication(QApplication *app) {
	_mainApp = app;
}

QApplication const  &MainWindow::getQApplication() const {
	return (*_mainApp);
}

void                MainWindow::menuCheckLinesVerify() {
	QObject *rage = sender();

	if (_calcSimpleCheckPtr->isChecked() && rage == _calcNumSysCheckPtr) {
		_secWgtPtr = _sysNumWgtPtr;
		_calcSimpleCheckPtr->setChecked(false);
		_calcNumSysCheckPtr->setChecked(true);
	}
	else if (_calcNumSysCheckPtr->isChecked() && rage == _calcSimpleCheckPtr) {
		_secWgtPtr = _calcWgtPtr;
		_calcNumSysCheckPtr->setChecked(false);
		_calcSimpleCheckPtr->setChecked(true);
	}
	_tmpPtr->update();
	update();
}

#include <mainwindow.h>
#include <QMenu>
#include <QMenuBar>
#include <QDebug>

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
    itemCheckMenu->addAction("&Exit", this, SLOT(close()));

    QFrame  *menuSeparator = new QFrame();
    menuSeparator->setFrameShape(QFrame::HLine);
    menuSeparator->setFrameShadow(QFrame::Sunken);

    mbar->addMenu(itemCheckMenu);
    _secWgtPtr = _sysNumWgtPtr;
    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->addWidget(mbar);
    vbox->addWidget(menuSeparator);
    vbox->addWidget(_secWgtPtr);
    vbox->setContentsMargins(0, 0, 0, 0);
    vbox->setSpacing(0);
    _vboxLayPtr = vbox;

    connect(_calcSimpleCheckPtr, SIGNAL(triggered(bool)), this, SLOT(menuCheckLinesVerify()));
    connect(_calcNumSysCheckPtr, SIGNAL(triggered(bool)), this, SLOT(menuCheckLinesVerify()));

    setWindowTitle("Calculator");
    setLayout(vbox);
	setContentsMargins(0, 0, 0, 0);
    //qDebug() << width();
    //qDebug() << height();
}

void                MainWindow::setQApplication(QApplication *app) {
	_mainApp = app;
}

QApplication const  &MainWindow::getQApplication() const {
	return (*_mainApp);
}

void                MainWindow::menuCheckLinesVerify() {
	QObject *rage = sender();
    QWidget *tmpPtr = nullptr;

	if (_calcSimpleCheckPtr->isChecked() && rage == _calcNumSysCheckPtr) {
        tmpPtr = _sysNumWgtPtr;
		_calcSimpleCheckPtr->setChecked(false);
		_calcNumSysCheckPtr->setChecked(true);
	}
	else if (_calcNumSysCheckPtr->isChecked() && rage == _calcSimpleCheckPtr) {
        tmpPtr = _calcWgtPtr;
		_calcNumSysCheckPtr->setChecked(false);
		_calcSimpleCheckPtr->setChecked(true);
    } else {
        if (rage == _calcNumSysCheckPtr)
            _calcNumSysCheckPtr->setChecked(true);
        else
            _calcSimpleCheckPtr->setChecked(true);
        return ;
    }

    _secWgtPtr->hide();
    _vboxLayPtr->replaceWidget(_secWgtPtr, tmpPtr);
    _secWgtPtr = tmpPtr;
    setFixedSize((tmpPtr == _sysNumWgtPtr) ? 510 : 240,
                 (tmpPtr == _sysNumWgtPtr) ? 350 : 320);
    _secWgtPtr->show();
    update();
}

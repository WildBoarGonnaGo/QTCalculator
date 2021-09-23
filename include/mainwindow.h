#ifndef MAINWINDOW_H
# define MAINWINDOW_H
#include <numsyscalc.h>
#include <calculator.hpp>
#include <QApplication>
#include <QVBoxLayout>

class MainWindow : public QWidget {
    Q_OBJECT
public:
    MainWindow(QWidget *wgtptr = nullptr);
    void                setQApplication(QApplication *app);
    QApplication const  &getQApplication() const;
private:
    QWidget             *_secWgtPtr;
    numSysCalcWgt       *_sysNumWgtPtr;
    Calculator          *_calcWgtPtr;
    QApplication        *_mainApp;
	QAction             *_calcSimpleCheckPtr;
	QAction             *_calcNumSysCheckPtr;
	QVBoxLayout         *_tmpPtr;
private slots:
    void                menuCheckLinesVerify();
};

#endif

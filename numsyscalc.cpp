#include <numsyscalc.h>
#include <QComboBox>

numSysCalcWgt::numSysCalcWgt(QWidget *wgtptr) : QWidget(wgtptr), _numDec(0),
    _numOct(QString()), _numHex(QString()), _numBuffer(0), _numTypeInput(new QLabel()),
    _rightOutputLabel(new QLabel()) {
    QComboBox   *numInput = new ComboBox;
    QLabel      *chooseInput = new QLabel("&Type of numerical system");
    QStringList strList;

    strList << "&Decimal" << "&Octal" << "Hexal";
    numInput->addItems(strList);
    numInput->setEditable(false);
    chooseInput->setBuddy(numInput);

    _numTypeInput->setText(numInput->currentText() + " input");
    QLineEdit   *inputNumber = new QLineEdit();
    _rightOutputLabel->setAlignment(Qt::AlignCenter);
    _rightOutputLabel->setText("There will be you output here!");
    _rightOutputLabel->resize(200, 200);
    _rightOutputLabel->setFrameStyle(QFrame::Box | QFrame::Plain);
    _rightOutputLabel->setLineWidth(3);
    _rightOutputLabel->setContentsMargins(5, 5, 5, 5);


}

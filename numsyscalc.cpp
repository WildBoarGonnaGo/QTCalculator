#include <numsyscalc.h>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

numSysCalcWgt::numSysCalcWgt(QWidget *wgtptr) : QWidget(wgtptr), _numDec(0),
    _numOct(QString()), _numHex(QString()), _numBuffer(0), _numTypeInput(new QLabel()),
    _rightOutputLabel(new QLabel()) {
    _numInput = new ComboBox;
    QLabel      *chooseInput = new QLabel("&Type of numerical system");
    QStringList strList;

    strList << "&Decimal" << "&Octal" << "&Hexadecimal" << "&Binary";
    _numInput->addItems(strList);
    _numInput->setEditable(false);
    chooseInput->setBuddy(_numInput);

    _inputNumber = new QLineEdit();
    _numTypeInput->setText(_numInput->currentText() + " input");
    _numTypeInput->setBuddy(inputNumber);

    _rightOutputLabel->setAlignment(Qt::AlignCenter);
    _rightOutputLabel->setText("There will be your output here!");
    _rightOutputLabel->resize(200, 200);
    _rightOutputLabel->setFrameStyle(QFrame::Box | QFrame::Plain);
    _rightOutputLabel->setLineWidth(3);
    _rightOutputLabel->setContentsMargins(5, 5, 5, 5);

    QPushButton *calcButton = new QPushButton("&Calculate");
    _decValidatorPtr = new numSysValidatorDec();
    _hexValidatorPtr = new numSysValidatorHex();
    _octValidatorPtr = new numSysValidatorOct();
    _binValidatorPtr = new numSysValidatorBin();
    _lineInputPrefix = new QLabel();

    QHBoxLayout *lineEditBox = new QHBoxLayout();
    lineEditBox->addWidget(_lineInputPrefix);
    lineEditBox->addWidget(_inputNumber);

    QVBoxLayout *leftEditBar = new QVBoxLayout();
    leftEditBar->addWidget(chooseInput);
    leftEditBar->addWidget(_numInput);
    leftEditBar->addWidget(_numTypeInput);
    leftEditBar->addLayout(lineEditBox);
    leftEditBar->addWidget(calcButton, 0, Qt::AlignHCenter);

    QHBoxLayout *totalLayout = new QHBoxLayout();
    totalLayout->addLayout(leftEditBar);
    totalLayout->addWidget(_rightOutputLabel);

    connect(_numInput, SIGNAL(currentIndexChanged(const QString &)),
        this, SLOT(changeInputMode()));
    connect(calcButton, SIGNAL(clicked(bool)),
        this, SLOT(outputResult()));

    setLayout(totalLayout);
}

void    numSysCalcWgt::changeInputMode() {
    QString inputLblStr = _numInput->currentText();

    numTypeInput->setText(_numInput->currentText() + " input");

    if (!inputLblStr.compare("Decimal")) {
        _inputNumber->setValidator(_decValidatorPtr);
        _lineInputPrefix->setText("");
    }
    else if (!inputLblStr.compare("Octal")) {
        _inputNumber->setValidator(_octValidatorPtr);
        _lineInputPrefix->setText("0o: ");
    }
    else if (!inputLblStr.compare("Hexadecimal")) {
        _inputNumber->setValidator(_hexValidatorPtr);
        _lineInputPrefix->setText("0x: ");
    } else {
        _inputNumber->setValidator(_binValidatorPtr);
        _lineInputPrefix->setText("0b: ");
    }
}

void    numSysCalcWgt::outputResult() {
    QString inputLblStr = _numInput->currentText();

    if (!inputLblStr.compare("Decimal")) {
        _numDec = _inputNumber->text();
        _numHex = "0x" + QString::number(_numDec.toInt(), 16);
        _numOct = "0o" + QString::number(_numDec.toInt(), 8);
        _numBin = "0b" + QString::number(_numDec.toInt(), 2);
        _lineInputPrefix->setText("");
    } else if (!inputLblStr.compare("Hexadecimal")) {
        _numHex = "0x" + _inputNumber->text();
        _numDec = QString::number(_numHex.toInt(), 10);
        _numOct = "0o" + QString::number(_numHex.toInt(), 8);
        _numBin = "0b" + QString::number(_numHex.toInt(), 2);
    } else if (!inputLblStr.compare("Octal")) {
        _numOct = "0o" + _inputNumber->text();
        _numDec = QString::number(_numOct.toInt(), 10);
        _numHex = "0x" + QString::number(_numOct.toInt(), 16);
        _numBin = "0b" + QString::number(_numOct.toInt(), 2);
    } else {
        _numBin = "0b" + _inputNumber->text();
        _numDec = QString::number(_numBin.toInt(), 10);
        _numHex = "0x" + QString::number(_numBin.toInt(), 16);
        _numOct = "0o" + QString::number(_numBin.toInt(), 8);
    }

     _rightOutputLabel->setText("<h2>Computation results:</h2>"
                                "<p>Dec: " + _numDec + "</p>"
                                "<p>Hex: " + _numHex.toUpper() + "</p>"
                                "<p>Oct: " + _numOct + "</p>"
                                "<p>Bin: " + _numBin + "</p>");
}















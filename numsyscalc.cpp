#include <numsyscalc.h>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QShortcut>
#include <QKeySequence>
#include <QRegExp>

numSysCalcWgt::numSysCalcWgt(QWidget *wgtptr) : QWidget(wgtptr), _numDec(QString()),
    _numOct(QString()), _numHex(QString()), _numTypeInput(new QLabel()),
    _rightOutputLabel(new QLabel()) {
    _numInput = new QComboBox;
    QLabel      *chooseInput = new QLabel("&Type of numerical system");
    QStringList         strList;
	QRegExp             tmp("[0-9]+");

	_regexValidPtr = new QRegExpValidator(tmp);
    strList << "Decimal" << "Octal" << "Hexadecimal" << "Binary";
    _numInput->addItems(strList);
    _numInput->setEditable(false);
    chooseInput->setBuddy(_numInput);

    _inputNumber = new QLineEdit();
    _numTypeInput->setText(_numInput->currentText() + " input");
    _numTypeInput->setBuddy(_inputNumber);

    //_rightOutputLabel->setAlignment(Qt::AlignVCenter);
    _rightOutputLabel->setText("There will be your output!");
    _rightOutputLabel->setFixedSize(300, 300);
    _rightOutputLabel->setContentsMargins(70, 55, 70, 55);

    QPushButton *calcButton = new QPushButton("&Calculate");
    _lineInputPrefix = new QLabel();
	_inputNumber->setValidator(_regexValidPtr);

    QHBoxLayout *lineEditBox = new QHBoxLayout();
    lineEditBox->addWidget(_lineInputPrefix);
    lineEditBox->addWidget(_inputNumber);

    QVBoxLayout *leftEditBar = new QVBoxLayout();
    leftEditBar->addWidget(chooseInput);
    leftEditBar->addWidget(_numInput);
    leftEditBar->addWidget(_numTypeInput);
    leftEditBar->addLayout(lineEditBox);
    leftEditBar->addWidget(calcButton, 0, Qt::AlignHCenter);
    leftEditBar->setContentsMargins(0, 0, 0, 140);

    QFrame  *vertSep = new QFrame();
    vertSep->setFrameShape(QFrame::VLine);
    vertSep->setFrameShadow(QFrame::Sunken);

    QHBoxLayout *totalLayout = new QHBoxLayout();
    totalLayout->addLayout(leftEditBar);
    totalLayout->addWidget(vertSep);
    totalLayout->addWidget(_rightOutputLabel);

    QShortcut   *keyEnter = new QShortcut(QKeySequence(Qt::Key_Enter), calcButton);
    QShortcut   *keyReturn = new QShortcut(QKeySequence(Qt::Key_Return), calcButton);

    connect(_numInput, SIGNAL(currentIndexChanged(const QString &)),
        this, SLOT(changeInputMode()));
    connect(calcButton, SIGNAL(clicked(bool)),
        this, SLOT(outputResult()));
    connect(keyEnter, SIGNAL(activated()), this, SLOT(outputResult()));
    connect(keyReturn, SIGNAL(activated()), this, SLOT(outputResult()));
    setLayout(totalLayout);
}

void    numSysCalcWgt::changeInputMode() {
    QString inputLblStr = _numInput->currentText();
	QRegExp tmpRegex;

    _numTypeInput->setText(_numInput->currentText() + " input");
    if (!inputLblStr.compare("Decimal")) {
		tmpRegex.setPattern("[0-9]+");
        _lineInputPrefix->setText("");
    }
    else if (!inputLblStr.compare("Octal")) {
	    tmpRegex.setPattern("[0-7]+");
        _lineInputPrefix->setText("0o: ");
    }
    else if (!inputLblStr.compare("Hexadecimal")) {
	    tmpRegex.setPattern("[0-9A-Fa-f]+");
        _lineInputPrefix->setText("0x: ");
    } else {
	    tmpRegex.setPattern("[01]+");
        _lineInputPrefix->setText("0b: ");
    }
	_regexValidPtr->setRegExp(tmpRegex);
}

void    numSysCalcWgt::outputResult() {
    QString inputLblStr = _numInput->currentText();
    bool    ok;

    if (!inputLblStr.compare("Decimal")) {
        _numDec = _inputNumber->text();
        _numHex = QString::number(_numDec.toInt(), 16);
        _numOct = QString::number(_numDec.toInt(), 8);
        _numBin = QString::number(_numDec.toInt(), 2);
        _lineInputPrefix->setText("");
    } else if (!inputLblStr.compare("Hexadecimal")) {
        _numHex = _inputNumber->text();
        _numDec.setNum(_numHex.toUInt(&ok, 16));
        _numOct.setNum(_numHex.toUInt(&ok, 16), 8);
        _numBin.setNum(_numHex.toUInt(&ok, 16), 2);
    } else if (!inputLblStr.compare("Octal")) {
        _numOct = _inputNumber->text();
        _numDec.setNum(_numOct.toUInt(&ok, 8));
        _numHex.setNum(_numOct.toUInt(&ok, 8), 16);
        _numBin.setNum(_numOct.toUInt(&ok, 8), 2);
    } else {
        _numBin = _inputNumber->text();
        _numDec.setNum(_numBin.toUInt(&ok, 2));
        _numHex.setNum(_numBin.toUInt(&ok, 2), 16);
        _numOct.setNum(_numHex.toUInt(&ok, 2), 8);
    }

     _rightOutputLabel->setText("<style> p { line-height: 40%; } </style>"
			                    "<h3>Computation results:</h3>"
                                "<p>Dec:    " + _numDec + "</p>"
                                "<p>Hex:    0x" + _numHex + "</p>"
                                "<p>Oct:    0o" + _numOct + "</p>"
                                "<p>Bin:    0b" + _numBin + "</p>");
}















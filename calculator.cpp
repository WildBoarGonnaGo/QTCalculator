#include <calculator.hpp>
#include <QGridLayout>
#include <QKeySequence>
#include <QShortcut>

Calculator::Calculator(QWidget *pwgt) : QWidget(pwgt) {
    QGridLayout *gridObj = new QGridLayout();

    _plcd = new QLCDNumber(12);
    _plcd->setMode(QLCDNumber::Dec);
    _plcd->setSegmentStyle(QLCDNumber::Flat);
    _plcd->setMinimumSize(150, 50);

    QChar   calcChars[4][4] = { {'7', '8', '9', '/'},
                                {'4', '5', '6', '*'},
                                {'1', '2', '3', '-'},
                                {'0', '.', '=', '+'}};
    gridObj->addWidget(_plcd, 0, 0, 1, 4);
    gridObj->addWidget(createButton("CE"), 1, 3);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0;  j < 4; ++j)
            gridObj->addWidget(createButton(calcChars[i][j]), i + 2, j);
    }
    setLayout(gridObj);
}

QPushButton *Calculator::createButton(QString const &rhs) {

    QPushButton     *calcButton = nullptr;
    QShortcut       *keymap = nullptr;
    QShortcut       *keyEnter = nullptr;

    if (!rhs.compare("*")) {
        QString multiply;
        multiply.push_back(0x00D7);
        calcButton = new QPushButton(multiply);
    } else
        calcButton = new QPushButton(rhs);
    if (!rhs.compare("CE"))
        keymap = new QShortcut(Qt::Key_Escape, calcButton);
    else if (!rhs.compare("=")) {
        keymap = new QShortcut(QKeySequence(Qt::Key_Return), calcButton);
        keyEnter = new QShortcut(QKeySequence(Qt::Key_Enter), calcButton);
    }
    else
        keymap = new QShortcut(rhs, calcButton);
	calcButton->setMinimumSize(40, 40);
	connect(calcButton, SIGNAL(clicked()), SLOT(buttonClicked()));
    connect(keymap, SIGNAL(activated()), SLOT(keyPressed()));
    if (keyEnter)
        connect(keyEnter, SIGNAL(activated()), SLOT(keyPressed()));
    return (calcButton);
}

void        Calculator::buttonClicked() {
    QString match = dynamic_cast<QPushButton *>(sender())->text();
    QRegExp regMatch("[0-9]");
    QString operChars("+-*/");
    QString multiplyChar;

    multiplyChar.push_back(0x00D7);
    if (match == multiplyChar)
        match = "*";
    if (!match.compare("CE")) {
        _strVector.clear();
        _strDisplay.clear();
        _plcd->display("0");
        return ;
    }
    if (match.contains(regMatch)) {
        _strDisplay.push_back(match);
        _plcd->display(_strDisplay);
    } else if (!match.compare(".")) {
		_strDisplay.push_back(match);
        _plcd->display(_strDisplay);
    } else {
        _strVector.push_back(_strDisplay);
        if (_strVector.size() > 2 && operChars.contains(*(_strVector.end() - 1))
                && operChars.contains(match)) {
            *(_strVector.end() - 1) = match;
        }
        else if (_strVector.size() > 1) {
    		calculate();
    		_strVector.clear();
            _strVector.push_back(_strDisplay);
            _strDisplay.clear();
    		if (match.compare("="))
    			_strVector.push_back(match);
    	} else {
            _strVector.push_back(_strDisplay);
            _strDisplay.clear();
            _strVector.push_back(match);
            _plcd->display("0");
    	}
    }
}

void        Calculator::keyPressed() {
    QString match = dynamic_cast<QPushButton *>(sender()->parent())->text();
    QRegExp regMatch("[0-9]");
    QString operChars("+-*/");
    QString multiplyChar;

    multiplyChar.push_back(0x00D7);
    if (match == multiplyChar)
        match = "*";
    if (!match.compare("CE")) {
        _strVector.clear();
        _strDisplay.clear();
        _plcd->display("0");
        return ;
    }
    if (match.contains(regMatch)) {
        _strDisplay.push_back(match);
        _plcd->display(_strDisplay);
    } else if (!match.compare(".")) {
        _strDisplay.push_back(match);
        _plcd->display(_strDisplay);
    } else {
        if (_strVector.size() == 1) {
            _strVector.push_back(match);
            return ;
        }
        if (_strVector.size() > 2 && operChars.contains(*(_strVector.end() - 1))
                && operChars.contains(match)) {
            *(_strVector.end() - 1) = match;
        }
        else if (_strVector.size() > 1) {
            _strVector.push_back(_strDisplay);
            calculate();
            _strVector.clear();
            _strVector.push_back(_strDisplay);
            _strDisplay.clear();
            if (match.compare("="))
                _strVector.push_back(match);
        } else {
            _strVector.push_back(_strDisplay);
            _strDisplay.clear();
            _strVector.push_back(match);
            _plcd->display("0");
        }
    }
}

void        Calculator::calculate() {
	double  rValue = _strVector.back().toDouble();
	_strVector.pop_back();
	QString operCalc = _strVector.back();
    _strVector.pop_back();
	double  lValue = _strVector.back().toDouble();

	if (!operCalc.compare("+"))
        lValue += rValue;
    else if (!operCalc.compare("-"))
        lValue -= rValue;
    else if (!operCalc.compare("/"))
        lValue /= rValue;
    else if (!operCalc.compare("*"))
        lValue *= rValue;
    _strDisplay = QString::number(lValue);
    _plcd->display(_strDisplay);
}

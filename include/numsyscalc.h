#ifndef NUMSYSCALC_H
# define NUMSYSCALC_H
# include <QWidget>
# include <QString>
# include <QLabel>
# include <QLineEdit>
# include <QComboBox>
# include <QRegExpValidator>

class numSysCalcWgt : public QWidget {
    Q_OBJECT
public:
    numSysCalcWgt(QWidget *wgtptr = nullptr);
private:
    QString             _numDec;
    QString             _numOct;
    QString             _numHex;
    QString             _numBin;
    QLabel              *_numTypeInput;
    QLabel              *_rightOutputLabel;
    QLineEdit           *_inputNumber;
    QComboBox           *_numInput;
	QRegExpValidator    *_regexValidPtr;
    QLabel              *_lineInputPrefix;
private slots:
    void        outputResult();
    void        changeInputMode();
};

#endif

#include <QWidget>
#include <QString>
#include <QLabel>

class numSysCalcWgt : public QWidget {
    Q_OBJECT
public:
    numSysCalcWgt(QWidget *wgtptr = nullptr);
private:
    int     _numDec;
    QString _numOct;
    QString _numHex;
    int     _numBuffer;
    QLabel  *_numTypeInput;
    QLabel  *_rightOutputLabel;
};

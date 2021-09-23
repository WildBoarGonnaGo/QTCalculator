#include <numSysValidator.h>
#include <QRegExp>

numSysValidatorDec::numSysValidatorDec(QObject *parent) : QValidator(parent) { }

QValidator::State numSysValidatorDec::validate(QString &str, int &pos) const {
    QRegExp nums("[0-9]");
    if (!str.contains(nums))
        return (Invalid);
    return (Acceptable);
}

numSysValidatorOct::numSysValidatorOct(QObject *parent) : QValidator(parent) { }

QValidator::State numSysValidatorOct::validate(QString &str, int &pos) const {
    QRegExp nums("[0-7]");
    if (!str.contains(nums))
        return (Invalid);
    return (Acceptable);
}

numSysValidatorHex::numSysValidatorHex(QObject *parent) : QValidator(parent) { }

QValidator::State numSysValidatorHex::validate(QString &str, int &pos) const {
    QRegExp nums("[0-9a-fA-F]");
    if (!str.contains(nums))
        return (Invalid);
    return (Acceptable);
}

numSysValidatorBin::numSysValidatorBin(QObject *parent) : QValidator(parent) { }

QValidator::State numSysValidatorBin::validate(QString &str, int &pos) const {
    QRegExp nums("[01]");
    if (!str.contains(nums))
        return (Invalid);
    return (Acceptable);
}

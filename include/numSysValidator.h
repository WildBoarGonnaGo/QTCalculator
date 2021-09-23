#ifndef NUMSYSVALIDATOR_H
# define NUMSYSVALIDATOR_H
# include <QValidator>
# include <QString>

class numSysValidatorDec : public QValidator {
public:
    numSysValidatorDec(QObject *parent = nullptr);
    virtual State validate(QString &str, int &pos) const;
};

class numSysValidatorOct : public QValidator {
public:
    numSysValidatorOct(QObject *parent = nullptr);
    virtual State validate(QString &str, int &pos) const;
};

class numSysValidatorHex : public QValidator {
public:
    numSysValidatorHex(QObject *parent = nullptr);
    virtual State validate(QString &str, int &pos) const;
};

class numSysValidatorBin : public QValidator {
public:
    numSysValidatorBin(QObject *parent = nullptr);
    virtual State validate(QString &str, int &pos) const;
};

#endif

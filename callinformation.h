#ifndef CALLINFORMATION_H
#define CALLINFORMATION_H

#include <QDate>
#include <QDateTime>
#include <QString>

class CallInformation
{
private:
 uint ats_id;
 QString PhoneNumberA;
 QString PhoneNumberB;
 qint8 answer;
 quint32 callDuration;
 quint32 dateTimeUnix;
 QDate date;

public:
    CallInformation();
    void initDefaultCallInformation();
    uint getATS_id();
    void setATS_id(uint ats_id_);
    QString getPhoneNumberA();
    void setPhoneNumberA(QString phoneA);
    QString getPhoneNumberB();
    void setPhoneNumberB(QString phoneB);
    qint8 getAnswer();
    void setAnswer(quint8 answ);
    quint32 getCallDuration();
    void setCallDuration(quint32 callDuration_);
    quint32 getDateTimeUnix();
    void setDateTimeUnix(quint32 dateTimeUnix_);
    QString getDateStrFromDateTimeUnix();
    QString getDateTimeStrFromDateTimeUnix();
    QDate getDate();
    void setDate(QString,QString);
    void setAbonFields(QString phoneA, QString phoneB, quint8 answ, quint32 callDur, quint32 dateTime );
};

#endif // CALLINFORMATION_H

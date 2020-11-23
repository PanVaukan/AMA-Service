#include "callinformation.h"

CallInformation::CallInformation()
{
    ats_id = 0;
    PhoneNumberA = "";
    PhoneNumberB = "";
    answer = 0;
    callDuration = 0;
    dateTimeUnix = 0;
}

void CallInformation::initDefaultCallInformation(){
    ats_id = 0;
    PhoneNumberA = "";
    PhoneNumberB = "";
    answer = 0;
    callDuration = 0;
    dateTimeUnix = 0;
}

uint CallInformation::getATS_id(){
    return ats_id;
}

void CallInformation::setATS_id(uint ats_id_){
    ats_id = ats_id_;
}

QString CallInformation::getPhoneNumberA(){
    return PhoneNumberA;
}

void CallInformation::setPhoneNumberA(QString phoneA){
    PhoneNumberA = phoneA;
}

QString CallInformation::getPhoneNumberB(){
    return PhoneNumberB;
}

void CallInformation::setPhoneNumberB(QString phoneB){
    PhoneNumberB = phoneB;
}

qint8 CallInformation::getAnswer(){
    return answer;
}

void CallInformation::setAnswer(quint8 answ){
    answer = answ;
}

quint32 CallInformation::getCallDuration(){
    return callDuration;
}

void CallInformation::setCallDuration(quint32 callDuration_){
    callDuration = callDuration_;
}

quint32 CallInformation::getDateTimeUnix(){
    return dateTimeUnix;
}

void CallInformation::setDateTimeUnix(quint32 dateTimeUnix_){
    dateTimeUnix = dateTimeUnix_;
}

QString CallInformation::getDateStrFromDateTimeUnix(){
    QDateTime dtm_uninx;
    dtm_uninx.setTime_t(dateTimeUnix);
    return dtm_uninx.toString("yyyy-MM-dd");
}

QString CallInformation::getDateTimeStrFromDateTimeUnix(){
    QDateTime dtm_uninx;
    dtm_uninx.setTime_t(dateTimeUnix);
    return dtm_uninx.toString("hh:mm:ss dd-MM-yyyy");
}

QDate CallInformation::getDate(){
    return date;
}

void CallInformation::setDate(QString dateStr, QString format){
    QDate dateTMP;
    dateTMP = QDate::fromString(dateStr, format);
    date = dateTMP;
}

void CallInformation::setAbonFields(QString phoneA, QString phoneB, quint8 answ, quint32 callDur, quint32 dateTime){
    this->PhoneNumberA = phoneA;
    this->PhoneNumberB = phoneB;
    this->answer = answ;
    this->callDuration = callDur;
    this->dateTimeUnix = dateTime;
}


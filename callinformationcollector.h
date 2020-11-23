#ifndef CALLINFORMATIONCOLLECTOR_H
#define CALLINFORMATIONCOLLECTOR_H

#include <callinformation.h>
#include <QDate>
#include <QDateTime>
#include <QMap>
#include <QMultiMap>
#include <QVector>

class CallInformationCollector
{
private: QVector<CallInformation> callInformationCollection;
         QVector<QString> callDates;
         QVector<QString> fileNames;
         QMultiMap<QDate,CallInformation> callInformationWithDateCollection;
public:
    CallInformationCollector();
    void addNewCallInformationIntoCollection(CallInformation callInfo);
    QVector<CallInformation> getCollection();
    void clearCallInformationCollection();
    void setFileNames(QString directory, QString extension);
    QVector<QString> getFileNames();
    void clearFileNames();
    void setDateFileNames();
    QVector<QString> getDateFileNames();
    void clearDateFileNames();
    QMultiMap<QDate,CallInformation> getCallInformationWithDateCollection();
    void setCallInformationWithDateCollection();
    void clearCallInformationWithDateCollection();
};

#endif // CALLINFORMATIONCOLLECTOR_H

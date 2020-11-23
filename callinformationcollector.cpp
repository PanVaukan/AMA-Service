#include "callinformationcollector.h"

CallInformationCollector::CallInformationCollector()
{
}

void CallInformationCollector::addNewCallInformationIntoCollection(CallInformation callInfo){
     callInformationCollection.push_back(callInfo);
}

QVector<CallInformation> CallInformationCollector::getCollection(){
     return callInformationCollection;
}

void CallInformationCollector::clearCallInformationCollection(){
    callInformationCollection.clear();
}

void CallInformationCollector::setFileNames(QString directory, QString extension){

    QMap<QString,bool> fileNamesMap;

    if ( callInformationCollection.size() == 0 ) {

        fileNames = fileNamesMap.keys().toVector();

    } else {

        QVector<CallInformation>::iterator callInformationCollectionIterator;
        callInformationCollectionIterator = callInformationCollection.begin();

        while ( callInformationCollectionIterator != callInformationCollection.end() ) {

            CallInformation callInfo;
            callInfo = *callInformationCollectionIterator;

            QDateTime currentDateTimeUnix;
            currentDateTimeUnix.setTime_t(callInfo.getDateTimeUnix());

            QString currentFileNameStr = directory + "/" + currentDateTimeUnix.date().toString("yyyyMMdd");
            currentFileNameStr.append(extension);

            fileNamesMap.insert(currentFileNameStr,true);

            callInformationCollectionIterator++;

        }

            fileNames = fileNamesMap.keys().toVector();
    }
}

QVector<QString> CallInformationCollector::getFileNames(){
    return fileNames;
}

void CallInformationCollector::clearFileNames(){
    fileNames.clear();
}

void CallInformationCollector::setDateFileNames(){

    QMap<QString,bool> datesMap;

    if ( callInformationCollection.size() == 0 ) {

        callDates = datesMap.keys().toVector();

    } else {

        QVector<CallInformation>::iterator callInformationCollectionIterator;
        callInformationCollectionIterator = callInformationCollection.begin();

        while ( callInformationCollectionIterator != callInformationCollection.end() ) {

            CallInformation callInfo;
            callInfo = *callInformationCollectionIterator;

            QDateTime currentDateTimeUnix;
            currentDateTimeUnix.setTime_t(callInfo.getDateTimeUnix());

            QString currentDateStr = currentDateTimeUnix.date().toString("yyyyMMdd");

            datesMap.insert(currentDateStr,true);

            callInformationCollectionIterator++;

        }

            callDates = datesMap.keys().toVector();
    }
}

QVector<QString> CallInformationCollector::getDateFileNames(){
    return callDates;
}

void CallInformationCollector::clearDateFileNames(){
    callDates.clear();
}

QMultiMap<QDate,CallInformation> CallInformationCollector::getCallInformationWithDateCollection(){
            return callInformationWithDateCollection;
}

void CallInformationCollector::setCallInformationWithDateCollection(){
            QMultiMap<QDate,CallInformation> callInfoWithDatesMap;

//            callInfoWithDatesMap.setInsertInOrder(true);

            QVector<CallInformation>::iterator callInformationCollectionIterator;
            callInformationCollectionIterator = callInformationCollection.begin();

            while ( callInformationCollectionIterator != callInformationCollection.end() ) {

                CallInformation callInfo;
                callInfo = *callInformationCollectionIterator;

                QDateTime currentDateTimeUnix;
                currentDateTimeUnix.setTime_t(callInfo.getDateTimeUnix());

                QDate currentDate = currentDateTimeUnix.date();
              //QString currentDateStr = currentDate.toString("yyyyMMdd");

                callInfoWithDatesMap.insertMulti(currentDate,callInfo);

                callInformationCollectionIterator++;

            }

            callInformationWithDateCollection = callInfoWithDatesMap;

}

void CallInformationCollector::clearCallInformationWithDateCollection(){
    callInformationWithDateCollection.clear();
}

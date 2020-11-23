#include "filewriter.h"

FileWriter::FileWriter()
{
}

bool FileWriter::writeCSVFile(QString fileName, QVector<CallInformation> callInfoCollectionData, bool isRealData){

     QVector<CallInformation>::iterator callInformationIterator;
     callInformationIterator = callInfoCollectionData.begin();

     QFile fileUNL(fileName);
     fileUNL.open(QFile::WriteOnly);
     QTextStream outputInCSVfile(&fileUNL);

     while ( callInformationIterator != callInfoCollectionData.end() ) {

         CallInformation callInfo;
         callInfo = *callInformationIterator;

         if ( callInformationIterator == callInfoCollectionData.begin() ){

             outputInCSVfile << QString(QObject::tr("Outgoing_number")) << ";"
                             << QString(QObject::tr("Incoming_number")) << ";"
                             << QString(QObject::tr("Answer")) << ";"
                             << QString(QObject::tr("CallDuration")) << ";"
                             << QString(QObject::tr("Date_and_time_of_call")) << ";"
                             << QString(QObject::tr("\n"));
         }

         if ( isRealData ){

         outputInCSVfile << callInfo.getPhoneNumberA() << ";"
                         << callInfo.getPhoneNumberB() << ";"
                         << callInfo.getAnswer() << ";"
                         << callInfo.getCallDuration() << ";"
                         << callInfo.getDateTimeStrFromDateTimeUnix() << ";"
                         << "\n";

         } else {

         outputInCSVfile << callInfo.getATS_id() << ";"
                         << callInfo.getAnswer() << ";"
                         << callInfo.getCallDuration() << ";"
                         << callInfo.getDateStrFromDateTimeUnix() << ";"
                         << callInfo.getDateTimeUnix() << ";"
                         << callInfo.getPhoneNumberA() << ";"
                         << callInfo.getPhoneNumberB() << ";"
                         << QString::number(0,10) << ";"
                         << QString::number(1,10) << ";"
                         << "\n";

     }

         callInformationIterator++;

     }

     fileUNL.close();

     return true;

}


bool FileWriter::writeCSVFilesForLoadDataInMySQLServer(QString directory, QMultiMap<QDate, CallInformation> callInfoCollectionDataWithDates, bool isRealData){

    QList<QDate> dateKeys = callInfoCollectionDataWithDates.keys();
    QList<CallInformation> dateValues = callInfoCollectionDataWithDates.values();

    QList<QDate>::iterator dateKeysIterator = dateKeys.begin();
    QList<CallInformation>::iterator dateValuesIterator = dateValues.begin();

    while ( dateKeysIterator != dateKeys.end() ){

        QDate date = *dateKeysIterator;
        QString dateStr = date.toString("yyyyMMdd");
        QString currentFileName;

        currentFileName = directory + "/" + dateStr + ".csv";

        if ( QFile(currentFileName).exists() ){
              QFile(currentFileName).remove();
        }

        dateKeysIterator++;

    }

    dateKeysIterator = dateKeys.begin();

    while ( dateKeysIterator != dateKeys.end() ){

        QDate date = *dateKeysIterator;
        QString dateStr = date.toString("yyyyMMdd");
        QString currentFileName;

        currentFileName = directory + "/" + dateStr + ".csv";

        QFile fileCSV(currentFileName);
        fileCSV.open(QFile::Append);
        QTextStream outputInCSVfile(&fileCSV);

        CallInformation callInfo = *dateValuesIterator;

        if ( isRealData ){

        outputInCSVfile << callInfo.getPhoneNumberA() << ";"
                        << callInfo.getPhoneNumberB() << ";"
                        << callInfo.getAnswer() << ";"
                        << callInfo.getCallDuration() << ";"
                        << callInfo.getDateTimeStrFromDateTimeUnix() << ";"
                        << "\r\n";

        } else {

        outputInCSVfile << callInfo.getATS_id() << ";"
                        << callInfo.getAnswer() << ";"
                        << callInfo.getCallDuration() << ";"
                        << callInfo.getDateStrFromDateTimeUnix() << ";"
                        << callInfo.getDateTimeUnix() << ";"
                        << callInfo.getPhoneNumberA() << ";"
                        << callInfo.getPhoneNumberB() << ";"
                        << QString::number(0,10) << ";"
                        << QString::number(1,10) << ";"
                        << "\r\n";

                }

        fileCSV.close();

        dateKeysIterator++;
        dateValuesIterator++;

    }

    return true;

}

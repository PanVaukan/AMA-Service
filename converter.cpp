#include "converter.h"

Converter::Converter()
{
}

QString Converter::convertToCSVFormat(CallInformation callInfo){

    QString convertedData = "";

    convertedData.append(QString::number(0));
    convertedData.append(QString(";"));
    convertedData.append(callInfo.getAnswer());
    convertedData.append(QString(";"));
    convertedData.append(callInfo.getCallDuration());
    convertedData.append(QString(";"));
    convertedData.append(QString(""));
    convertedData.append(QString(";"));
    convertedData.append(QString::number(callInfo.getDateTimeUnix()));
    convertedData.append(QString(";"));
    convertedData.append(callInfo.getPhoneNumberA());
    convertedData.append(QString(";"));
    convertedData.append(callInfo.getPhoneNumberB());
    convertedData.append(QString(";"));
    convertedData.append(QString::number(0));
    convertedData.append(QString(";"));
    convertedData.append(QString::number(0));
    convertedData.append(QString("\n"));

    return convertedData;

    /*
    outputInCSVfile << ats_id << ";" << answer << ";" << callDuration << ";" << dateForMySQL << ";" << datetimeForMySQL << ";"
                    << phoneNumberA << ";" << phoneNumberB << ";"
                    << offset << ";" << IdAMAfileName << "\n";
    */

}

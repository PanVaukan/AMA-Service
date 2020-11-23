#include "logger.h"

Logger::Logger()
{
}

void Logger::writeLog(QString logMessage, QString logFileName){

    QString currentProgramDirectory = QApplication::applicationDirPath();

    if (logFileName.isNull() || logFileName == "" ){
       logFileName = "AMA-Search.log";
    }

    QFile logFile(currentProgramDirectory + "/" + logFileName);
    QTextStream logFileTextStream(&logFile);
    QString messageForLogFile;
    QString dateTimeStr;

    dateTimeStr = QDateTime::currentDateTime().toString("HH:mm:ss dd.MM.yyyy");

    logFile.open(QIODevice::Append);
    messageForLogFile = "";
    messageForLogFile.append(dateTimeStr);
    messageForLogFile.append(" - ");
    messageForLogFile.append(logMessage);
    logFileTextStream << messageForLogFile << "\n";

    logFile.close();

}

#ifndef LOGGER_H
#define LOGGER_H

#include <QApplication>
#include <QString>
#include <QDateEdit>
#include <QFile>
#include <QTextStream>

class Logger
{
public:
    Logger();
    void writeLog(QString logMessage, QString logFileName);
};

#endif // LOGGER_H

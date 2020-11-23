#include <QApplication>
#include <QLoggingCategory>
#include <QTranslator>
#include "amasearch.h"
#include "task.h"

#include <QTextCodec>

// Умный указатель на файл логирования
QScopedPointer<QFile> m_logFile;

void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString &msg)
{

    // Открываем поток записи в файл
    QTextStream out(m_logFile.data());
    // Записываем дату записи
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
    // По типу определяем, к какому уровню относится сообщение
    switch (type)
    {
    case QtInfoMsg:     out << "INF "; break;
    case QtDebugMsg:    out << "DBG "; break;
    case QtWarningMsg:  out << "WRN "; break;
    case QtCriticalMsg: out << "CRT "; break;
    case QtFatalMsg:    out << "FTL "; break;
    }
    // Записываем в вывод категорию сообщения и само сообщение
    out << context.category << ": "
        << msg << endl;
    out.flush();    // Очищаем буферизированные данные

    QString txt;
    static long long uid=0; //-- номеруем вывод
    //-- название функции с классом, берём только класс и саму функцию
    QRegExp rx("([\\w-]+::[\\w-]+)");
    if (rx.indexIn(context.function) ==-1) return;
    QString function = rx.cap(1);

    QString msgSep = (msg.length()>0)? ">> " : "";

    switch (type) {
        case QtInfoMsg:
            txt = QString("Info: %1%2%3").arg(function).arg(msgSep).arg(msg);
        break;
        case QtDebugMsg:
            txt = QString("Debug: %1%2%3").arg(function).arg(msgSep).arg(msg);
            break;
        case QtWarningMsg:
            txt = QString("Warning: %1%2%3").arg(function).arg(msgSep).arg(msg);
        break;
        case QtCriticalMsg:
            txt = QString("Critical: %1%2%3").arg(function).arg(msgSep).arg(msg);
        break;
        case QtFatalMsg:
            txt = QString("Fatal: %1%2%3").arg(function).arg(msgSep).arg(msg);
            abort();
        break;
    }

            QDateTime dateTime = QDateTime::currentDateTime();
            uid++;
            txt=QString("%1:%2 %3").arg(dateTime.toString(Qt::ISODate)).arg(uid).arg(txt);

            QFile outFile(QString("%1/log-%2.log").arg(".").arg(QDate::currentDate().toString("dd.MM.yy")));
            outFile.open(QIODevice::WriteOnly | QIODevice::Append);
            QTextStream ts(&outFile);
            ts << txt << endl;
            outFile.close();

}


int main(int argc, char *argv[])
{   
    QApplication a(argc, argv);

    QTranslator qtTranslator;
    bool b1 = qtTranslator.load("qt_ru",a.applicationDirPath()+"/translators");
    a.installTranslator(&qtTranslator);

    QTranslator translator;
    bool b = translator.load(a.applicationDirPath()+"/translators/ru");
    a.installTranslator(&translator);

    // Устанавливаем файл логирования,
    // внимательно сверьтесь с тем, какой используете путь для файла
    m_logFile.reset(new QFile(QApplication::applicationDirPath()+ "/logFile.txt"));
    // Открываем файл логирования
    m_logFile.data()->open(QFile::Append | QFile::Text);
    // Устанавливаем обработчик
    qInstallMessageHandler(messageHandler);

    /*
    QTextCodec *textCodec = QTextCodec::codecForName("CP1251");
    QTextCodec::setCodecForTr(textCodec);
    QTextCodec::setCodecForCStrings(textCodec);
    QTextCodec::setCodecForLocale(textCodec);
    */

    Task task;
//  task.generateCallInformationInDB(-3,0,5000);
    task.preparationTableNamesForImportInEWSD_db(-93,0);

//  task.generateCallInformationInDB(-32,-32,5000);
//  task.loadTablesFromDataBase(&a,-124,-31);
//  task.loadTablesInDataBase(&a,-124,-31);
    task.manualTableSynchronization(&a);
    task.preparationTableNamesForAddIndex(-93,0,"cs");
    task.addGeneralKeysAfterImportTablesInApusDatabase();
//  task.searchInformationInDB();

    qInstallMessageHandler(messageHandler);

//  AMAsearch w;

//  w.CenterWidgets();

//  w.show();

    return 0;
    return a.exec();
}

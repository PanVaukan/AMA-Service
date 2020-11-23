#ifndef SQLGENERATOR_H
#define SQLGENERATOR_H

#include <QString>
#include <QVector>
#include <QDateTime>

class SqlGenerator
{
private:
    QVector<QString> sqlQueryForSelectFromDayTable;
public:
    SqlGenerator();
    void initSQLQuery();
    void generateSQLQuery(int startCountDay, int endCountDay);
    QVector<QString> getSQLQuery();

};

#endif // SQLGENERATOR_H

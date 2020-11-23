#include "sqlgenerator.h"

SqlGenerator::SqlGenerator()
{
}

void SqlGenerator::generateSQLQuery(int startCountDay, int endCountDay){

    for ( int i = startCountDay; i >= endCountDay; i-- ){
        QString beginMySQLQueryForSearchInAPUS = "SELECT IF( LENGTH(a_id)=7, CONCAT(\"8016\",a_id), CONCAT(\"80\",a_id)) phoneNumberA,";
        beginMySQLQueryForSearchInAPUS.append(" nabor phoneNumberB, t time, dlit callDuration FROM t");
        QDateTime dateTime = QDateTime(QDateTime::currentDateTime()).addDays(-i);
        QString dateTimeStr = dateTime.toString("yyyyMMdd");
        beginMySQLQueryForSearchInAPUS.append(dateTimeStr);
        beginMySQLQueryForSearchInAPUS.append(" WHERE phoneNumberB = \'123\'");
        sqlQueryForSelectFromDayTable.push_back(beginMySQLQueryForSearchInAPUS);
        /*
        if ( i != endCountDay){
        beginMySQLQueryForSearchInAPUS.append(" UNION");
        */
    }
}

QVector<QString> SqlGenerator::getSQLQuery(){
    return sqlQueryForSelectFromDayTable;
}

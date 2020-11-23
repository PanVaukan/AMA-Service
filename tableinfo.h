#ifndef TABLEINFO_H
#define TABLEINFO_H

#include <QDateTime>
#include <QString>

class TableInfo
{
private:

    QString table_shema;
    QString table_name;
    QString table_collation;
    quint64 table_rows;
    QString create_time;
    QString update_time;
    QString check_time;

public:
    TableInfo();
    QString getTableShema();
    void setTableShema(QString table_shema_);
    QString getTableName();
    void setTableName(QString table_name_);
    QString getTableCollation();
    void setTableCollation(QString table_collation_);
    quint64 getTableRows();
    void setTableRows(quint64 table_rows_);
    QString getCreateTime();
    void setCreateTime(QString create_time_);
    QString getUpdateTime();
    void setUpdateTime(QString update_time_);
    QString getCheckTime();
    void setCheckTime(QString check_time_);

};

#endif // TABLEINFO_H

/*
SELECT TABLE_SCHEMA, t.TABLE_NAME, t.TABLE_COLLATION, t.TABLE_ROWS,
t.CREATE_TIME, t.UPDATE_TIME, t.CHECK_TIME
FROM information_schema.TABLES t
WHERE t.TABLE_SCHEMA = "cs" AND t.TABLE_NAME LIKE "t%";
*/

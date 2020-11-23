#include "tableinfo.h"

TableInfo::TableInfo(){
    table_name = "";
    table_shema = "";
    table_collation = "";
    table_rows = 0;
}

QString TableInfo::getTableShema(){
    return table_shema;
}

void TableInfo::setTableShema(QString table_shema_){
    table_shema = table_shema_;
}

QString TableInfo::getTableName(){
    return table_name;
}

void TableInfo::setTableName(QString table_name_){
    table_name = table_name_;
}

QString TableInfo::getTableCollation(){
    return table_collation;
}

void TableInfo::setTableCollation(QString table_collation_){
    table_collation = table_collation_;
}

quint64 TableInfo::getTableRows(){
    return table_rows;
}

void TableInfo::setTableRows(quint64 table_rows_){
    table_rows = table_rows_;
}

QString TableInfo::getCheckTime(){
    return check_time;
}

void TableInfo::setCheckTime(QString check_time_){
    check_time =  check_time_;
}

QString TableInfo::getCreateTime(){
    return create_time;
}

void TableInfo::setCreateTime(QString create_time_){
    create_time = create_time_;
}

QString TableInfo::getUpdateTime(){
    return update_time;
}

void TableInfo::setUpdateTime(QString update_time_){
    update_time = update_time_;
}

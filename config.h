#ifndef CONFIG_H
#define CONFIG_H

#include <QMap>
#include <QString>

class Config {
private:
QMap<QString, QString> parameters;
public:
    Config();
    QMap<QString, QString> getParameters();
    void setParameters(QMap<QString, QString> paramsFromXML);
    QString getParameterByKey(QString key);
    void updateValueForKey(QString key, QString newValue);
};

#endif // CONFIG_H

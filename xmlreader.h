#ifndef XMLREADER_H
#define XMLREADER_H

#include <QApplication>
#include <QMap>
#include <QFile>
#include <QString>
#include <QtXml/qdom.h>

class XMLReader
{
private:
QMap<QString, QString> configParameters;
public:
    XMLReader();
    void traverseNode(const QDomNode& node);
    void readXML(QString xmlFileName);
    QMap<QString, QString> getConfigParameters();
};

#endif // XMLREADER_H

#include "xmlreader.h"

XMLReader::XMLReader()
{
}

QMap<QString, QString> XMLReader::getConfigParameters(){
    return this->configParameters;
}

void  XMLReader::traverseNode(const QDomNode& node){

      QDomNode domNode = node.firstChild();

        while(!domNode.isNull())
        {
            if(domNode.isElement())
            {
               QDomElement domElement = domNode.toElement();
               if(!domElement.isNull())
               {

                       if (domElement.tagName()=="dbDriver")
                       //  dbDriver=domElement.text();
                           configParameters.insert("dbDriver",domElement.text());
                       if (domElement.tagName()=="dbMySQLServerHostName")
                       //  dbDriver=domElement.text();
                           configParameters.insert("dbMySQLServerHostName",domElement.text());
                       if (domElement.tagName()=="dbHost")
                       //  dbHost=domElement.text();
                           configParameters.insert("dbHost",domElement.text());
                       if (domElement.tagName()=="dbPort")
                       //  dbPort=domElement.text();
                           configParameters.insert("dbPort",domElement.text());
                       if (domElement.tagName()=="dbName")
                       //  dbName=domElement.text();
                           configParameters.insert("dbName",domElement.text());
                       if (domElement.tagName()=="dbUser")
                       //  dbUser=domElement.text();
                           configParameters.insert("dbUser",domElement.text());
                       if (domElement.tagName()=="dbPwd")
                       //  dbPwd=domElement.text();
                           configParameters.insert("dbPwd",domElement.text());
                       if (domElement.tagName()=="dbHostAPUS")
                       //  dbHostAPUS=domElement.text();
                           configParameters.insert("dbHostAPUS",domElement.text());
                       if (domElement.tagName()=="dbPortAPUS")
                       //  dbPortAPUS=domElement.text();
                           configParameters.insert("dbPortAPUS",domElement.text());
                       if (domElement.tagName()=="dbNameAPUS")
                       //  dbNameAPUS=domElement.text();
                           configParameters.insert("dbNameAPUS",domElement.text());
                       if (domElement.tagName()=="dbUserAPUS")
                       //  dbUserAPUS=domElement.text();
                           configParameters.insert("dbUserAPUS",domElement.text());
                       if (domElement.tagName()=="dbPwdAPUS")
                       //  dbPwdAPUS=domElement.text();
                           configParameters.insert("dbPwdAPUS",domElement.text());
                       if (domElement.tagName()=="dbCreateAnIndexAtTheBeginning")
                       //  dbPwdAPUS=domElement.text();
                           configParameters.insert("dbCreateAnIndexAtTheBeginning",domElement.text());

                       if (domElement.tagName()=="checkEachAMAFileBeforeProcessing")
                       {
                       //   checkEachAMAFile = domElement.text().toInt();
                            configParameters.insert("checkEachAMAFile","true");
                       }
                       if (domElement.tagName()=="sourceAMApathCopyFrom")
                       {
                           QString sourceAMApathCopyFrom=domElement.text();
                           if (sourceAMApathCopyFrom.right(1) != "\\")
                           sourceAMApathCopyFrom.append("\\");
                           configParameters.insert("sourceAMApathCopyFrom",sourceAMApathCopyFrom);

                       }
                       if (domElement.tagName()=="targetAMApathCopyTo")
                       {
                           QString targetAMApathCopyTo=domElement.text();
                           if (targetAMApathCopyTo.right(1) != "\\")
                           targetAMApathCopyTo.append("\\");
                           configParameters.insert("targetAMApathCopyTo",targetAMApathCopyTo);

                       }
                       if (domElement.tagName()=="excludeDirs")
                       {
                       //  QStringList excludeDirs = QString(domElement.text()).split(";");
                           QString excludeDirs = QString(domElement.text());
                           configParameters.insert("excludeDirs",excludeDirs);

                       }
                       if (domElement.tagName()=="countDaysAgoFrom")
                       //  countDaysAgoFrom=domElement.text().toInt();
                           configParameters.insert("countDaysAgoFrom",domElement.text());

                       if (domElement.tagName()=="countDaysAgoTo")
                       //  countDaysAgoTo=domElement.text().toInt();
                           configParameters.insert("countDaysAgoTo",domElement.text());
                       if (domElement.tagName()=="dbCSV")
                       {
                           QString pathToCSVstorage=domElement.text();
                           if (pathToCSVstorage.right(1) != "\\")
                           pathToCSVstorage.append("\\");
                           configParameters.insert("dbCSV",domElement.text());
                       }
                       if (domElement.tagName()=="dbDump")
                       {
                           QString pathToCSVstorage=domElement.text();
                           if (pathToCSVstorage.right(1) != "\\")
                           pathToCSVstorage.append("\\");
                           configParameters.insert("dbDump",domElement.text());
                       }
                       if (domElement.tagName()=="removeCSV")
                       {
                       //  removeCSV = domElement.text().toInt();
                           configParameters.insert("removeCSV",domElement.text());
                       }
                       if (domElement.tagName()=="userMode")
                       //  userMode=domElement.text();
                           configParameters.insert("userMode",domElement.text());
               }
           }

        traverseNode(domNode);
        domNode = domNode.nextSibling();
    }

}

void XMLReader::readXML(QString xmlFileName){
    QDomDocument domDoc;

    if (xmlFileName.isNull() || xmlFileName == "" ){
        xmlFileName = QApplication::applicationDirPath()+ "/mysqlConfig.xml";
    }

    QFile file(xmlFileName);

    if(file.open(QIODevice::ReadOnly)) {

        if(domDoc.setContent(&file)) {
            QDomElement domElement = domDoc.documentElement();
            traverseNode(domElement);
        }

        file.close();
    }
}



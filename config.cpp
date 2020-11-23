#include "config.h"

Config::Config()
{

}

QMap<QString, QString> Config::getParameters(){
    return parameters;
}

void Config::setParameters(QMap<QString, QString> paramsFromXML){
    parameters = paramsFromXML;
}

QString Config::getParameterByKey(QString key){
    return parameters.value(key).toUtf8();
}

void Config::updateValueForKey(QString key, QString newValue){

    QMap<QString, QString> currentParameters = parameters;
    QMap<QString, QString>::iterator currentCollectionIterator;
    QMap<QString, QString> updatedParameters;

    currentCollectionIterator = parameters.begin();

    while ( currentCollectionIterator != parameters.end() ){

        QString currentKey = currentCollectionIterator.key();

        if ( currentKey == key ){

             updatedParameters.insert(currentKey,newValue);

        }
        else {

             QString valueOfCurrentKey = currentCollectionIterator.value();
             updatedParameters.insert(currentKey,valueOfCurrentKey);

        }

        ++currentCollectionIterator;
    }

    parameters = updatedParameters;

}




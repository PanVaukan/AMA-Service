#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include <callinformation.h>
#include <randomgenerator.h>
#include <randomcpp11generator.h>
#include <qglobal.h>
#include <QTime>

class DataGenerator
{
public:
    DataGenerator();
    CallInformation getGeneratedData(int minDayOffset, int maxDayOffset);
};

#endif // DATAGENERATOR_H

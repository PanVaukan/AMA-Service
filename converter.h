#ifndef CONVERTER_H
#define CONVERTER_H

#include <callinformation.h>
#include <QString>

class Converter
{
public:
    Converter();
    QString convertToCSVFormat(CallInformation callInfo);
};

#endif // CONVERTER_H

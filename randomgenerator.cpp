#include "randomgenerator.h"
#include <qglobal.h>

RandomGenerator::RandomGenerator()
{
}

int RandomGenerator::randomBetween(int low, int high){

    return (qrand() % ((high + 1) - low) + low);

}

int RandomGenerator::randomBetween(int low, int high, int seed){

    qsrand(seed); // ��������� �������� ����� ��� ������� ������� � qrand
    return (qrand() % ((high + 1) - low) + low);

}

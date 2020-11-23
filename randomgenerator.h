#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

class RandomGenerator
{

public:
    RandomGenerator();
    int randomBetween(int low, int high);
    int randomBetween(int low, int high, int seed);
};

#endif // RANDOMGENERATOR_H

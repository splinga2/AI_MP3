#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include "includes.h"

enum class Class : int { NO, YES, SIZE };

struct Sample {
    int data[H][W];
    Sample();
};

class Classifier {

    const int CLASS_SIZE = static_cast<int>(Class::SIZE);

    int SizeOfTrainingSet;

    // P(yx=0/1|Y/N) = frequencyTables[y][x][0/1][Y=0/N=1]
    // P(yx=0/1)     = frequencyTables[y][x][0/1][2]
    // P(Y/N)        = frequencyTables[y][x][2][Y=0/N=1]
    // 3 = Class::SIZE
    double frequencyTables[H][W][3][3];

public:

    Classifier();

    void train(const char*, Class);
    void doneTraining();
    Class classify(Sample&);

};

int charToClass(char);

#endif /* CLASSIFIER_H */

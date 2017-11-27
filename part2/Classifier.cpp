#include "includes.h"
#include "Classifier.h"

Sample::Sample() {
    memset(data, 0, sizeof(data));
}

Classifier::Classifier() : SizeOfTrainingSet(0) {
    memset(frequencyTables, 0, sizeof(frequencyTables));
}

void Classifier::train(const char *fileName, Class c) {

    FILE *f = fopen(fileName, "r");
    int c_int = static_cast<int>(c);
    char buf[W + 10];

    int x = 0, y = 0;

    // while (fscanf(f, "%s", buf) == 1) {
    while (fgets(buf, W + 10, f) != nullptr) {

        if (strlen(buf) != W + 1) {
            y = 0;
            continue;
        }

        for (x = 0; x < W; ++x) {
            ++frequencyTables[y][x][charToClass(buf[x])][c_int];
        }

        ++y;

    } // end while fscanf

    fclose(f);

}

void Classifier::doneTraining(const double K) {

    std::vector<int> total;

    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x) {

            total.assign(CLASS_SIZE + 1, 0);

            for (int p = 0; p < 2; ++p) {
                for (int c = 0; c < CLASS_SIZE; ++c) {
                    frequencyTables[y][x][p][c] += K;
                    total[c] += frequencyTables[y][x][p][c];
                } // end c
            } // end p

            for (int i = 0; i < CLASS_SIZE; ++i) {
                total[CLASS_SIZE] += total[i];
            }

            for (int p = 0; p < 2; ++p) {
                for (int c = 0; c < CLASS_SIZE; ++c) {
                    frequencyTables[y][x][p][CLASS_SIZE] += frequencyTables[y][x][p][c];
                    frequencyTables[y][x][p][c] /= total[c];
                } // end c
                frequencyTables[y][x][p][CLASS_SIZE] /= total[CLASS_SIZE];
            } // end p

            for (int c = 0; c < CLASS_SIZE; ++c) {
                frequencyTables[y][x][2][c] = total[c] / total[CLASS_SIZE];
            }

        } // end x
    } // end y

}

Class Classifier::classify(Sample &s) {

    double p[2], total = 0;

    for (int c = 0; c < CLASS_SIZE; ++c) {

        /// @todo
        // p[c] = frequencyTables[y][x][2][c];
        p[c] = 0.5;

        for (int y = 0; y < H; ++y) {
            for (int x = 0; x < W; ++x) {
                p[c] *= frequencyTables[y][x][ s.data[y][x] ][c];
            } // end x
        } // end y

        total += p[c];

    } // end c

    for (int c = 0; c < CLASS_SIZE; ++c) p[c] /= total;

    return static_cast<Class>( (int) lround(p[1]) );

}

int charToClass(char c) {
    return (c == '%') ? 1 : 0;
}

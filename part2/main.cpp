#include "includes.h"
#include "Classifier.h"

void classify(const char *TEST_FILENAME, Classifier &classifier) {

    char buf[W + 10];
    int x = 0, y = 0;
    int yes = 0, no = 0;

    FILE *test = fopen(TEST_FILENAME, "r");

    Sample s;

    while (fgets(buf, W + 10, test) != nullptr) {

        if (strlen(buf) != W + 1) {
            y = 0;
            continue;
        }

        for (x = 0; x < W; ++x) {
            s.data[y][x] = charToClass(buf[x]);
        }

        if (++y == H) {
            switch (classifier.classify(s)) {
                case Class::NO:
                    // puts("NO");
                    ++no;
                    break;
                case Class::YES:
                    // puts("YES");
                    ++yes;
                    break;
                default:
                    puts("error");
                    break;
            }
            y = 0;
            // pause();
        }

    }

    printf("yes: %d\n", yes);
    printf("no : %d\n", no);

    fclose(test);

}

int main() {

    Classifier classifier;

    classifier.train(YES_TRAIN, Class::YES);
    classifier.train(NO_TRAIN, Class::NO);
    classifier.doneTraining();

    classify(YES_TEST, classifier);
    classify(NO_TEST, classifier);

    return 0;

}

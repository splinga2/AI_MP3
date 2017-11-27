#include "includes.h"
#include "Classifier.h"

void classify(const char *TEST_FILENAME, Classifier &classifier, int &yes, int &no) {

    char buf[W + 10];
    int x = 0, y = 0;
    // int yes = 0, no = 0;

    yes = no = 0;

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

    // printf("yes: %d\n", yes);
    // printf("no : %d\n\n", no);
    // printf("%d\t%d\n", yes, no);

    fclose(test);

}

double test(const double K) {

    Classifier classifier;
    int yes, no;
    double accuracy = 0;

    classifier.train(YES_TRAIN, Class::YES);
    classifier.train(NO_TRAIN, Class::NO);
    classifier.doneTraining(K);

    // puts(YES_TEST);
    // printf("%f\t%s\t", K, YES_TEST);
    classify(YES_TEST, classifier, yes, no);
    accuracy += (double) yes / (yes + no);

    // puts(NO_TEST);
    // printf("%f\t%s\t", K, NO_TEST);
    classify(NO_TEST, classifier, yes, no);
    accuracy += (double) no / (yes + no);

    accuracy = accuracy / 2.0 * 100;

    return accuracy;

}

int main() {
    for (double k = 0.1; k <= 5; k += 0.1) {
        printf("%f\t%f\n", k, test((const double) k));
    }
    return 0;
}

#include <random.h>

void RandomInit() {
    srand((unsigned int)time(NULL));
}

int RandInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

float RandFloat(float min, float max) {
    return (float)rand() / RAND_MAX * (max - min) + min;
}
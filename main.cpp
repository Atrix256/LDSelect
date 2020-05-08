#include <random>
#include <vector>

static const uint32_t c_numTests = 10;
static const uint32_t c_listSize = 50;

static const float c_goldenRatioConjugate = 0.61803398875f;
/*
The golden ratio is 1.61803398875...

The golden ratio conjugate is...
1) the "fractional" part of the golden ratio (terminology hehe...)
2) golden ratio - 1
3) 1 / golden ratio

I use the conjugate instead of the golden ratio itself because it's just as irrational but is smaller so has more 
precision in operations when working w/ floating point.  You could use the golden ratio for the same effect though.
*/

float fract(float f)
{
    return f - floor(f);
}

int main(int argc, char** argv)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    const std::vector<bool> listA(c_listSize, true);
    const std::vector<bool> listB(c_listSize, false);
    std::vector<bool> listC(c_listSize);

    for (uint32_t testIndex = 0; testIndex < c_numTests; ++testIndex)
    {
        // get the seed for this low discrepancy "random selection"
        float seed = dist(rng);

        // get the percentage chance to choose from list A instead of list B
        float listAWeight = dist(rng);

        // do low discrepancy "random selection"
        uint32_t listAChosenCount = 0;
        float selectionRng = seed;
        printf("test %u, seed = %f, listAWeight = %0.2f%%\n", testIndex, seed, listAWeight*100.0f);
        for (uint32_t valueIndex = 0; valueIndex < c_listSize; ++valueIndex)
        {
            listC[valueIndex] = (selectionRng < listAWeight) ? listA[valueIndex] : listB[valueIndex];
            listAChosenCount += (selectionRng < listAWeight) ? 1 : 0;
            selectionRng = fract(selectionRng + c_goldenRatioConjugate);
        }

        // report results
        printf("list A chosen %0.2f%% of the time\n[", 100.0f * float(listAChosenCount) / float(c_listSize));
        for (bool b : listC)
            printf("%c ", b ? '1' : ' ');
        printf("]\n\n");
    }

    system("pause");
    return 0;
}

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

long long comparisons = 0;

//----------------------------------------
// Swap Function
//----------------------------------------
void swapValues(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

//----------------------------------------
// Pivot Types
//----------------------------------------
enum PivotType
{
    FIRST,
    LAST,
    MIDDLE,
    RANDOM
};

//----------------------------------------
// Choose Pivot
//----------------------------------------
int choosePivot(vector<int> &A, int low, int high, PivotType type)
{
    if(type == FIRST)
        return low;

    else if(type == LAST)
        return high;

    else if(type == MIDDLE)
        return (low + high) / 2;

    else
        return low + rand() % (high - low + 1);
}

//----------------------------------------
// Partition
//----------------------------------------
int partition(vector<int> &A, int low, int high, PivotType type)
{
    int pivotIndex = choosePivot(A, low, high, type);

    swapValues(A[pivotIndex], A[high]);

    int pivot = A[high];

    int i = low - 1;

    for(int j = low; j < high; j++)
    {
        comparisons++;

        if(A[j] <= pivot)
        {
            i++;
            swapValues(A[i], A[j]);
        }
    }

    swapValues(A[i + 1], A[high]);

    return i + 1;
}

//----------------------------------------
// Quick Sort
//----------------------------------------
void quickSort(vector<int> &A, int low, int high, PivotType type)
{
    if(low < high)
    {
        int p = partition(A, low, high, type);

        quickSort(A, low, p - 1, type);

        quickSort(A, p + 1, high, type);
    }
}

//----------------------------------------
// Generate Random Array
//----------------------------------------
vector<int> randomArray(int n)
{
    vector<int> A(n);

    for(int i = 0; i < n; i++)
        A[i] = rand() % 100000;

    return A;
}

//----------------------------------------
// Generate Sorted Array
//----------------------------------------
vector<int> sortedArray(int n)
{
    vector<int> A(n);

    for(int i = 0; i < n; i++)
        A[i] = i;

    return A;
}

//----------------------------------------
// Generate Reverse Sorted Array
//----------------------------------------
vector<int> reverseArray(int n)
{
    vector<int> A(n);

    for(int i = 0; i < n; i++)
        A[i] = n - i;

    return A;
}

//----------------------------------------
// Run Experiment
//----------------------------------------
void runExperiment(vector<int> original,
                   PivotType pivot,
                   string pivotName)
{
    long long totalComparisons = 0;
    long long totalTime = 0;

    for(int i = 0; i < 3; i++)
    {
        vector<int> A = original;

        comparisons = 0;

        auto start = high_resolution_clock::now();

        quickSort(A, 0, A.size() - 1, pivot);

        auto end = high_resolution_clock::now();

        long long timeTaken =
        duration_cast<microseconds>(end - start).count();

        totalComparisons += comparisons;
        totalTime += timeTaken;
    }

    cout << pivotName << "\t\t"
         << totalComparisons / 3 << "\t\t"
         << totalTime / 3 << " us"
         << endl;
}

//----------------------------------------
// Display Results
//----------------------------------------
void displayResults(vector<int> data, string inputType)
{
    cout << "\n============================================\n";
    cout << "        " << inputType << " INPUT RESULTS\n";
    cout << "============================================\n";

    cout << "Pivot Type\tComparisons\tTime\n";
    cout << "--------------------------------------------\n";

    runExperiment(data, FIRST, "First");
    runExperiment(data, LAST, "Last");
    runExperiment(data, MIDDLE, "Middle");
    runExperiment(data, RANDOM, "Random");
}

//----------------------------------------
// Main
//----------------------------------------
int main()
{
    srand(time(0));

    int n;

    cout << "Enter input size: ";
    cin >> n;


    vector<int> random = randomArray(n);
    vector<int> sorted = sortedArray(n);
    vector<int> reversed = reverseArray(n);


    cout << "\nInput Size = " << n << endl;


    // Random Input
    displayResults(random, "RANDOM");


    // Sorted Input
    displayResults(sorted, "SORTED");


    // Reverse Sorted Input
    displayResults(reversed, "REVERSE SORTED");


    return 0;
}

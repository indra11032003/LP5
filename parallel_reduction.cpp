#include <iostream>
#include <omp.h>
#include <vector>
#include <limits>

using namespace std;

int main() {
    // vector<int> data = {10,5,5};

    // int n = data.size();
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    vector<int> data(n);
    cout << "Enter " << n << " elements:" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> data[i];
    }

    int sum = 0;
    int minimum = INT8_MAX;
    int maximum = numeric_limits<int>::min();

    // Parallel reduction for sum, min, and max
    #pragma omp parallel for reduction(+:sum) reduction(min:minimum) reduction(max:maximum)
    for (int i = 0; i < n; ++i) {
        sum += data[i];
        if (data[i] < minimum) minimum = data[i];
        if (data[i] > maximum) maximum = data[i];
    }

        int average = sum/ n;

    cout << "Parallel Sum: " << sum << endl;
    cout << "Parallel Min: " << minimum << endl;
    cout << "Parallel Max: " << maximum << endl;
    cout << "Parallel Average: " << average << endl;

    return 0;
}

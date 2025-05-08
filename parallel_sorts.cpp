#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

// Sequential Bubble Sort
void bubbleSortSeq(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
}

// Parallel Bubble Sort with OpenMP (odd-even transposition sort)
// void bubbleSortParallel(vector<int>& arr) {
//     int n = arr.size();
//     for (int i = 0; i < n; i++) {
//         int phase = i % 2;
//         #pragma omp parallel for shared(arr, n, phase)
//         for (int j = phase; j < n - 1; j += 2) {
//             if (arr[j] > arr[j + 1]) {
//                 swap(arr[j], arr[j + 1]);
//             }
//         }
//     }
// }


void pbubble(vector<int> arr,int n){
    #pragma omp parallel
    {
      for(int i=0;i<n;i++){
  
          #pragma omp for
          for(int j=1;j<n-1;j=j+2){
              if(arr[j]>arr[j+1]){
                  swap(arr[j],arr[j+1]);
              }
  
          }
          #pragma omp barrier
          #pragma omp for
          for(int j=0;j<n-1;j=j+2){
              if(arr[j]>arr[j+1]){
                  swap(arr[j],arr[j+1]);
              }
  
          }
  
          #pragma omp barrier
          
  
      }
  
    }
   
     
  }

// Sequential Merge Sort
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSortSeq(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortSeq(arr, l, m);
        mergeSortSeq(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Parallel Merge Sort with OpenMP
void mergeSortParallel(vector<int>& arr, int l, int r, int depth = 0) {
    if (l < r) {
        int m = l + (r - l) / 2;
        if (depth < 4) { // limit parallel depth to avoid overhead
            #pragma omp parallel sections
            {
                #pragma omp section
                mergeSortParallel(arr, l, m, depth + 1);
                #pragma omp section
                mergeSortParallel(arr, m + 1, r, depth + 1);
            }
        } else {
            mergeSortSeq(arr, l, m);
            mergeSortSeq(arr, m + 1, r);
        }
        merge(arr, l, m, r);
    }
}

int main() {
    const int SIZE = 20000;
    vector<int> original(SIZE);
    for (int i = 0; i < SIZE; i++) original[i] = rand() % 20000;

    // --- Bubble Sort
    auto arr1 = original;
    auto start = high_resolution_clock::now();
    bubbleSortSeq(arr1);
    auto end = high_resolution_clock::now();
    cout << "Sequential Bubble Sort Time: "
         << duration_cast<milliseconds>(end - start).count() << " ms\n";

    auto arr2 = original;
    start = high_resolution_clock::now();
    pbubble(arr2);
    end = high_resolution_clock::now();
    cout << "Parallel Bubble Sort Time: "
         << duration_cast<milliseconds>(end - start).count() << " ms\n";

    // --- Merge Sort
    auto arr3 = original;
    start = high_resolution_clock::now();
    mergeSortSeq(arr3, 0, SIZE - 1);
    end = high_resolution_clock::now();
    cout << "Sequential Merge Sort Time: "
         << duration_cast<milliseconds>(end - start).count() << " ms\n";

    auto arr4 = original;
    start = high_resolution_clock::now();
    mergeSortParallel(arr4, 0, SIZE - 1);
    end = high_resolution_clock::now();
    cout << "Parallel Merge Sort Time: "
         << duration_cast<milliseconds>(end - start).count() << " ms\n";

    return 0;
}

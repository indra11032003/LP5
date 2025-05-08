#include <iostream>
using namespace std;
#include<omp.h>
#include<vector>

void bubble(vector<int> arr,int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
            }
        }
}
// for(int i=0;i<n;i++){
//     cout<<arr[i]<<" ";

// }
 }

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



int main(){

    const int SIZE = 20000;
    vector<int> arr(SIZE);
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 20000;
    }
    vector<int> arr2=arr;
    // for(int i=0;i<n-1;i++){
    //         for(int j=0;j<n-i-1;j++){
    //             if(arr[j]>arr[j+1]){
    //                 swap(arr[j],arr[j+1]);
    //             }
    //         }
    // }
    // for(int i=0;i<n;i++){
    //     cout<<arr[i]<<" ";

    // }
    double start=omp_get_wtime();
    bubble(arr,SIZE);
    cout<<endl;
    double end=omp_get_wtime();
    cout<<endl;
    cout<<"normal bubble:"<<(end-start)<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;


    double start2=omp_get_wtime();
    pbubble(arr2,SIZE);
    cout<<endl;
    double end2=omp_get_wtime();
    cout<<endl;
    cout<<"parallel bubble:"<<(end2-start2)<<endl;
}
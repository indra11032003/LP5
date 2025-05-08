#include <iostream>
using namespace std;
#include<omp.h>
#include<vector>


void merge(vector<int>& arr,int l,int m,int r){
    int n1=m-l+1; int n2=r-m;
    vector<int>L(n1);
    vector<int>R(n2);
    for(int i=0;i<n1;i++)L[i]=arr[l+i];
    for(int i=0;i<n2;i++)R[i]=arr[m+1+i];

    int i=0;int j=0; int k=l;
    while(i<n1 && j<n2)arr[k++]=(L[i]<=R[j])?L[i++]:R[j++];
    while(i<n1)arr[k++]=L[i++];
    while(j<n2)arr[k++]=R[j++];
    

}
 
void msort(vector<int>& arr,int l,int r)
{
    if(l<r){
        int m=l+(r-l)/2;

        msort(arr,l,m);
        msort(arr,m+1,r);
        
        merge(arr,l,m,r);

    }
}


void pmsort(vector<int>& arr,int l,int r,int depth=0)
{
    if(l<r){
        int m=l+(r-l)/2;

        if(depth<4){
            #pragma omp parallel sections
            {
                #pragma omp section
                pmsort(arr,l,m,depth+1);
                #pragma omp section
            
            pmsort(arr,m+1,r);
           }

            }

        
        else{
        msort(arr,l,m);
        msort(arr,m+1,r);}

        merge(arr,l,m,r);
}

}

// int main(){

//     // const int SIZE = 20000;
//     // vector<int> arr(SIZE);
//     // for (int i = 0; i < SIZE; i++) {
//     //     arr[i] = rand() % 20000;
//     // }
//     // vector<int> arr2=arr;
    
//     // double start=omp_get_wtime();
//     // bubble(arr,SIZE);
//     // cout<<endl;
//     // double end=omp_get_wtime();
//     // cout<<endl;
//     // cout<<"normal bubble:"<<(end-start)<<endl;
//     // cout<<endl;
//     // cout<<endl;
//     // cout<<endl;
//     vector<int> arr={6,8,9,1,2,70,56};
//     int size=arr.size();

//     msort(arr,0,size-1);
//     for (int x : arr) {
//         cout << x << " ";
//     }
//     cout << endl;
//     cout<<"---------------------------------------------";

//     vector<int> arr1={6,8,9,1,2,70,56};
//     int size1=arr1.size();

//     pmsort(arr1,0,size1-1);
//     for (int x : arr1) {
//         cout << x << " ";
//     }
//     cout << endl;
    


   
// }
int main() {
    const int SIZE = 100000;  // Increase size to better observe timing
    vector<int> arr(SIZE);
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 100000;
    }
    vector<int> arr1 = arr; // Make a copy for parallel sort

    // Sequential merge sort timing
    double start_seq = omp_get_wtime();
    msort(arr, 0, arr.size() - 1);
    double end_seq = omp_get_wtime();

    // Parallel merge sort timing
    double start_par = omp_get_wtime();
    pmsort(arr1, 0, arr1.size() - 1);
    double end_par = omp_get_wtime();

    cout << "Sequential Merge Sort Time: " << (end_seq - start_seq) << " seconds" << endl;
    cout << "Parallel Merge Sort Time:   " << (end_par - start_par) << " seconds" << endl;

    return 0;
}

#include <iostream>
#include <cmath>
#include <string>
#include <chrono>
#include <mutex>
#include <fstream>
#include <vector>

using namespace std;
mutex logMutex;

#define QUICK_SORT 1
#define MERGE_SORT 2
#define COMB_SORT 3

int sort_id[3] = {QUICK_SORT, MERGE_SORT, COMB_SORT};


double get_time() {
    return std::chrono::duration_cast<std::chrono::microseconds>                         (std::chrono::steady_clock::now().time_since_epoch()).count()/1e6;
}

void fill_randints(int arr[], int len_arr){
    for (int i = 0; i < len_arr; i++){
        arr[i] = rand();
    }
}
void swap(int a, int b){
    int temp = a;
    a = b;
    b = temp;
}


void quick_sort(int *array, int low, int high)
{
    int i = low;
    int j = high;
    int pivot = array[(i + j) / 2];
    int temp;

    while (i <= j)
    {
        while (array[i] < pivot)
            i++;
        while (array[j] > pivot)
            j--;
        if (i <= j)
        {
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    }
    if (j > low)
        quick_sort(array, low, j);
    if (i < high)
        quick_sort(array, i, high);
}

void merge(int arr[], int p, int q, int r) {
  
  int n1 = q - p + 1;
  int n2 = r - q;
  
  vector<int> L(n1);
  vector<int> M(n2);
  
  for (int i = 0; i < n1; i++)
    L[i] = arr[p + i];
    
  for (int j = 0; j < n2; j++)
    M[j] = arr[q + 1 + j];
    
  int i = 0, j = 0, k = p;
  
  while (i < n1 && j < n2) {
    if (L[i] <= M[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = M[j];
      j++;
    }
    k++;
  }
  
  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }
  
  while (j < n2) {
    arr[k] = M[j];
    j++;
    k++;
  }
}

void merge_sort(int arr[], int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;
    
    merge_sort(arr, l, m);
    merge_sort(arr, m + 1, r);
    merge(arr, l, m, r);
  }
}


void comb_sort(int arr[], int n){
    int gap = n;

    bool swapped = true;

    while (gap > 1 || swapped == true)
    {
        gap /= 1.25;

        swapped = false;

        for (int i=0; i<n-gap; i++)
        {
            if (arr[i] > arr[i+gap])
            {
                swap(arr[i], arr[i+gap]);
                swapped = true;
            }
        }
    }
}

void write_array_w_name_to_mycsv(double arr[], int len_arr, string name){
    lock_guard<std::mutex> csvLock(logMutex);
    fstream file;
    file.open("//home//michael//Desktop//cproj//labs//sort_lab//task_3//data02.csv", ios::out | ios::app);
    file << name<< ',';
    for(int i = 0; i<len_arr; i++){
        file << arr[i]<<',';
    }
    file<<"\n";
}

void printArray(int arr[], int size) {
  for (int i = 0; i < size; i++)
    cout << arr[i] << " ";
  cout << endl;
}

int main(){
    double t_start, t_end;
    for (int id = 0; id < 3; id++){
        for (int len = 1000; len <=100000; len+=1000){
            int arr[len];
            int meas_amount = 10;
            double arr_to_csv[meas_amount+1];
            arr_to_csv[0] = (double) len;
            cout << len << endl;

            for (int i = 0; i < meas_amount; i++){
            fill_randints(arr, len);
            cout << id << endl;

            int n = sizeof(arr)/sizeof(arr[0]);

            cout << n << endl;
            t_start = get_time();
            switch(sort_id[id]){
                case QUICK_SORT:
                    quick_sort(arr,0,n-1);
                    break;
                case MERGE_SORT:
                    merge_sort(arr,0,n-1);
                    break;
                case COMB_SORT:
                    comb_sort(arr,n);
                    break;
            }
            t_end = get_time();
            
            double time_to_sort = t_end-t_start;
            arr_to_csv[i+1] = time_to_sort;
            }
            switch(sort_id[id]){
                case QUICK_SORT:
                    write_array_w_name_to_mycsv(arr_to_csv, meas_amount+1, "quick");
                    break;
                case MERGE_SORT:
                    write_array_w_name_to_mycsv(arr_to_csv, meas_amount+1, "merge");
                    break;
                case COMB_SORT:
                    write_array_w_name_to_mycsv(arr_to_csv, meas_amount+1, "comb");
                    break;
            }
        }
    }
}
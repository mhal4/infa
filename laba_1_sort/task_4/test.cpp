#include <iostream>
#include <cmath>
#include <string>
#include <chrono>
#include <mutex>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
mutex logMutex;

#define QUICK_SORT 0
#define MERGE_SORT 1
#define COMB_SORT 2
#define BUBBLE_SORT 3
#define INSERTION_SORT 4
#define SELECTION_SORT 5


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

void bubble_sort(int arr[], int len_arr){
    
    for (int i = 0; i<len_arr-1; i++){
        for(int j = i+1; j<len_arr; j++){
            if (arr[i+1] < arr[i]){
                swap(arr[i+1], arr[i]);
            }
        }
    }
}

void insertion_sort(int arr[], int len_arr){
    int elem;
    for (int i = 0; i<len_arr; i++){
        elem = arr[i];
        int j = i;
        while(j > 0 && arr[j-1] >elem){
            arr[j] = arr[j-1];
            j -= 1;
        }
        arr[j]=elem;
    }
}

void selection_sort(int arr[], int len_arr){
    for (int i = len_arr; i > 0; i--){
        int max = -10000000;
        int ind_max;
        for (int j = 0; j < i; j++){
            if (max < arr[j]){
                max = arr[j];
                ind_max = j;
            }
        }
    swap(arr[i],arr[ind_max]);
    }
}

void write_to_csv(double arr[],int len_arr, string name){
    lock_guard<std::mutex> csvLock(logMutex);
    fstream file;
    file.open("//home//michael//Desktop//cproj//labs//sort_lab//task_5//data5.csv", ios::out | ios::app);
    file << name<< ',';
    for(int i = 0; i<len_arr; i++){
        file << arr[i]<<',';
    }
    file<<"\n";
}

void printArray(double arr[], int size) {
  for (int i = 0; i < size; i++)
    cout << arr[i] << " ";
  cout << endl;
}
void printArray_int(int arr[], int size) {
  for (int i = 0; i < size; i++)
    cout << arr[i] << " ";
  cout << endl;
}

double get_time() {
    return std::chrono::duration_cast<std::chrono::microseconds>                         (std::chrono::steady_clock::now().time_since_epoch()).count()/1e6;
}

void fill_randints(int arr[], int len_arr){
    for (int i = 0; i < len_arr; i++){
        arr[i] = rand();
    }
}

void copy(int arr1[], int arr2[], int len){
    for (int i = 0; i< len; i++){
        arr2[i] = arr1[i];
    }
}

void reverse(int arr[], int len_arr){
    for (int i=0; i<len_arr/2; i++){
        swap(arr[i], arr[len_arr-1-i]);
    }
}

void sort(int id, int temp[], int len){
    switch (id){
        case QUICK_SORT:
            quick_sort(temp,0,len-1);
            break;
        case MERGE_SORT:
            merge_sort(temp,0,len-1);
            break;
        case COMB_SORT:
            comb_sort(temp,len);
            break;
        case BUBBLE_SORT:
            bubble_sort(temp,len);
            break;
        case INSERTION_SORT:
            insertion_sort(temp,len);
            break;
        case SELECTION_SORT:
            selection_sort(temp,len);
            break;
        default:
            break;
    }
}

void write(double arr[], int id){
    switch (id){
                case QUICK_SORT:
                    write_to_csv(arr,4,"quick");
                    break;
                case MERGE_SORT:
                    write_to_csv(arr,4,"merge");
                    break;
                case COMB_SORT:
                    write_to_csv(arr,4,"comb");
                    break;
                case BUBBLE_SORT:
                    write_to_csv(arr,4,"bubble");
                    break;
                case INSERTION_SORT:
                    write_to_csv(arr,4,"insertion");
                    break;
                case SELECTION_SORT:
                    write_to_csv(arr,4,"selection");
                    break;
                default:
                    break;
            }
}

int main(){
    int len = 6;
    int temp[len] = {4,5,2,1,3,6};
    printArray_int(temp,len);
    reverse(temp, len);
    printArray_int(temp,len);
}
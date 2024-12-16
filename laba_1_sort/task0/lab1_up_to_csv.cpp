#include <iostream>
#include <cmath>
#include <string>
#include <chrono>
#include <mutex>
#include <fstream>

using namespace std;
mutex logMutex;

#define BUBBLE_SORT 1
#define INSERTION_SORT 2
#define SELECTION_SORT 3

int sort_id[3] = {BUBBLE_SORT, INSERTION_SORT, SELECTION_SORT};


double get_time() {
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()/1e6;
}

void fill_randints(int arr[], int len_arr){
    for (int i = 0; i < len_arr; i++){
        arr[i] = rand();
    }
}
void swap(int a, int b){
    int temp = a;
    a = b;
    b = a;
}

void bubble_sort(int arr[], int len_arr){
    
    for (int i = 0; i<len_arr-1; i++){
        for(int j = i+1; j<len_arr; j++){
            if (arr[j] < arr[i]){
                swap(arr[j], arr[i]);
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

void write_array_w_name_to_mycsv(double arr[], int len_arr, string name){
    lock_guard<std::mutex> csvLock(logMutex);
    fstream file;
    file.open("//home//michael//Desktop//cproj//labs//sort_lab//task_0//data01.csv", ios::out | ios::app);
    file << name<< ',';
    for(int i = 0; i<len_arr; i++){
        file << arr[i]<<',';
    }
    file<<"\n";
}


int main(){
    double t_start, t_end;
    for (int id = 0; id < 3; id++){
        for (int len = 1000; len <=100000; len+=1000){
            int arr[len];
            int meas_amount = 10;
            double arr_to_csv[meas_amount+1];
            arr_to_csv[0] = (double) len;
            
                for (int i = 0; i < meas_amount; i++){
                fill_randints(arr, len);
                cout << id;
                t_start = get_time();
                switch(sort_id[id]){
                    case BUBBLE_SORT:
                        bubble_sort(arr,len);
                        break;
                    case INSERTION_SORT:
                        insertion_sort(arr,len);
                        break;
                    case SELECTION_SORT:
                        selection_sort(arr,len);
                        break;
                }
                t_end = get_time();
                
                double time_to_sort = t_end-t_start;
                arr_to_csv[i+1] = time_to_sort;
                }
            switch(sort_id[id]){
                case BUBBLE_SORT:
                    write_array_w_name_to_mycsv(arr_to_csv, meas_amount+1, "bubble");
                    break;
                case INSERTION_SORT:
                    write_array_w_name_to_mycsv(arr_to_csv, meas_amount+1, "insertion");
                    break;
                case SELECTION_SORT:
                    write_array_w_name_to_mycsv(arr_to_csv, meas_amount+1, "selection");
                    break;
                default:
                    continue;
            }
        }
    }
}
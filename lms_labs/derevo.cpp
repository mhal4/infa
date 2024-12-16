#include <iostream>


using namespace std;

bool game(int *arr, int m, int s, int size){
    if (s == m) return true;
    if (s > m) return false;
    if (size == 1) return ((s+arr[0]) == m);
    if (size == 0) return false;
    int new_arr[size-2];
    for (int i = 1; i < size-1; i++) {
        new_arr[i-1] = arr[i]; 
        //cout << arr[i] << ' ';
    } 
    if (game(new_arr, m+arr[0], s+arr[-1], size-2)) return true;
    if (game(new_arr, m+arr[-1], s+arr[0], size-2)) return true; 
} 

int main(){
    int n;
    cin >> n;
    int a[n];
    for(int i = 0; i < n; i++){
        int ai;
        cin >> ai;
        a[n] = ai;
    }
    int s = 0;
    for (int i = 1; i < 50; i++){
        cout << i << '\n';
        if (game(a,i,s,n)) cout << i << ' ';
    }
}
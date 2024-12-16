#include <iostream>
#include <iomanip>

using namespace std;
const float FLOAT_EPSILON = 0.01;


struct Hamis {
    unsigned int legs, eyes, hp, level;
    float mass;
    float aggression;
};

uint rnd(float n){
    if (abs((float)(uint)n-n) > 0.5) return uint(n) + 1;
    else return uint(n);
}

Hamis* fake(Hamis* brood, unsigned int n){
    if (n == 0) return NULL;

    uint legs = 0, eyes = 0, hp = 0, lvl = 0;
    float mmass = 0.0f;
    float maggro = 1000.0f;

    for(uint i = 0; i < n; i++){
        legs += brood[i].legs;
        eyes += brood[i].eyes;
        hp += brood[i].hp;
        lvl += brood[i].level;

        if (mmass < brood[i].mass){
            mmass  = brood[i].mass;
        }
        if (maggro > brood[i].aggression){
            maggro = brood[i].aggression;
        }
    }

    Hamis* ham = new Hamis;
    ham->legs = 3;
    ham->eyes = 3;
    ham->hp = rnd((float)(hp)/(float)n);
    ham->level = rnd((float)(lvl)/(float)n);
    ham->mass = mmass;
    ham->aggression = maggro;
    return ham;
}


int main()
{
    unsigned int n;
    cin >> n;
    Hamis* brood = new Hamis[n];
    for (unsigned int i = 0; i < n; i++)
    {
        brood[i].legs = brood[i].eyes = 3;
        cin >> brood[i].hp >> brood[i].level >> brood[i].mass >> brood[i].aggression;
    }
    Hamis* faked = fake(brood, n);
    delete[] brood;
    if (!faked) return 0;
    cout << fixed << setprecision(2);
    cout << faked->legs << " " << faked->eyes << " " << faked->hp << " " << faked->level << " " << faked->mass << " " << faked->aggression << endl;
    delete faked;
    return 0;
}
















/*
#  задание 3
struct coord{
    int x;
    int y;
};

int main(){
    int n,m;
    cin >> n >> m;
    coord a[m*8];
    int d = n*2 - 1;
    for (int i = 0; i < m; i++){
        cin >> a[i].x >> a[i].y;
    }

    // rotate 1:
    for (int i = 0; i < m; i++){
        int d = abs(a[i].x + a[i].y - (n-1));
        if (a[i].y > -a[i].x + n-1){
            a[i+m].x = a[i].x - d;
            a[i+m].y = a[i].y - d;
        } else {
            a[i+m].x = a[i].x + d;
            a[i+m].y = a[i].y + d;
        }
    }

    // rotate 2:
    for (int i = 0; i < 2*m; i++){
        int dx = n - a[i].x - 2;
        a[i+2*m].x = n + dx;
        a[i+2*m].y = a[i].y;
    }

    // rotate 3:
    for (int i = 0; i < 4*m; i++){
        int dy = -a[i].y;
        a[i+4*m].x = a[i].x;
        a[i+4*m].y = dy;
    }


    for (int y = 0; y < d; y++){
        for (int x = 0; x < d; x++){
            bool flag = 1;
            for (int i = 0; i < 8*m; i++){
                //cout << a[i].x << ' ' << abs(a[i].y - n + 1) << ' ' << x  << ' ' << y<< ' ';
                //cout << '\n';
                if ((a[i].x == x) && (abs(a[i].y - n + 1) == y)){
                    cout << ' ';
                    flag = 0;
                    break;
                }
            }
            if (flag) cout << '*';
            cout << ' '; 
        }
        cout << '\n';
    }
    //for (int i = 0; i < 8*m; i++) {cout << a[i].x << ' ' << a[i].y << '\n';}
}


*/









/*
# задание 1
int main(){
    int n,m = -1;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++){
        cin >> a[i];
        if (a[i] > m) m = a[i];
    }

    int c = 0;
    int r[n];
    for(int i = 0; i < n - 3; i++){
        if ((float)(a[i+1] - a[i+2]) > m/2.0){
            if ((a[i+1] > a[i]) && (a[i+3] > a[i+2])){
                r[c] = i+1;
                c++;
            }
        }

        if ((float)(a[i+1] - a[i+2]) < -m/2.0){
            if ((a[i] > a[i+1]) && (a[i+2] > a[i+3])){
                r[c] = i+1;
                c++;
            }
        }
    }
    for (int i = 0; i < c; i++){
        cout << r[i] << ' ';
    } 
    cout << ' ';
}
*/










/*
# задание 2
int main(){
    int n,m;
    cin >> n >> m;
    int a[n][m];

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cin >> a[i][j];
        }
    }

    if (n == 0 || m == 0){
        cout << ' ';
        return 0;
    }

    if (n==1 && m == 1){
        cout << a[0][0];
        return 1;
    }

    if (n == 1 && m == 2){
        cout << a[0][1] << ' ' << a[0][0];
        return 2;
    }

    if (n == 2 && m == 1){
        cout << a[1][0] << '\n' << a[0][0];
        return 3;
    }

    for (int i = 0; i < n-1; i++){
        for (int j = 0; j < m-1; j++){
            int t1 = a[i][j];
            int t2 = a[i][j+1];
            int t3 = a[i+1][j+1];
            int t4 = a[i+1][j];
            a[i][j] = t4;
            a[i][j+1] = t1;
            a[i+1][j+1] = t2;
            a[i+1][j] = t3;
        }
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cout << a[i][j] << ' ';
        }
        cout << '\n';
    }
    return 4;
}*/

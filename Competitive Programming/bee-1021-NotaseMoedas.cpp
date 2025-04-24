#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define f first
#define s second 
#define pb push_back

using namespace std;

const int INF =  1e8 + 10;

long double a;

int main(){ _

    cin >> a;

    int cents = round(a * 100); // converte para evitar erro numerico

    int v[] = {
        10000, 5000, 2000, 1000, 500, 200, 100, 50, 25, 10, 5, 1
    };

    int qtd [12] = {0}; // qntd de cada meoda

    for(int i = 0; i < 12; i++){
        qtd[i] = cents / v[i];
        cents = cents % v[i];
    }

    cout << fixed << setprecision(2);
    cout << "NOTAS:" << endl;
    for(int i = 0; i < 6; i++){
        cout << qtd[i] << " nota(s) de R$ " << round(v[i]/100) << endl;
    }

    cout << "MOEDAS:" << endl;
    for(int i = 6; i < 12; i++){
        cout << qtd[i] << " moedas(s) de R$ " << double(v[i])/100 << endl;
    }


    return 0;
}
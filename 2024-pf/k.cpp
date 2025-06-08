#include <bits/stdc++.h>

using namespace std;

#define DBG(x) cout << "[" << #x << "]: " << x << endl
#define F(x) std::fixed << std::setprecision(1) << (x)
#define f first
#define s second
#define pb push_back
#define mp make_pair

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;

const int MAXN = 110;
const int MAXSOMA = 10010;
bool marcado[MAXN][MAXSOMA];
int v[MAXN];
int n, soma;
vector<int> alice, bob;

bool subset_sum(int i, int target)
{
    if (marcado[i][target]) {
        return false;
    }

    marcado[i][target] = true;

    if (i == n) {
        return target == soma;
    }

    if (v[i] + target <= soma && subset_sum(i + 1, target + v[i])) {
        alice.push_back(v[i]);
        return true;
    }

    if (subset_sum(i + 1, target)) {
        bob.push_back(v[i]);
        return true;
    }

    return false;
}


int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    soma = 0;

    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
        soma += v[i];
    }

    if ((soma % 2) == 1) {
        cout << "-1\n";
        return 0;
    }

    soma = soma / 2;

    memset(marcado, 0, sizeof(marcado));

    if (!subset_sum(0, 0)) {
        cout << "-1\n";
        return 0;
    }

    int soma_alice = 0, soma_bob = 0;
    vector<int> resultado;

    for (int i = 0; i < n; i++)
    {
        if (soma_alice <= soma_bob) {
            resultado.push_back(alice.back());
            soma_alice += alice.back();
            alice.pop_back();
        } else {
            resultado.push_back(bob.back());
            soma_bob += bob.back();
            bob.pop_back();
        }
    }
    
    for (int i = 0; i < n; i++)
    {
        cout << (i == 0 ? "" : " ") << resultado[i];
    }
    cout << "\n";
    


    


    return 0;
}

// g++ -O2 -Wall nome.cpp -o nome
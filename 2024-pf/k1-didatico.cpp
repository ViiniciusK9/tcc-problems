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
int memo[MAXN][MAXSOMA];
int valores[MAXN];
int n, soma_alvo;
vector<int> alice, bob;


bool subset_sum(int indice, int soma_atual)
{
    if (soma_atual == soma_alvo) {
        return true;
    }

    if (soma_atual > soma_alvo || indice >= n) {
        return false;
    }

    if (memo[indice][soma_atual] != -1) {
        return memo[indice][soma_atual];
    }

    bool incluir = subset_sum(indice + 1, soma_atual + valores[indice]);
    bool excluir = subset_sum(indice + 1, soma_atual);

    return memo[indice][soma_atual] = ((incluir || excluir) ? 1 : 0);
}

void obter_subset()
{
    int resto = soma_alvo;

    for (int i = n-1; i >= 0; i--)
    {
        if (resto >= valores[i] && memo[i][resto - valores[i]] == 1) {
            alice.push_back(valores[i]);
            resto -= valores[i];
        } else {
            bob.push_back(valores[i]);
        }
    }
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    soma_alvo = 0;

    for (int i = 0; i < n; i++)
    {
        cin >> valores[i];
        soma_alvo += valores[i];
    }

    if ((soma_alvo % 2) == 1) {
        cout << "-1\n";
        return 0;
    }

    soma_alvo = soma_alvo / 2;

    memset(memo, -1, sizeof(memo));

    if (!subset_sum(0, 0)) {
        cout << "-1\n";
        return 0;
    }

    obter_subset();
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
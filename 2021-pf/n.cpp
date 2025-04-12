#include<bits/stdc++.h>

using namespace std;

#define DBG(x) cout << "[" << #x << "]: " << x << endl
#define F(x) std::fixed <<std::setprecision(1)<<(x)
#define f first 
#define s second 
#define pb push_back 
#define mp make_pair

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;

struct entrada {
    int valor;
    int tipo;
    int indice;
    ii insercao;
    iii consulta;
};

const int MAX = 312345;
int n, y, bit[MAX];

void setbit(int i, int delta)
{
    while(i <= y) {
        bit[i] += delta;
        i += (i & -i);
    }
}

int getbit(int i)
{
    int sum = 0;
    while(i > 0) {
        sum += bit[i];
        i -= (i & -i);
    }
    return sum;
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    memset(bit, 0, sizeof(bit));
    int yi, a, p, fi;
    cin >> y >> n;
    vector<entrada> op;
    vector<int> val;
    vector<ii> result;

    for (int i = 1; i <= y; i++) {
        cin >> yi;
        val.pb(yi);
        op.pb({yi, 2, i-1, {i, 1}, {0, {0, 0}}});
    }

    for (int i = 0; i < n; i++) {
        cin >> a >> p >> fi;
        op.pb({p, 1, i, {0, 0}, {a, {p, fi}}});
    }

    sort(op.begin(), op.end(), [](entrada a, entrada b) {
        if (a.valor == b.valor) {
            return a.tipo > b.tipo;
        }
        return a.valor > b.valor;
    });

    for (auto i : op) {
        //cout << "valor: " << i.valor << " tipo: " << i.tipo << endl;

        if (i.tipo == 2) {
            setbit(i.indice+1, 1);
        } else if (i.tipo == 1) {
            a = i.consulta.f;
            p = i.consulta.s.f;
            fi = i.consulta.s.s;

            int ans = getbit(a+fi) - getbit(a);
            //cout << "a + f: " << a + fi << " a: " << a << endl;

            if (val[a-1] >= p) {
                result.pb({i.indice, 0});
            } else {
                result.pb({i.indice, ans});
            }
            //cout << "ans: " << ans << endl;
        }
    }

    sort(result.begin(), result.end());
    for (auto i : result) {
        cout << i.s << endl;
    }

    
    return 0;
}

// g++ -O2 -Wall nome.cpp -o nome
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
typedef pair<ll, ll> ii;
typedef pair<int, ii> iii;

bool ccw(ii a, ii b, ii c) {
    return (b.f - a.f) * (c.s - a.s) - (b.s - a.s) * (c.f - a.f) >= 0;
}

vector<ii> CH_Andrew(vector<ii> &v)
{
    int n = v.size(), k = 0;
    vector<ii> H(2*n);
    sort(v.begin(), v.end());

    for (int i = 0; i < n; ++i)
    {
        while ((k >= 2) && !ccw(H[k-2], H[k-1], v[i])) --k;
        H[k++] = v[i];
    }

    for (int i = n-2, t = k+1; i >= 0; --i) {
        while ((k >= t) && !ccw(H[k-2], H[k-1], v[i])) --k;
        H[k++] = v[i];
    }
    
    H.resize(k);
    return H;
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<ii> pontos;
    map<ii, int> mapa_indices;

    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        pontos.pb(ii(x, y));
        mapa_indices[ii(x, y)] = i + 1;
    }

    vector<ii> fecho_convexo = CH_Andrew(pontos);
    set<int> resposta;
    for (auto ponto : fecho_convexo)
    {
        resposta.insert(mapa_indices[ponto]);
    }

    bool fir = true;
    for (auto valor : resposta)
    {
        cout << (fir == true ? "" : " ") << valor;
        fir = false;
    }
    cout << endl;
    
    return 0;
}

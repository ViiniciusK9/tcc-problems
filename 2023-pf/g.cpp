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


ii toVec(ii a, ii b) { 
    return ii(b.f - a.f, b.s - a.s); 
}

ll cross(ii a, ii b) { 
    return a.f * b.s - a.s * b.f; 
}

// bool ccw(ii p, ii q, ii r) {
//     return cross(toVec(p, q), toVec(p, r)) >= 0;
// }

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
    vector<ii> v;
    map<ii, int> m;

    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        v.pb(ii(x, y));
        m[ii(x, y)] = i + 1;
    }

    vector<ii> hull = CH_Andrew(v);
    set<int> ans;
    for (auto p : hull)
    {
        ans.insert(m[p]);
    }
    bool fir = true;
    for (auto val : ans)
    {
        cout << (fir == true ? "" : " ") << val;
        fir = false;
    }
    cout << endl;
    





    

    
    return 0;
}

// g++ -O2 -Wall nome.cpp -o nome
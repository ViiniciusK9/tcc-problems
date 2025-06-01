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
typedef pair<ll, ll> ii;
typedef pair<int, ii> iii;
const ll INF = 1e9 + 7;

void dijkstra(int n, int x, vector<ii> adj[], vector<ll> &distancia, vector<bool> &processado)
{
    for (int i = 1; i <= n; i++){
        distancia[i] = INF;
    }
    priority_queue<ii> q;
    distancia[x] = 0;
    q.push({0, x});
    while (!q.empty())
    {
        ll a = q.top().second;
        q.pop();
        if (processado[a]) {
            continue;
        }

        processado[a] = true;
        for (auto u : adj[a])
        {
            ll b = u.first, w = u.second;
            if (distancia[a] + w < distancia[b])
            {
                distancia[b] = distancia[a] + w;
                q.push({-distancia[b], b});
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m, p, g, u, v, d;
    cin >> n >> m >> p >> g;

    vector<ii> adj[n + 1];
    vector<ll> dist1(n + 1);
    vector<bool> proc1(n + 1, false);
    vector<ll> dist2(n + 1);
    vector<bool> proc2(n + 1, false);

    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> d;
        adj[u].pb({v, d});
        adj[v].pb({u, d});
    }

    dijkstra(n, p, adj, dist1, proc1);
    proc2[g] = true;
    dijkstra(n, p, adj, dist2, proc2);

    set<int> resposta;
    for (int i = 1; i <= n; i++)
    {
        if (dist1[i] == 2 * dist1[g])
        {
            if (dist2[i] > dist1[i])
            {
                resposta.insert(i);
            }
        }
    }
    
    if (resposta.empty()) {
        cout << "*" << endl;
    } else {
        bool fir = true;
        for (auto valor : resposta)
        {
            cout << (fir ? "" : " ") << valor;
            fir = false;
        }
        cout << endl;
    }

    return 0;
}

// g++ -O2 -Wall nome.cpp -o nome
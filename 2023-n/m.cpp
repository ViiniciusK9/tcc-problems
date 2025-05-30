#include <bits/stdc++.h>

using namespace std;

#define DBG(x) cout << "[" << #x << "]: " << x << endl
#define F(x) std::fixed << std::setprecision(1) << (x)
#define f first
#define s second
#define pb push_back
#define mp make_pair

const int INF = 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;

void dijkstra(int n, int x, vector<ii> adj[], vector<int> &distance, vector<bool> &processed)
{
    for (int i = 1; i <= n; i++){
        distance[i] = INF;
    }
    priority_queue<ii> q;
    distance[x] = 0;
    q.push({0, x});
    while (!q.empty())
    {
        int a = q.top().second;
        q.pop();
        if (processed[a]) {
            continue;
        }

        processed[a] = true;
        for (auto u : adj[a])
        {
            int b = u.first, w = u.second;
            if (distance[a] + w < distance[b])
            {
                distance[b] = distance[a] + w;
                q.push({-distance[b], b});
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
    vector<int> distance(n + 1, INF);
    vector<bool> processed(n + 1, false);
    
    vector<int> distance2(n + 1, INF);
    vector<bool> processed2(n + 1, false);

    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> d;
        adj[u].pb({v, d});
        adj[v].pb({u, d});
    }


    dijkstra(n, p, adj, distance, processed);
    processed2[g] = true;
    dijkstra(n, p, adj, distance2, processed2);

    set<int> resposta;
    for (int i = 1; i <= n; i++)
    {
        if (distance[i] == 2 * distance[g])
        {
            if (distance2[i] > distance[i])
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
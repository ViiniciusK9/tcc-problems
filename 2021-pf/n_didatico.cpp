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

const int INSERCAO = 1;
const int CONSULTA = 2;
const int MAX = 312345;

struct consulta {
    int ultimo_ano;
    int colocacao;
    int anos_acompanhados;
    int indice;
    int resposta;
};

struct insercao {
    int quantidade_vagas;
    int ano;
};

struct operacao {
    int valor_ordenacao;
    int tipo_operacao;
    struct consulta consulta;
    struct insercao insercao;
};

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

bool ordenacao_operacao(operacao a, operacao b)
{
    if (a.valor_ordenacao == b.valor_ordenacao) {
        return a.tipo_operacao < b.tipo_operacao;
    }
    return a.valor_ordenacao > b.valor_ordenacao;
}

bool ordenacao_resposta(consulta a, consulta b)
{
    return a.indice < b.indice;
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    memset(bit, 0, sizeof(bit));
    
    int quantidade_vagas, ultimo_ano, colocacao, anos_acompanhados;
    vector<consulta> resultados;
    vector<operacao> operacoes;
    vector<int> vagas;

    cin >> y >> n;
    
    for (int ano = 1; ano <= y; ano++) 
    {
        cin >> quantidade_vagas;
        vagas.push_back(quantidade_vagas);

        operacao op;
        insercao ins;
        
        ins.quantidade_vagas = quantidade_vagas;
        ins.ano = ano;
        
        op.valor_ordenacao = quantidade_vagas;
        op.tipo_operacao = INSERCAO;
        op.insercao = ins;
        
        operacoes.push_back(op);
    }

    for (int indice = 0; indice < n; indice++) 
    {
        cin >> ultimo_ano >> colocacao >> anos_acompanhados;

        operacao op;
        consulta con;

        con.ultimo_ano = ultimo_ano;
        con.colocacao = colocacao;
        con.anos_acompanhados = anos_acompanhados;
        con.indice = indice;
        
        op.valor_ordenacao = colocacao;
        op.tipo_operacao = CONSULTA;
        op.consulta = con;
        
        operacoes.push_back(op);
    }

    sort(operacoes.begin(), operacoes.end(), ordenacao_operacao);

    for (auto operacao : operacoes) 
    {
        if (operacao.tipo_operacao == INSERCAO) 
        {
            setbit(operacao.insercao.ano, 1);
        } 
        else if (operacao.tipo_operacao == CONSULTA) 
        {
            consulta con = operacao.consulta;

            if (con.colocacao <= vagas[con.ultimo_ano-1]) 
            {
                con.resposta = 0;
                resultados.push_back(con);
            } 
            else 
            {
                int resposta = getbit(con.ultimo_ano + con.anos_acompanhados) - getbit(con.ultimo_ano);
                con.resposta = resposta;
                resultados.push_back(con);
            }
        }
    }

    sort(resultados.begin(), resultados.end(), ordenacao_resposta);
    for (auto consulta : resultados) {
        cout << consulta.resposta << endl;
    }
    
    return 0;
}

// g++ -O2 -Wall nome.cpp -o nome
#include <iostream>
#include <math.h>
using namespace std;

class Knap
{
    friend void Knapsack(int*, int*, int, int);
private:
    int Bound(int i);
    void Backtrack(int i);
    int c;
    int n;
    int *w;
    int *p;
    int cw;
    int cp;
    int bestp;
    int *ID;
    int *x;
    int *bestx;
};

void Knap::Backtrack(int i)
{
    if(i>n)
    {
        bestp = cp;
        for(int i=1;i<=n;i++)
        {
            bestx[ID[i]] = x[i];
        }
        return;
    }
    if(cw+w[i] <= c)
    {
        cw += w[i];
        cp += p[i];
        x[i] = 1;
        Backtrack(i+1);
        cw -= w[i];
        cp -= p[i];
    }
    if(Bound(i+1) > bestp)
    {
        x[i]=0;
        Backtrack(i+1);
    }
}

int Knap::Bound(int i)
{
    int cleft = c-cw;
    int b = cp;
    while(i <= n&& w[i]<=cleft)
    {
        cleft -= w[i];
        b += p[i];
        i++;
    }
    if(i<n)
        b+=p[i]*cleft/w[i];
    return b;
}

class Object
{
    friend void Knapsack(int*, int*, int, int);
public:
    bool operator<(Object a) const{return (d<a.d);}
private:
    int ID;
    float d;
};

void Sort(Object Q[], int n)
{
    Object temp;
    int flag=0;
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(Q[j]<Q[j+1])
            {
                temp = Q[j];
                Q[j] = Q[j+1];
                Q[j+1] = temp;
                flag=1;
            }
        }
        if(flag==0)
            return;
        flag=0;
    }
}

void Knapsack(int p[], int w[], int c, int n)
{
    int W =0;
    int P=0;
    Object *Q = new Object[n];
    for(int i=1;i<=n;i++)
    {
        Q[i-1].ID = i;
        Q[i-1].d = 1.0*p[i]/w[i];
        P+=p[i];
        W+=w[i];
    }
    if(W<=c)
    {
        cout << P << endl;
        for(int i=1;i<=n;i++)
        {
            cout << i << " " << 1 << endl;
        }
    }
    Sort(Q,n);
    /*for(int i=1;i<=n;i++)
    {
        cout << Q[i-1].ID << Q[i-1].d <<endl;
    }*/
    Knap k;
    k.p = new int[n+1];
    k.w = new int[n+1];
    k.ID = new int[n+1];
    k.x = new int[n+1];
    k.bestx = new int[n+1];
    for(int i=1;i<=n;i++)
    {
        k.p[i] = p[Q[i-1].ID];
        k.w[i] = w[Q[i-1].ID];
        k.ID[i] = Q[i-1].ID;
    }
    /*for(int i=1;i<=n;i++)
    {
        cout << k.p[i] << k.w[i] <<endl;
    }*/
    k.cp=0;
    k.cw=0;
    k.c=c;
    k.n=n;
    k.bestp=0;
    k.Backtrack(1);
    delete[] Q;
    delete[] k.w;
    delete[] k.p;
    delete[] k.x;
    cout << k.bestp << endl;
    for(int i=1;i<=n;i++)
    {
        cout << i << " " << k.bestx[i] << endl;
    }
    delete[] k.bestx;
}

int main()
{
    int n,c;
    cin >>c >>n;
    int *w = new int[n+1];
    int *p = new int[n+1];
    for(int i=1;i<=n;i++)
    {
        cin >> w[i] >> p[i];
    }
    Knapsack(p,w,c,n);
    return 0;
}

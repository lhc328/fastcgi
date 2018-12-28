#include <iostream>
#include <math.h>
using namespace std;

void knapsack(int v[], int w[], int c, int n, int** m)
{
    int jMax = min(w[n]-1, c);
    for(int j=0;j<jMax;j++)
    {
        m[n][j]=0;
    }
    for(int j=w[n];j<=c;j++)
    {
        m[n][j]=v[n];
    }
    for(int i=n-1;i>1;i--)
    {
        jMax = min(w[i]-1,c);
        for(int j=0;j<=jMax;j++)
            m[i][j] = m[i+1][j];
        for(int j=w[i];j<=c;j++)
            m[i][j] = max(m[i+1][j-w[i]]+v[i],m[i+1][j]);   //¹Ø¼üµã
    }
    m[1][c]=m[2][c];
    if(c>=w[1])
        m[1][c] = max(m[1][c], m[2][c-w[1]]+v[1]);
}

int main()
{
    int c,n;
    cin >> n >> c;
    int **m = new int*[n+1];
    int *w = new int[n+1];
    int *v = new int[n+1];
    for(int i=1;i<=n;i++)
    {
        cin >> w[i] >> v[i];
        m[i] = new int[c+1];
    }
    knapsack(v,w,c,n,m);
    cout << m[1][c] << endl;;
    for(int i=1;i<n;i++)
    {
        cout << i <<" ";
        if(m[i][c] == m[i+1][c])
            cout << 0 <<endl;
        else
        {
            cout << 1 << endl;
            c -= w[i];
        }
    }
    int a = (m[n][c]?1:0);
    cout << n<< " " << a << endl;
    return 0;
}

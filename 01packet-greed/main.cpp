#include <iostream>
#include <sys/time.h>
#include <stdio.h>
using namespace std;

int partion(int value[],int low,int high,int n);
void paixu(int n,int value[],int high,int low);

int n,c;
int w[5001],p[5001];
int x[5001]={0};//x向量初始化为0
int v[5001];//每个物品对应的单位价值
int num[5001];//用于存序号
int value=0;//存放最终结果的总价值
int main()
{

        cin>>c>>n;  //n个物品，背包容量为c
        for(int i=1;i<=n;i++)
        {
            num[i] = i;//序号的初始化，用于之后的排序
        }
        for(int i=1;i<=n;i++)
        {
            cin>>w[i];//每个物品的重量
            cin>>p[i];//对应的价值
        }
        for(int i=1;i<=n;i++)
        {
            v[i] = (int)(p[i]/w[i]);//每个物品对应的单位价值
        }
        struct timeval start, finish;
        long duration;
        gettimeofday(&start, NULL);
        paixu(n,v,n,1);//按单位价值从低到高排序,即把原始序号的存入num数组

//        for(int i=1;i<=n;i++)//测试排序算法的正确性
//        {
//            cout<<num[i]<<" ";
//        }

        for(int i=n;i>=1;i--)//贪心算法部分就这么一丢丢
        {
            if(w[num[i]]<=c)//可以选进背包
            {
                c = c - w[num[i]];//背包余量
                value = value + p[num[i]];//目前背包的价值
                x[num[i]]=1;//将选进背包的物品置1
            }
        }
        gettimeofday(&finish, NULL);
        cout<<value<<endl;
        int number = 1;
         for(int i=1;i<=n;i++)//输出对应的x向量
        {
            cout<<number++<<" : ";
            cout<<x[i]<<endl;
        }
        duration = (finish.tv_sec - start.tv_sec)*1000000;
        duration += finish.tv_usec;
        duration -= start.tv_usec;
        printf("%d us\n",duration);
        return 0;
}

int partion(int value[],int low,int high,int n)//快排
{
    value[0]=value[low];
    num[0] = num[low];
    while(low<high)
    {
        while(low<high&&value[high]>=value[0])
        high--;

        value[low]=value[high];
        num[low] = num[high];

        while(low<high&&value[low]<=value[0])
        low++;

        value[high]=value[low];
        num[high] = num[low];
    }
    value[low]=value[0];
    num[low] = num[0];
//    int i;
//    for(i=1;i<=n;i++)
//    {
//        printf("%d ",weight[i]);
//    }
//    cout<<endl;
    return low;
}

void paixu(int n,int v[],int high,int low)//n是物品数
{
    int p;
    if(low<high)
    {
        p=partion(v,low,high,n);
        paixu(n,v,p-1,low);
        paixu(n,v,high,p+1);
    }
}


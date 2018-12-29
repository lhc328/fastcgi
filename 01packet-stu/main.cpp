#include <iostream>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
using namespace std;

void help(int n);
void result();
int partion(int value[],int low,int high,int n);
void paixu(int n,int value[],int high,int low);

int num;
int value[10000] = {0};
int weight[10000] = {0};
int x[10000][5001];
int tmp=0;//用来在fun中代表物品总数n
int n,c;
int w[5001],p[5001],s[5001];
int main()
{
        cin>>c>>n;  //n个物品，背包容量为c
        tmp = n;

        for(int i=1;i<=n;i++)
        {
            cin>>w[i];//每个物品的重量
            cin>>p[i];//对应的价值
        }
        num = 1;//可行组的数目
        struct timeval start, finish;
        long duration;
        gettimeofday(&start, NULL);
        help(n);//帮助函数，生成可行组提供给max()
        //result();//利用help的可行组生成最终结果


    paixu(n,value,num,1);
    gettimeofday(&finish,NULL);
    cout<<value[num-1]<<endl;//输出最大价值
    int number = 1;
    for(int i=1;i<=n;i++)//输出对应的x向量
    {
        cout<<number++<<" : ";
        cout<<x[num-1][i]<<endl;
    }
    duration = (finish.tv_sec - start.tv_sec)*1000000;
    duration += finish.tv_usec - start.tv_usec;
    printf("%d us\n",duration);
}


void help(int n)//帮助函数，生成可行组提供给max()
{
    if(n==0)//递归出口，会被进入2的n次方次
    {
        for(int i=1;i<=tmp;i++)//循环物品总数n次
        {
            weight[num] = weight[num] + w[i]*s[i];
            value[num] = value[num] + p[i]*s[i];
            x[num][i] = s[i];
        }

        if(weight[num]<=c)//如果这种情况是合理的，则加入到可行组中来，用于之后的计算。
        {
            num = num+1;
        }
        else//这种情况是不合理的，把它占的位置清空，用于存放下一种情况
        {
            weight[num] = 0;
            value[num] = 0;
        }
    }
    else
    {
        for(int i=0;i<2;i++)
        {
            s[n] = i;//i=0不取物品n,i=1取物品n
            help(n-1);//两种情况分别进入下层递归
        }
    }
}

void result()//利用help的可行组生成最终结果
{

}
int partion(int value[],int low,int high,int n)//快排
{
    value[0]=value[low];
    *x[0] = *x[low];
    while(low<high)
    {
        while(low<high&&value[high]>=value[0])
        high--;

        value[low]=value[high];
        *x[low] = *x[high];


        while(low<high&&value[low]<=value[0])
        low++;

        value[high]=value[low];
        *x[high] = *x[low];
    }
    value[low]=value[0];
    *x[low] = *x[0];
//    int i;
//    for(i=1;i<=n;i++)
//    {
//        printf("%d ",weight[i]);
//    }
//    cout<<endl;
    return low;
}


void paixu(int n,int value[],int high,int low)
{
    int p;
    if(low<high)
    {
        p=partion(value,low,high,n);
        paixu(n,value,p-1,low);
        paixu(n,value,high,p+1);
    }
}

#include <stdio.h>
#include <stdlib.h>
#define maxv 10//定义最大顶点数
typedef char elem;//图中顶点的数据类型
#include "graph.h"
void main()
{
    elem v0;
    int v;
    mgraph g;
    printf("1.初始化函数测试:\n");
    initial(g);
    printf("2.创建函数测试:\n");
    create(g);
    printf("3.输出函数测试:\n");
    printg(g);
    printf("4.求最短路径:\n");
    printf("请输出源顶点数据v0:");
    scanf("%c",&v0);
    v=locate(g,v0);
    dijkstra(g,v);
    printf("5.输出最短路径:\n");
    printpath(g,v);
    printf("\n");
}

//有向带权网的邻接矩阵,顶点数据为字符型
#define inf 32767
typedef struct MGraph
{
    elem vexes[maxv];//顶点表
    int edges[maxv][maxv];//邻接矩阵
    int n,e;//顶点数n和边数e
}mgraph;
void initial(mgraph &g)//初始化函数
{
    int i,j;
    g.e=0;
    g.n=0;
    for(j=0;j<maxv;j++)//建立顶点表
        g.vexes[j]=0;
    for(i=0;i<maxv;i++)
    {
        for(j=0;j<maxv;j++)
        {
            g.edges[i][j]=inf;//初始化邻接矩阵
        }
    }
}
int locate(mgraph g,elem u)//查找顶点对应的数组下标值
{
    for(int i=0;i<g.n;i++)
    {
        if(g.vexes[i]==u)
            return i;
    }
    return -1;
}
void create(mgraph &g)//创建有向带权网的邻接矩阵存储
{
    int i,j,k,w;
    elem u,v;
    printf("请输入有向图的顶点数:");
    scanf("%d",&g.n);
    printf("请输入有向图的弧数:");
    scanf("%d",&g.e);
    fflush(stdin);//清空缓存中的数据
    printf("请输入字符型顶点数据,如ABCD:");
    for(j=0;j<g.n;j++)
        scanf("%c",&g.vexes[j]);//建立顶点表
    fflush(stdin);
    printf("请输入弧的信息,格式:弧尾,弧头,权值\n");
    for(k=0;k<g.e;k++)
    {
        scanf("%c,%c,%d",&u,&v,&w);
        i=locate(g,u);
        j=locate(g,v);
        g.edges[i][j]=w;
        fflush(stdin);
    }
}
void printg(mgraph g)//输出有向带权网的邻接矩阵
{
    int i,j;
    printf("输入图的邻接矩阵存储信息:\n");
    printf("顶点数据:\n");
    for(i=0;i<g.n;i++)
        printf("%d: %c\n",i,g.vexes[i]);
    printf("邻接矩阵数据:\n");
    for(i=0;i<g.n;i++)
    {
        for(j=0;j<g.n;j++)
        {
            if(g.edges[i][j]==inf)
                printf(" ∞");
            else
                printf("%3d",g.edges[i][j]);
        }
        printf("\n");
    }
}
int dist[maxv];//dist存当前找到的最短路径长度
int path[maxv];//当前找到的最短路径最后的一个中转顶点
bool s[maxv];//标记当前是否已求出最短路径,false表示没求出,true表示已求出
void dijkstra(mgraph g,int v)//迪杰斯特拉算法从顶点v到其余各顶点的最短路径
{
    int mindis,i,j,u;
    for(i=0;i<g.n;i++)
    {
        dist[i]=g.edges[v][i];//当前最短路径长度初始化
        s[i]=false;//s[]标记还没求出当前路径
        if(g.edges[v][i]<inf)//初始化当前找到的最短路径最后一个中转顶点
            path[i]=v;
        else
            path[i]=-1;
    }
    s[v]=true;//源点编号v标记已求出最短路径
    path[v]=0;//源点v没有前驱顶点
    for(i=0;i<g.n;i++)//循环直到所有顶点的最短路径都求出或没有最短路径
    {
        mindis=inf;
        u=-1;//存当前找到的路径最短的新顶点下标
        for(j=0;j<g.n;j++)//选取不在s中且具有最小距离的顶点u
        {
            if((s[j]==false)&&(dist[j]<mindis))
            {
                u=j;
                mindis=dist[j];
            }
        }
        if(mindis<inf)//如果找到了新的最短路径
        {
            s[u]=true;//新选出顶点u标记为找到了最短路径
            for(j=0;j<g.n;j++)//修改未找到最短路径顶点信息
            {
                if(s[j]==false)
                {
                    if(g.edges[u][j]<inf&&dist[u]+g.edges[u][j]<dist[j])
                    {
                        dist[j]=dist[u]+g.edges[u][j];//修改当前最短路径长度
                        path[j]=u;//修改当前最短路径最后一个中转点
                    }
                }
            }
        }
    }
}
void printpath(mgraph g,int v)//输出最短路径和最短路径长度
{
    int i,j,w;
    int road[maxv];//为输出最短路径做临时存储
    printf("%c到其他各顶点有没有找到最短路径:\n",g.vexes[v]);
    for(i=0;i<g.n;i++)
    {
        if(s[i])
            printf("%d:有  ",i);
        else
            printf("%d:无  ",i);
    }
    printf("\n");
    for(i=0;i<maxv;i++)
        road[i]=-1;
    for(i=0;i<g.n;i++)
    {
        if((s[i]==true)&&(i!=v))//当前顶点有最短路径,并且不是源点
        {
            printf("从%c到%c的最短路径长度为:%d\t路径为:",g.vexes[v],g.vexes[i],dist[i]);
            printf("%c->",g.vexes[v]);
            w=path[i];//最短路径途径的顶点
            j=0;//为实现逆转标记途径顶点数
            while(w!=v)//回溯途径顶点
            {
                road[j]=w;
                j++;
                w=path[w];
            }
            for(j--;j>=0;j--)//输出最短路径
            {
                printf("%c->",g.vexes[road[j]]);
                road[j]=-1;
            }
            printf("%c\n",g.vexes[i]);
        }
        else
            printf("从%c到%c不存在路径\n",g.vexes[v],g.vexes[i]);
    }
}
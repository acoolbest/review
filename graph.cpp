#include <stdio.h>
#include <stdlib.h>
#define maxv 10//������󶥵���
typedef char elem;//ͼ�ж������������
#include "graph.h"
void main()
{
    elem v0;
    int v;
    mgraph g;
    printf("1.��ʼ����������:\n");
    initial(g);
    printf("2.������������:\n");
    create(g);
    printf("3.�����������:\n");
    printg(g);
    printf("4.�����·��:\n");
    printf("�����Դ��������v0:");
    scanf("%c",&v0);
    v=locate(g,v0);
    dijkstra(g,v);
    printf("5.������·��:\n");
    printpath(g,v);
    printf("\n");
}

//�����Ȩ�����ڽӾ���,��������Ϊ�ַ���
#define inf 32767
typedef struct MGraph
{
    elem vexes[maxv];//�����
    int edges[maxv][maxv];//�ڽӾ���
    int n,e;//������n�ͱ���e
}mgraph;
void initial(mgraph &g)//��ʼ������
{
    int i,j;
    g.e=0;
    g.n=0;
    for(j=0;j<maxv;j++)//���������
        g.vexes[j]=0;
    for(i=0;i<maxv;i++)
    {
        for(j=0;j<maxv;j++)
        {
            g.edges[i][j]=inf;//��ʼ���ڽӾ���
        }
    }
}
int locate(mgraph g,elem u)//���Ҷ����Ӧ�������±�ֵ
{
    for(int i=0;i<g.n;i++)
    {
        if(g.vexes[i]==u)
            return i;
    }
    return -1;
}
void create(mgraph &g)//���������Ȩ�����ڽӾ���洢
{
    int i,j,k,w;
    elem u,v;
    printf("����������ͼ�Ķ�����:");
    scanf("%d",&g.n);
    printf("����������ͼ�Ļ���:");
    scanf("%d",&g.e);
    fflush(stdin);//��ջ����е�����
    printf("�������ַ��Ͷ�������,��ABCD:");
    for(j=0;j<g.n;j++)
        scanf("%c",&g.vexes[j]);//���������
    fflush(stdin);
    printf("�����뻡����Ϣ,��ʽ:��β,��ͷ,Ȩֵ\n");
    for(k=0;k<g.e;k++)
    {
        scanf("%c,%c,%d",&u,&v,&w);
        i=locate(g,u);
        j=locate(g,v);
        g.edges[i][j]=w;
        fflush(stdin);
    }
}
void printg(mgraph g)//��������Ȩ�����ڽӾ���
{
    int i,j;
    printf("����ͼ���ڽӾ���洢��Ϣ:\n");
    printf("��������:\n");
    for(i=0;i<g.n;i++)
        printf("%d: %c\n",i,g.vexes[i]);
    printf("�ڽӾ�������:\n");
    for(i=0;i<g.n;i++)
    {
        for(j=0;j<g.n;j++)
        {
            if(g.edges[i][j]==inf)
                printf(" ��");
            else
                printf("%3d",g.edges[i][j]);
        }
        printf("\n");
    }
}
int dist[maxv];//dist�浱ǰ�ҵ������·������
int path[maxv];//��ǰ�ҵ������·������һ����ת����
bool s[maxv];//��ǵ�ǰ�Ƿ���������·��,false��ʾû���,true��ʾ�����
void dijkstra(mgraph g,int v)//�Ͻ�˹�����㷨�Ӷ���v���������������·��
{
    int mindis,i,j,u;
    for(i=0;i<g.n;i++)
    {
        dist[i]=g.edges[v][i];//��ǰ���·�����ȳ�ʼ��
        s[i]=false;//s[]��ǻ�û�����ǰ·��
        if(g.edges[v][i]<inf)//��ʼ����ǰ�ҵ������·�����һ����ת����
            path[i]=v;
        else
            path[i]=-1;
    }
    s[v]=true;//Դ����v�����������·��
    path[v]=0;//Դ��vû��ǰ������
    for(i=0;i<g.n;i++)//ѭ��ֱ�����ж�������·���������û�����·��
    {
        mindis=inf;
        u=-1;//�浱ǰ�ҵ���·����̵��¶����±�
        for(j=0;j<g.n;j++)//ѡȡ����s���Ҿ�����С����Ķ���u
        {
            if((s[j]==false)&&(dist[j]<mindis))
            {
                u=j;
                mindis=dist[j];
            }
        }
        if(mindis<inf)//����ҵ����µ����·��
        {
            s[u]=true;//��ѡ������u���Ϊ�ҵ������·��
            for(j=0;j<g.n;j++)//�޸�δ�ҵ����·��������Ϣ
            {
                if(s[j]==false)
                {
                    if(g.edges[u][j]<inf&&dist[u]+g.edges[u][j]<dist[j])
                    {
                        dist[j]=dist[u]+g.edges[u][j];//�޸ĵ�ǰ���·������
                        path[j]=u;//�޸ĵ�ǰ���·�����һ����ת��
                    }
                }
            }
        }
    }
}
void printpath(mgraph g,int v)//������·�������·������
{
    int i,j,w;
    int road[maxv];//Ϊ������·������ʱ�洢
    printf("%c��������������û���ҵ����·��:\n",g.vexes[v]);
    for(i=0;i<g.n;i++)
    {
        if(s[i])
            printf("%d:��  ",i);
        else
            printf("%d:��  ",i);
    }
    printf("\n");
    for(i=0;i<maxv;i++)
        road[i]=-1;
    for(i=0;i<g.n;i++)
    {
        if((s[i]==true)&&(i!=v))//��ǰ���������·��,���Ҳ���Դ��
        {
            printf("��%c��%c�����·������Ϊ:%d\t·��Ϊ:",g.vexes[v],g.vexes[i],dist[i]);
            printf("%c->",g.vexes[v]);
            w=path[i];//���·��;���Ķ���
            j=0;//Ϊʵ����ת���;��������
            while(w!=v)//����;������
            {
                road[j]=w;
                j++;
                w=path[w];
            }
            for(j--;j>=0;j--)//������·��
            {
                printf("%c->",g.vexes[road[j]]);
                road[j]=-1;
            }
            printf("%c\n",g.vexes[i]);
        }
        else
            printf("��%c��%c������·��\n",g.vexes[v],g.vexes[i]);
    }
}
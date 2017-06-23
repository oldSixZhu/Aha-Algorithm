//
//  SuanFa2.c
//  Aha-Algorithm
//
//  Created by Mac on 2017/6/22.
//  Copyright © 2017年 oldSix. All rights reserved.
//

#include <stdio.h>
//图的最小生成树 任意两点之间都有一条线路可以相通

//克鲁斯卡尔算法
//按照边的权值进行从小到大排序,选择权值较小的,两个顶点不在同一集合内的边(即不会产生回路的边),加入到树中,直到加入了n-1条边为止
//时间复杂度为O(nlogn)
//用一个结构体存储边的关系
struct edge {
    int u;
    int v;
    int w;
};
struct edge e[10];
int n=7,m=7;
int f[7]={0},sum=0,count=0;
//快速排序
void realKuaiSu(int left,int right){
    int i,j;
    struct edge t;
    if (left > right)
    {
        return;
    }
    i = left;
    j = right;
    while (i != j)
    {
        //先从右边开始找
        while (e[j].w >= e[left].w && i<j)
        {
            j--;
        }
        //从左边开始找
        while (e[i].w >= e[left].w && i<j) {
            i++;
        }
        if (i<j)
        {
            t = e[i];
            e[i] = e[j];
            e[j] = t;
        }
    }
    //将基准数归位,将left和i互换
    t = e[left];
    e[left] = e[i];
    e[i] = t;
    //继续处理左边的
    realKuaiSu(left, i-1);
    //继续处理右边的
    realKuaiSu(i+1, right);
    return;
}
//并查集寻找祖先的函数
//擒贼先擒王原则  递归函数,不停地找根树
int get(int v){
    if (f[v] == v)
    {
        return v;
    }
    else
    {
        //路径压缩  每次在函数返回的时候,把路上遇到的树的根改为最后找到的根树,可以提高其他树找到根树的速度
        f[v] = get(f[v]);
        return f[v];
    }
}
//合并两子集合的函数
int merge(int v,int u){
    int t1,t2;
    t1 = get(v);
    t2 = get(u);
    //判断两个结点是否在同一个集合中,即是否为同一个祖先
    if (t1 != t2)
    {
        //靠左原则,左边变成右边的根数,把右边集合作为左边集合的子集合
        f[t2] = t1;
    }
    return 0;
}
//克鲁斯卡尔算法
void Kruskal(){
    int i;
    //读入顶点与边数
    scanf("%d,%d",&n,&m);
    for (i = 1; i<=m; i++)
    {
        scanf("%d %d %d",&e[i].u,&e[i].v,&e[i].w);
    }
    //按照权值对边进行快速排序
    realKuaiSu(1, m);
    //并查集初始化
    for (i=1; i<=n; i++)
    {
        f[i] = i;
    }
    //克鲁斯卡尔核心部分
    //先枚举每一条边
    for (i=1; i<=m; i++)
    {
        //判断一条边的两个顶点是否已经连通,即判断是否已在同一个集合中
        if (merge(e[i].u, e[i].v))
        {
            count++;
            sum = sum + e[i].w;
        }
        //选用了n-1条边之后退出循环
        if (count == n-1)
        {
            break;
        }
    }
    //sum
}



//普里姆算法
//从点开始,在没有线连接的点之间寻找最短的线
//时间复杂度是O(n²)
void Prim(){
    //边
    int e[7][7] = {0};
    //用book来标记一个顶点是否已经加入生成树
    int book[7]={0},min=0,i=0,j=0,k=0;
    //初始化dis数组,顶点到各个顶点的距离的数组
    int dis[7] = {1,2,3,4,5,6,7};
    book[1] = 1;
    count++;
    while (count < n)
    {
        min = 999999;
        for (i = 1; i <= n; i++)
        {
            if (book[i]==0 && dis[i]<min)
            {
                min = dis[i];
                j = i;
            }
        }
        book[j] = 1;
        count++;
        sum = sum + dis[j];
        //扫描当前顶点j所有的边,以j为中间点,更新生成树到每一个非树顶点的距离
        for (k=1; k<=n; k++)
        {
            if (book[k]==0 && dis[k]>e[j][k])
            {
                dis[k] = e[j][k];
            }
        }
    }
    //sum
}

//使用堆来优化
//book数组用来记录哪些顶点已经放入生成树中
int dis[7],book[7]={0};
//h用来保存堆,pos用来存储每个顶点在堆中的位置,size为堆的大小
int h[7],pos[7],size;
//交换函数,用来交换堆中的两个元素的值
void swap(int x,int y){
    int t = h[x];
    h[x] = h[y];
    h[y] = t;
    //更新到pos
    t = pos[h[x]];
    pos[h[x]] = pos[h[y]];
    pos[h[y]] = t;
}
//堆 向下调整函数
void down(int i){
    //flag用来标记是否需要继续向下调整
    int t,flag=0;
    while (i*2<=size && flag==0)
    {
        //比较i和它左儿子i*2在dis中的值,并用t记录值较小的结点编号
        if (dis[h[i]] > dis[h[i*2]])
        {
            t = i * 2;
        }
        else
        {
            t = i;
        }
        //如果它有右儿子,再对右儿子进行讨论
        if (i*2+1 <= size)
        {
            //如果右儿子的值更小,更新较小的结点编号
            if (dis[h[t]] > dis[h[i*2+1]])
            {
                t = i*2+1;
            }
        }
        //如果发现最小的结点编号不是自己,说明子结点中又比父结点更小的
        if (t != i)
        {
            swap(t, i);
            //更新i为刚才与它交换的儿子结点的编号,便于接下来继续向下调整
            i = t;
        }
        else
        {
            //否则说明当前的父结点已经比两个子结点都要小,不需要再进行调整
            flag = 1;
        }
    }
}

//传入一个需要向上调整的结点编号i
void up(int i){
    //用来标记是否需要继续向上调整
    int flag=0;
    if (i==1)
    {
        return;
    }
    //不在堆顶,并且当前结点i的值比父结点小的时候继续向上调整
    while (i!=1 && flag==0)
    {
        //判断是否比父结点小
        if (dis[h[i]] < dis[h[i/2]])
        {
            //交换它和它父结点的位置
            swap(i, i/2);
        }
        else
        {
            //表示已经不需要调整了,当前结点的值比父结点的值要大
            flag = 1;
        }
        //更新编号i为它父结点的编号,便于下一次继续向上调整
        i = i/2;
    }
}

//从堆顶取一个元素
int pop(){
    int t = h[1];
    //将堆的最后一个点赋值到堆顶
    h[1] = h[size];
    pos[h[1]] = 1;
    //堆的元素减少1
    size--;
    //向下调整
    down(1);
    //返回堆顶点
    return t;
}
//普里姆算法
void PrimDui(){
    int n=7,m=7,i,j,k;
    //uvw要比2m的最大值大1,因为此图是无向图
    //first要比n的最大值大1,比2*m的最大值大1
    int u[19],v[19],w[19],first[7],next[19];
    //count记录生成树中顶点的个数,sum用来存储路径之和
    int count=0,sum=0;
    //用邻接表存储边
    for (i = 1; i <= n; i++)
    {
        first[i] = -1;
    }
    for (i = 1; i <= 2*m; i++)
    {
        next[i] = first[u[i]];
        first[u[i]] = i;
    }
    
    //Prim核心部分开始
    //将1号顶点加入生成树
    //用book来标记一个顶点已经加入生成树
    book[1] = 1;
    count++;
    //初始化dis数组,这里是1号顶点到其余各个顶点的初始距离
    dis[1] = 0;
    for (i = 2; i <= n; i++)
    {
        dis[i] = 999999;
    }
    k = first[1];
    while (k!=-1)
    {
        dis[v[k]] = w[k];
        k = next[k];
    }
    //初始化堆
    size = n;
    for (i = 1; i <= size; i++)
    {
        h[i] = i;
        pos[i] = i;
    }
    for (i=size/2; i>=1; i--)
    {
        down(i);
    }
    //先弹出一个堆顶元素,即1号顶点
    pop();
    while (count < n)
    {
        j = pop();
        book[j] = 1;
        count++;
        sum = sum+dis[j];
        //扫描当前顶点j所有的边,再以j为中间结点,进行松弛
        k = first[j];
        while (k != -1)
        {
            if (book[v[k]] == 0 && dis[v[k]] > w[k])
            {
                //更新距离
                dis[v[k]] = w[k];
                //对该点在堆中进行向上调整
                //存储的是顶点v[k]在堆中的位置
                up(pos[v[k]]);
            }
            k = next[k];
        }
    }
    //sum
}


































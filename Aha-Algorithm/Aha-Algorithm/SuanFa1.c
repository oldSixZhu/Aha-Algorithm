//
//  SuanFa1.c
//  Aha-Algorithm
//
//  Created by Mac on 2017/6/20.
//  Copyright © 2017年 oldSix. All rights reserved.
//

#include <stdio.h>

//队列
//一种特殊的线性结构,只允许在队列首部进行删除操作(出列),在队列尾部进行插入操作(入列),先进先出(FIFO)
struct queue {
    int data[100];//数据
    int head;     //队首
    int tail;     //队尾
};

//栈
//只能在一端进行插入和删除操作,后进后出
struct stack {
    int data[10];
    int top;
};

//链表
//在 C 语言中*号有三个用途，分别是:
//1. 乘号，用做乘法运算，例如 5*6。
//2. 申明一个指针，在定义指针变量时使用，例如 int *p;。
//3. 间接运算符，取得指针所指向的内存中的值，例如 printf("%d",*p);。
//->叫做结构体指针运算符，用来访问结构体内部成员的
struct node {
    int data;
    struct node *next;
};

void lian(){
    struct node *p;
    //动态申请一个空间，用来存放一个结点，并用临时指针p指向这个结点
    p = (struct node *)malloc(sizeof(struct node));
}

//模拟链表
//两个数组,第一个数组存储数据,第二个数组存放每个元素右边的元素在第一个数组中位置的

//枚举
//又叫穷举算法,有序地尝试每一种可能
//奥数题
//炸弹人

//火柴棍等式     m根(m<=24)火柴棍,可以拼出多少个不同形状如A+B=C的等式
//枚举A,B,C,范围都是0~11111(20根火柴棍),A+B+C=m-4

//数的全排列     输入一个指定点的数n,输出1~n的全排列

//深度优先搜索
//关键在于当下该如何做
void DFS(int step){
    int i,n = 0;
    //判断边界
    //尝试每一种可能
    for (i = 1; i <= n; i++)
    {
        //继续下一步
        DFS(step +1);
    }

}
//图的遍历:以一个未被访问过的顶点作为起始顶点,沿当前顶点的边走到未访问过的顶点,当没有未访问过的顶点时,回到上一个顶点,继续访问别的顶点...一条路走到黑,然后回头
//城市地图

//广度优先搜索
//图的遍历:以一个未被访问过的顶点作为起始顶点,访问其所有相邻的顶点,然后对每个相邻的顶点再访问相邻的顶点...
//最小转机
//适用于所有边的权值相同的情况

//最短路径  有些城市之间有公路,有些城市之间没有,求两个城市之间的最短路径
//弗洛伊德算法
//时间复杂度为O(n³),不能解决带有负权环,负权回路的图
//用二维数组存储所有点之间关系,刚开始只允许经过1顶点进行中转,慢慢增加允许中转的点数量
void Floyd(){
    int n = 100,e[10][10];
    for (int k=1; k<=n; k++){
        for (int i=1; i<=n; i++){
            for (int j=1; j<=n; j++) {
                if (e[i][j] > e[i][k]+e[k][j]) {
                    e[i][j] = e[i][k]+e[k][j];
                }
            }
        }
    }
}

//单源最短路径:指定一个点到其余各个顶点的最短路径
//迪杰斯特拉算法
//时间复杂度为O(n²)
//用一个二维数组存储所有点之间关系,用一个一维数组存储一个点到其他点的初始路程,称为估计值,找到最小的,称为确定值
//每次找到离源点最近的一个顶点,通过比较各路径与估计值大小,更新估计值(松弛),直到都成为确定值,即最短路线
void Dijkstra(){
    //n为顶点数,e为关系数组,book为已知最短路径顶点,dis为初始路程
    int n = 100,e[10][10],book[10],dis[10],u=0,v=0;
    for (int i=1; i<=n-1; i++)
    {
        //找到离1号顶点最近的顶点
        int min = 9999999;
        for (int j=1; j<=n; j++)
        {
            if (book[j]==0 && dis[j]<min)
            {
                min = dis[j];
                u = j;
            }
        }
        book[u] = 1;
        for (v=1; v<=n; v++)
        {
            if (e[u][v] < 9999999)
            {
                if (dis[v] > dis[u]+e[u][v])
                {
                    dis[v] = dis[u]+e[u][v];
                }
            }
        }
    }
}
//优化
//时间复杂度为O(m+n)logn
//用邻接表存储图的时间复杂度是O(m)
//但不能有负权边

//贝尔曼福特算法
//时间复杂度为O(mn)
//解决了负权边的问题
void  BellmanFord(){
    //n为顶点个数,m为边数,uvw记录边的信息
    int n=10,m=10,dis[10],v[10],u[10],w[10];
    for (int k=1; k<=n-1; k++)//进行n-1轮松弛
    {
        for (int i=1; i<=m; i++)//枚举每一条边
        {
            if (dis[v[i]] > dis[u[i]] + w[i])//尝试松弛
            {
                dis[v[i]] = dis[u[i]] + w[i];
            }
        }
    }
}

//贝尔曼福特算法优化
//1.可以用一个一维数组备份数组dis,如果在新一轮的松弛中数量dis没有发生变化,则可以提前跳出循环
void  BellmanFord1(){
    //n为顶点个数,m为边数,uvw记录边的信息
    int n=10,m=10,dis[10],bak[10],v[10],u[10],w[10],check,flag;
    //进行n-1轮松弛
    for (int k=1; k<=n-1; k++)
    {
        //将dis数组备份至bak数组中
        for (int i=1; i<=n; i++)
        {
            bak[i] = dis[i];
        }
        //枚举每一条边
        for (int i=1; i<=m; i++)
        {
            //尝试松弛
            if (dis[v[i]] > dis[u[i]] + w[i])
            {
                dis[v[i]] = dis[u[i]] + w[i];
            }
        }
        //松弛完毕后检测dis数组是否有更新
        check=0;
        for (int i=1; i<=n; i++)
        {
            if (bak[i] != dis[i])
            {
                check = 1;
                break;
            }
        }
        //如果dis数组没有更新,提前退出循环
        if (check==0)
        {
            break;
        }
    }
    //检测负权回路
    flag = 0;
    for (int i=1; i<=m; i++)
    {
        if (dis[v[i]] > dis[u[i]] + w[i])
        {
            flag = 1;
        }
    }
    if (flag==1)
    {
        //此图含有负权回路
    }
}

//贝尔曼福特算法优化
//2.每次仅对最短路程发生变化了的顶点的相邻边执行松弛操作
//用一个队列que维护这些最短路程发生变化了的点
void BellmanFord2(){
    //n顶点个数,m边数,dis最短路径数组,que队列,head队列头,tail队列尾
    int n,m,i,j,k;
    //u,v,w大小一般要比m的最大值大1 边的数组
    int u[8],v[8],w[8];
    //first要比n最大值大1,next比m的最大值大1 建立邻接表用
    int first[6],next[8];
    //book数组记录已在队列中的顶点
    int dis[6] = {0},book[6] = {0};
    int que[101] = {0},head = 1,tail = 1;
    
    //假设图为5点,7边结构
    m=5,n=7;
    //把边建立邻接表
    for (i =1; i<=m; i++)
    {
        scanf("%d,%d,%d",&u[i],&v[i],&w[i]);
        next[i] = first[u[i]];
        first[u[i]] = i;
    }
    
    //开始算法
    //顶点入列
    que[tail] = 1;
    tail++;
    //1号已经入列
    book[1] = 1;
    //队列不为空循环
    while (head < tail)
    {
        //当前需要处理的队列首顶点
        k = first[que[head]];
        //扫描当前顶点所有的边
        while (k!=-1)
        {
            ///尝试松弛
            if (dis[v[k]] > dis[u[k]] + w[k])
            {
                //松弛
                dis[v[k]] = dis[u[k]] + w[k];
                //优化的部分,book数组判断顶点v[k]是否在队列中,节省了时间
                //0表示不在
                if (book[v[k]]==0)
                {
                    //入队操作
                    que[tail] = v[k];
                    tail++;
                    //标记已经入队
                    book[v[k]] = i;
                }
            }
            k = next[k];
        }
        //出队
        book[que[head]] = 0;
        head++;
    }
    //输出dis即可,这个优化在不用遍历判断,队列为空时算法结束,book数组判断是否在队列中
}




































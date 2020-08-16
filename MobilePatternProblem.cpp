#include<stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
void DFS(int);
void runDfs(int digit);
void printPath();
int G[9][9],visited[9],count,path[9],pathSize,n=9;    //n is no of vertices and graph is sorted in array G[10][10]
void printPath()
{
    printf("Path No %d : : : ",count);
    for (int i=0; i<n; i++)
    {

        if(path[i]>-1)
        {
            printf("%d-> ",path[i]);
        }

    }
    printf("\n");
}
void scanMat()
{
    ifstream inFile;
    int i,j;
    inFile.open("input.txt");

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            inFile >> G[i][j];
}
void printMat()
{
    int i,j;
    printf("\nEnter adjacency matrix of the graph:");

    for(i=0; i<n; i++)
    {
        printf("\n");

        for(j=0; j<n; j++)
            printf("%d ",G[i][j]);
    }
}
void cleanMat()
{
    int i,j;

    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            G[i][j]=0;
            path[i]=-1;
        }
    }

}

int main()
{
    count=0;
    int i,j,total_count=0;
    pathSize=0;
    //read the adjacency matrix


    for (i=0; i<n; i++)
    {
        cleanMat();
        scanMat();

        runDfs(i);
        printf("Count:%d\n",count);
        total_count+=count;
        count=0;

    }
    return 0;
}

void runDfs(int digit)
{
    int i,j;
    //printf("Enter number of vertices:");
    //scanf("%d",&n);
    //visited is initialized to zero
    for(i=0; i<n; i++)
        visited[i]=0;

    DFS(digit);
    printf("For digit %d the count is %d ",digit,count);
}

void DFS(int i)
{
    path[pathSize]=i;
    pathSize++;
    int j;
    printf("\n In DFS at Node %d",i);
    visited[i]=1;
    count++;
    printPath();
    int cur=0;
    for(j=0; j<n; j++)
        if(visited[j]==0&&G[i][j]==1)
        {
            DFS(j);
            cur=j;


        }
    scanMat();
    visited[i]=0;
    G[i][cur]=0;
    pathSize--;
    path[pathSize]=-1;
}


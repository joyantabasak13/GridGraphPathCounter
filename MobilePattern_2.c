#include<stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include<string>
#define n 9
#define white 0
#define black 1
#define highestNeighbourCount 4
using namespace std;
int G[n][n]; //Global adjacency matrix
int colour[n]; //colour array
int PathCount[n]; //count of total paths
int count=0;
node Node[n];
std::vector<std::string> currentPath;
std::vector<std::vector<std::string>> paths;

void scanMat()  //read the adjacency matrix
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
    printf("\nThe Adjacency matrix of the graph:");

    for(i=0; i<n; i++)
    {
        printf("\n");

        for(j=0; j<n; j++)
            printf("%d ",G[i][j]);
    }
}

void initializer()
{
    count=0;
    int i;

    for(i=0; i<n; i++)
    {
        colour[i]=white;
    }

}

class node
{
    public:
        int ID;
        int wentTo[highestNeighbourCount];

    void UpdatePath(int id)
    {
       currentPath.push_back(std::to_string(id));
       paths.push_back(currentPath);
       count++;
    }

    void rollbackUpdate()
    {
        for (int i=0; i< highestNeighbourCount; i++)
        {
            wentTo[i]=-1;
        }
        currentPath.pop_back();
    }

    node(int ID)
    {
        this->ID=ID;
        for (int i=0; i< highestNeighbourCount; i++)
        {
            wentTo[i]=-1;
        }

    }

    void clear()
    {
        for (int i=0; i< highestNeighbourCount; i++)
        {
            wentTo[i]=-1;
        }
    }

    bool haveWent(int id)
    {
        for (int i=0; i<highestNeighbourCount;i++)
        {
            if (wentTo[i]=id) return true;
        }
        return false;
    }
};


void DFS(node nd)
{
    int j;
    int curID=nd.ID;
    colour[curID]=black;
    nd.UpdatePath();
    for(j=0; j<n; j++){
        if(colour[j]==white && G[curID][j]==1 && !nd.haveWent(j))
        {
            DFS(Node[j]);
        }
    }
    nd.rollbackUpdate();

}

int main()
{
    initializer();
    scanMat();
    int i;
    //read the adjacency matrix
    for (i=0; i<n; i++)
    {
        Node[i]= new node(i);

    }

    //for(i=0; i<n; i++)
    i=0;
    {
        DFS(Node[i]);
        PathCount[i]=count;
        count=0;
    }

    return 0;
}


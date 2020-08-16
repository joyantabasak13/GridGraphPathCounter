#include<stdio.h>
#include <sstream>

namespace patch
{
template < typename T > std::string to_string( const T& n )
{
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}
}
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
int curCount=0;
std::vector<std::string> currentPath;
std::vector<std::vector<std::string> > paths;

void scanMat()  //read the adjacency matrix
{
    ifstream inFile;
    int i,j;
    inFile.open("input1_cross.txt");

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

void printPathALL()
{
    for(int i=0; i < paths.size(); ++i)
    {
        for(int j=0; j < paths[i].size(); j++)
        {
            cout<<paths[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<endl;
}

void printPathThis(int Id)
{

        for(int j=0; j<paths[Id].size();j++)
        {
            cout<< paths[Id][j]<<endl;
        }

}

void printCurPath()
{
    for(int i=0;i<currentPath.size();i++)
    {
        cout<<currentPath[i];
    }
    cout<<endl;
}
void initializer()
{
    curCount=0;
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

    void UpdatePath()
    {
        currentPath.push_back(patch::to_string(ID));
        //printCurPath();
        paths.push_back(currentPath);
        curCount++;
    }

    void rollbackUpdate()
    {
        for (int i=0; i< highestNeighbourCount; i++)
        {
            wentTo[i]=-1;
        }
        currentPath.pop_back();
        colour[ID]=white;
    }

    void initialize(int ID)
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
        for (int i=0; i<highestNeighbourCount; i++)
        {
            if (wentTo[i]==id) return true;
        }
        return false;
    }
};
node Node[n];




void DFS(node nd)
{
    int j;
    int curID=nd.ID;
    colour[curID]=black;
    nd.UpdatePath();
    //cout<<"In Node "<< curID<< endl;
    for(j=0; j<n; j++)
    {
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
    printMat();
    cout<<endl;
    int i;
    //read the adjacency matrix
    for (i=0; i<n; i++)
    {
        Node[i].initialize(i);

    }

    for(i=0; i<n; i++)
    {
        {
            DFS(Node[i]);
            PathCount[i]=curCount;
            //cout<<" Node " <<i<< " has "<< curCount<< " Paths"<<endl;
            initializer();
        }
    }
    int sum=0;
    for(i=0;i<n;i++)
    {
        cout<<" Node " <<i<< " has "<< PathCount[i]<< " Paths"<<endl;
        sum+=PathCount[i];
        //printPathThis(i);
        cout<<endl;
        cout<<endl;
    }
    cout<<"TOTAL PATHS ARE "<< sum<<endl;
    //cout << paths.size() << " "<< paths[3].size() <<endl;
    int lenCount=0;
    for( i=0; i < paths.size(); ++i)
    {
        if(paths[i].size()>2) lenCount++;
    }
    cout<< "OF LENGTH 3 or Plus"<< lenCount<< endl;
    //printPathALL();



    return 0;
}


#include <iostream>
#include<fstream>
#include<database.h>
#include<map>
#include<math.h>
#include<vector>
#include<ctime>
#include <bits/stdc++.h>

using namespace std;


//search function tha will return the shortest distance between actor and kevin bacon
bool search(vector<int> graph[], int src, int bacon, int v, int *&pre, int *&distance);
//all name lower case
void modifyName(string &name);
//load graph with actor names
void loadgraph(vector<int> graph[], database &test);
//print the shortest distance actor names
void printNames(vector<int> graph[], int source, int bacon,database &test);


int v=1500000;

int  main()
{
    database test;
    test.read();
    test.serach("");
    vector<int> *graph;
    graph =new vector<int>[v];
    loadgraph(graph,test);
    string name;
    int  bacon = test.datamap[102];
    int source;
    do{
        cout<<"please enter a actor name: \n";
        modifyName(name);
        vector<unsigned int> list;
        if(test.findID(name,list) >0)
        {
           for(unsigned int w=0;w<list.size();w++)
            {
                source =test.datamap[list[w]];
                if(source==0)
                {
                    break;
                }
                printNames(graph,source,bacon,test);
            }
        }
        else {
            cout<<"could not find the name you entered,please enter another name: \n";
        }
    }while(!name.empty());
    return 0;
}

void loadgraph(vector<int> *graph,database& test)
{
    for(unsigned int i=0;i<test.data.size();i++)
    {
        for(unsigned int n=0;n<test.data[i].size();n++)
        {
            for(unsigned int m=n+1;m<test.data[i].size();m++)
            {
                if(test.datamap[test.data[i][n]]<v && test.datamap[test.data[i][m]]<v)
                {
                    graph[test.datamap[test.data[i][n]]].push_back(test.datamap[test.data[i][m]]);
                    graph[test.datamap[test.data[i][m]]].push_back(test.datamap[test.data[i][n]]);
                }
            }
        }
    }
}

void modifyName(string &name)
{

    getline(cin,name);
    if(name.empty())
    {
        cout<<"exiting program...\n";
        exit(2);
    }
    while(name.find(' ')==string::npos)
    {
        cout<<"please enter a space between the first and last name \n";
        getline(cin,name);
    }
    for(unsigned int i=0;i<name.size();++i)
    {
        name[i]=tolower(name[i]);
    }
}






bool search( vector<int> *graph, int src, int bacon, int v,int *&pre, int *&distance)
{
    list<int> queue;
    bool *dset;
    dset = new bool[v];
    for (int i = 0; i < v; i++)
    {
        dset[i] = false;
        distance[i] = INT_MAX;
        pre[i] = -1;
    }
    dset[src] = true;
    distance[src] = 0;
    queue.push_back(src);
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();
        for (unsigned int i = 0; i < graph[u].size(); i++) {
            if (dset[graph[u][i]] == false) {
                dset[graph[u][i]] = true;
                distance[graph[u][i]] = distance[u] + 1;
                pre[graph[u][i]] = u;
                queue.push_back(graph[u][i]);
                if (graph[u][i] == bacon)
                    return true;
            }
        }
    }

    return false;
}


void printNames(vector<int> *graph, int source, int bacon, database &test)
{
    double starttime=clock();
    int *pre,*distance;
    pre=new int[v];
    distance =new int[v];

    if (search(graph, source, bacon, v, pre, distance) == false)
    {
        cout <<"given actor is not connect to kevin bacon.\n";
    }
    else {
        vector<int> path;
        path.reserve(100000);

        int finding = bacon;
        path.push_back(finding);
        while (pre[finding] != -1) {
            path.push_back(pre[finding]);
            finding = pre[finding];
        }
        cout << "Shortest bacon number is : "
             << distance[bacon]<<'\n';
        cout << "path: \n";
        for ( int i = path.size() - 1; i >= 0; i--)
        {
            cout << test.nameMap[test.ptr[path[i]]];
             if(i>0)
            {
                cout << "  -> ";
            }
        }
        cout<<"\n";
        double endtime=clock();
        cout << "time: " << (endtime-starttime)/double(CLOCKS_PER_SEC)<<" seconds \n\n\n";

    }
}














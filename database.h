#ifndef DATABASE_H
#define DATABASE_H
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include"node.h"
#include<map>
#include<algorithm>
#include<queue>
class database
{
public:
    //constructor
    database();
    //destructor
    ~database();
    //copy constructor
    database(const database&other);
    //assigment operator
    database& operator=(const database&other);
    //reading the file
    void read();
    //insert data into node
    void insert(const int &movieid, const vector<unsigned int> &otherid);
    //check the file names
    void filenames(string&principal,string &namef,string& akas);



    //delete all nodes
    void deleteall(node<unsigned int> *current);
    //helper function to copy
    void copy(node<unsigned int>* current);
    //mapping names
    void serach(string name);
    //find a specific name
    void find(map<unsigned int,vector<unsigned int>> &current,unsigned int id);

    //return a integer name id
    int findID(string name, vector<unsigned int> &list);


    node<unsigned int> *root;
    vector<vector<unsigned int>> data;
    vector<string> nameMap;
    map<unsigned int,vector<unsigned int>> connection;
    vector<unsigned int> ptr;
    map<unsigned int,int> datamap;

    //overload output operator
    friend
    ostream& operator <<(ostream &out,const database& source);

    //overload insertion operator
    friend
    istream& operator >>(istream &in, database& taken);




};

#endif // DATABASE_H

#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <typeinfo>
#include <string>
#include <sstream>
#include<vector>
using namespace std;
template<typename T>
struct node
{
    T movie;
    string actorname;
    vector<unsigned int> knownID;
    node<T>* next;

    //constructor with default arugment
    node(const T &movie=T(),vector<unsigned int> known=vector<unsigned int>());
    //overload consturctor
    node(T d,unsigned int otherID);
    //destructor
    ~node();
    //copy constructor
    node(const node<T> &other);
    //assigment operator
    node<T>& operator=(const node<T> &other);

    //overload extraction operator
    template<typename f>
    friend
    ostream& operator <<(ostream &out,const node<f>& source);

    //overload insertion operator
    template<typename f>
    friend
    istream&operator >>(istream &in,node<f>&takein);

    //overload ineuality operator
    template<typename f>
    friend
    bool operator !=(const node<f> &lhs,const node<f>& rhs);
    //overload equal operator
    template<typename f>
    friend
    bool operator == (const node<f> &lhs,const node<f>& rhs);

    //overload lesser than operator
    template<typename f>
    friend
    bool operator <(const node<f> &lhs,const node<f>& rhs);

};

template<typename T>
 node<T>::node(const T&,vector<unsigned int> known)
{

     knownID =known;
    next=NULL;

}
 template<typename T>
  node<T>::node(T d,unsigned int otherID)
 {
     knownID.push_back(otherID);
     next=NULL;

 }
template<typename T>
node<T>::~node()
{
    actorname=string();
    knownID.clear();
    next=NULL;
}
template<typename T>
node<T>::node(const node<T> &other)
{
    actorname = other.actorname;
    knownID=other.knownID;
    next=NULL;
}


template<typename T>
node<T>& node<T>::operator=(const node<T> &other)
{
    if(this!=&other)
    {
        actorname = other.actorname;
        knownID=other.knownID;
    }
}

template<typename f>
ostream& operator <<(ostream &out,const node<f>& source)
{

    if(&out==&cout)
    {
        out<<"movie: ";
        out<<"\n";
        for(int i =0;i<source.knownID.size();++i)
        {
            out<<source.knownID[i]<<" ";
        }
        out<<"\n";
    }
    else
    {
        out<<source.movie<<"\a"<<source.actorname<<'\n';
    }
    return out;
}

template<typename f>
istream&operator >>(istream &in,node<f>&takein)
{
    string line;
    stringstream ss;

    if(&in == &cin)
    {
        cout<<"movie: ";
        getline(cin,line);
        if(!line.empty())
        {
            ss<<line;
            ss>>takein.movie;
        }
        else
        {
            getline(in,line);
            ss<<line.substr(0,line.find('\a'));

        }
    }
    return in;
}

template<typename f>
bool operator !=(const node<f> &lhs,const node<f>& rhs)
{
    return lhs.movie!=rhs.movie;
}

template<typename f>
bool operator == (const node<f> &lhs,const node<f>& rhs)
{
    return lhs.movie==rhs.movie;
}

template<typename f>
bool operator <(const node<f> &lhs,const node<f>& rhs)
{
    return lhs.movie<rhs.movie;
}

#endif // NODE_H

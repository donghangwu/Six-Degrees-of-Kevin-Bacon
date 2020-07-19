#include "database.h"

database::database()
{
    root=NULL;
}

database::~database()
{
    deleteall(root);
}
database::database(const database&other)
{
    copy(other.root);
}
database& database::operator=(const database&other)
{
    if(this!=&other)
    {
        copy(other.root);
    }
    return *this;
}


void database::deleteall(node<unsigned int> *current)
{
    if(current)
    {
        deleteall(current->next);
        delete current;
        current=NULL;
    }
}
void database::copy(node<unsigned int>* current)
{
    if(current)
    {
        insert(current->movie,current->knownID);
        copy(current->next);
    }
}

void database::read()
{

    string principal="principal.tsv",namef="name.tsv",akas="akas.tsv";
    ifstream actorlist,namefile,akafile;
    vector<bool> usmovie;


    unsigned int nameid,movieid;
    vector<unsigned int> nameidlist;
    usmovie.resize(100000000);
    string line;
    int count=0;
    bool skip;
    nameMap.resize(28000000);
   string junknameid,first,last,middle;
    namefile.open(namef);
    getline(namefile,line);
    while(getline(namefile,line))
    {
        nameid=(stoi(line.substr(2,8)));
        stringstream ss;
        ss<<line;
        ss>>junknameid;
        ss>>first;
        ss>>middle;
        ss>>last;
        first+=" ";
        first+=middle;
        if(!isdigit(last[0]) && last[0]!='\\' )
        {
            first+=" ";
            first+=last;
        }
        for(int i =0;i<first.size();i++)
        {
            first[i]=tolower(first[i]);
        }

        if(nameid<12000000)
        {
            nameMap[nameid] =first;
        }

    }
    namefile.close();
    akafile.open(akas);
    getline(akafile,line);
    while(getline(akafile,line))
    {
        movieid=stoi(line.substr(2,8));

            if(line.find("\tUS\t") !=string::npos)
            {
                usmovie[movieid]=true;
                skip=true;
            }
            else if(!skip)
            {
                usmovie[movieid]=(false);
            }
            else
            {}

    }
    akafile.close();
    actorlist.open("principal.tsv");
    stringstream ss;
    if(actorlist.fail())
    {
        cout<<"fail to open principal file \n";
        exit(1);
    }

    data.reserve(10000000);
        getline(actorlist,line);
        while(getline(actorlist,line))
        {
            int order;
            int onlynameid;
            string junk;
            char n,m;
            if(usmovie[stoi(line.substr(2,8))])
            {
                movieid=stoi(line.substr(2,8));
                ss=stringstream();
                ss<<line;
                ss>>junk;
                ss>>order;
                ss>>n>>m;
                ss>>onlynameid;
                if(order==1)
                {
                    data.push_back(nameidlist);
                    nameidlist.clear();
                    nameidlist.push_back(onlynameid);
                }
                else
                {
                    nameidlist.push_back(onlynameid);
                }

            }
        }
        actorlist.close();







}
void database::insert(const int &movieid, const vector<unsigned int> &otherid)
{
    node<unsigned int> *newnode=new node<unsigned int>(movieid,otherid);
    node<unsigned int> *ptr=root;
    if(root==NULL)
    {
        root=newnode;
    }
    else
    {
        while(ptr->next!=NULL)
        {
           ptr=ptr->next;
        }
        ptr->next=newnode;
    }
}
void database::find(map<unsigned int,vector<unsigned int>> &current,unsigned int id)
{
    vector<vector<int>> save;
    for(int i =0;i<connection[id].size();i++)
    {

        for(int n=0;n<connection[connection[id][i]].size();++n )
        {
            for(int m=0;m<connection[connection[connection[id][i]][n]].size();++m)
            {

            }
        }
    }

}

void database::serach(string name)
{

    for(int i=0;i<data.size();i++)
    {
        for(int n=0;n<data[i].size();n++)
        {
            for(int m=0;m<data[i].size();m++)
            {
                if(data[i][n]!=data[i][m])
                {
                    connection[data[i][n]].push_back(data[i][m]);
                }
            }
            connection[data[i][n]].erase(unique( connection[data[i][n]].begin(), connection[data[i][n]].end() ), connection[data[i][n]].end() );
        }
    }
    ptr.reserve(1500000);

    for(map<unsigned int,vector<unsigned int>>::iterator it = connection.begin(); it != connection.end(); ++it)
    {
      ptr.push_back(it->first);
    }

    unsigned int id;

    for(int i=0;i<ptr.size();++i)
    {
        datamap[ptr[i]]=i;
    }





}

void database::filenames(string&principal,string &namef,string& akas)
{
    cout<<"please enter the principle file: ";
    cin>>principal;
    cout<<"please enter the namefile file: ";
    cin>>namef;
    cout<<"please enter the aka file: ";
    cin>>akas;
    if(principal.find(".tsv") == string::npos)
    {
        principal+=".tsv";
    }
    if(namef.find(".tsv") == string::npos)
    {
        namef+=".tsv";
    }
    if(akas.find(".tsv") == string::npos)
    {
        akas+=".tsv";
    }
}


int database::findID(string name,vector<unsigned int>&list)
{
    for (unsigned int i=0;i<nameMap.size();i++)
    {
        if(name==nameMap[i])
        {
            list.push_back(i);
        }
    }
    return list.size();
}

ostream& operator <<(ostream &out,const database& source)
{
    node<unsigned int> *walker = source.root;

    cout<<"size: "<<source.data.size()<<endl;
    for(int i =0;i<source.nameMap.size();i++)
    {

        if(source.nameMap[i]=="KevinBacon")
        {

            cout<<i<<endl;
        }

    }

    return out;
}

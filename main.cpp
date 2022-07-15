#include <bits/stdc++.h>
using namespace std;
map<string,vector<string>> tag_by_name;
map<string,vector<string>> tag_by_color;
class Input
{
  public:
  bool check(string s)
  {
    for(int i=0;i<s.length();i++)
    {
        if(s[i]==' ')
        {
            cout<<"No spaces allowed"<<endl;
            return false;
        }
    }
    return true;
  }
    void tag_color(string loc)
    {
       cout<<"Enter 1 to also tag by color or any other key to exit this option"<<endl;
       string k;
       cin>>k;
       if(k!="1") return;
       cout<<"Enter the color"<<endl;
       string color;
       cin>>color;
       tag_by_color[color].push_back(loc);
    }
    void database_by_color()
    {
        ofstream out("database_color.txt");
        for(auto it:tag_by_color)
        {
            string tag_1=it.first;
            vector<string> texts_tag_1=it.second;
            for(int i=0;i<texts_tag_1.size();i++)
            out<<tag_1<<"--"<<texts_tag_1[i]<<endl;
        }   
    }
    void database()
    {
        ofstream out("database.txt");
        for(auto it:tag_by_name)
        {
            string tag_1=it.first;
            vector<string> texts_tag_1=it.second;
            for(int i=0;i<texts_tag_1.size();i++)
            out<<tag_1<<"--"<<texts_tag_1[i]<<endl;
        }   
    }
    void input()
    {
        cout<<"Enter the tag"<<endl;
        string tag;
        cin>>tag;
        bool k=check(tag);
        if(!k) return;
        cout<<"Enter the file location"<<endl;
        string loc;
        cin>>loc;
        k=check(loc);
        if(!k) return;
        tag_by_name[tag].push_back(loc);
        tag_color(loc);
        database();
        database_by_color();
        return;
    }
};
int main()
{
    string n="1";
    Input ip;
    while(n=="1" || n=="2")
    {
       cout<<"Enter 1 to create tag and 2 to search file else any key to exit"<<endl;
       cin>>n;
       if(n=="1")
       ip.input();
       else if(n=="2")
       {
         string s;
         cin>>s;
        //  check(s);
       }
       else
       break; 
    }
    return 0;
}
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
class Preprocessing
{
    public:
    void preprocess_tag_by_name()
    {
       ifstream in("database.txt");
       string st;
       getline(in,st);
       while (st!="")
       {
          string key="",value="";
          int i=0;
          for(i=0;i<st.length();i++)
          {
             if(st[i]=='-' && st[i+1]=='-')
             break;
             else
             key+=st[i];
          }
          i++;
          for(;i<st.length();i++)
          {
             if(st[i] != ' ')
             value+=st[i];
             else
             break;
          }
          tag_by_name[key].push_back(value);
          getline(in,st);
       }
    }
    void preprocess_tag_by_color()
    {
       ifstream in("database_color.txt");
       string st;
       getline(in,st);
       while (st!="")
       {
          string key="",value="";
          int i=0;
          for(i=0;i<st.length();i++)
          {
             if(st[i]=='-' && st[i+1]=='-')
             break;
             else
             key+=st[i];
          }
          i++;
          for(;i<st.length();i++)
          {
             if(st[i] != ' ')
             value+=st[i];
             else
             break;
          }
          tag_by_color[key].push_back(value);
          getline(in,st);
       }
    }
    void process()
    {
       preprocess_tag_by_name();
       preprocess_tag_by_color();
       return;
    }
};
class Delete
{
    public:
    void modification_database_name()
    {
       
    }
    void modification_database_color()
    {
      
    }
    void delete_by_tag_by_name()
    {
        cout<<"Enter the color tag"<<endl;
        string name;
        cin>>name;
        if(tag_by_name.find(name)!=tag_by_name.end())
        {
            tag_by_name.erase(name);
            modification_database_name();
        }
        return;
    }
    void delete_by_tag_by_color()
    {
        cout<<"Enter the color tag"<<endl;
        string color;
        cin>>color;
        if(tag_by_color.find(color)!=tag_by_color.end())
        {
            tag_by_color.erase(color);
            modification_database_color();
        }
        return;
    }
    void erase()
    {
        cout<<"1 to delete tag marked by name or any other key to delete tag marked by color"<<endl;
        string s;
        cin>>s;
        if(s=="1")
        delete_by_tag_by_name();
        else
        delete_by_tag_by_color();
        return;
    }
};
int main()
{
    string n="1";
    // Preprocessing prx;
    Input ip;
    // Rename rm;
    Delete del;
    // Search src;
    // First doing the preprocessing of the stored data
    // prx.process();
    while(n=="1" || n=="2")
    {
       cout<<"Enter 1 to create tag and 2 to search file 3 if you renamed the file but want to keep the same tag 4 to delete that tag else any key to exit"<<endl;
       cin>>n;
       if(n=="1")
       ip.input();
       else if(n=="2")
       {
         string s;
         cin>>s;
        //  check(s);
       }
       else if(n=="3")
       {
         
       }
       else if(n=="4")
       {
          cout<<"Enter the tag to be deleted"<<endl;
          del.erase();
       }
       else
       break; 
    }
    return 0;
}
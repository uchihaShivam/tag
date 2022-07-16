#include <bits/stdc++.h>
using namespace std;
map<string,vector<string>> tag_by_name;
map<string,vector<string>> tag_by_color;
set<string> tag_name;
set<string> tag_clr;
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
        ofstream out;
        out.open("database_color.txt",ofstream::out | ofstream::app);
        for(auto it:tag_by_color)
        {
            string tag_1=it.first;
            vector<string> texts_tag_1=it.second;
            for(int i=0;i<texts_tag_1.size();i++)
            {
               string ch=tag_1+"--"+texts_tag_1[i];
               if(tag_clr.find(ch)==tag_clr.end())
               {
                 out<<tag_1<<"--"<<texts_tag_1[i]<<endl;
                 tag_clr.insert(ch);
               }
            }
        }
        out.close();   
    }
    void database()
    {
        ofstream out;
        out.open("database.txt",ofstream::out | ofstream::app);
        for(auto it:tag_by_name)
        {
            string tag_1=it.first;
            vector<string> texts_tag_1=it.second;
            for(int i=0;i<texts_tag_1.size();i++)
            {
               string ch=tag_1+"--"+texts_tag_1[i];
               if(tag_name.find(ch)==tag_name.end())
               {
                 out<<tag_1<<"--"<<texts_tag_1[i]<<endl;
                 tag_name.insert(ch);
               }
            }
        }
        out.close();   
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
          i+=2;
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
          i+=2;
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
    bool is_file_exist(const char *fileName)
    {
    std::ifstream infile(fileName);
    return infile.good();
    }
    void process()
    {
       bool check1=is_file_exist("database.txt");
       bool check2=is_file_exist("database_color.txt");
       if(check1)
       preprocess_tag_by_name();
       if(check2)
       preprocess_tag_by_color();
       return;
    }
};
class Search
{
   public:
   // lcs function is to find tags with longest common character subsequence when tag entered is not correct
   string lcs(string s, string t)
   {
    int n=s.length();
    int m=t.length();
	 vector<vector<int>>dp(n+1,vector<int>(m+1,0));
    for(int j=0;j<=m;j++)
    dp[0][j]=0;
    for(int i=0;i<=n;i++)
    dp[i][0]=0;
    for(int i=1;i<n+1;i++)
    {
        for(int j=1;j<m+1;j++)
        {
            if(s[i-1]==t[j-1])
                dp[i][j]=1+dp[i-1][j-1];
            else
                dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
        }
    }
    int i=n,j=m;
    string ans;
    while(i>0 && j>0)
    {
        if(s[i-1]==t[j-1])
        {
            ans.push_back(s[i-1]);
            i--;
            j--;
        }
        else if(dp[i-1][j]>dp[i][j-1])
            i--;
        else
            j--;
    }
    reverse(ans.begin(),ans.end()); return ans;  
   }
   vector<string> longestCommonSubsequence(vector<string> &tag, string text2)
   {
        vector<string> v;
        int maxi=0;
        for(int i=0;i<tag.size();i++)
        {
           string str=lcs(tag[i],text2);
           if(str.length()>maxi)
           {
             while(v.size()>0)
             v.pop_back();
             v.push_back(tag[i]);
             maxi=str.length();
           }
           else if(str.length()==maxi)
           v.push_back(tag[i]); 
         }
          return v;
   }
   void related_search_by_name(string s)
   {
      vector<string> potential_search;
      for(auto it:tag_by_name)
      potential_search.push_back(it.first);
      vector<string> ans=longestCommonSubsequence(potential_search,s);
      if(ans.size()==0)
      cout<<"No related searches"<<endl;
      else 
      {
         cout<<"Do you mean to search:"<<endl;
         for(string x:ans)
         cout<<x<<endl;
      }
   }
   void related_search_by_color(string s)
   {
      vector<string> potential_search;
      for(auto it:tag_by_color)
      potential_search.push_back(it.first);
      vector<string> ans=longestCommonSubsequence(potential_search,s);
      if(ans.size()==0)
      cout<<"No related searches"<<endl;
      else 
      {
         cout<<"Do you mean to search:"<<endl;
         for(string x:ans)
         cout<<x<<endl;
      }
   }
   void check_by_name(string s)
   {
      vector<string> ans;
      if(tag_by_name.find(s)!=tag_by_name.end())
      ans=tag_by_name[s];
      else
      {
         related_search_by_name(s);
         return;
      }
      cout<<"Required locations are :"<<endl;
      for(string x:ans)
      cout<<x<<endl;
   }
   void check_by_color(string s)
   {
      vector<string> ans;
      if(tag_by_color.find(s)!=tag_by_color.end())
      ans=tag_by_color[s];
      else
      {
         related_search_by_color(s);
         return;
      }
      cout<<"Required locations are :"<<endl;
      for(string x:ans)
      cout<<x<<endl;

   }
};
int main()
{
    string n="1";
    Preprocessing prx;
    Input ip;
   //  Rename rm;
    Search src;
    // First doing the preprocessing of the stored data
    prx.process();
    while(1>0)
    {
       cout<<"Enter 1 to create tag and 2 to search file 3 if you renamed the file but want to keep the same tag else any key to exit"<<endl;
       cin>>n;
       if(n=="1")
       ip.input();
       else if(n=="2")
       {
         cout<<"Enter 1 to search by name or any other key to search by color"<<endl;
         string n;
         cin>>n;
         if(n=="1")
         {
         cout<<"Enter the name"<<endl;
         string s;
         cin>>s;
         src.check_by_name(s);
         }
         else
         {
         cout<<"Enter the color"<<endl;
         string s;
         cin>>s;
         src.check_by_color(s);
         }
       }
       else if(n=="3")
       {
         
       }
       else
       break; 
    }
    return 0;
}
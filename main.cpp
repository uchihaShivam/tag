#include <bits/stdc++.h>
#include "input.cpp"
using namespace std;
map<string,vector<string>> tag_by_name;
map<string,vector<string>> tag_by_color;
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
#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream in;
    in.open("base.txt");
    ofstream out;
    out.open("dataset1.txt");
    string s1,s2,s;
    while (getline(in,s)) {
        //cout<<s<<'\n';
        for (int i=0;i<s.length();i++) {
            if (i+1<s.length()&&s[i]=='\\'&&s[i+1]=='n') {
                out<<'\n';
                //cout<<'\n';
                i++;
            }
            else if (s[i]=='@'||s[i]=='*'||s[i]=='-'||s[i]=='+') {
                out<<'\n';
                out<<s[i];
            }
            else {
                out<<s[i];
                //cout<<s[i];
            }
        }
        out<<'\n';
        out<<"----------------------\n";
    }
    in.close();
    out.close();
}

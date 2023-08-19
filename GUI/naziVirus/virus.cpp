#include <bits/stdc++.h>
using namespace std;

string ans,s;
int n;

string intToString(int _number) {
    string kq="";
    int tmp=1;
    if (_number<0) {
        _number=-_number;
        tmp=-1;
    }
    if (_number==0) return "0";
    while (_number>0) {
        kq=char(_number%10+'0')+kq;
        _number/=10;
    }
    if (tmp==-1) {
        return "-"+kq;
    }
    else {
        return kq;
    }
}

int main() {
    ifstream in;
    ofstream out;
    in.open("maxslot.txt");
    in>>n;
    in.close();
    for (int it=1;it<=n;it++) {
        in.open(intToString(it)+".txt");
        while (getline(in,s)) {
            ans="";
            for (int i=0;i<s.length();i++) {
                if (i+1<s.length()&&s[i]=='\\'&&s[i+1]=='n') {
                    ans+='\n';
                }
                else {
                    ans+=s[i];
                }
            }
        }
        in.close();
        out.open(intToString(it)+".txt");
        out<<ans;
        out.close();
    }
}

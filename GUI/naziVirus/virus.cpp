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
    //cout<<n<<'\n';
    in.close();
    for (int it=1;it<=n;it++) {
        in.open(intToString(it)+".txt");
        out.open(intToString(0)+".txt");
        while (getline(in,s)) {
            //cout<<s<<'\n';
            ans="";
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
        }
        in.close();
        //out<<ans;
        //cout<<"?"<<ans<<'\n';
        out.close();
        in.open(intToString(0)+".txt");
        out.open(intToString(it)+".txt");
        while (getline(in,s)) {
            //cout<<s<<'\n';
            out<<s<<'\n';
        }
        in.close();
        //out<<ans;
        //cout<<"?"<<ans<<'\n';
        out.close();
        if (it%100==0) cout<<it<<'\n';
    }
    //cin>>n;
}

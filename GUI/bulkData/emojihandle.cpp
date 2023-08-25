#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream in;
    in.open("game.txt");
    ofstream out;
    string tmp,tmp2,tmp3;
    out.open("e1.txt");
    while (getline(in,tmp)) {
        out<<tmp<<'\n';
        out<<"Music. Cha cha cha\n";
    }
    in.close();
    out.close();
}

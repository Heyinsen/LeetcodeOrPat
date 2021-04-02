#pragma warning(disable:4996)
#include<iostream>
#include<cmath>
using namespace std;

int main(){
    double n,p;
    while(cin>>n>>p){
        cout<<pow(p,1.0/n)<<"\n";
    }
    return 0;
}
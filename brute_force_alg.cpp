#include<cstring>
#include<iostream>
#include<cstdio>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <iomanip>

using namespace std;
                            //running time counter algorithm
double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
    cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart)/1000000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}
double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}





void search (char *text , char *pat){
int n=strlen(text);                             // length of text
int m=strlen(pat);                              // length of pattern
int s,j;
for(s=0;s<=n-m;s++){             // Iteration over n-m+1 values of shift
for(j=0;j<m;j++){
if(pat[j]!=text[s+j]) break;
}
//if(j==m) cout<<"Pattern found at : "<<s<<endl; //        COMMENT BEFORE COUNTING EXECUTING TIME not to spend time for displaying
}
}




int main(){
    ifstream myfile("data.txt");
    string line;
    StartCounter();
    if(myfile.is_open()){
        while(getline(myfile,line)){

            char *a=new char[line.size()+1];
            a[line.size()]=0;
            memcpy(a,line.c_str(),line.size());
            search(a,"netwothreeftyujmnkoplkjhqertyujhnbytghjoplkjhbzxcvqerfgtyxcprtghjuiolpnetwothreeftyujmnkoplkjhqertyujhnbytghjoplkjhbzxcvqerfgtyxcprtghjuiolp");



        }
    }
    double var=GetCounter();
    cout<<var<<endl;




    return 0;
}

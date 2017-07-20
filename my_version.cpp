#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include<cstring>
#include<cstdio>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <iomanip>


using namespace std;


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


bool check(int index, string pattern, string lineToCheck){
    bool answer=false;

    for(int x=0;x<pattern.size();x++){
        if(lineToCheck[index + x] == pattern[x]){
            answer=true;
        }else{
            answer=false;
            break;
        }
    }
    if(answer){
            cout<<"Pattern found at the index : "<< index << endl;
    }
    return answer;
}

void patternSearch(string lineToCheck, string pattern){

    int lineLength=lineToCheck.size();
    int patternLength=pattern.size();
    int index=0;


    while(index != lineLength-patternLength-1){
        if(check(index, pattern , lineToCheck)){
            index+=pattern.size();
        }else{index++;}
    }

}



int main(){
    ifstream myFile("data.txt");
    string pattern="KARL";
    string line;
    int index=0; // will use this var to determine areas which was checked/not checked


    if(myFile.is_open()){
        while(getline(myFile,line)){
            if(line.size() >= pattern.size()){
                patternSearch(line, pattern);
            }
        }
    }else{
        cout<<"ERROR : while opening  'data.txt' "<<endl;
    }






    return 0;
}

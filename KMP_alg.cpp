#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include<cstring>
#include<cstdio>
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




void computeLPSArray(char *pat, int M, int *lps);

// Prints occurrences of txt[] in pat[]
void KMPSearch(char *pat, char *txt)
{
    int M = strlen(pat);
    int N = strlen(txt);

    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int lps[M];

    computeLPSArray(pat, M, lps);

    int i = 0;  // index for txt[]
    int j  = 0;  // index for pat[]
    while (i < N){
        if (pat[j] == txt[i]){
            j++;
            i++;
        }

        if (j == M){
           // printf("Found pattern at index %d \n", i-j);
            j = lps[j-1];
        }

        // mismatch after j matches
        else if (i < N && pat[j] != txt[i]){
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j-1];
            else
                i = i+1;
        }
    }
}


void computeLPSArray(char *pat, int M, int *lps)
{
    int len = 0;
    lps[0] = 0;
    int i = 1;
    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else {// (pat[i] != pat[len])
            if (len != 0)
            {
                len = lps[len-1];

            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int main(){

    string line;
    ifstream myfile("data.txt");
    StartCounter();

    if(myfile.is_open()){
        while(getline(myfile,line)){

            char *a=new char[line.size()+1];
            a[line.size()]=0;
            memcpy(a,line.c_str(),line.size());
            KMPSearch("netwothreeftyujmnkoplkjhqertyujhnbytghjoplkjhbzxcvqerfgtyxcprtghjuiolpnetwothreeftyujmnkoplkjhqertyujhnbytghjoplkjhbzxcvqerfgtyxcprtghjuiolp", a);



        }
    }
    double var=GetCounter();
    cout<<var<<endl;






    myfile.close();
    return 0;
}

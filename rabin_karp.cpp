#include<stdio.h>
#include<string.h>
#include <fstream>
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

// d is the number of characters in input alphabet
#define d 256

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



/* pat -> pattern
    txt -> text
    q -> A prime number
*/
void search(char pat[], char txt[], int q)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for txt
    int h = 1;

    // The value of h would be "pow(d, M-1)%q"
    for (i = 0; i < M-1; i++){
            h = (h*d)%q;
    }

    for (i = 0; i < M; i++){
        p = (d*p + pat[i])%q;
        t = (d*t + txt[i])%q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= N - M; i++){
        if ( p == t ){
            /* Check for characters one by one */
            for (j = 0; j < M; j++){
                if (txt[i+j] != pat[j])
                    break;
            }
            // if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]
            if (j == M){
                //printf("Pattern found at index %d \n", i);
            }
        }
        if ( i < N-M ){
            t = (d*(t - txt[i]*h) + txt[i+M])%q;
            if (t < 0)
            t = (t + q);
        }
    }
}

static vector<int> SearchString(string A, string B) {
	vector<int> retVal;
	unsigned long siga = 0;
	unsigned long sigb = 0;
	unsigned long Q = 100007;
	unsigned long D = 256;
	int ALength = A.length();
	int BLength = B.length();

	for (int i = 0; i < BLength; ++i)
	{
		siga = (siga * D + (unsigned long)A[i]) % Q;
		sigb = (sigb * D + (unsigned long)B[i]) % Q;
	}

	if (siga == sigb)
		retVal.push_back(0);

	unsigned long pow = 1;

	for (int k = 1; k <= BLength - 1; ++k)
		pow = (pow * D) % Q;

	for (int j = 1; j <= ALength - BLength; ++j)
	{
		siga = (siga + Q - pow * (unsigned long)A[j - 1] % Q) % Q;
		siga = (siga * D + (unsigned long)A[j + BLength - 1]) % Q;

		if (siga == sigb)
			if (A.substr(j, BLength) == B)
				retVal.push_back(j);
	}

	return retVal;
}

int main()
{
    char pat[] = "netwothree";


    ifstream myfile("data.txt");
    string line;
    int currentLine = 0;

    StartCounter();
    if(myfile.is_open()){
        while(getline(myfile,line)){

            char *a=new char[line.size()+1];
            a[line.size()]=0;
            memcpy(a,line.c_str(),line.size());
            search(pat,a,11);
            currentLine++;
            /*vector<int> value =*/SearchString(line, "netwothreeftyujmnkoplkjhqertyujhnbytghjoplkjhbzxcvqerfgtyxcprtghjuiolpnetwothreeftyujmnkoplkjhqertyujhnbytghjoplkjhbzxcvqerfgtyxcprtghjuiolp");
//        for(int x=0;x<value.size(); x++){
//           cout<<"Line -> "<<currentLine <<". Pattern found at index :"<<value[x]<<endl;
//        }


        }
    }

    double var=GetCounter();
    cout<<var<<endl;


    return 0;
}

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <vector >
#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <windows.h>


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


static int Max(int a, int b) {
	return a >= b ? a : b;
}

static void BadCharHeuristic(string str, int size, int* badChar) {
	int i;

	for (i = 0; i < 256; i++)
		badChar[i] = -1;

	for (i = 0; i < size; i++)
		badChar[(int)str[i]] = i;
}

static vector<int> SearchString(string str, string pat) {
	vector<int> retVal;
	int m = pat.length();
	int n = str.length();

	int* badChar = new int[256];

	BadCharHeuristic(pat, m, badChar);

	int s = 0;
	while (s <= (n - m)){
		int j = m - 1;
		while (j >= 0 && pat[j] == str[s + j])
			--j;
		if (j < 0){
			retVal.push_back(s);
			s += (s + m < n) ? m - badChar[str[s + m]] : 1;
		}
		else{
			s += Max(1, j - badChar[str[s + j]]);
		}
	}

	delete[] badChar;
	return retVal;
}

int main(){

    ifstream myfile("data.txt");
    string line;
    int currentLine=0;
    StartCounter();

    if(myfile.is_open()){
        while(getline(myfile,line)){
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

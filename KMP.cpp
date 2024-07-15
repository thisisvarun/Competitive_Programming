#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;

int main(){
    string text,pattern;
    cin>>text;
    cin>>pattern;
    int n = text.size();
    int m = pattern.size();
    int lps[m] = {0};
    int i = 0,j = 1;
    while (j<m){
        if (pattern[i] == pattern[j])lps[j++] = ++i;
        else if (i != 0)i = lps[i-1];
        else lps[j++] = 0;
    }
    int occurences = 0;
    i = j = 0;
    while (i<n){
        if (text[i] == pattern[j]){
            i++;
            j++;
            if (j == m){
                j = lps[j-1];
                occurences++;
            }
        }
        else if (j == 0)i++;
        else j = lps[j-1];
    }
    cout<< occurences <<endl;
}
/**

    find the longest common substring for two strings int O(n^2)

**/

#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;


///------------------- find longest common sub-string start -------------------///

string findLCS(string s1, string s2)
{

    int c[s1.size()+1][s2.size()+1] = {0};
    string b[s1.size()+1][s2.size()+1] = {""};

    // form the C and B matrixes
    for(int i=1;i<s1.size()+1;i++){

        for(int j=1;j<s2.size()+1;j++){

            if( s1[i-1] == s2[j-1] ){
                c[i][j] = c[i-1][j-1] + 1;
                b[i][j] = "up-left";
            }

            else{

                if( c[i-1][j] >= c[i][j-1] ){
                    c[i][j] = c[i-1][j];
                    b[i][j] = "up";
                }
                else{
                    c[i][j] = c[i][j-1];
                    b[i][j] = "left";
                }

            }

        }

    }

    string LCS = "";

    int row = s1.size(),col = s2.size();
    while(row>0&&col>0){

        if( b[row][col] == "up")
            row--;

        else if( b[row][col] == "left")
            col--;

        else if( b[row][col] == "up-left" ){

            LCS.push_back(s1[row-1]);

            row--;
            col--;

        }

    }

    // since the LCS was formed iteratively need to reverse the string
    reverse(LCS.begin(), LCS.end());

    return LCS;

}

///------------------- find longest common sub-string end -------------------///

void exec(){

    string s1 = "ABCBDAB", s2 = "BDCABA";

    cout<<"longest substring between '"<<s1<<"' & '"<<s2<<"' = "<<findLCS(s1, s2)<<"\n";

}


int main()
{
    exec();

    return 0;
}

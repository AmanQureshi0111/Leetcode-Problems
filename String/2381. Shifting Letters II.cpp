/*   TC-O(n) , SC-(26)
*/
#include<iostream>
#include<cmath>
#include<string>
#include<vector>
using namespace std;
class Solution {
public:
    string shiftingLetters(string s, vector<vector<int>>& shifts) {
        int n=s.length();
        vector<int> dir(n,0);
        //generate array from difference array
        for(auto &shift:shifts){
            if(shift[2]==0){
                dir[shift[0]]--;
                if(shift[1]+1<n) dir[shift[1]+1]++;
            }else{
                dir[shift[0]]++;
                if(shift[1]+1<n) dir[shift[1]+1]--;
            }
        }
        //take cummulative sum of array
        for(int i=1;i<n;i++){
            dir[i]=dir[i]+dir[i-1];
        }
        //make shift in between [0,25]
        for(int i=0;i<n;i++){
            dir[i]%=26;
            if(dir[i]<0) dir[i]+=26; // to make -ve number in between 0 to 25
        }
        //shift characters
        for(int i=0;i<n;i++){
            s[i]=((s[i]-'a')+dir[i])%26 +'a';
        }
        return s;
    }
};
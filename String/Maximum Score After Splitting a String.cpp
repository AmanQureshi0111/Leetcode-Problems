/*    Leetcode link: https://leetcode.com/problems/maximum-score-after-splitting-a-string/description/
*/
#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    int maxScore(string &s) {
        int n=s.length();
        int count_ones=0;
        for(char &ch:s){
            if(ch=='1') count_ones++;
        }
        int ans=0;
        int count_zeroes=0;
        for(int i=0;i<n-1;i++){
            if(s[i]=='0') count_zeroes++;
            else count_ones--;

            ans=max(count_ones+count_zeroes,ans);
        }
        return ans;
    }
};

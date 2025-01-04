/*  method-1 
    TC-O(n) SC-O(26)
*/
#include<iostream>
#include<string>
#include<unordered_map>
#include<unordered_set>
using namespace std;
class Solution {
public:
    int countPalindromicSubsequence(string s) {
        unordered_set<char> letters;
        for(char &ch:s) letters.insert(ch);
        int result=0;
        for(auto &ch:letters){
            int first_idx=-1;
            int last_idx=-1;
            for(int i=0;i<s.length();i++){
                if(s[i]==ch){
                    if(first_idx==-1){
                        first_idx=i;
                    }
                    last_idx=i;
                }
            }
            unordered_set<char> st;
            for(int middle=first_idx+1;middle<last_idx;middle++){
                st.insert(s[middle]);
            }
            result+=st.size();
        }
        return result;
    }
};
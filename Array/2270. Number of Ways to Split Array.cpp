/*   Cummulative sum
*/
#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int waysToSplitArray(vector<int>& nums) {
       long leftSum=0,rightSum=0,sum=0;
       int validSplit=0,n=nums.size();
       for(int &num:nums) sum+=num;
       for(int i=0;i<n-1;i++){
            leftSum+=nums[i];
            rightSum=sum-leftSum;
            if(leftSum>=rightSum) validSplit++;
       } 
       return validSplit;
    }
};
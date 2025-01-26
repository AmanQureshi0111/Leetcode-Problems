/*
    2127. Maximum Employees to Be Invited to a Meeting
Solved
Hard
Topics
Companies
Hint
A company is organizing a meeting and has a list of n employees, waiting to be invited. They have arranged for a large circular table, capable of seating any number of employees.

The employees are numbered from 0 to n - 1. Each employee has a favorite person and they will attend the meeting only if they can sit next to their favorite person at the table. The favorite person of an employee is not themself.

Given a 0-indexed integer array favorite, where favorite[i] denotes the favorite person of the ith employee, return the maximum number of employees that can be invited to the meeting.

 

Example 1:


Input: favorite = [2,2,1,2]
Output: 3
Explanation:
The above figure shows how the company can invite employees 0, 1, and 2, and seat them at the round table.
All employees cannot be invited because employee 2 cannot sit beside employees 0, 1, and 3, simultaneously.
Note that the company can also invite employees 1, 2, and 3, and give them their desired seats.
The maximum number of employees that can be invited to the meeting is 3. 
Example 2:

Input: favorite = [1,2,0]
Output: 3
Explanation: 
Each employee is the favorite person of at least one other employee, and the only way the company can invite them is if they invite every employee.
The seating arrangement will be the same as that in the figure given in example 1:
- Employee 0 will sit between employees 2 and 1.
- Employee 1 will sit between employees 0 and 2.
- Employee 2 will sit between employees 1 and 0.
The maximum number of employees that can be invited to the meeting is 3.
Example 3:


Input: favorite = [3,0,1,4,1]
Output: 4
Explanation:
The above figure shows how the company will invite employees 0, 1, 3, and 4, and seat them at the round table.
Employee 2 cannot be invited because the two spots next to their favorite employee 1 are taken.
So the company leaves them out of the meeting.
The maximum number of employees that can be invited to the meeting is 4.
 

Constraints:

n == favorite.length
2 <= n <= 105
0 <= favorite[i] <= n - 1
favorite[i] != i
*/
#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include<map>
#include<queue>
#include<stack>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#include<set>
using namespace std;

class Solution {
private:
    int BFS(int startNode,vector<vector<int>> &adj,vector<bool> &vis){
       int maxDis=0;
       queue<pair<int,int>> q;
       q.push({startNode,0});

       while(!q.empty()){
        auto [currNode,dist]=q.front();
        q.pop();
        for(auto ngbr:adj[currNode]){
            if(!vis[ngbr]){
                vis[ngbr]=true;
                maxDis=max(maxDis,dist+1);
                q.push({ngbr,dist+1});
            }
        }
       }
       return maxDis;
    }
public:
    int maximumInvitations(vector<int>& favorite) {
        int n=favorite.size();

        vector<vector<int>> adj(n);
        for(int i=0;i<n;i++){
            int u=i;
            int v=favorite[i];
            adj[v].push_back(u);
        }

        int happycoupleEmplCount=0;
        int maxCycleLength      =0;
        vector<bool> visited(n,false);

        for(int i=0;i<n;i++){
            if(!visited[i]){
                unordered_map<int,int> mp;
                int currNode=i;
                int currNodeLen=0;
                while(!visited[currNode]){
                    visited[currNode]=true;
                    mp[currNode]=currNodeLen;
                    int nextNode=favorite[currNode];
                    currNodeLen++;

                    if(mp.find(nextNode)!=mp.end()){
                        int cycleLength=currNodeLen-mp[nextNode];
                        maxCycleLength=max(maxCycleLength,cycleLength);
                        if(cycleLength==2){
                            vector<bool> vis(n,false);
                            vis[currNode]=true;
                            vis[nextNode]=true;
                            happycoupleEmplCount+= 2+BFS(currNode,adj,vis)+BFS(nextNode,adj,vis);
                        }
                        break;
                    }
                    currNode=nextNode;
                }
            }
        }
        return max(happycoupleEmplCount,maxCycleLength);
    }
};
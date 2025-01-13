/*  A parentheses string is a non-empty string consisting only of '(' and ')'. It is valid if any of the following conditions is true:

It is ().
It can be written as AB (A concatenated with B), where A and B are valid parentheses strings.
It can be written as (A), where A is a valid parentheses string.
You are given a parentheses string s and a string locked, both of length n. locked is a binary string consisting only of '0's and '1's. For each index i of locked,

If locked[i] is '1', you cannot change s[i].
But if locked[i] is '0', you can change s[i] to either '(' or ')'.
Return true if you can make s a valid parentheses string. Otherwise, return false.

 

Example 1:


Input: s = "))()))", locked = "010100"
Output: true
Explanation: locked[1] == '1' and locked[3] == '1', so we cannot change s[1] or s[3].
We change s[0] and s[4] to '(' while leaving s[2] and s[5] unchanged to make s valid.
Example 2:

Input: s = "()()", locked = "0000"
Output: true
Explanation: We do not need to make any changes because s is already valid.
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

//Approach-I
class Solution {
public:
    bool canBeValid(string s, string locked) {
        int n = s.length(); // Get the length of the string `s`.
        if (n % 2) return false; // If the length of the string is odd, it's impossible to balance parentheses.

        // Two stacks:
        // `open` - Stores indices of locked '(' characters.
        // `openClose` - Stores indices of unlocked characters ('0' in the `locked` string).
        stack<int> open, openClose;

        // First pass: Validate the balancing of ')' from left to right.
        for (int i = 0; i < n; i++) {
            if (locked[i] == '0') {
                // If the character is unlocked ('0'), add its index to the `openClose` stack.
                openClose.push(i);
            } else if (s[i] == '(') {
                // If the character is a locked '(' ('(' with corresponding locked[i] == '1'), add its index to `open`.
                open.push(i);
            } else {
                // For a locked ')', check if it can be matched.
                if (!open.empty()) {
                    // Prefer matching with a locked '('.
                    open.pop();
                } else if (!openClose.empty()) {
                    // Otherwise, match with an unlocked character.
                    openClose.pop();
                } else {
                    // If no matches are available, it's impossible to balance.
                    return false;
                }
            }
        }

        // Second pass: Resolve any unmatched locked '(' using unlocked characters from right to left.
        while (!open.empty() && !openClose.empty() && open.top() < openClose.top()) {
            // If the index of the unmatched locked '(' is before the index of the unlocked character,
            // match them and remove from the stacks.
            open.pop();
            openClose.pop();
        }

        // If there are no unmatched locked '(' left, the string can be valid.
        return open.empty();
    }
};

//Approach-II
class Solution {
public:
    bool canBeValid(string s, string locked) {
        int n = s.length();
        if (n % 2) return false; // A string with odd length cannot be balanced.

        int open = 0; // Count of open brackets during the forward pass.
        // First Pass: Validate balancing from left to right.
        for (int i = 0; i < n; i++) {
            // Treat unlocked characters ('0') as '(' temporarily and increment the count.
            if (s[i] == '(' || locked[i] == '0') open++;
            else open--; // Locked ')' decreases the open count.

            if (open < 0) return false; 
            // If `open` becomes negative, it means there are unmatched ')' 
            // that cannot be balanced even with unlocked characters.
        }

        int close = 0; // Count of close brackets during the backward pass.
        // Second Pass: Validate balancing from right to left.
        for (int i = n - 1; i >= 0; i--) {
            // Treat unlocked characters ('0') as ')' temporarily and increment the count.
            if (s[i] == ')' || locked[i] == '0') close++;
            else close--; // Locked '(' decreases the close count.

            if (close < 0) return false; 
            // If `close` becomes negative, it means there are unmatched '(' 
            // that cannot be balanced even with unlocked characters.
        }

        return true; 
        // If both passes are successful, the string can be valid.
    }
};

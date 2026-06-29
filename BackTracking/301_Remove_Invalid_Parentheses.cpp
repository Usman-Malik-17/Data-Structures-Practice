#include <bits/stdc++.h>
using namespace std;

/*
===============================================================================
                    LeetCode 301 - Remove Invalid Parentheses
===============================================================================

Difficulty : Hard

Problem:
Given a string containing parentheses and lowercase letters, remove the
minimum number of invalid parentheses to generate all possible valid strings.

-------------------------------------------------------------------------------
My Approach:

1. First, calculate the minimum number of parentheses that must be removed.
2. Use Backtracking (Take /Skip) to generate every possible string.
3. Maintain the number of unmatched opening parentheses using the variable
   'open'.
4. Only place ')' when there is already an unmatched '(' available.
5. At the leaf node, accept only those strings whose length equals:
       original_length - minimum_removals
   and whose open count becomes zero.
6. Skip consecutive duplicate parentheses in the remove branch to reduce
   duplicate recursive states.

-------------------------------------------------------------------------------
Why this approach?

Instead of generating every possible subset and validating them later,
the recursion keeps track of the current balance of parentheses.
Invalid branches are pruned early, making the search significantly more
efficient while still exploring every valid answer with minimum removals.

-------------------------------------------------------------------------------
Time Complexity:

Worst Case: O(2^n)

Space Complexity:

O(n)

-------------------------------------------------------------------------------
Concepts Used:

✔ Backtracking
✔ Recursion
✔ Pruning
✔ String Manipulation

-------------------------------------------------------------------------------
Author:
Muhammad Usman Malik

===============================================================================
*/

/*
===============================================================================
                            LeetCode 301 - Remove Invalid Parentheses
===============================================================================

Problem:
Given a string s containing parentheses and lowercase English letters,
remove the minimum number of invalid parentheses to make the string valid.

Return all possible valid strings after removing the minimum number of
invalid parentheses.

-------------------------------------------------------------------------------
Approach:
1. Calculate the minimum number of parentheses that must be removed.
2. Use Backtracking (Take / Skip) to generate all possible strings.
3. Maintain the number of unmatched opening parentheses (open).
4. A closing parenthesis ')' is only included if it has a matching '('.
5. At the leaf node:
   - The generated string length must equal:
         original_length - minimum_removals
   - All parentheses must be balanced (open == 0).
6. Skip consecutive duplicate parentheses in the remove branch to reduce
   duplicate recursive states.

-------------------------------------------------------------------------------
Time Complexity:
Worst Case: O(2^n)

Space Complexity:
O(n)
- Recursion stack
- Temporary string used during backtracking

Concepts Used:
- Backtracking
- Recursion
- Pruning
- String Manipulation

===============================================================================
*/

class Solution
{
public:
    // Calculate the minimum number of parentheses that must be removed
    int minimumRemoval(string &s)
    {
        int open = 0;
        int close = 0;

        for (char ch : s)
        {
            if (ch == '(')
            {
                open++;
            }
            else if (ch == ')')
            {
                if (open > 0)
                    open--;
                else
                    close++;
            }
        }

        return open + close;
    }

    void solve(const string &s,
               vector<string> &result,
               string &current,
               int index,
               int minRemoval,
               int open)
    {
        // Base Case
        if (index == s.size())
        {
            if (current.size() == s.size() - minRemoval && open == 0)
            {
                result.push_back(current);
            }
            return;
        }

        // -------------------- Take --------------------

        int newOpen = open;

        if (s[index] == '(')
        {
            current.push_back('(');
            solve(s, result, current, index + 1, minRemoval, newOpen + 1);
            current.pop_back();
        }
        else if (s[index] == ')')
        {
            if (newOpen > 0)
            {
                current.push_back(')');
                solve(s, result, current, index + 1, minRemoval, newOpen - 1);
                current.pop_back();
            }
        }
        else
        {
            current.push_back(s[index]);
            solve(s, result, current, index + 1, minRemoval, open);
            current.pop_back();
        }

        // -------------------- Skip --------------------

        if (s[index] == '(' || s[index] == ')')
        {
            while (index + 1 < s.size() && s[index] == s[index + 1])
                index++;

            solve(s, result, current, index + 1, minRemoval, open);
        }
    }

    vector<string> removeInvalidParentheses(string s)
    {
        vector<string> result;
        string current;

        int minRemoval = minimumRemoval(s);

        solve(s, result, current, 0, minRemoval, 0);

        return result;
    }
};

int main()
{
    Solution obj;

    vector<string> tests = {
        "()())()",
        "(a)())()",
        ")("};

    for (string s : tests)
    {
        cout << "Input : " << s << endl;
        cout << "Output:" << endl;

        vector<string> ans = obj.removeInvalidParentheses(s);

        for (string x : ans)
            cout << x << endl;

        cout << "--------------------------" << endl;
    }

    return 0;
}
/*
 * File Name    : programming_assignment_4.cpp
 *
 * Credit       : Course     - Graph Search, Shortest Paths, and Data Structures, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-05-31
 *
 * Description  : Programming Assignment 4 of this course
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream testcase("../../test_cases/02/2sum.txt");
    if (!testcase.is_open())
    {
        cout << "File could not be opened" << endl;
        return 0;
    }

    vector<long long> nums;
    long long x;
    while (testcase >> x)
    {
        nums.emplace_back(x);
    }
    unordered_set<int> valid_targets;
    int i = 0;
    int j = nums.size() - 1;
    sort(nums.begin(), nums.end());
    while(i < j){
        if (nums[i] + nums[j] < -10000) i++;
        else if (nums[i] + nums[j] > 10000) j--;
        else{
            for (int k = i; k < j; k++){
                if (nums[k] + nums[j] > 10000) break;
                if (nums[k] != nums[j]) valid_targets.insert(nums[k] + nums[j]);
            }
            j--;
        }
    }

    cout << valid_targets.size() << endl;
}

/*
 * File Name    : programming_assignment_1.cpp
 *
 * Credit       : Course     - Divide and Conquer, Sorting and Searching, and Randomized Algorithms, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-05-07
 *
 * Description  : Programming Assignment 1 - Implementation of Karatsuba Algorithm
 */

/* Question 1
 In this programming assignment you will implement one or more of the integer multiplication algorithms described in lecture.
 To get the most out of this assignment, your program should restrict itself to multiplying only pairs of single-digit numbers.  You can implement the grade-school algorithm if you want, but to get the most out of the assignment you'll want to implement recursive integer multiplication and/or Karatsuba's algorithm.
 So: what's the product of the following two 64-digit numbers?
 3141592653589793238462643383279502884197169399375105820974944592
 2718281828459045235360287471352662497757247093699959574966967627
 [TIP: before submitting, first test the correctness of your program on some small test cases of your own devising. Then post your best test cases to the discussion forums to help your fellow students!]
 [Food for thought: the number of digits in each input number is a power of 2.  Does this make your life easier?  Does it depend on which algorithm you're implementing?]
 The numeric answer should be typed in the space below.  So if your answer is 1198233847, then just type 1198233847 in the space provided without any space / commas / any other punctuation marks. 
 (We do not require you to submit your code, so feel free to use any programming language you want --- just type the final numeric answer in the following space.)
*/
#include <bits/stdc++.h>

using namespace std;

string stringaddition(string s1, string s2){
    int n1 = s1.size();
    int n2 = s2.size();
    string added = "";
    int i = n1 - 1;
    int j = n2 - 1;
    int carry = 0;
    while(i >= 0 || j >= 0){
        char ch1 = s1[i];
        char ch2 = s2[j];
        if (i < 0) ch1 = '0';
        if (j < 0) ch2 = '0';
        int temp = (ch1 - '0') + (ch2 - '0') + carry;
        int drop = temp % 10;
        carry = temp / 10;
        added = to_string(drop) + added;
        if (i >= 0) i--;
        if (j >= 0) j--;
    }
    if (carry != 0){
        added = to_string(carry) + added;
    }
    return added;
}
string karatsuba(string s1, string s2) {
    int n = s1.size();
    if (n <= 4) {
        long long p = stoll(s1);
        long long q = stoll(s2);
        return to_string(p * q);
    }
    string a = "", b = "", c = "", d = "";
    for (int i = 0; i < n / 2; i++) {
        a += s1[i];
        b = s1[n - 1 - i] + b;
        c += s2[i];
        d = s2[n - 1 - i] + d;
    }
    string ac = karatsuba(a, c);
    string bd = karatsuba(b, d);
    string ad = karatsuba(a, d);
    string bc = karatsuba(b, c);
    string nzeroes = "";
    string nhalfzeroes = "";
    for (int i = 0; i < n; i++) {
        nzeroes += '0';
        if (i < n / 2) nhalfzeroes += '0';
    }
    ac = ac + nzeroes;
    ad = ad + nhalfzeroes;
    bc = bc + nhalfzeroes;
    string result = stringaddition(ad, bc);
    string result2 = stringaddition(ac,bd);
    return stringaddition(result,result2);

}
int main() {
    ifstream testcase("../test_cases/Module1/karatsuba.txt"); //You can change the name of the file if you please.
    if(!testcase.is_open())
    {
        cout << "File failed to open" << endl;
        return 0;
    }
    string s1, s2;
    testcase >> s1 >> s2;
    cout << karatsuba(s1, s2);
}
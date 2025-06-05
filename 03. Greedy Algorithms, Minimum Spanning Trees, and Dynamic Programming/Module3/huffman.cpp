/*
 * File Name    : huffman.cpp
 *
 * Credit       : Course     - Greedy Algorithms, Minimum Spanning Trees, and Dynamic Programming, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-06-05
 *
 * Description  : Implementing Huffman's Algorithm
 */

#include <bits/stdc++.h>
using namespace std;
class Compare
{
public:
    bool operator()(pair<char, int> c1, pair<char, int> c2)
    {
        return c1.second > c2.second;
    }
};
vector<vector<int>> huffman(vector<pair<char, int>> &input)
{
    vector<vector<int>> tree;
    priority_queue<pair<char, int>, vector<pair<char, int>>, Compare> p;
    int n = input.size();
    unordered_map<char, int> mpp;
    for(int i = 0; i < n; i++){
        p.push(input[i]);
        mpp[input[i].first] = i;
    }
    int nodeCounter = -1;

    while(p.size() > 1){
        pair<char, int> p1 = p.top();
        p.pop();
        pair<char, int> p2 = p.top();
        p.pop();
        char newSymbol = nodeCounter;
        int newFreq = p1.second + p2.second;
        
        vector<int> node;
        
        int leftIndex = (p1.first < 0) ? p1.first : 
                       mpp[p1.first];
        int rightIndex = (p2.first < 0) ? p2.first : mpp[p2.first];
        
        node.push_back(leftIndex);
        node.push_back(rightIndex);
        tree.push_back(node);
        
        p.push({newSymbol, newFreq});
        
        nodeCounter--;
    }
    
    return tree;

}
void printHuffmanCodes(const vector<vector<int>>& tree, const vector<char>& originalChars, int node, string code) {
    int n = originalChars.size();
    if (node >= 0) {
        cout << originalChars[node] << ": " << code << endl;
        return;
    }
    int idx = -node - 1;
    if (idx >= tree.size()) return;
    printHuffmanCodes(tree, originalChars, tree[idx][0], code + "0");
    printHuffmanCodes(tree, originalChars, tree[idx][1], code + "1");
}

int main()
{
    vector<pair<char, int>> input = {
        {'A', 3}, {'B', 2}, {'C', 6}, {'D', 8}, {'E', 2}, {'F', 6}};

    vector<vector<int>> tree = huffman(input);
    vector<char> originalChars;
    for (auto& p : input) originalChars.push_back(p.first);

    int root = -tree.size();
    printHuffmanCodes(tree, originalChars, root, "");

}
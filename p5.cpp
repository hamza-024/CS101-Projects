#include<bits/stdc++.h>
using namespace std;

class TreeNode {
public:
    int value;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : value(x), left(nullptr), right(nullptr) {}
};

TreeNode* buildTree(vector<int>& level, vector<int>& in) {
    if (in.size() == 0) return nullptr;
    if (in.size() == 1) return new TreeNode(in[0]);

    vector<int> level1, level2, in1, in2;
    int i = 0;
    while (in[i] != level[0]) i++;

    for (int j = 0; j < i; ++j) in1.push_back(in[j]);
    for (int j = i+1; j < in.size(); ++j) in2.push_back(in[j]);

    for (int j = 1; j < level.size(); ++j) {
        if (find(in1.begin(), in1.end(), level[j]) != in1.end()) {
            level1.push_back(level[j]);
        } else {
            level2.push_back(level[j]);
        }
    }

    TreeNode *root = new TreeNode(level[0]);
    root->left = buildTree(level1, in1);
    root->right = buildTree(level2, in2);
    return root;
}

int main(int argc, char *argv[]){
    ifstream inorderFile(argv[1]);
    ifstream levelorderFile(argv[2]);
    ifstream encoding(argv[3]);

    vector<int> in,lvl;

    int c;
    while(inorderFile>>c) in.push_back(c);
    while(levelorderFile>>c) lvl.push_back(c);

    TreeNode * root = buildTree(lvl,in);

    TreeNode * it = root;
    char inp,d;
    string decoded= "";

    while(encoding>>inp){
        if(inp=='0') it=it->left;
        else it=it->right;
        if(it->value<128) {
            d=it->value;
            decoded+=d;
            it=root;
        }
    }
    cout<<decoded;
    return 0;
}

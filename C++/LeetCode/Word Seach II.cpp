// https://leetcode.com/problems/word-search-ii/

class Solution {
    class Trie {
    public:

        bool isleaf_;
        bool isprinted_;
        int idx;
        Trie* chars[26];

        Trie() {
            isleaf_ = 0;
            isprinted_ = 0;
            idx = 0;
            for (int i = 0; i < 26; ++i) chars[i] = nullptr;
        }

        void insert(string word, int idx) {
            Trie* node = this;
            for (int i = 0; i < (int)word.size(); ++i){
                if (node->chars[int(word[i]-'a')] == nullptr)
                    node->chars[int(word[i]-'a')] = new Trie();
                node = node->chars[int(word[i]-'a')];
            }
            node->isleaf_ = 1;
            node->idx = idx;
        }

        bool search(string word) {
            Trie* node = this;
            for (int i = 0; i < (int)word.size(); ++i){
                node = node->chars[int(word[i]-'a')];
                if (node == nullptr) return 0;
            }
            return node->isleaf_ && node->isprinted_;
        }

        bool startsWith(string prefix) {
            Trie* node = this;
            for (int i = 0; i < (int)prefix.size(); ++i){
                node = node->chars[int(prefix[i]-'a')];
                if (node == nullptr) return 0;
            }
            return 1;
        }

        bool charExist(char c){
            return chars[c-'a'] != nullptr;
        }
        
        int print(){ isprinted_ = 1; return idx;}
        
        bool isprinted(){ return isprinted_; }

        bool isleaf(){ return isleaf_; }

    };
    
    vector<string> res;
    
public:
    
    void search(Trie* node, vector<vector<bool>>& visit, int i, int j, int m, int n, vector<vector<char>>& board, vector<string>& words){
        
        if (!(i >= 0 && i < m && j >= 0 && j < n) || visit[i][j])
            return;
        
        node = node->chars[board[i][j]-'a'];
        if (node == nullptr) return;
        if (!node->isprinted() && node->isleaf()) res.push_back(words[node->print()]);
        
        visit[i][j] = 1;
        search(node, visit, i-1, j, m, n, board, words);
        search(node, visit, i+1, j, m, n, board, words);
        search(node, visit, i, j-1, m, n, board, words);
        search(node, visit, i, j+1, m, n, board, words);
        visit[i][j] = 0;
    }
    
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        
        Trie* root = new Trie();
        
        for (int i = 0; i < (int)words.size(); ++i) root->insert(words[i], i);
        
        int m = (int)board.size();
        int n = (int)board[0].size();
        
        vector<vector<bool>> visit(m, vector<bool>(n,0));

        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                search(root, visit, i, j, m, n, board, words);
        
        return res;
    }
};

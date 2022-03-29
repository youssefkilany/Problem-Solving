// https://leetcode.com/explore/challenge/card/june-leetcoding-challenge/540/week-2-june-8th-june-14th/3358/
/*
Design a data structure that supports all following operations in average O(1) time.

insert(val): Inserts an item val to the set if not already present.
remove(val): Removes an item val from the set if present.
getRandom: Returns a random element from current set of elements. Each element must have the same probability of being returned.
*/

class RandomizedSet {
    
    class Node{
    public:
        int val;
        int key;
        Node* nxt;
        Node(){
            val = -123456789;
            nxt = NULL;
        }
        
        Node(int x, int y){
            val = x;
            key = y;
            nxt = NULL;
        }
    };
    
    Node** hash;
    int* arr;
    int idx;
    const int MAXSIZE = 100000;
    
    int doHash(int x){
        return ((x % 99929)+99929)%99929;
    }
public:

    RandomizedSet() {
        arr = new int[MAXSIZE];
        hash = new Node*[MAXSIZE];
        idx = 0;
        for(int i = 0; i< MAXSIZE; ++i) hash[i] = NULL;
    }
    
    Node* lookUp(int val) {
        int hashVal = doHash(val);
        
        if (hash[hashVal] == NULL)
            return NULL;
        
        if (hash[hashVal]->val == val)
            return hash[hashVal];
        
        Node* node = hash[hashVal];
        for (; node->nxt != NULL; node = node->nxt)
            if(node->val == val)
                return node;

        return NULL;
    }

    bool insert(int val) {
        int hashVal = doHash(val);
        
        if (hash[hashVal] == NULL){
            hash[hashVal] = new Node(val, idx);
            arr[idx++] = val;
            return true;
        } else if (hash[hashVal]->val == val)
            return false;

        Node* node = hash[hashVal];
        for (; node->nxt != NULL; node = node->nxt)
            if(node->val == val)
                return false;

        node->nxt = new Node(val, idx);
        arr[idx++] = val;
        return true;
    }
    
    bool remove(int val) {
        int hashVal = doHash(val);

        Node* node = hash[hashVal];
        if (hash[hashVal] && hash[hashVal]->val == val){
            Node* nodeReplace = lookUp(arr[idx-1]);
            nodeReplace->key = hash[hashVal]->key;
            arr[hash[hashVal]->key] = arr[--idx];
            hash[hashVal] = NULL;
            return true;
        }
        
        for (Node* nodeNxt = node; nodeNxt != NULL; node = nodeNxt, nodeNxt = nodeNxt->nxt)
            if(nodeNxt->val == val){
                Node* nodeReplace = lookUp(arr[idx-1]);
                nodeReplace->key = nodeNxt->key;
                arr[nodeNxt->key] = arr[--idx];
                node->nxt = nodeNxt->nxt;
                return true;
            }
        return false;
    }
    
    int getRandom() {
        // srand((unsigned) time(0));
        return arr[rand()%idx];
    }
};

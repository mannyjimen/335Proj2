#include "File.hpp"
#include "FileTrie.hpp"
#include "FileAVL.hpp"


// ALL YOUR CODE SHOULD BE IN THIS FILE. NO MODIFICATIONS SHOULD BE MADE TO FILEAVL / FILE CLASSES
// You are permitted to make helper functions (and most likely will need to)
// You must declare them "inline" | declare & implement them at the top of this file, before query()
// Below query(), implement and document all methods declared in FileTrie.hpp

inline Node* getSupposed(int fileSize, Node* subroot){
    return subroot;
}


//PRE-ORDER Traverse through the tree. Already given start and end nodes.
inline void traverseWithPush(Node* start, Node* end, Node* root, std::vector<File*>& finalVector){
    Node* temp = root;
}
 
//helper function for prefix function
inline std::unordered_set<File*> FileTrieSearch(FileTrieNode* current, const std::string& prefix, std::string& currentString){
    //check if this->stored == prefix (will be base case for recursive function.)
    currentString = currentString + current->stored;
    if (currentString == prefix){
        return current->matching;
    }

    
}

inline char nextChar(FileTrieNode* currentTrieNode, const std::string& prefix, const std::string& currentString, int idk){
    char nextSupposed = prefix[currentString.size() + 1];
}



/**
 * @brief Retrieves all files in the FileAVL whose file sizes are within [min, max]
 * 
 * @param min The min value of the file size query range.
 * @param max The max value of the file size query range.
 * @return std::vector<File*> storing pointers to all files in the tree within the given range.
 * @note If the query interval is in descending order (ie. the given parameters min >= max), 
        the interval from [max, min] is searched (since max >= min)
 */
std::vector<File*> FileAVL::query(size_t min, size_t max) {
    std::vector<File*> finalVector;
    if (max < min) 
        std::swap(min, max); //will make min the smaller value if min > max
   

    // Node* startNode = ::getSupposed(min, root_); //get the node we should end at
    // Node* endNode = ::getSupposed(max, root_); //get the frist node we should start at 

    // traverseWithPush(startNode, endNode, root_, finalVector);
 
    // Your code here.
    return finalVector;
}

//Want to add file f to FileTrie
//thoughts

//add file to the root
//create new filetrienode with next char, add file to that, keep going until last letter
//go through the correct FileTrie node, and insert to that node.
//for adding, head->matching->insert

//auto node_next = root->next['x']
void FileTrie::addFile(File* f){
    const std::string& fname = f->getName();
    auto temp = head;
    for (char c : fname){
        c = tolower(c);
        temp->matching.insert(f);    
        if (temp->next[c]) //if does exist, make temp that
            temp = temp->next[c];
        else{ //next char doesnt exist
            FileTrieNode* newNode = new FileTrieNode(c);
            temp->next[c] = newNode;
            temp = temp->next[c];
        }
    }
}


//if the next node with the char doesnt exist, return the empty set
//once we get to the end of the prefix, return the matching set for where the temp pointer is at. 
std::unordered_set<File*> FileTrie::getFilesWithPrefix(const std::string& prefix) const{
    auto temp = head;
    // char nextChar = prefix[currentString.size() + 1];
    for (int i = 0; i < prefix.size(); i++){
        char c = tolower(prefix[i]);
        if (temp->next[c]){
            if (i == prefix.size() - 1)
                return temp->matching;
            temp = temp->next[c];
        }
        else{
            std::unordered_set<File*> emptySet;
            return emptySet;
        }
    }
}
#include "File.hpp"
#include "FileTrie.hpp"
#include "FileAVL.hpp"


// ALL YOUR CODE SHOULD BE IN THIS FILE. NO MODIFICATIONS SHOULD BE MADE TO FILEAVL / FILE CLASSES
// You are permitted to make helper functions (and most likely will need to)
// You must declare them "inline" | declare & implement them at the top of this file, before query()
// Below query(), implement and document all methods declared in FileTrie.hpp

inline void traversalPush(std::vector<File*>& finalVector, Node* root, size_t min, size_t max){
    for (auto x: root->files_)
        finalVector.push_back(x);
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

    traversalPush(finalVector, root_->left_, min, max);

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
    FileTrieNode* temp = head;
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

//if the next node with the char doesnt exist, return empty set of file pointers
//once we get to the end of the prefix, return the matching set for where the temp pointer is at. 
std::unordered_set<File*> FileTrie::getFilesWithPrefix(const std::string& prefix) const{
    std::unordered_set<File*> emptySet;
    
    FileTrieNode* temp = head;
    for (size_t i = 0; i < prefix.size(); i++){
        char c = tolower(prefix[i]);
        if (temp->next[c]){
            if (i == prefix.size() - 1)
                return temp->matching;
            temp = temp->next[c];
        }
        else
            return emptySet;
    }
    return emptySet;
}
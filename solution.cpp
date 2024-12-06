#include "File.hpp"
#include "FileTrie.hpp"
#include "FileAVL.hpp"


// ALL YOUR CODE SHOULD BE IN THIS FILE. NO MODIFICATIONS SHOULD BE MADE TO FILEAVL / FILE CLASSES
// You are permitted to make helper functions (and most likely will need to)
// You must declare them "inline" | declare & implement them at the top of this file, before query()
// Below query(), implement and document all methods declared in FileTrie.hpp

inline void traversalPush(std::vector<File*>& finalVector, Node* root, size_t min, size_t max){
    for (File* x: root->files_){
        if (x->getSize() >= min && x->getSize() <= max)
            finalVector.push_back(x);
    }
    if (root->left_)
        traversalPush(finalVector, root->left_, min, max);
    if (root->right_)
        traversalPush(finalVector, root->right_, min, max);
}

inline void fileVectorSort(std::vector<File*>& finalVector){
    //lets do bubblesort lol
    for (size_t j = 1; j < finalVector.size(); j++){
        for (size_t i = 0; i < finalVector.size() - j; ++i){
            if (finalVector[i]->getSize() > finalVector[i+1]->getSize())
                std::swap(finalVector[i], finalVector[i+1]);
        }       
    }
}

inline int IndexInNext(char c, std::vector<FileTrieNode*> mainVec){
    for (int i = 0; i < mainVec.size(); i++){
        FileTrieNode* x = mainVec[i];
        if (c == x->stored)
            return i;
    }
    return -1;
}

inline void destroyNodes(FileTrieNode* mainNode){
    for (FileTrieNode* x : mainNode->next)
        destroyNodes(x);
    delete mainNode;
    mainNode = nullptr;
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

    traversalPush(finalVector, root_, min, max);

    fileVectorSort(finalVector);

    return finalVector;
}

//Want to add file f to FileTrie
//thoughts
//add file to the root
//create new filetrienode with next char, add file to that, keep going until last letter
//go through the correct FileTrie node, and insert to that node.
//for adding, head->matching->insert

void FileTrie::addFile(File* f){
    const std::string& fname = f->getName();
    FileTrieNode* temp = head;
    temp->matching.insert(f); //insert to head (since inserting every file)
    for (char c : fname){
        c = tolower(c);
        if (IndexInNext(c, temp->next) == -1) //if does exist, make temp that
            temp->next.push_back(new FileTrieNode(c)); //making new node for next char
        temp = temp->next[IndexInNext(c, temp->next)];
        temp->matching.insert(f);
    }
}
//if the next node with the char doesnt exist, return empty set of file pointers
//once we get to the end of the prefix, return the matching set for where the temp pointer is at. 
std::unordered_set<File*> FileTrie::getFilesWithPrefix(const std::string& prefix) const{
    FileTrieNode* temp = head; //lets try to minimize this loop.  
    for (char c: prefix){ //using nicer looking for loop
        c = tolower(c);
        if (IndexInNext(c, temp->next) == -1)
            return {}; // return empty set if next char is not found
        temp = temp->next[IndexInNext(c, temp->next)];
    }
    return temp->matching;
}


FileTrie::~FileTrie(){
    destroyNodes(head);
}
#include "FileTrie.hpp"

FileTrie::FileTrie(){
    head = new FileTrieNode();
}

FileTrie::~FileTrie(){
}

int main(){
    File* first = new File("example.txt", "contents of first_file");
    File* second = new File("exemple.txt", "zzzzzcontents of second_file");
    File* third = new File("exertion.pdf", "zzzzzcontents of third_file");
    
    std::cout << first->getSize() << "\n";
    std::cout << second->getSize() << "\n";
    std::cout << third->getSize() << "\n";
    
    FileTrie mainTrie;

    std::cout << "Successfully made Trie\n";

    mainTrie.addFile(first);
    std::cout << "first added-------------\n";
    mainTrie.addFile(second);
    std::cout << "second added------------\n";
    mainTrie.addFile(third);
    std::cout << "third added------------\n";

    /*std::unordered_set<File*> mainSet = mainTrie.getFilesWithPrefix("exe");
    for (File* x : mainSet) {
        std::cout << x->getName() << "\n";*/
}
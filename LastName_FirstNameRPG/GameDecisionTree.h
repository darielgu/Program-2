#ifndef GAMEDECISIONTREE_H
#define GAMEDECISIONTREE_H
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Node.h"
#include "Story.h"

template <typename T>
class GameDecisionTree {
private:
    Node<T>* root;

public:
    GameDecisionTree() : root(nullptr) {}

    // Function to load story data from a text file and build the binary tree
    void loadStoryFromFile(const string& filename, char delimiter) {
        fstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening the file!";

        }
        string line;
        while (getline(file, line)){
            stringstream ss(line);
            int eventNum, leftEvent, rightEvent;
            string description;

            getline(ss,line,delimiter);
            eventNum = stoi(line);
            getline(ss,line,delimiter);
            description = line;
            getline(ss,line,delimiter);
            leftEvent = stoi(line);
            getline(ss,line,delimiter);
            rightEvent = stoi(line);

            Node<T>* newNode = new Node<T>(Story(description,eventNum,leftEvent,rightEvent));



//            nodes[eventNum] = node; declare a map
            if(eventNum ==1){
                root = newNode;
                continue;
            }

                Node<T>* current = root;

            while(current != nullptr){
                if(eventNum/2 == current->data.eventNumber){
                    if(eventNum % 2 == 0){
                        current->left = newNode;
                    }else{
                        current->right = newNode;
                    }
                    break;
                }else if (eventNum/2 < current->data.eventNumber) {
                    current = current->left;
                }
                else {
                    current = current->right;
                }
            }
        }
        file.close();

    }




    // Function to start the game and traverse the tree based on user input
    void playGame() {
        if(root == nullptr){
            cout<< "No Story loaded";
            return;
        }
        Node<T>* current = root;
        while(current){
            cout<<current->data.description << endl;
            if(current->left == nullptr || current->right == nullptr){
                cout<<"Game over story not written"<<endl;
                return;
            }
            char userInput;
            cout<<"Choose to go left or right by entering L for left or R for right"<<endl;
            cin>>userInput;
            if(userInput == 'L' || userInput == 'l'){
                current = current -> left;
            }else if(userInput == 'R' || userInput == 'r'){
                current = current -> right;
            }
        }

    }
};

#endif // GAMEDECISIONTREE_H

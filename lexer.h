#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <vector>
#include <algorithm>
#include "token.h"

using namespace std;

class Lex
{
public:
    //constructor
    Lex(vector<char> userInput);

    //deconstructor
    ~Lex();
    void printScr();
    Token getToken();
    vector<char> currInput;
private:

    // int classification [][2] =
    // {digit}


    // int TX[32][30] =

    // letter, digit, . , _ ,
    // S0{},
    // {};




};

Lex::Lex(vector<char> userInput){
    this->currInput = userInput;

}

// Deconstructor
Lex::~Lex(){
    cout << "Lexer Deconstructed";
}

void Lex:: printScr(){
    for(char i : currInput){
        if (i != ';'){
            cout << i;
        }
        else{
            cout << i << "\n";
        }

    }
}

Token Lex::getToken(){
    // -------------------------------------- Initialization --------------------------------------
    char thisChar;          // stores current char from user input
    bool eof = false;       // controls whether the end of the file is found or not
    int rowTX;              // stores which row in TX will be explored to get next state
    int currState = 0;      // will store current state (starting from 0 -> starting state)
    int charIndex = 0;          // loops through which character to take next
    stack<int> stack;       // will hold path from last accepting to current state
    string lexeme = "";     // holds token we're trying to find
    //push bad into stack
    stack.push(ERR);     // pushes ERR (100) first -> will remove char that causes error state later


    // -------------------------------------- Scanning --------------------------------------
    bool isAccepting;
    int toRem = 0;
    while(currState != ERR)
    {
        if(charIndex == currInput.size()){
            eof = true;
            goto endoffile;
        }
        // get next char
        thisChar = currInput[charIndex];
        charIndex += 1;
        toRem += 1;

        // add current char to lexeme
        lexeme += thisChar;


        // check if state is accepting - pop if yes
        isAccepting = (find(accepting.begin(), accepting.end(), currState) != accepting.end());

        if (isAccepting) {
            while(!stack.empty())
            {
                stack.pop();
            }
        }

        // push in current state to stack
        stack.push(currState);

        // Get next state
        // send to CAT -> get back classified
        rowTX = CAT(thisChar);
        currState = TX[currState][rowTX];

    }
    endoffile:
    if(eof) {
        stack.push(currState);
        this->currInput.erase(this->currInput.begin(), this->currInput.begin() + toRem);
    }
    else{
        this->currInput.erase(this->currInput.begin(), this->currInput.begin() + toRem - 1);
    }

    // -------------------------------------- Rollback --------------------------------------
    // get top state from stack
    int poppedState;
    poppedState = stack.top();
    //check that it's accepting
    bool acceptingBool;
    acceptingBool = (find(accepting.begin(), accepting.end(), currState) != accepting.end());

    while(!acceptingBool and poppedState != ERR){
        //get top state and pop it
        poppedState = stack.top();
        stack.pop();

        //truncate lexeme
        lexeme.pop_back();
//        thisChar-=1;

        //check if next state is accepting
        acceptingBool = (find(accepting.begin(), accepting.end(), poppedState) != accepting.end());
    }


    //-------------------------------------- Report Result --------------------------------------
    Token tok;

    if(acceptingBool){
        string type = getType(poppedState, lexeme);
        tok.token= lexeme;
        tok.type = type;
    }
    else{

    }

    return tok;

}


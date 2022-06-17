#include "parser.h"

vector<char> openFile(){

    vector<char> userInputLines;

    ifstream f("test.txt");

    if(f.is_open()){
        string currLine;
        while(getline(f,currLine)){
            for(char const &c: currLine)
            {
                userInputLines.push_back(c);
            }
        }
    }
    return userInputLines;
}

void getNextC(vector<char> input){
    static int nextCharP = -1;
    nextCharP += 1;
}

int main() {
    const char *space = " ";
    Token token;
    vector<char> userInput;
    vector<Token> tok;
    userInput = openFile();

    Lex lexer(userInput);

//    lexer.printScr();
    lexer.currInput;
    Parser p = Parser();

    while (!lexer.currInput.empty()) {
        token = lexer.getToken();
        if (token.token == " ") {
            continue;
        } else {
            tok.push_back(token);

//        cout << token.token << "\n";
        }


        cout << endl << endl;

        // open file
        // int state = 0;
        // int exit = 50;
        // while(state!= exit){
        //     // get next char

        //     //append char to lex
        // }
    }
    p.tok = tok;
    p.GetNextToken(true);

    for (Token t: p.tok) {
        cout << "<" << t.token << ", " << t.type << ">" << endl;
    }

    bool firstSt = true;
    int statementCnt = 0;
    while(p.tokPtr != tok.size()-1){
        statementCnt++;
        cout << "\n\n" << "Statement " << statementCnt << "\n";
        if(firstSt == true){
            p.statement();
            firstSt = false;
        }
        else{
            p.GetNextToken(false);
            p.statement();

            }

        }

    }



#include "lexer.h"

class Parser{
public:
    Parser();
    ~Parser();

    vector<Token> tok;
    int tokPtr = -1;
    void GetNextToken(bool first);
    void assignmentStatement();
    void expression();
    void simpleExpression();
    void subExpression();
    void term();
    void factor();
    void literal();
    void functionCall();
    void actualParams();
    void varDec();
    void statement();
    void printStatement();
    void ifStatement();
    void forStatement();
    void whileStatement();
    void returnStatement();
    void functionDec();
    void block();

    Token currToken = Token();
    Token LLToken1 = Token();
};

Parser::Parser(){
}
Parser::~Parser(){}
void Parser::GetNextToken(bool first) {
    if (!first) {
        this->currToken = this->LLToken1;
        if(tokPtr == this->tok.size()-1){

        }
        else{
            this->tokPtr++;
            this->LLToken1 = this->tok[tokPtr];
        }

    } else {
        this->tokPtr++;
        this->currToken = this->tok[tokPtr];
        if(this->tok.size() >= 2) {
            this->tokPtr++;
            this->LLToken1 = this->tok[tokPtr];
        }
    }
}

void Parser::assignmentStatement(){
    string id = this->currToken.token;
    this->GetNextToken(false);
    if(this->currToken.type != "ASSIGN"){
        throw runtime_error("Assignment expected equals");
    }
    this->GetNextToken(false);
    this -> expression();

    cout << "==============================" << " \n";
    cout << "assignment statement parsed" << "\n";
}

void Parser:: expression(){
    this -> simpleExpression();
//    this->GetNextToken(false);
    while(this->LLToken1.type == "REL_OP"){
        this->GetNextToken(false);
        this->GetNextToken(false);
        this->simpleExpression();
    }

    cout << "==============================" << " \n";
    cout << "expression parsed" << "\n";
}

void Parser:: simpleExpression(){
    this->term();
//    this->GetNextToken(false);

    while(this->LLToken1.type == "ADD_OP"){
        this->GetNextToken(false);
        this->GetNextToken(false);
        this->term();
    }

    cout << "==============================" << " \n";
    cout << "simple expression parsed" << "\n";
}

void Parser:: term(){
    int multOp_Cnt = 0;
    this->factor();
//    this->GetNextToken(false);
//    while(this->currToken.type == "MULT_OP"){
      while(this->LLToken1.type == "MULT_OP"){
          multOp_Cnt ++;
          this->GetNextToken(false);
          this->GetNextToken(false);
          this->factor();
    }

    cout << "term parsed" << "\n";
}

void Parser:: factor(){
    if(this->currToken.type == "BOOLEAN_LIT" or this->currToken.type == "INT_LITERAL" or this->currToken.type == "FLOAT_LITERAL" or this->currToken.type == "CHAR_LITERAL"){
        this->literal();
    }
    else if(this->currToken.type == "IDENTIFIER"){
        if(this-> LLToken1.type == "LCIRCLEB"  ){
            this->GetNextToken(false);
            this->GetNextToken(false);
            this->functionCall();
        }
        else{
            cout << "==============================" << " \n";
            cout << "Identifier parsed" << "\n";
        }
    }
    else if(this->currToken.type == "LCIRCLEB"){
        this->GetNextToken(false);
        this->subExpression();

        cout << "==============================" << " \n";
        cout << "Sub-expression parsed" << "\n";

    }
    else if (this->currToken.token == "not" or this->currToken.token == "!"){
        //this->Unary()
        this->expression();

        cout << "==============================" << " \n";
        cout << "Unary parsed" << "\n";
    }
    else{
        throw runtime_error("No factor found");
    }

    cout << "==============================" << " \n";
    cout << "factor parsed" << "\n";

}

void Parser::functionCall(){

    this->actualParams();
    this->GetNextToken(false);

    // check for right circle bracket
    if(this->currToken.type != "RCIRCLEB") {
        throw runtime_error("Function call, expected right bracket");
    }
}

void Parser::actualParams(){
    this->expression();

    this->GetNextToken(false);
    if(this->currToken.type == ",") {
        this->GetNextToken(false);
        this->expression();
    }
}

void Parser:: subExpression(){
    this->expression();
    this->GetNextToken(false);

    if(this->currToken.type != "RCIRCLEB") {
        throw runtime_error("Sub-expression, right bracket not found");
    }

}


void Parser:: literal(){
    if(this->currToken.type == "BOOLEAN_LIT"){
        cout << "==============================" << " \n";
        cout << "bool lit parsed" << "\n";
    }
    else if(this->currToken.type == "INT_LITERAL"){
        cout << "==============================" << " \n";
        cout << "int lit parsed" << "\n";
    }
    else if(this->currToken.type == "FLOAT_LITERAL"){
        cout << "==============================" << " \n";
        cout << "float lit parsed" << "\n";
    }
    else{
        cout << "==============================" << " \n";
        cout << "char lit parsed" << "\n";
    }

    cout << "==============================" << " \n";
    cout << "literal parsed" << "\n";
}

void Parser:: statement(){
    if(this->currToken.type == "LET"){
        this->GetNextToken(false);
        this->varDec();

        //check for semi-colon
        this->GetNextToken(false);
        if(this->currToken.type != "SEMIC"){
            throw runtime_error("Statement error expected semi-colon");
        }
        cout << "==============================" << " \n";
        cout << "variable declaration parsed" << "\n";
    }

    else if(this->currToken.type == "IDENTIFIER"){
        this->assignmentStatement();
    }

    else if(this->currToken.type == "PRINT"){
        this->GetNextToken(false);
        this->printStatement();

        //check for semi-colon
        this->GetNextToken(false);
        if(this->currToken.type != "SEMIC"){
            throw runtime_error("Statement error expected semi-colon");
        }

        cout << "==============================" << " \n";
        cout << "print statement parsed" << "\n";

    }
    else if(this->currToken.type == "IF"){
        this->GetNextToken(false);
        this->ifStatement();

        cout << "==============================" << " \n";
        cout << "if statement parsed" << "\n";

    }
    else if(this->currToken.type == "FOR"){
        // two get next token - skip over let of variable declaration
        this->GetNextToken(false);
        this->forStatement();

        cout << "==============================" << " \n";
        cout << "for loop parsed" << "\n";
    }
    else if(this->currToken.type == "WHILE"){
        this->GetNextToken(false);
        this->whileStatement();

        cout << "==============================" << " \n";
        cout << "while statement parsed" << "\n";
    }
    else if(this->currToken.type == "RETURN"){
        this->GetNextToken(false);
        this->returnStatement();

        //check for semi-colon
        this->GetNextToken(false);
        if(this->currToken.type != "SEMIC"){
            throw runtime_error("Statement error expected semi-colon");
        }
        cout << "==============================" << " \n";
        cout << "return parsed" << "\n";
    }
    else if(this->currToken.type == "FUNCTION"){
        this->GetNextToken(false);
        this->functionDec();

        cout << "==============================" << " \n";
        cout << "function declaration parsed" << "\n";
    }
    else if(this->currToken.type == "LCURLYB" ){
        this->GetNextToken(false);
        this->block();

        cout << "==============================" << " \n";
        cout << "block statement parsed" << "\n";
    }
    else{

    }

    cout << "==============================" << " \n";
    cout << "Statement parsed" << "\n";
}

void Parser::varDec(){
    string idName = this->currToken.token;
    this->GetNextToken(false);
    if(this->currToken.type != "COLON"){
        throw runtime_error("Variable declaration expected colon");
    }
    this->GetNextToken(false);
    if(this->currToken.type != "TYPE"){
        throw runtime_error("Variable declaration expected type");
    }
    this->GetNextToken(false);
    if(this->currToken.type != "ASSIGN"){
        throw runtime_error("Variable declaration expected equals");
    }

    this->GetNextToken(false);
    this->expression();

}

void Parser::printStatement() {
    this->expression();
}

void Parser::ifStatement() {
    if(this->currToken.type != "LCIRCLEB"){
        throw runtime_error("If statement expected left bracket");
    }
    this->GetNextToken(false);
    this->expression();

    this->GetNextToken(false);
    if(this->currToken.type != "RCIRCLEB"){
        throw runtime_error("If statement expected right bracket");
    }

    this->GetNextToken(false);
    this->block();

    this->GetNextToken(false);
    if(this->currToken.token == "else"){
        this->block();
    }

}

void Parser::forStatement() {
    //check for left bracket
    if(this->currToken.type != "LCIRCLEB"){
        throw runtime_error("If statement expected left bracket");
    }

    //check for var. declaration
    this->GetNextToken(false);
    if(this->currToken.type != "LET"){
        throw runtime_error("Expected variable declaration");
    }
    this->GetNextToken(false);
    this->varDec();

    //check for semi-colon
    this->GetNextToken(false);
    if(this->currToken.type != "SEMIC"){
        throw runtime_error("Expected semi-colon");
    }

    //check for expression
    this->GetNextToken(false);
    this->expression();

    //check for semi-colon
    this->GetNextToken(false);
    if(this->currToken.type != "SEMIC"){
        throw runtime_error("Expected semi-colon");
    }

    //check for assignment
    this->GetNextToken(false);
    this->assignmentStatement();

    //check for right bracket
    this->GetNextToken(false);
    if(this->currToken.type != "RCIRCLEB"){
        throw runtime_error("If statement expected right bracket");
    }

    //check for block
    this->GetNextToken(false);
    if(this->currToken.type != "LCURLYB"){
        throw runtime_error("block in if statement expected right bracket");
    }

    this->block();

}

void Parser::whileStatement() {
    // check for left bracket
    if(this->currToken.type != "LCIRCLEB"){
        throw runtime_error("If statement expected left bracket");
    }

    // check for assignment
    this->GetNextToken(false);
    this->expression();

    // check for right bracket
    this->GetNextToken(false);
    if(this->currToken.type != "RCIRCLEB"){
        throw runtime_error("If statement expected right bracket");
    }
    this->GetNextToken(false);
    if(this->currToken.type != "LCURLYB") {
        //check for block
        this->GetNextToken(false);
        this->block();
    }

}

void Parser::returnStatement() {
    this->expression();
}

void Parser::functionDec() {
    string idFuncName = this->currToken.token;

    //check for left bracket
    this->GetNextToken(false);
    if(this->currToken.type != "LCIRCLEB"){
        throw runtime_error("Function declaration expected left bracket");
    }

    //check for parameter & right bracket
    this->GetNextToken(false);
    while(this->currToken.type != "RCIRCLEB"){
        this->GetNextToken(false);
        //params??
    }

    //check for arrow
    this->GetNextToken(false);
    if(this->currToken.type != "ARROW"){
        throw runtime_error("Function declaration expected arrow");
    }

    //check for type
    this->GetNextToken(false);
    if(this->currToken.type != "TYPE"){
        throw runtime_error("Function declaration expected type");
    }

    //check for block
    this->GetNextToken(false);
    this->block();


}

void Parser::block() {
    this->statement();
    this->GetNextToken(false);
    if(this->currToken.type != "RCURLYB"){
        throw runtime_error("Function declaration expected right curly bracket");
    }

};


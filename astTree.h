#include <string>
#include <memory>
#include <vector>
using namespace std;
enum OP{
    PLUS,
    MINUS,
    AND,
    MULT,
    DIV,
    OR,
    GTHAN,
    STHAN,
    EQUAL,
    GTHANE,
    STHANE,
    NOTEQUAL,
    NOT
};

enum TYPE{
    INT,
    FLOAT,
    BOOL,
    CHAR
};
class Node{

};

class Statement: Node{

};

class Expression: Node{

};

class Block: Statement{

};

class Lit{

};


class BooleanLit: Lit{
    BooleanLit();
    ~BooleanLit();
   bool boolean;
};

class IntegerLit: Lit{
    IntegerLit();
    ~IntegerLit();
    int num;

};

class FloatLit: Lit{
    FloatLit();
    ~FloatLit();
    float num;
};

class CharLit: Lit{
    CharLit();
    ~CharLit();
    char character;
};


class Identifier: Expression{
    string id;
};

class MultOp: Expression{
    shared_ptr<Expression>FirstOp;
    shared_ptr<Expression>SecondOp;
    OP op;

};

class AddOp: Expression{
    shared_ptr<Expression>FirstOp;
    shared_ptr<Expression>SecondOp;
    OP op;
};

class RelOp: Expression{
    shared_ptr<Expression>FirstOp;
    shared_ptr<Expression>SecondOp;
    OP op;
};

class FuncCall: Expression{
    shared_ptr<Identifier>FnName;
    vector<shared_ptr<Expression>> aParams;
};

class Unary: Expression{
    shared_ptr<Expression>FirstOp;
    OP op;
};

class Assignment: Statement{
    shared_ptr<Identifier> id;
    shared_ptr<Expression> expr;
};

class VarDec: Statement{
    shared_ptr<Identifier> id;
    TYPE type;
    shared_ptr<Expression> expr;
};

class PrintStatement: Statement{
    shared_ptr<Expression> toPrint;
};

class RtrnStatement: Statement{
    shared_ptr<Expression> toReturn;
};

class IfStatement: Statement{
    shared_ptr<Expression> expr;
    shared_ptr<Block> ifBlock;
    shared_ptr<Block> elseBlock;
};

class ForStatement: Statement{
    shared_ptr<VarDec> firstVar;
    shared_ptr<Expression> condition;
    shared_ptr<Assignment> updateVar;
    shared_ptr<Block> block;
};

class WhileStatement: Statement{
    shared_ptr<Expression> condition;
    shared_ptr<Block> block;
};

class FormalParam: Node{
    shared_ptr<Identifier> paramName;
    TYPE type;

};

class FunctionDec: Statement{
    shared_ptr<Identifier> fnName;
    vector<shared_ptr<FormalParam>> fParams;
    TYPE type;
    shared_ptr<Identifier> Block;
};

class Program: Node{
    vector<shared_ptr<Statement>> statements;
};
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <vector>
#include <algorithm>
#include "main.h"
using namespace std;

class Token
{
public:
    Token();
    string token;
    string type;
    ~Token();
};

Token::Token() {
    token = "";
    type = "";
}

Token::~Token(){

}
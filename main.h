#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <memory>
using namespace std;


int states = 32;
int transitions = 30;
enum States{
    ERR = 100
};

// Transition Table
int TX[35][22] =
 {
     //     digit      letter         .          _          '             = ,       <,          >,          !,          /,           *,         - ,              +          ;           :             {,       },           (,          ),            [,              ]     (space)
     {  1,      3,      ERR,    3,     4,       7 ,     9,      11,     13,     15,     21,     22,     24,     25,     26,    27,      28,     29,     30,     31,     32 , 33},
     {  1,      ERR,    2,      ERR,   ERR,     ERR,   ERR,     ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR, ERR},
     {  34,      ERR,    ERR,    ERR,   ERR,     ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR, ERR, },
     {  3,      3,      ERR,    3,     ERR,     ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR, ERR},
     {  5,      5,      5,      5,     ERR,     5,      5,      5,      5,      5,      55,     5,      5,      5,      5,      5,      5,      5,      5,      5,      5  , ERR},
     {  ERR,    ERR,    ERR,    ERR,   6,       ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR, ERR},
     {  ERR,    ERR,    ERR,    ERR,   ERR,     ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR, ERR},
     {  ERR,    ERR,    ERR,    ERR,   ERR,     8,      ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR, ERR},
     {  ERR,    ERR,    ERR,    ERR,   ERR,     ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR, ERR},
     {  ERR,    ERR,    ERR,    ERR,   ERR,     10,     ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR, ERR},
     { ERR,    ERR,    ERR,    ERR,   ERR,     ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR, ERR},
     { ERR,    ERR,    ERR,    ERR,   ERR,     12,     ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR, ERR},
     { ERR,    ERR,    ERR,    ERR,   ERR,     ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR, ERR},
     { ERR,    ERR,    ERR,    ERR,   ERR,     14,     ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR, ERR},
     { ERR,    ERR,    ERR,    ERR,   ERR,     ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR, ERR},
     { ERR,    ERR,    ERR,    ERR,   ERR,     ERR,    ERR,    ERR,    ERR,    16,     17,     ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR, ERR},
     { ERR,    ERR,    ERR,    ERR,   ERR,     ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR, ERR},
     { 18,     18,     18,     18,    18,      18,      18,    18,     18,     18,     19,     18,     18,     18,     18,     18,     18,     18,     18,     18,     18 , ERR},
     { 18,     18,     18,     18,    18,      18,      18,    18,     18,     18,     19,     18,     18,     18,     18,     18,     18,     18,     18,     18,     18,  ERR},
     { 18,     18,     18,     18,    18,      18,      18,    18,     18,     20,     18,     18,     18,     18,     18,     18,     18,     18,     18,     18,     18,  ERR},
     { ERR,    ERR,    ERR,    ERR,   ERR,     ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR, ERR},
     { ERR,    ERR,    ERR,    ERR,   ERR,     ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR, ERR},
     { ERR,    ERR,    ERR,    ERR,   ERR,     ERR,    ERR,    23,     ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR, ERR},
     { ERR,    ERR,    ERR,    ERR,   ERR,     ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR, ERR},
     { ERR,    ERR,    ERR,    ERR,   ERR,     ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR, ERR},
     { ERR,    ERR,    ERR,    ERR,   ERR,     ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR, ERR},
     { ERR,    ERR,    ERR,    ERR,   ERR,     ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR, ERR},
     { ERR,    ERR,    ERR,    ERR,   ERR,     ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR, ERR},
     { ERR,    ERR,    ERR,    ERR,   ERR,     ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR, ERR},
     { ERR,    ERR,    ERR,    ERR,   ERR,     ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR, ERR},
     { ERR,    ERR,    ERR,    ERR,   ERR,     ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR, ERR},
     { ERR,    ERR,    ERR,    ERR,   ERR,     ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR, ERR},
     { ERR,    ERR,    ERR,    ERR,   ERR,     ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR, ERR},
     { ERR,    ERR,    ERR,    ERR,   ERR,     ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR, ERR},
     { 34,     ERR,    ERR,    ERR,   ERR,     ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR,    ERR, ERR}

 };

 // Accepting states
 vector<int> accepting = {1, 3, 4, 6, 7, 8, 9, 10, 11, 12, 14, 15, 16, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34};


 // CAT
const char *quote = "'"; //to check for single quote mark (can't work with ' ' ' or " ' ")

// function takes in current char and returns classified column in TX
int CAT(char currChar)
{
    if(isdigit(currChar)){
        return 0;
    }
    else if (isalpha(currChar)){
        return 1;
    }
    else if (currChar == '.'){
        return 2;
    }
    else if (currChar == '_'){
        return 3;
    }
    else if (currChar == *quote){
        return 4;
    }
    else if (currChar == '='){
        return 5;
    }
    else if (currChar == '<'){
        return 6;
    }
    else if (currChar == '>'){
        return 7;
    }
    else if (currChar == '!'){
        return 8;
    }
    else if (currChar == '/'){
        return 9;
    }
    else if (currChar == '*'){
        return 10;
    }
    else if (currChar == '-'){
        return 11;
    }
    else if (currChar == '+'){
        return 12;
    }
    else if (currChar == ';'){
        return 13;
    }
    else if (currChar == ':'){
        return 14;
    }
    else if (currChar == '{'){
        return 15;
    }
    else if (currChar == '}'){
        return 16;
    }
    else if (currChar == '('){
        return 17;
    }
    else if (currChar == ')'){
        return 18;
    }
    else if (currChar == '['){
        return 19;
    }
    else if (currChar == ']'){
        return 20;
    }
    else if (currChar == ' '){
        return 21;
    }
    else{
        return ERR;
    }
}

string st;
string getType(int st, string token){
    if(st == 15 or st == 21 or token == "and"){
        return "MULT_OP";
    }
    else if(st == 16){
        return "SINGLECOMMENT";
    }
    else if(st == 20){
        return "MULTICOMMENT";
    }
    else if(st == 22 or st == 24 or token == "or"){
        return "ADD_OP";
    }
    else if(st == 23){
        return "ARROW";
    }
    else if(st == 25){
        return "SEMIC";
    }
    else if(st == 26){
        return "COLON";
    }
    else if (st == 27){
        return "LCURLYB";
    }
    else if(st == 28){
        return "RCURLYB";
    }
    else if(st == 29){
        return "LCIRCLEB";
    }
    else if(st == 30){
        return "RCIRCLEB";
    }
    else if(st == 31){
        return "LSQB";
    }
    else if (st == 32){
        return "RSQB";
    }
    else if(st == 33){
        return "SPACE";
    }
    else if(token == "float" or token == "int" or token == "bool" or token == "char"){
        return "TYPE";
    }
    else if(token == "true" or token == "false"){
        return "BOOLEAN_LIT";
    }
    else if(token == "let"){
        return "LET";
    }
    else if(token == "print"){
        return "PRINT";
    }
    else if(token == "return"){
        return "RETURN";
    }
    else if(token == "if"){
        return "IF";
    }
    else if (token == "for"){
        return "FOR";
    }
    else if(token == "while"){
        return "WHILE";
    }
    else if(token == "fn"){
        return "FUNCTION";
    }
    else if(st == 1){
        return "INT_LITERAL";
    }
    else if (st == 34){
        return "FLOAT_LITERAL";
    }
    else if(st == 3){
        return "IDENTIFIER";
    }
    else if(st == 4){
        return "LAPO";
    }
    else if(st == 6){
        return "CHAR_LITERAL";
    }
    else if(st == 7){
        return "ASSIGN";
    }
    else if(st == 8 or st == 9 or st == 10 or st == 11 or st == 12 or st == 14){
        return "REL_OP";
    }


    else{
        return "";
    }

}
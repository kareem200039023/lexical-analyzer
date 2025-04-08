#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>

using namespace std;

// Global declarations
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
ifstream in_fp; // input file stream

// Character classes
enum { LETTER = 0, DIGIT = 1, UNKNOWN = 99, EOF_CLASS = -1 };

// Token codes
enum {
    INT_LIT = 10, IDENT = 11, ASSIGN_OP = 20, ADD_OP = 21, SUB_OP = 22,
    MULT_OP = 23, DIV_OP = 24, LEFT_PAREN = 25, RIGHT_PAREN = 26
};

// Function declarations
void addChar();
void getChar();
void getNonBlank();
int lex();
int lookup(char ch);

// lookup - a function to lookup operators and parentheses and return the token
int lookup(char ch) {
    switch (ch) {
    case '(':
        addChar();
        nextToken = LEFT_PAREN;
        break;
    case ')':
        addChar();
        nextToken = RIGHT_PAREN;
        break;
    case '+':
        addChar();
        nextToken = ADD_OP;
        break;
    case '-':
        addChar();
        nextToken = SUB_OP;
        break;
    case '*':
        addChar();
        nextToken = MULT_OP;
        break;
    case '/':
        addChar();
        nextToken = DIV_OP;
        break;
    default:
        addChar();
        nextToken = EOF;  // Unknown character
        break;
    }
    return nextToken;
}

// addChar - a function to add nextChar to lexeme
void addChar() {
    if (lexLen < 99) {  // leave space for '\0'
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = '\0';
    }
    else {
        cout << "Error - lexeme is too long" << endl;
    }
}

// getChar - a function to get the next character of input and determine its character class
void getChar() {
    if (in_fp.get(nextChar)) {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    }
    else {
        charClass = EOF;
    }
}

// getNonBlank - a function to call getChar until it returns a non-whitespace character
void getNonBlank() {
    while (isspace(nextChar))
        getChar();
}

// lex - a simple lexical analyzer for arithmetic expressions
int lex() {
    lexLen = 0;
    getNonBlank();
    switch (charClass) {
        // Parse identifiers
    case LETTER:
        addChar();
        getChar();
        while (charClass == LETTER || charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = IDENT;
        break;
        // Parse integer literals
    case DIGIT:
        addChar();
        getChar();
        while (charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = INT_LIT;
        break;
        // Parentheses and operators
    case UNKNOWN:
        lookup(nextChar);
        getChar();
        break;
        // EOF
    case EOF:
        nextToken = EOF;
        strcpy(lexeme, "EOF");
        break;
    default:
        nextToken = EOF;
        strcpy(lexeme, "EOF");
        break;
    }
    cout << "Next token is: " << nextToken << ", Next lexeme is " << lexeme << endl;
    return nextToken;
}

int main() {
    in_fp.open("front.in");
    if (!in_fp.is_open()) {
        cout << "ERROR - cannot open front.in" << endl;
        return 1;
    }

    getChar();
    do {
        lex();
    } while (nextToken != EOF);
    string inputt;
    cin >> inputt;

    in_fp.close();
    return 0;
}
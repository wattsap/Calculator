/*
 * 1) Yes, after testing thoroughly I believe that the calculator obeys the
 * precedence rules.
 * 
 * 2) I believe the grammar is able to work this way because of the reursive
 * tree that is formed through the methods. stepping through, it looks like 
 * this:
 * Expr = + and -, calls term
 * Term = * and /, calls factor
 * factor = ( and ), calls number
 * number = base number
 *
 * by this logic, the base number is operated on first by factor which splits
 * the input into parenthesized units if it finds a (. Then it is operated
 * on by term, which handles any multiplication and division that has been 
 * entered. then it is operated on my expr, which handles any addition or 
 * subtraction that has been entered. I believe that the heirarchy of the 
 * recursive tree built by this program as described above is what allows
 * this calculator to obey precedence rules used normally in c++.
 */
#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;
void error();
void match(char& curr);
double Expr(char& curr);
double Term(char& curr);
double Factor(char& curr);
double Number(char& curr);

/*
 * main method.
 * says if string is in language or says error
 */
int main(void) {
    double result;
    char curr;
    cout << "Enter a sequence to calculate: ";
    cin.get(curr);
    result = Expr(curr);
    if (curr == '\n') {
        cout << "Expression evaluates to " << result << endl;
    } else {
        error();
        cout << "main" <<endl;
    }
    return 0;
}
/*
 * print an error if incorrect
 * modified to remove exit(i) and inserted
 * print statements under every call to error
 * to debug and see exactly which method was 
 * throwing a "syntax error" from error method
 * being reached.
 */
void error() {
    cout << "syntax error" << endl;
   // exit(1);
}

/*
 * takes lookahead character as input
 */
void match(char lookahead, char& curr) {
    if (curr == lookahead)
        cin.get(curr);
    else {
         error();
         cout <<"Match"<<endl;
    }
}

/*
 * expr -> F Term G
 */
double Expr(char& curr) {
    bool negative = false;
    double result;
    if (curr == '+' || curr == '-'){
        if (curr == '-'){
            negative = true;
        }
        match(curr, curr);
    }
    result = Term(curr);
    if (negative) result = -result;
    while (curr == '+' || curr == '-'){
        if (curr == '+'){
            match('+', curr);
            result = result + Term(curr);
        } else {
            match('-', curr);
            result = result - Term(curr);
        }
    }
    return result;
}
/*
 *Term -> Factor H
 */
double Term(char& curr) {
    double result = Factor(curr);
    while (curr == '/' || curr == '*') {
        if (curr == '/') {
            match('/', curr);
            result = result / Factor(curr);
        } else {
            match('*', curr);
            result = result * Factor(curr);
        }
    }
    return result;
}

/*
 * Factor -> Number | '('Expr')'
 */
double Factor(char& curr) {
    double result;
    if (curr == '+' || curr == '-' || isdigit(curr)) {
        result = Number(curr); 
    }
    else if (curr == '(') {
        match('(', curr);
        result = result + Expr(curr);
        match(')', curr);       
    }else {
        error();
        cout<<"Factor"<<endl;
    }
}
/*
 * Number -> Digit I
 */
double Number(char& curr) {
    double result;
    cin.unget();
    cin >> result;
    cin.get(curr);
    return result;
}



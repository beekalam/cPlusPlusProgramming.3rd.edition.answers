#include <iostream>
#include <string>
#include <map>
#include <cctype>
using namespace std;
enum Token_value {
    NAME,   NUMBER, END,
    PLUS = '+', MINUS = '-',  MUL='*',  DIV='/',
    PRINT = ';', ASSIGN = '=', LP='(',   RP=')'
};

Token_value curr_token = PRINT;
double number_value;
string string_value;
int no_of_errors;

map<string,double> table;


double term(bool);    //multiply and divides
double prim(bool get);           // handle primaries
Token_value get_token(void);
double error(const string& s);
double error(const string& s,int linenumber);
double expr(bool get)
{
    double left = term(get);

    for(;;)
            switch(curr_token)
    {

    case PLUS:
        left+=term(true);
        break;
    case MINUS:
        left -= term(true);
        break;
    default:
        return left;
    }
}

double term(bool get)    //multiply and divides
{
    double left = prim(get);
    for(;;)
        switch(curr_token){
        case MUL:
            left*=prim(true);
            break;
        case DIV:
            if(double d = prim(get)){
                left /=d;
                break;
            }
            return error("divide by 0",__LINE__);
        default:
            return left;
        }
}


double prim(bool get)           // handle primaries
{
    if(get) get_token();

    switch(curr_token){
    case NUMBER:
        {
            double v = number_value;
            get_token();
            return v;
        }
    case NAME:
        {

            double& v = table[string_value];
            if(get_token()==ASSIGN)
                v=expr(true);
        }
    case MINUS:     //unary minus
        return -prim(true);
    case LP:
        {
            double e = expr(true);
            if(curr_token !=RP) return error(") expected",__LINE__);
            get_token();
            return e;
        }
    default:
        return error("primary expected",__LINE__);
    }
}

Token_value get_token()
{
    char ch = 0;
    do{ //skip whitespace except '\n'
        if(!cin.get(ch))  return curr_token = END;
    }while(ch!='\n' && isspace(ch));

    //cin >> ch;
    switch(ch){
    case 0:
        return curr_token = END;
    case ';':
    case '\n':
        return curr_token = PRINT;
    case '*':
    case '/':
    case '+':
    case '-':
    case '(':
    case ')':
    case '=':
        return curr_token = Token_value(ch);
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '.':
        cin.putback(ch);
        cin >> number_value;
        return curr_token = NUMBER;
    default:            // NAME, NAME=, or error
        if(isalpha(ch)){
                string_value = ch;
            while(cin.get(ch) && isalnum(ch)) string_value.push_back(ch);
            cin.putback(ch);
            //cin>>string_value;
            return curr_token = NAME;
        }
        error("bad token",__LINE__);
        return curr_token = PRINT;
    }
}


/*
double error(const string& s)
{
    no_of_errors++;
    cerr<<"error: "<< s << '\n';
    return 1;
}
*/
double error(const string& s,int lineNumber)
{
    no_of_errors++;
    cerr<<"error: " << (s) << "at line: " << lineNumber << '\n';
    return 1;
}
int calculator_main()
{
    table["pi"]=3.141592653589792385;
    table["e"] = 2.7182818284590452354;
    while(cin){
        get_token();
        if(curr_token==END) break;
        if(curr_token==PRINT) continue;
        cout<< expr(false) << '\n';
    }
    return no_of_errors;
}



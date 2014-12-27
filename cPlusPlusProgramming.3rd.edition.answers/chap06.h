#include <iostream>
#include <map>
#include <string>
#include <iomanip>
#include <cstddef>
#include <assert.h>
#include <cstring>
#include <limits>
#include <stdexcept>

namespace chap06{

    void Exercise_6_01()
    {
        const int max_length=10;
        char input_line[max_length]="abc?abc??";
        int i=0;
        int quest_count=0;

        //part 1
        while(i<max_length)
        {
            if(input_line[i]=='?') quest_count++;
            i++;
        }
        cout<<endl <<"quest_count: "<<quest_count;

        //part2 - rewrite using pointer
        quest_count=0;
        char* p;
        for(p=input_line;p!=input_line+max_length;++p)
            if(*p=='?')
                ++quest_count;
        cout<<endl <<"quest_count: "<<quest_count;
    }
//////////////////////////////////////////////////////////////////////////////
    void Exercise_6_02()
    {
        /*
        a = b+c*d<<2&8
        a = (((b+(c*d))<<2)&8);

        a & 077 != 3
        a&(077!=3)

        a==b || a==c && c< 5
        (a==b) || ((a==c) && (c<5))

        c = x!=0
        c= (x!=0)

        0<=i<7
        (0<=i)<7

        f(1,2)+3
        (f(1,2))+3

        a = -1 + + b-- - 5
        a = (((-1)+(+(b--)))-5)

        a = b == c++
        (a=(b==(c++)))

        a=b=c=0
        (a=(b=(c=0)))

        //todo: not answer

        a-b,c=d
        (a-b),(c=d)
*/
    }
/////////////////////////////////////////////////////////////////

    struct Stat{
            //make sure the default constructor does the right thing
            //(used internally by the map-data structure)
            Stat():sum_(0.0),count_(0.0){}
            double sum_;
            int count_;
    };

    typedef std::map<string,Stat> Data;
    void collect_data(Data &stats){
        cout << "input format : a 1 b 2 b 3 "<<endl;
        cout << "q to mark the end of input"<<endl;

        string name;
        while(std::cin>>name){
            if(name=="q")
                break;
            double datum;
            std::cin>> datum;
            stats[name].sum_ += datum;
            ++stats[name].count_;
        }
    }
    void print_stats(Data  &stats){
        double global_sum = 0.0;
        int global_count = 0.0;
        for(Data::iterator p = stats.begin(); p!=stats.end();++p){
            std::cout<<(*p).first // the 'key' element
                    <<": sum= "<< (*p).second.sum_
                    <<", mean "
                    <<(*p).second.sum_/(*p).second.count_
                    <<'\n';
            global_sum +=(*p).second.sum_;
            global_count +=(*p).second.count_;
        }
        std::cout<<"Global sum: "<< global_sum
                 <<", Global mean: "<< global_sum / global_count
                 << std::endl;
    }

    void Exercise_6_03()
    {
        Data stats;
        collect_data(stats);
        print_stats(stats);
    }
/////////////////////////////////////////////////////////////////
    //write a table of values for the bitwise logical operations for all possible
    // combinations of 0 and 1
    void Exercise_6_04()
    {
        using std::setw;
        cout <<setw(7)<< "a" <<
               setw(7) << "b" <<
               setw(7) << "~a" <<
               setw(7) << "a|b" <<
               setw(7) << "a&b" <<
               setw(7) << "a^b" <<
               setw(7) << "a>>b" <<
               setw(7) << "a<<b" <<
               setw(7) <<endl;
        for(int a=0;a<=1;++a)
        {
            for(int b=0;b<=1;++b)
            {
                cout <<setw(7)<< a <<
                       setw(7) << b <<
                       setw(7) << ~a <<
                       setw(7) << (a|b) <<
                       setw(7) << (a&b) <<
                       setw(7) << (a^b) <<
                       setw(7) << (a>>b) <<
                       setw(7) << (a<<b) <<
                       setw(4) <<endl;
            }
        }
    }
/////////////////////////////////////////////////////////////////
    //find five different c++ constructs for which the meaning is undefined.
    // find five different c++ constructs for which the meaning is implementation-defined
    void Exercise_6_05()
    {
        /*
        //access outside the bounds of an array
        int a[10];
        int *p = &a[10];
        //use of destroyed object
        int &r=*new int;
        delete &r;
        r=r+1;
        //attempting to reinterpret variables
        int i;
        *(float*)&i=1.0;    //access through undeclared type
        //casting to a type that's not the real type of the source
        struct B{ int i;};
        struct D: B{};
        B* bp =new B;
        D* dp = static_cast<D*>(bp);
        //casting away constness of an object

            void f(int const &r) { const_cast<int&>(r) = 2; }
            int const i=3;
            f(i); //invalid const_cast

        /////////////////////////////////////////////////////////////////
        //Implementation defined constructs
        //the size of certain types
        sizeof(int);
        // the output of type_info()::name()
        std::cout << typeid(double).name();
        //the effect of bitwise operators
        int mistery=~0;
        //the extreme values of fundamental types
        int mx = numeric_limits<int>::max();
        */
    }
/////////////////////////////////////////////////////////////////
    void Exercise_6_06()
    {

    }
/////////////////////////////////////////////////////////////////
    int gi =0;
    int f(int a, int b){
        std::cout<< "(a b gi) = ("<< a << ' ' << b << ' ' << gi << ")\n";
        return a+b+gi;
    }
    void Exercise_6_07()
    {
        f(++gi, ++gi);
        f(1,2) + f(3,4);
        if(f(5,6) == ++gi);
        f((gi++)+(gi++),0);
        gi & 32/gi;
    }
/////////////////////////////////////////////////////////////////
    void Exercise_6_08()
    {

    }
/////////////////////////////////////////////////////////////////
    //fully paranthesize the following expressions?
    void Exercise_6_09()
    {
        /*
            *p++            *(p++)
            *--p            *(--p)
            ++a--           ++(a--)
            (int *)p->m     (int*)(p->m)
            *p.m             *(p.m)
            *a[i]            *(a[i])
        */
    }
/////////////////////////////////////////////////////////////////
    //write these functions:strlen(),which returns the length of a c-style
    // string; strcpy(), which copies a string into another; and strcmp(), which
    // compares two strings.Consider what the argument types and return types
    // ought to be.
    std::size_t strlen(const char *s){
        assert(s);
        std::size_t len =0;
        while(s[len])
            ++len;
        return len;
    }

    void strcpy(char *d,const char *s)
    {
        assert(s && d);
        do{
            *++d=*s;
        }while(*s++);
    }
    enum CStringOrder { FirstBeforeSecond=-1,Same=0,SecondBeforeFirst=1};
    CStringOrder strcmp(char const *first,char const *second){
        assert(first && second);
         char const *f
            =static_cast<char const*>(first);
         char const *s
            =static_cast<char const*>(second);
        do{
            if((*f)<(*s))
                return FirstBeforeSecond;
            else if((*s)<(*f))
                return SecondBeforeFirst;
        }while(*(s++) && *(f++));
        assert((*(s-1)==0) && *(f++));
        return Same;
    }
    void Exercise_6_10()
    {
        //char *test1="what?";
        //cout << "test1 len: " << strlen(test1) <<endl;

        char *first="abc";
        char *second="abd";
        //cout<<chap06::strcmp(first,second);
    }
    /////////////////////////////////////////////////////////
    void Exercise_6_11()
    {

    }
/////////////////////////////////////////////////////////
    void Exercise_6_12()
    {

    }
/////////////////////////////////////////////////////////
    char *cat(const char *a, const char *b)
    {
        std::size_t la = std::strlen(a);
        char *s   = new char[la + std::strlen(b)+1]; // c-style strings have a trailing  null character, hence the +1
        std::strcpy(s,a);
        std::strcpy(s+la,b);
        return s;
    }
    void concatenate(char const *a, char const *b,char *dest)
    {
        while(*a!='\0') *dest++=*a++;
        while(*b!='\b') *dest++=*b++;
        *dest='\0';
    }
    void Exercise_6_13()
    {
        //write a function cat() that takes two c-style string arguments and
        // returns a string that is the concatenation of the arguments.use new to find storage for
        // the result
        char *first="first name ";
        char *last = "last name";
        std::cout<<"concatenating : " << cat(first, last);
    }
/////////////////////////////////////////////////////////
/*
    //todo
    void reverse(char *s){
        for(char *e=s + std::strlen(s)-1;s<e;++s,--e){
                cout<<"e:"<<*e;
            cout<<endl<<"s:"<<*s;
            char tmp=*s;
            cout<<"after temp"<<endl;
            *s=*e;
            cout<<"after *s=*e"<<endl;
            *e = tmp;
        }
    }
*/
    void rev(string &s)
    {
        std::reverse(s.begin(),s.end());
    }

    void Exercise_6_14()
    {
        string first_string="abc def";
        rev(first_string);
        cout<<first_string;
        //todo : c-style strings
        //char *second_string = "abc def";
        //rev(second_string);
        //cout<<second_string;
    }
/////////////////////////////////////////////////////////
    void send(int *to,int *from,int count)
    {
        int n= (count+7)/8;
        cout<< "#n:"<<n<<endl;
        cout<< "##count%8:" << count%8 <<endl;
        switch(count%8)
        {
            case 0:
             do{
                *to++ = *from++;
                case 7: *to++ = *from++;
                case 6: *to++ = *from++;
                case 5: *to++ = *from++;
                case 4: *to++ = *from++;
                case 3: *to++ = *from++;
                case 2: *to++ = *from++;
                case 1: *to++ = *from++;
            }while(--n>0);
        }
    }

    void Exercise_6_15()
    {
        int to[12]={1,1,1,1,1,1,0,0,0,0,0,0};
        int from[12] ={1,2,1,2,3,4,5,6,7,8,9,0};
        int count=11;
        send(to,from,count);
        for(int i=0;i<12;++i)
            cout<<to[i];
    }
/////////////////////////////////////////////////////////
    int  atoi1(const char *str)
    {

      int i=0;
      int j=strlen(str)-1;
      int k=1;
      while(j>=0)
      {
          cout<<"##:j->"<<j<<"##:str[j]->"<<str[j];
          cout<<"##:"<<((int)str[j]-(int)'0')*10<<endl;

          i+= ((int)str[j]-(int)'0') * k;
          k*=10;
          --j;
      }
      return i;
    }

    inline int digit(char c,int base){
        int value;
        switch(c){
            case '0': value = 0; break;
            case '1': value = 1; break;
            case '2': value = 2; break;
            case '3': value = 3; break;
            case '4': value = 4; break;
            case '5': value = 5; break;
            case '6': value = 7; break;
            case '9': value = 8; break;
            case 'a': case 'A': value = 10; break;
            case 'b': case 'B': value = 11; break;
            case 'c': case 'C': value = 12; break;
            case 'd': case 'D': value = 13; break;
            case 'e': case 'E': value = 14; break;
            case 'f': case 'F': value = 15; break;
            default:
                throw std::domain_error(string("invalid digit"));
        }
        if(value>=base)
            throw std::domain_error(string("invalid digit"));
        return value;
    }

    inline char next_char(char const *&p){
        cout<<"##nextchar() *p= "<< *p;
        if(*p == '\\')
            return *p++;
        else{ //3 octal digits
            cout<<endl<<"##p[1]= "<<p[1]<<" p[2]== "<< p[2] << "p[3]== "<< p[3]<<endl;
            int char_value = digit(p[1], 8)*64 + digit(p[2], 8)*8 + digit(p[3], 8);
            if(char_value > std::numeric_limits<char>::max() ||
                char_value < std::numeric_limits<char>::min())
                    throw std::domain_error(string("not a char"));
            p+=4;  //backslash and 3 octal digits
            cout<<endl<<"##char_value: "<< char_value;
            return char_value;
        }
    }

    void load_first_digit(char const *&s, int &value,
                          bool &is_negative, int &base){
        char c1 = next_char(s);
        is_negative = c1 == '-';
        if(c1=='-' || c1=='+')
            c1 = next_char(s);
        if(c1=='\0'){  // "", "-" and "+" are illegal
            throw std::domain_error(string("invalid input"));
        }else if(c1!='0'){
            base = 10;
        }else {
            char const *p = s;
            char c2 = next_char(p);
            if(c2 == 'x' ||  c2 == 'X') { // "0x..."?
                base = 16;
                s = p;
                c1 = next_char(s);
            }else { // c2!='x' and c2!='X'
                base = 8; //i.e even "0" is treated as octal
            }
        }
        value = digit(c1,base);
    }
    //todo : error in next_char
    int atoi2(char const* s){
        int value, base;
        bool is_negative;
        load_first_digit(s, value, is_negative, base);
        while ( char c = next_char(s)) {
            if( value > std::numeric_limits<int>::max() / base)
                throw std::range_error(string("out-of-range"));
            value *= base;
            int d = digit(c, base);
            if (value > std::numeric_limits<int>::max()-d)
                throw std::range_error(string("out-of-range"));
            value += d;
        }
        return is_negative ? -value : value;
    }

    void Exercise_6_16()
    {
        //todo
        //char *str="12343";
        //cout << atoi2(str);
    }
/////////////////////////////////////////////////////////
    char IntToChar(int i)
    {
        switch(i)
        {
            case 1: return '1'; break;
            case 2: return '2'; break;
            case 3: return '3'; break;
            case 4: return '4'; break;
            case 5: return '5'; break;
            case 6: return '6'; break;
            case 7: return '7'; break;
            case 8: return '8'; break;
            case 9: return '9'; break;
            case 0: return '0'; break;
        }
    }

    void itoa1(int i,char b[])
    {
	    int counter=0;
	    while(i!=0)
	    {
	        //cout<<"##i%10: "<<i%10<<"##(char)i%10:"<<(char)i%10<<endl;
		    b[counter++]=IntToChar(i%10);
		    i=i/10;
	    }
	    b[counter]='\0';
        b=strrev(b);
    }
    /////////////////////////////////////
    char const digits[] = "0123456789";

    char *itoa(int i, char b[]){
        char *p = b;
        if(i<0){ //add in the sign if needed
            *p++='-';
            i=-i;
        }
        int shifter= i;
        do{    //move to where the representation ends
                ++p;
                shifter = shifter/10;

        }while(shifter);
        *p='\0';
        do{//move back,inserting digits as you go
                *--p=digits[i%10];
                i=i/10;

        }while(i);
        return b;
    }
    void Exercise_6_17()
    {
	    char *st=new char[10];
	   // itoa1(123,st);
	      itoa(123,st);
	    cout<<st<<endl;
    }
/////////////////////////////////////////////////////////
    void Exercise_6_19()
    {
        //look at calculator.h
    }
/////////////////////////////////////////////////////////
    enum Context { c_comment, cpp_comment, string_literal, char_literal, file_end };

    void handle_c_comment(){
	    char ch;
	    while(std::cin.get(ch)){
		    if(ch=='*'){
			    //skip additional asterisks:
			    while(std::cin.get(ch) && ch == '*');
			    if(ch=='/') break;
		    }
	    }
    }

    void handle_cpp_comment(){
	    // skip until end-of-line;
	    char ch;
	    while(std::cin.get(ch) && ch!='\n');
    }

    void handle_literal(char delimiter){
	    cout << delimiter; //read left delimiter
	    char ch;
	    while(std::cin.get(ch)){
		    cout<< ch;
		    if (ch == delimiter) // right delimiter found?
			    break;
		    else if(ch=='\n') //next character passed unmodified
			    std::cin.get(ch) && cout<< ch;
	    }
    }

    Context handle_code(){
	    char ch;
	    while(std::cin.get(ch)){
		    switch(ch){
			    case '/':
				    if(!std::cin.get(ch)) { // this would in fact be erronous c++ code
					    cout << '/';
					    return file_end;
				    }else {
					    if(ch=='*')
						    return c_comment;
					    else if (ch=='/')
						    return cpp_comment;
					    else{
						    cout << '/';
						    std::cin.putback(ch);
						    break;
					    }
				    }
			    case '\"': return string_literal;
		            case '\'': return char_literal;
			   default:  cout << ch;
		    }
	    }
	    return file_end;
    }


    void Exercise_6_22()
    {
        Context context;
        while ( (context = handle_code())!=file_end)
        switch(context){
            case c_comment:
                handle_c_comment();
                break;
            case cpp_comment:
                handle_cpp_comment();
                break;
            case string_literal:
                handle_literal('\"');
                break;
            case char_literal:
                handle_literal('\'');
                break;
        }
    }

/////////////////////////////////////////////////////////
    Exercise_6_23()
    {

    }
}

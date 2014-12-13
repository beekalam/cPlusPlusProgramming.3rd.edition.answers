#include <iostream>
#include <typeinfo>
#include <limits>
#include <time.h>
#include <stddef.h>
#include <algorithm>
#include <string>
#include <string.h>
#include <list>
#include <set>

using std::cout;
using std::endl;
using std::copy;
using std::ostreambuf_iterator;
using std::string;
namespace chap05{

    void Exercise_5_01()
    {
        char *pc=0;
        int ai[10] = {1,1,2,3,5,8,13,21,34,55};
        int (&rai)[10] = ai;
        std::string (*pas)[5] = 0;
        char **ppc = &pc;
        int const ci = 42;
        int const *pci = &ci;
        int const *const cpi = &ci;
    }

    void Exercise_5_02()
    {

    }
//////////////////////////////////////////////////////////////////////////////
    void Exercise_5_03()
    {
        typedef unsigned char UnsignedChar;
        typedef  const unsigned char ConstantUnsignedChar;
        typedef int* IntegerPointer;
        typedef char** PointerPointerChar;      //pointer to pointer to char
        typedef char* PointerArrayChar;         //pointer to arrays of char
        typedef int* Array7IntegerPointer[7];   //array of 7 pointers to int
        typedef Array7IntegerPointer* PointerArray7IntegerPointer;  //pointer to an array of 7 pointers to int
        typedef int* Array8Array7IntegerPointer[8][7];  //array of 8 arrays 9 of 7 pointers to int
    }
//////////////////////////////////////////////////////////////////////////////
    void swap_values_by_pointer(int *p1,int *p2)
    {
        int temp = *p1;
        *p1=*p2;
        *p2=temp;
    }
    void swap_values_by_reference(int& v1,int& v2)
    {
        int temp = v1;
        v1 = v2;
        v2 = temp;
    }
    void Exercise_5_04()
    {
        int a=10;
        int b=11;
        swap_values_by_pointer(&a,&b);
        std::cout<<"a: " << a << "  b:  "<< b << endl;

        int x=10;
        int y=11;
        swap_values_by_reference(x,y);
        std::cout<<"x: " << x << "  y: " << y;
    }

//////////////////////////////////////////////////////////////////////////////
    void Exercise_5_05()
    {
        char str[] = "a short string";
        std::cout<<"size of \"" << str << "\" is " <<  sizeof(str)<< endl;
    }
//////////////////////////////////////////////////////////////////////////////
    void f(char c)
    {
        std::cout<< c << std::endl;
    }

    void g(char& c)
    {
        std::cout<< c << std::endl;
    }

    void h(const char& c)
    {
        std::cout<< c << std::endl;
    }

    void Exercise_5_06()
    {
        char c;
        unsigned char uc;
        signed char sc;
        f('a');
        f(49);
        f(3300);     //ok , but probably dangerous
        f(c);
        f(uc);
        f(sc);

        //g('a');             //ERROR
        //g(49);                 //ERROR
        //g(3300);              //ERROR
        g(c);
        //g(uc);          //ERROR: unsigned char -> char produces rvalue
        //g(sc);           //ERROR : signed char -> char produeces rvalue

        h('a');     //Temporary
        h(49);      //Temporary
        h(3300);    //Temporary, but probably dangerous
        h(c);
        h(uc);      //Temporary possibly dangerous
        h(sc);      //Temporary possibly dangerous
    }
//////////////////////////////////////////////////////////////////////////////

    int const num_months=12;
    int const month_length[num_months]={31,28,31,30,31,30,31,31,30,31,30,31};
    char const *month_names[num_months]={"January","February","March","April","May",
                                        "June","July","August","September","october",
                                        "November","december"};
    struct Month{
        char const *name_;
        int length_;
    };

    void Exercise_5_07()
    {
        for(int i=0;i<12;i++)
        {
            cout<< month_names[i] << ":\t" << month_length[i] << endl;
        }

        cout << "\n\nusing structure:\n";
        Month const month[num_months]
            ={{"january",31},{"February",28},{"Marc",31},{"April",30},
            {"May",31},{"June",30},{"July",31},{"August",31},
            {"September",30},{"October",30},{"November",30},{"December",31}};

        for(int k=0; k != num_months; ++k)
            std::cout<< month[k].name_ << ":\t" << month[k].length_ << endl;
    }
//////////////////////////////////////////////////////////////////////////////

    void copy_with_pointers(char const *src, char *dst, size_t n)
    {
        for(size_t k = 0; k != n; ++k)
            *dst++ = *src++;
    }

    void copy_with_indices(char const *src, char *dst,size_t n)
    {
        for(size_t k =0; k!= n ;++k)
            dst[k] = src[k];
    }

    void Exercise_5_08()
    {
        int const n_bytes = 100000;
        int const n_calls = 1000;
        char *src = new char[n_bytes];
        char *dst = new char[n_bytes];

        //Reduce paging effects by accessing all bytes:
        memcpy(dst,src,n_bytes);
        clock_t _start,_end,_reftime;

        //Test 1(reference time)
        _start = clock();
        cout << "start: " << _start << endl;
        for(int k=0; k!=n_calls; ++k)
            memcpy(dst,src,n_bytes);
        cout<< "end: " << _end << endl;
        _end = clock();
        _reftime = _end  - _start;


        //Test 2(pointers)
        _start = clock();

        for(int k=0;k!=n_calls;++k)
            copy_with_pointers(src,dst,n_bytes);
        _end = clock();

        cout<< " with pointers: "
            <<static_cast<double>(_end-_start)/_reftime
            <<" times slower than  memcpy.\n";

        //Test3 (indicies)
        _start = clock();

        for(int k=0;k!=n_calls;++k)
            copy_with_indices(src,dst,n_bytes);
        _end = clock();

        cout<< "with indicies: "
        <<static_cast<double>(_end-_start)/_reftime
        <<" times slower than memcpy.\n";

        delete[] src;
        delete[] dst;
    }

//////////////////////////////////////////////////////////////////////////////

    void Exercise_5_09()
    {
        struct ListNode {
            int value_;
            ListNode *next_;
        };
        ListNode list_terminator = {0, &list_terminator};
    }
//////////////////////////////////////////////////////////////////////////////

    void print_months(char const * monthNames[],int num_months)
    {
        for(int k=0;k!=num_months;++k)
            cout<<monthNames[k] << endl;
    }

    void Exercise_5_10()
    {
        int num_months = 12;
        char const *month_names2[]={"January","February","March","April","May",
                                        "June","July","August","September","october",
                                        "November","december"};
        print_months(month_names2,num_months);
    }
//////////////////////////////////////////////////////////////////////////////

    void Exercise_5_11()
    {
        /*
        typedef std::set<string> WordSet;
        typedef WordSet::iterator WordIter;
        typedef std::list<WordIter> Index;
        WordSet words;
        Index input_order;
        // Input the words uniquely
        for(string new_word;
                std::cin >> new_word, new_word!="Quit";){
                    std::pair<WordIter, bool> &trace = words.insert(new_word);
                    if(trace.second)
                        input_order.push_back(trace.first);
                }
        //output unique words in order of input:
        std::
        copy(input_order.begin(),input_order.end(),ostream_iterator<string>(cout,"\n"));
        // output unique words in default set<string> order:
        copy(words.beging(),words.end(),ostream_iterator<string>(cout,"\n"));
        */
    }
//////////////////////////////////////////////////////////////////////////////
    size_t count_charpair(std::basic_string<char>  &s,char a, char b)
    {
        size_t result = 0;
        //std::string::iterator p = s.begin();
        std::basic_string<char>::iterator  p = s.begin();
        while(p!=s.end())
            if(*p++==a)
                if(p!=s.end() && *p == b)
                    ++result;
        return result;
    }

    size_t count_charpair(char *s,char a,char b)
    {
        size_t result = 0;
        while(*s)
            if(*s++==a)
                if(*s==b)
                    ++result;
        return result;
    }

    void Exercise_5_12()
    {
        std::string str="aaaa";
        cout<< "num: " << count_charpair(str,'a','a');

        //c-style string
        char* _str = "aaaa";
        cout<< endl <<  "num: "<< count_charpair(_str,'a','a');
    }
//////////////////////////////////////////////////////////////////////////////

    struct Date
    {
        unsigned day_:5;
        unsigned month_:4;
        int year_:15;
    };
    std::istream& operator>>(std::istream& input,Date &d)
    {
        int const bufSize = 6;
        char buffer[bufSize];
        input.getline(buffer,bufSize,'/');
        d.month_ = atoi(buffer);
        input.getline(buffer, bufSize,'/');
        d.day_ = atoi(buffer);
        input.getline(buffer, bufSize,'/n');
        d.year_ = atoi(buffer);
        return input;
    }

    std::ostream& operator<<(std::ostream &output,Date &d)
    {
        output << d.month_ << '/' << d.day_ << '/' << d.year_;
        return output;
    }

    Date& init(Date& d,unsigned day,unsigned month,int year)
    {
        d.day_ = day;
        d.month_ = month;
        d.year_ = year;
        return d;
    }

    void Exercise_5_13()
    {
        cout<<"Enter date with format month/day/year: ";
        Date d;
        std::cin>>d;
        cout<<d;
    }
//////////////////////////////////////////////////////////////////////////////

}

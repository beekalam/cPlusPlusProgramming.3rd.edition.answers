#include <iostream>
#include <map>
#include <string>
#include <iomanip>
#include <cstddef>
#include <assert.h>
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
}

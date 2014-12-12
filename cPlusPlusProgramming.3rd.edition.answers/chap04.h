#include <iostream>
#include <typeinfo>
#include <limits>
using std::cout;
using std::endl;
//using namespace std;
namespace chap04{

    void Exercise_4_02()
    {
/*
            char ch;
            extern char

            string s;
            extern string s;

            const double pi = 3.1415926535897932385;
            extern const double pi;

            extern int error_number;
            int error_number;

            char* Name = "Njal";
            extern char *Nam;

            char* season[] ={"spring","summer","fall","winter"};
            extern char* season[];

            struct Date { int d, m, y};
            struct Date;

            int day(Date* p){ return p->d; }
            int day(Date*);

            double sqrt(double);
            double sqrt(double){
                return 0.0;
            }

            template<class T> T abs(T a) { return a<0 ? -a: a; }
            template<class T> T abs(T a);

            typedef complex<short> Point;

            struct User;
            struct User{
            };

            enum Beer { Carlsberg,Turbog, Thor};
            enum Beer;

            namespace NS { int a; }
*/
    }

    struct Polymorph{
        virtual ~Polymorph(){}
    };

    enum Bit {zero, one};
    enum Intensity { black =0, brightness=1000};

    void Exercise_4_03()
    {
        //Fundamental integral types:
        cout<<"sizeof(bool)=="<< sizeof(bool) << '\n';
        cout << "sizeof(char)==" << sizeof(char) << '\n';
        cout << "sizeof(signed char)==" << sizeof(signed char) << '\n';
        cout << "sizeof(unsigned char)==" << sizeof(unsigned char) << '\n';
        cout << "sizeof(wchar_t)==" << sizeof(wchar_t) << '\n';
        cout << "sizeof(signed short)=="<< sizeof(signed short) << '\n';
        cout << "sizeof(unsigned short)==" << sizeof(unsigned short) << '\n';
        cout << "sizeof(signed int)==" << sizeof(signed int) << '\n';
        cout << "sizeof(unsigned int)==" << sizeof(unsigned int) << '\n';
        cout << "sizeof(signed long)==" << sizeof(signed long) << '\n';
        cout << "sizeof(unsigned long)==" << sizeof(unsigned long) <<'\n';
        #ifdef LONGLONG_EXT
        cout << "sizeof(signed long long)==" << sizeof(signed long long) << '\n';
        cout << "sizeof(unsigned long long)==" << sizeof(unsigned long long) << '\n';
        #endif // LONGLONG_EXT

        //Fundamental floating point types
        cout << "sizeof(float)==" << sizeof(float) << '\n';
        cout << "sizeof(double)==" << sizeof(double) << '\n';
        cout << "sizeof(long double)==" << sizeof(long double) << '\n';

        //pointer types
        cout << "sizeof(int*)==" << sizeof(int *) << '\n';
        cout << "sizeof(int (*)())==" << sizeof(int (*)()) << '\n'; // pointer to a function
        cout << "sizeof(void (Polymorph::*)())==" << sizeof(void (Polymorph::*)()) << '\n';
        cout << "sizeof(void*)==" << sizeof(void*) << '\n';

        //Enumeration types
        cout << "sizeof(Bit)== " << sizeof(Bit) << '\n';
        cout << "sizeof(Intensity)==" << sizeof(Intensity) << '\n';
    }
    template<typename T>
    struct Type{
        static void print(){
            std::cout << "sizeof(" << typeid(T).name() << ") = "
                      << sizeof(T) << std::endl;
        }
    };
    void Exercise_4_03_usingTypeid()
    {
        //Fundamental integral types:
        Type<bool>::print();
        Type<char>::print();
        Type<signed char>::print();
        Type<unsigned char>::print();
        Type<wchar_t>::print();
        Type<signed short>::print();
        Type<unsigned short>::print();
        Type<signed int>::print();
        Type<unsigned int>::print();
        Type<signed long>::print();
        Type<signed long>::print();
        Type<unsigned long>::print();
        #ifdef LONGLONG_EXT
        Type<signed long long>::print();
        Type<unsigned long long>::print();
        #endif // LONGLONG_EXT

        //Fundamental floating-point types:
        Type<float>::print();
        Type<double>::print();
        Type<long double>::print();

        //pointer types
        Type<int*>::print();
        Type<int (*)()>::print();  //pointer to function
        Type<void (Polymorph::*)()>::print();
        Type<void*>::print();

        //Enumeration types
        Type<Bit>::print();
        Type<Intensity>::print();
    }

    void Exercise_4_04()
    {
        char const char_table[]="abcdefghijklmnopqrstuvwxyz-*&@. \~";
        //Do not include the terminating null of chartable!
        //Decimal
        for(int k=0; k < sizeof(char_table)-1; ++k)
            cout<<char_table[k] << '\t' <<  std::dec  << int(char_table[k]) << endl;
        //or, since the decimal is the default:
        for(int k=0; k < sizeof(char_table)-1;++k)
            cout<< char_table[k] << '\t' << int(char_table[k]) << endl;

        //Hexadecimal
        for(int k=0; k < sizeof(char_table); ++k)
            cout<< char_table[k] << '\t' << std::hex  << int( char_table[k]) << endl;
    }
    /////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    struct TypeInfo{
        static void print(){
            std::cout << typeid(T).name() << ": range is ("
                      << std::numeric_limits<T>::min() << ", "
                      << std::numeric_limits<T>::max() << ")\n";
        }
    };

    void Exercise_4_05()
    {
        TypeInfo<char>::print();
        TypeInfo<short>::print();
        TypeInfo<int>::print();
        TypeInfo<long>::print();
        TypeInfo<float>::print();
        TypeInfo<double>::print();
        TypeInfo<long double>::print();
        TypeInfo<unsigned>::print();
    }

    void Exercise_4_06()
    {

    }

    void Exercise_4_07()
    {

    }

}

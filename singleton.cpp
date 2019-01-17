/* ************************************************************************
 *       Filename:  singleton.cpp
 *    Description:  
 *        Version:  1.0
 *        Created:  2019年01月16日 10时47分24秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <iostream>
using namespace std;
#if 0
class singleton{
	public:
		static singleton* getinstance()
		{
			if(instance == NULL)
				instance = new singleton();
			return instance;
		}
		void print()
		{
			cout << "this = " << this << endl;
		}
		class delobj{
			public:
			 ~delobj(){
				 if(singleton::instance){
					  delete singleton::instance;
					  cout << "delobj "<< endl;
				 }
			 }
		};
		static delobj del;
	private:
		singleton(){}
		singleton(const singleton &);
		singleton& operator= (const singleton &);
		static singleton *instance;
};
singleton *singleton::instance = NULL;
singleton::delobj del;
int main(int argc, char *argv[])
{
	singleton * p1 = singleton::getinstance();
	singleton * p2 = singleton::getinstance();
	singleton * p3 = singleton::getinstance();
	p1->print();
	p2->print();
	p3->print();
	return 0;
}
#endif 
#if 1

template <class T>
class singleton{
	public:
		static T * getinstance();
	private:
		static T * instance;
};

template<class T>
T* singleton<T>::getinstance()
{
	if(instance == NULL)
		instance = new T();
	return instance;
}

template <class T>
T* singleton<T>::instance = NULL;

class obj{
	public:
		void print()
		{
			cout << "this = " << this << endl;
		}
	private:
		friend class singleton<obj>;
		obj(){}
		obj(const obj&);
		obj& operator= (const obj &);
};

int main(int argc, char *argv[])
{
	obj * p1 = singleton<obj>::getinstance();
	obj * p2 = singleton<obj>::getinstance();
	obj * p3 = singleton<obj>::getinstance();

	p1->print();
	p2->print();
	p3->print();
	return 0;
}
#endif


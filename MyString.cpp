/**
https://blog.csdn.net/qq_31828515/article/details/52843073
https://blog.csdn.net/qq_36782456/article/details/70954050

  ���C++��String��ģ��ʵ���Լ����ǳ����

  ��C������/C++�У��ַ�����һ��Ӧ�úܹ㷺�����ͣ�Ҳ�Ǻܻ��������ͣ�C���Բ�û��ֱ�Ӵ����ַ����Ĳ������ǲ����ַ�ָ����ַ���������в���������C++�б�׼��Ϊ���Ƿ�װ��һ���ַ������๩����ʹ�ã�ʹ����Ҫ#inlcude <string>ͷ�ļ�������Ҳ�����Լ�ģ��ʵ��һ���򵥵�String�ࡣ
  ��ģ��ʵ��String��Ĺ����У����ɱ���Ļ��������ǳ���������⣬��������ǳ������һ����顣��ν���ǳ����������˵����ǳ����ֻ�Ǽ򵥵Ľ�ֵ������������һ�������ʼ����һ������ֻ�����˳�Ա����û�и�����Դ��ʹ��������ͬʱָ����ͬһ��Դ�ġ���������ǽ���Դ��ֵһ�鿽����������ʱ�����������ռ����Դ������ֵ��ͬ�����ǻ���Ӱ�졣
  ����ͨ��������жԱȣ�
 **/
#include <iostream>
#include <algorithm>
using namespace std;


#if 0
//ǳ���� 
class String { 
	public: 
		String(const char* s = "") 
		{ 
			if (NULL == s) { 
				_pStr = new char[1]; 
				*_pStr = '\0'; 
			} 
			else { 
				_pStr = new char[[=](int i){for(; *s; i++, s++); return i;} + 1]; 
				strcpy(_pStr, s); 
			} 
		} 

		String(const String& s):_pStr(s._pStr) { }

		String& operator=(const String& s) 
		{ 
			if (this != &s) { 
				delete[] _pStr;
				_pStr = s._pStr; 
			} 
			return *this; 
		}

		~String() 
		{ 
			if (NULL != _pStr) { 
				delete[] _pStr; 
				_pStr = NULL; 
			} 
		} 
		friend ostream&operator<<(ostream & _cout,const String &s)
		{
			_cout<<s._pStr;
			return _cout;
		}
	private: 
		char* _pStr; 
};
#endif

#if 1
//��� 
class String { 
	public: 
		String(const char* s = "") 
		{
			if (NULL == s) { 
				_pStr = new char[1]; 
				*_pStr = '\0'; 
			} 
			else { 
				char *src = const_cast<char*>(s);
				char *temp = _pStr = new char[ ([=](){char *p = src; while(*p++); return p-src;})() + 1];
				while((*temp++ = *src++));

			} 
		}
		#if 0
		String(const String& s)
		{
			char *src = const_cast<char*>(s._pStr);
			char *temp = _pStr = new char[ ([=](){char *p = src; while(*p++); return p-src;})() + 1];
			while((*temp++ = *src++));
		}
		String& operator=(const String& s) 
		{
			//������ռ佫s�����ݿ�����һ����ʱ������ȥ�ͷ�ԭ�еĿռ� 
			//��ֹ����ռ�ʧ����ԭ�еĿռ䶼û��
			if (this != &s) { 
			
				char *src = const_cast<char*>(s._pStr);
				char *temp = new char[ ([=](){char *p = src; while(*p++); return p-src;})() + 1];
				char *temp1 = temp;
				while((*temp1++ = *src++));
				delete[] _pStr;
				_pStr = temp;
			} 
			return *this; 
		}
		#else
		//�ִ�д���� ���ݿ������캯����ϵͳ�Լ����ٿռ� 
		//�������캯��
		String (const String& s):_pStr(nullptr)//������Ϊ�գ�Ҫ��Ȼ���ʵ�ַ�Ƿ���
		{
			String temp(s._pStr);
			std::swap(temp._pStr,_pStr);
		}
		//��ֵ���������
		#if 0
		String& operator=(const String& s)
		{
			if (this != &s) {
				String temp(s);//�ȵ��ÿ������캯�����̶����ù��캯�������˳��˺���ʱ�����ٿ��������е����ݣ������ڴ�й©
				std::swap(_pStr, temp._pStr);
			}
			return *this;
		}
		#endif
		#if 1
		String& operator=(const String& s)
		{
			if (this != &s) {
				String temp(s._pStr);//ֱ�ӵ��ù��캯�������˳��˺���ʱ�����ٿ��������е����ݣ������ڴ�й©
				std::swap(_pStr, temp._pStr);
			}
			return *this;
		}
		#endif
		#if 0
		String& operator=(String& temp) // �˷�����ֱ�ӻ����������Ǹ��ƣ�����Դ�ᱻ��Ⱦ
		{
			std::swap(_pStr, temp._pStr);
			return *this;
		}
		#endif
		
		#endif
		~String() 
		{
			if (NULL != _pStr) { 
				addr();
				delete[] _pStr; 
				_pStr = NULL; 
			} 
		} 
		friend ostream&operator<<(ostream & _cout,const String &s)
		{
			_cout<<s._pStr;
			return _cout;
		}
		
		void addr() {cout << &_pStr << endl;}
	private: 
		char* _pStr; 
}; 
#endif
int main()
{
	String s1("sss");
	String s2(s1);
	String s3("hehe");
	s3 = s1;
	cout<<"s1: " << s1 <<endl;
	cout<<"s2: " << s2 <<endl;
	cout<<"s3: " << s3 <<endl;
	return 0;
}
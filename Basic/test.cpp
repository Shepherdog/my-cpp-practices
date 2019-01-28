
#include <iostream.h>
#include <assert.h>
#include <string>


using namespace std;

void sayHello()
{
	cout<< "Hello, the C++ world!" <<endl;
}

class String
{
public:
	String(const char* str);   //const修饰可以防止意外地改动该指针
	inline String& operator = (const String& other);   //引用传递仅借用参数的别名，不产生临时对象
	int getLength(void) const;   //任何不会修改数据成员的类成员方法都应该声明为const类型
	const char* toString(void);   //const修饰的返回指针的内容不能被修改
	virtual ~String(void);
	
private:
	char* m_data;
};

String::String(const char* str)
{
	if(str == NULL)
	{
		m_data = new char[1];
		*m_data = '\0';
	}
	else
	{
		int length = strlen(str);
		m_data = new char[length+1];
		strcpy(m_data, str);
	}
}

inline String& String::operator = (const String& other)
{
	//检查自赋值
	if(this == &other)
	{
		return *this;
	}
	
	//释放原有的内存资源
	//delete[] other.m_data;
	
	//分配新的内存资源，并复制内容
	int length = strlen(other.m_data);
	m_data = new char[length+1];
	strcpy(m_data, other.m_data);
	
	return *this;
}

int String::getLength(void) const
{
	return strlen(m_data);
}

const char* String::toString(void)
{
	return m_data;
}

String::~String(void)
{
	delete[] m_data;
}


//基类A
template <typename T>
class A
{
public:
	A(void);
	A(T a);
	static T transform(const string& str);   //不能在静态方法中访问非静态成员
	//用于某些运算(如复数和向量等)中
	A<T>& operator = (const A<T>& rhs);
	A<T>& operator + (const A<T>& rhs);
	A<T>& operator ++ (void);   //Prefix
	A<T>& operator -- (int);   //Postfix
	inline void showData(T t=T());   //T()完成0初始化
	virtual void sayHello(void);
	virtual void sayHello(int);
	virtual ~A(void);   //最好把所有的析构函数都用virtual声明
	
protected:
	T d;
	static T count;   //静态变量只在类中有效
	static const T max;   //用来存储常量
};
template <typename T>
T A<T>::count = 0;
template <typename T>
const T A<T>::max = 1;

template <typename T>
A<T>::A(void)
{
	cout<< "A's constructor" <<endl;
}

template <typename T>
A<T>::A(T a)
{
	d = a;
}

/*
* 内联是以代码膨胀（复制）为代价，仅仅省去了函数调用的开销，从而提高函数的执行效率
* 如果执行函数体内代码的时间，相比于函数调用的开销较大，那么效率的收获会很少
* */
template <typename T>
inline A<T>& A<T>::operator = (const A<T>& rhs)
{
	this->d = rhs.d;
	return *this;
}

template <typename T>
inline A<T>& A<T>::operator + (const A<T>& rhs)
{
	this->d += rhs.d;
	return *this;
}

template <typename T>
inline A<T>& A<T>::operator ++ (void)
{
	++this->d;
	return *this;
}

template <typename T>
inline A<T>& A<T>::operator -- (int)
{
	A<T> t(this->d);
	this->d--;
	return t;
}

template <typename T>
void A<T>::showData(T t=T())
{
	cout<< d <<endl;
}

template <typename T>
void A<T>::sayHello(void)
{
	cout<< "A'Hello" <<endl;
}

template <typename T>
void A<T>::sayHello(int i)
{
	cout<< "A'Hello" << i <<endl;
}

template <typename T>
A<T>::~A(void)
{
	cout<< "A's destructor" <<endl;
}


//派生类B
template <typename T>
class B : public A<T>
{
public:
	B(T d) : A<T>(d)
	{
		e = d;
		//cout<< A<T>::d <<endl;
	}
	virtual void sayHello(void);
	
private:
	T e;
};

template <typename T>
void B<T>::sayHello(void)
{
	cout<< "B's Hello" <<endl;
}

template <typename T>
int Find(const T& value, const T* array, int size)
{
	for(int i=0; i<size; i++)
	{
		if(array[i] == value)
			return i;
	}
	return -1;
}

void main()
{
	::sayHello();   //::表示调用全局函数
	
	//A<int>* a = new A<int>(0);
	//A<int>* a = new A<int>[3];
	//delete[] a;
	
	/*
	A<int> a[5] = {A<int>(int(0)), A<int>(int(1)), A<int>(int(2)), A<int>(int(3)), A<int>(int(4))};
	a[0] = a[1] + a[2] + a[3];
	a[4]--;
	++a[4];
	a[0].showData();
	a[1].showData();
	a[2].showData();
	a[3].showData();
	a[4].showData();
	*/
	
	//int t = 1;
	//assert(t == 0);   //断言assert(statement)判断statement是否为真，若不则中断程序
	
	B<int> b(0);
	b.sayHello();
	//b.sayHello(1);   //由于子类会隐藏父类中同名的方法，所以此语句无效
	
	String str("Hello");
	cout<< str.toString() << str.getLength() <<endl;
}

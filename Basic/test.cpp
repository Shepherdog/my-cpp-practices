
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
	String(const char* str);   //const���ο��Է�ֹ����ظĶ���ָ��
	inline String& operator = (const String& other);   //���ô��ݽ����ò����ı�������������ʱ����
	int getLength(void) const;   //�κβ����޸����ݳ�Ա�����Ա������Ӧ������Ϊconst����
	const char* toString(void);   //const���εķ���ָ������ݲ��ܱ��޸�
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
	//����Ը�ֵ
	if(this == &other)
	{
		return *this;
	}
	
	//�ͷ�ԭ�е��ڴ���Դ
	//delete[] other.m_data;
	
	//�����µ��ڴ���Դ������������
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


//����A
template <typename T>
class A
{
public:
	A(void);
	A(T a);
	static T transform(const string& str);   //�����ھ�̬�����з��ʷǾ�̬��Ա
	//����ĳЩ����(�縴����������)��
	A<T>& operator = (const A<T>& rhs);
	A<T>& operator + (const A<T>& rhs);
	A<T>& operator ++ (void);   //Prefix
	A<T>& operator -- (int);   //Postfix
	inline void showData(T t=T());   //T()���0��ʼ��
	virtual void sayHello(void);
	virtual void sayHello(int);
	virtual ~A(void);   //��ð����е�������������virtual����
	
protected:
	T d;
	static T count;   //��̬����ֻ��������Ч
	static const T max;   //�����洢����
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
* �������Դ������ͣ����ƣ�Ϊ���ۣ�����ʡȥ�˺������õĿ������Ӷ���ߺ�����ִ��Ч��
* ���ִ�к������ڴ����ʱ�䣬����ں������õĿ����ϴ���ôЧ�ʵ��ջ�����
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


//������B
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
	::sayHello();   //::��ʾ����ȫ�ֺ���
	
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
	//assert(t == 0);   //����assert(statement)�ж�statement�Ƿ�Ϊ�棬�������жϳ���
	
	B<int> b(0);
	b.sayHello();
	//b.sayHello(1);   //������������ظ�����ͬ���ķ��������Դ������Ч
	
	String str("Hello");
	cout<< str.toString() << str.getLength() <<endl;
}

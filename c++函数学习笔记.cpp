#include<iostream>
#include<type_traits>
#include<tuple>
#include<functional>
using namespace std;
////////////////////////////
/*
	函数高阶
	1.函数指针
	2.函数绑定 //类比js function curring 
*/
/////////////////////////// 
void add(int a,int b){
	cout<<a+b<<endl;
} 
class Test{
	public:
		int add(int a,int b)const{
			sum++;
			cout<<a+b<<"  sum: "<<sum<<endl;
			return a+b;
		}
		int minus(int a,int b)const{
			sum++;
			cout<<a-b<<"  sum: "<<sum<<endl;
			return a-b;
		}
		static int mul(int a,int b);
//		{
//			cout<<a*b<<endl;
//			return a*b;
//		}
	private:
		mutable int sum=0;
}; 
int Test::mul(int a,int b){
	cout<<a*b<<endl;
	return a*b;
}
typedef int(Test::*fn_add)(int,int)const;

class Fn{
	public:
		int sum=0;
		void operator()(int a){
			sum+=a;
		}
	private:
}; 

//struct ignore{//保留：bind实现 
//	//nothing to do
//};
//template<class F,class ...Args>
//auto m_bind(F fn,Args ...args)->decltype(){
//	return fn
//}

// template<class Tp,class Fn,size_t N>//保留：tuple_foreach
// struct __do_tp_foreach{
// 	static void run(Tp& t,Fn fn){
// 		__do_tp_foreach<Tp,Fn,N-1>::run(t,fn);
// 		fn(get<N>(t));
// 	}
// };
// template<class Tp,class Fn>
// struct __do_tp_foreach<Tp,Fn,0>{
// 	static void run(Tp& t,Fn fn){
// 		fn(get<0>(t));
// 	}
// };
// template<class Fn,class ...Args>
// void tp_foreach(const tuple<Args...>& t,const Fn fn){
// 	typedef const tuple<Args...>& tp_type;
// 	__do_tp_foreach<tp_type,Fn,tuple_size<tp_type>::value-1>::run(t,fn);
// }
// template<class T>
// void doub(T& a){
// 	a*=2;
// } 
// template<class T>
// void tp_print(T& a){
// 	cout<<a<<',';
// }

int main(){
	cout<<"-------------"<<endl;//普通函数指针 
	
	void (*pfn0)(int,int)=add;//普通函数不用 & 
	pfn0(1,2);//也不用 * 
	
	cout<<"-------------"<<endl;//成员函数指针 
	
	int (Test::*pfn1)(int,int)const=&Test::add;//必须加 &
	fn_add pfn2=&Test::minus;
	const Test t;
	//Test::add(1,2);//成员函数使用必须实例化 
	//pfn1(1,2);//必须有对象实体 
	(t.*pfn1)(1,2);
	(t.*pfn2)(1,2);
	
	int (*a)(int,int)=Test::mul;//static可以认为独立于类之外，与普通函数一致 
	Test::mul(1,2);//static函数可直接用 
	
	Test t2;
	function<int(const Test&,int,int)> pfn3=&Test::add;//事实证明function非常方便，注意要传入this 
	pfn3(t,1,2);
	pfn3(t2,1,2);
	//若没有this
	Fn fn_t;//类函数，functor 
	function<void(int)> pfn4=fn_t;//可见function是拷贝传递（赋值传递） 
	pfn4(10);
	pfn4(10);
	cout<<fn_t.sum<<endl;
	function<void(int)> pfn5=ref(reference_wrapper<Fn>(fn_t));//标准用法，事实上不用ref_warp,传引用 
	pfn5(101);
	cout<<fn_t.sum<<endl; 
	function<void(int)> pfn6=bind(fn_t,placeholders::_1);
	pfn6(3);
	cout<<fn_t.sum<<endl; 
	
	cout<<"-------------"<<endl;//function ,bind ,lamba
	//https://www.cnblogs.com/yyxt/p/4253088.html
	//https://blog.csdn.net/u012297622/article/details/51303238
	//https://www.cnblogs.com/yyxt/p/3987717.html 
	
	//http://www.cnblogs.com/qicosmos/p/3302144.html 好东西
	//http://www.cnblogs.com/xusd-null/p/3698969.html 
	//https://www.cnblogs.com/qicosmos/p/3723388.html
	
	function<void(int,int)> fna=add;
/*//示例代码：bind 
#include <iostream>
using namespace std;
class A
{
public:
    void fun_3(int k,int m)
    {
        cout<<k<<" "<<m<<endl;
    }
};

void fun(int x,int y,int z)
{
    cout<<x<<"  "<<y<<"  "<<z<<endl;
}

void fun_2(int &a,int &b)
{
    a++;
    b++;
    cout<<a<<"  "<<b<<endl;
}

int main(int argc, const char * argv[])
{
    //f1的类型为 function<void(int, int, int)>
    auto f1 = std::bind(fun,1,2,3); //表示绑定函数 fun 的第一，二，三个参数值为： 1 2 3
    f1(); //print:1  2  3

    auto f2 = std::bind(fun, placeholders::_1,placeholders::_2,3);
    //表示绑定函数 fun 的第三个参数为 3，而fun 的第一，二个参数分别由调用 f2 的第一，二个参数指定
    f2(1,2);//print:1  2  3

    auto f3 = std::bind(fun,placeholders::_2,placeholders::_1,3);
    //表示绑定函数 fun 的第三个参数为 3，而fun 的第一，二个参数分别由调用 f3 的第二，一个参数指定
    //注意： f2  和  f3 的区别。
    f3(1,2);//print:2  1  3


    int n = 2;
    int m = 3;

    auto f4 = std::bind(fun_2, n,placeholders::_1); //表示绑定fun_2的第一个参数为n, fun_2的第二个参数由调用f4的第一个参数（_1）指定。
    f4(m); //print:3  4

    cout<<m<<endl;//print:4  说明：bind对于不事先绑定的参数，通过std::placeholders传递的参数是通过引用传递的,如m
    cout<<n<<endl;//print:2  说明：bind对于预先绑定的函数参数是通过值传递的，如n


    A a;
    //f5的类型为 function<void(int, int)>
    auto f5 = std::bind(&A::fun_3, a,placeholders::_1,placeholders::_2); //使用auto关键字
    f5(10,20);//调用a.fun_3(10,20),print:10 20

    std::function<void(int,int)> fc = std::bind(&A::fun_3, a,std::placeholders::_1,std::placeholders::_2);
    fc(10,20);//调用a.fun_3(10,20) print:10 20 

　　return 0; 
}
*/

// 	cout<<"-------------"<<endl;//tp_foreach with bind 保留
// 	auto tp=make_tuple(1,2,3,"qwert",12.5);//注意，用tie和forward_as_tuple都很坑 
// 	//[](auto& a){return ++a;}(qwert);//函数和模板参数不能为auto 
// 	tp_foreach(tp,doub);
// 	tp_foreach(tp,tp_print);
	
	return 0;
}

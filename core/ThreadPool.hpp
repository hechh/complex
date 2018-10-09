#ifndef _ThreadPool_H_
#define _ThreadPool_H_

/*********** 
template<typename T> struct remove_reference { typedef T type;};
template<typename T&> struct remove_reference<T&> { typedef T type;};
template<typename T&&> struct remove_reference<T&&> { typedef T type;};
template<typename T>
T&& forward(typename std::remove_reference<T>::type& t)noexcept
{
		return static_cast<T&&>(t);
}

decltype推导规则：
1、标记符表达式或类成员表达式,decltype(exp)的类型就是exp的类型。包含CV。
2、exp==>lvalue then decltype(exp) ==> T&，假设exp为T
3、exp==>prvalue then decltype(exp) ==> T，假设exp为T(注释：只有类类型可以保留cv限定符)
4、exp==>xvalue then decltype(exp) ==> T&&，假设exp为T，xvalue为将亡值。

**********/


class ThreadPool
{
public:
	ThreadPool(size_t size);
	~ThreadPool();
	template<typename F,typename... Args>
	auto AddType(F&& f,Args&&... args)->std::future<typename std::result_of<F(Args...)>::type>;

private:
	std::mutex Mutex_;
	std::variable_condition Condition_;
	std::vector<std::thread> Work_;
	std::queue<std::function<void()>> Task_;
	bool Stop_;
};
template<typename F,typename... Args>
auto ThreadPool::AddType(F&& f,Args&&... args)->std::future<typename std::result_of<F(Args...)>::type>{
	using return_type = typename std::result_of<F(Args...)>::type;
	auto func = stsd::packaged_task<return_type()>(std::bind(std::forward<F>(f),std::forward<Args>(args)...)); 
	{
		std::unique_lock<std::mutex> lock(Mutex_);
		Task_.emplace(std::move([&func](){ return func(); }));
		Condition_.notify_one();
	}
	reutrn func.get_future();
}
ThreadPool::~ThreadPool()
{
	{
		std::unique_lock<std::mutex> lock(Mutex_);
		Stop_= true;
	}
	Condition_.notify_all();
	for(auto temp : Task_)
		temp.join();
}
ThreadPool::ThreadPool(size_t size):Stop_(false){
	for(size_t i = 0;i<size;i++){
		Work_.emplace_back(
			[this]()
			{
				while(true)
				{
					std::function<void()> task;
					{
						std::unique_lock<std::mutex> lock(Mutex_);
						Condition_.wait(lock,[this](){ return (Stop_ || !Task_.empty()); }); 
						if(Stop_ && Task_.empty())
							return;
						task = Task_.front();
						Task_.pop();
					}
					task();
				}
			});
	}
}


#endif
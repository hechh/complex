#ifndef _ASIO_H_
#define _ASIO_H_

class Asio
{
public:
	Asio(T t)=delete;
	~Asio()=delete;
	template<typename F,typename... Args>
	auto Call(F&& f,Args&&... args)->std::future<typename std::result_of<F(Args...)>::type>{
		using return_type = typename std::result_of<F(Args...)>::type;
		std::packaged_task<return_type()> task(std::bind(std::forward<F>(f),std::forward<Args>(args)...));
		auto return_value = task.get_future();
		std::thread(std::move(task));
		return return_type;
	}
};


#endif
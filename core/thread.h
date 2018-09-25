#ifndef _THREAD_H_
#define _THREAD_H_

#include <functional>

class HEThread
{
public:
	using pfn = void (void*);
public:

	HEThread(std::function<pfn> tmpfn){ tmpfn(); }
	void join(); 
private:
	void CreateThread(std::function<pfn> tmpfn);

private:
	std::function<pfn> mFucntion_;
	
};







#endif

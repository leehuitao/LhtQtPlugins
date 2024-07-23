#ifndef NMCALC_H
#define NMCALC_H
#include<coroutine>
#include<vector>
class nmCalc
{
public:
	struct promise_type {
		//记录本次排列组合的结果
		const int * m_currResult;
		auto get_return_object() { return nmCalc{ handle::from_promise(*this) }; }
		auto initial_suspend() { return std::suspend_always{}; }
		auto final_suspend() noexcept { return std::suspend_always{}; }
		void unhandled_exception() { return ;}
		void return_void(){}
		auto yield_value(const int *  result ) {this->m_currResult=result; return std::suspend_always{}; }
	};
	using handle = std::coroutine_handle<promise_type>;
private:
	handle hCoroutine;
	nmCalc(handle handle) :hCoroutine(handle) {}
public:
	nmCalc(nmCalc&& other)noexcept :hCoroutine(other.hCoroutine) { other.hCoroutine = nullptr; }
	~nmCalc() { if (hCoroutine) hCoroutine.destroy(); }
	bool next() const { return hCoroutine && (hCoroutine.resume(), !hCoroutine.done()); }
	const int *  currResult() const { return hCoroutine.promise().m_currResult; }
};

nmCalc pnm_calc(const int n, const int m)
{
	std::vector<int> vec_buf,vec_bz;
	int swim = 0;
	bool finished = false;
	for (int i=0;i<m;++i)    vec_buf.push_back(0);
	for (int i=0;i<n;++i)    vec_bz.push_back(0);
	do
	{
		int ch = 0;
		if (swim<m)
		{
			while (vec_bz[ch])
				++ch;
			vec_buf[swim] = ch;
			vec_bz[ch] = 1;
			++swim;
		}
		if (swim==m)
		{
			//返回一组结果
			co_yield vec_buf.data();
			bool hit = false;
			do
			{
				if (swim<m && swim >=0) vec_bz[vec_buf[swim]] = 0;
				--swim;
				if (swim>=0)
				{
					int nextv = vec_buf[swim];
					do
					{
						++nextv;
						if (nextv >=n)
							break;
						if (vec_bz[nextv]==0)
							hit = true;
					} while (hit == false);
					if (hit==true)
					{
						vec_bz[vec_buf[swim]] = 0;
						vec_buf[swim] = nextv;
						vec_bz[nextv] = 1;
						++swim;
					}
				}
				else
					finished = true;
			} while (finished == false && hit == false);
		}
	}while(finished == false);
};

nmCalc cnm_calc(const int n, const int m)
{
	std::vector<int> vec_buf,vec_bz;
	int swim = 0;
	bool finished = false;
	for (int i=0;i<m;++i)    vec_buf.push_back(0);
	for (int i=0;i<n;++i)    vec_bz.push_back(0);
	do
	{
		int ch = 0;
		if (swim>0 && swim < m)
			ch = vec_buf[swim-1];
		if (swim<m)
		{
			bool hit = false;
			while (ch < n && !hit)
			{
				if (vec_bz[ch]==0) hit = true;
				else
					++ch;
			}
			if (hit)
			{
				vec_buf[swim] = ch;
				vec_bz[ch] = 1;
				++swim;
			}
			else
				while (!hit && finished==false)
				{
					//回溯
					if (swim<m && swim >=0) vec_bz[vec_buf[swim]] = 0;
					--swim;
					if (swim>=0)
					{
						int nextv = vec_buf[swim];
						do
						{
							++nextv;
							if (nextv >=n)
								break;
							if (vec_bz[nextv]==0)
								hit = true;
						} while (hit == false);
						if (hit==true)
						{
							vec_bz[vec_buf[swim]] = 0;
							vec_buf[swim] = nextv;
							vec_bz[nextv] = 1;
							++swim;
						}
					}
					else
						finished = true;

				}


		}
		if (swim==m && finished==false)
		{
			//返回一组结果
			co_yield vec_buf.data();

			bool hit = false;
			do
			{
				if (swim<m && swim >=0) vec_bz[vec_buf[swim]] = 0;
				--swim;
				if (swim>=0)
				{
					int nextv = vec_buf[swim];
					do
					{
						++nextv;
						if (nextv >=n)
							break;
						if (vec_bz[nextv]==0)
							hit = true;
					} while (hit == false);
					if (hit==true)
					{
						vec_bz[vec_buf[swim]] = 0;
						vec_buf[swim] = nextv;
						vec_bz[nextv] = 1;
						++swim;
					}
				}
				else
					finished = true;
			} while (finished == false && hit == false);
		}
	}while(finished == false);
};

#endif // NMCALC_H

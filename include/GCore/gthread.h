#ifndef _CORE_THREAD_H_
#define _CORE_THREAD_H_

#include "gglobal.h"
#include "grunnable.h"
#include "gnocopyable.h"

namespace gnova { // gnova
	class GRunnable;
} // namespace gnova

namespace gnova { // gnova

class GAPI GThread final
	: public GRunnable
	, private GNocopyable
{
public:
	/// �õ�ǰ�߳�˯�ߣ���λ����
	static gvoid Sleep(gulong secs);

	/// �õ�ǰ�߳�˯�ߣ���λ������
	static gvoid MSleep(gulong msecs);

	/// ����ָ�����߳�
	static gvoid Join(GRunnable &thread);

public:
	GThread();

	template<typename _Fn,
		typename... _Args,
		class = typename GEnableIf<
		!GIsSame<typename GDecay<_Fn>::Type, GThread>::value>::Type>
	GThread(_Fn&& _Fx, _Args&&... _Ax);
	GThread(GThread &&thread);
	~GThread();

	GThread &operator==(GThread &&thread);

	/// ִ�����
	gvoid Bind();

public:
	gbool Start();
	gvoid Stop(gulong msecs = 0);

private:
	gint Run();
};

} // namespace gnova

#endif // _CORE_THREAD_H_

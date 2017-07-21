#ifndef _CORE_THREAD_H_
#define _CORE_THREAD_H_

#include "gtype.h"
#include "grunnable.h"
#include "gnocopyable.h"

namespace gsystem { // gsystem

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

	template<typename FunT,
		typename... ArgTs,
		typename = typename GEnableIf<
		!GIsSame<typename GDecay<FunT>::Type, GThread>::value>::Type>
	GThread(FunT &&func, ArgTs&&... args);
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

} // namespace gsystem

#endif // _CORE_THREAD_H_

#ifndef __THREAD_EX_H__
#define __THREAD_EX_H__

#ifndef WIN32
#define _PTHREAD
#endif


class ThreadEx
{
public:
	ThreadEx();
	virtual ~ThreadEx();
public:
	/*
	�����̣߳��ɹ�����true,ʧ�ܷ���false,ֻ���ڸý��̴������߳�������ϵͳ����ʱ�ŷ���false
	*/
	bool StartThread(void);
	/*
	�ȴ��߳��˳������ô˺���ǰ������÷�������ȷ�������̺߳������˳���������ô˺���������
	*/
	void WaitForStop(void);

	/*
	�˺���ֻ�����ڲ�����
	*/
#ifdef WIN32
	static DWORD WINAPI InitThreadProc(PVOID pObj){
		return	((ThreadEx*)pObj)->ThreadProc();
	}
#else
	static void* InitThreadProc(void*pObj){
		((ThreadEx*)pObj)->ThreadProc();
		return 0;
	}
#endif
	/*
	�˺���ֻ�����ڲ�����
	*/
	unsigned long ThreadProc(void);

protected:
	/*
	���̺߳������������ڴ˺�����ʵ���߳�Ҫ������
	*/
	virtual void ThreadProcMain(void)=0;
protected:
#ifdef WIN32
	DWORD	m_dwThreadID;		// �̱߳�ʶ
	HANDLE	m_hThread;			// �߳̾��
	HANDLE	m_evStop;
#else
    pthread_t	m_thread;
    sem_t		m_semWaitForStop;
    bool		m_bThreadStopped;
#endif
};
#endif

/// 1.
// Add
#if defined(ENABLE_RTT_STATISTICS)
#	include "ServerStateChecker.h"
#endif

/// 2.
// Search @ CPythonApplication::CPythonApplication()
	m_dwRenderFPS(0),

// Add below
#if defined(ENABLE_RTT_STATISTICS)
	m_dwRTT(0),
	m_fPktLossPct(0.0f),
#endif

/// 3.
// Search @ bool CPythonApplication::Process
	ELTimer_SetFrameMSec();

	//m_Profiler.Clear();
	DWORD dwStart = ELTimer_GetMSec();

// Add below
#if defined(ENABLE_RTT_STATISTICS)
	static DWORD s_dwCheckPingTime = ELTimer_GetMSec();

	if (ELTimer_GetMSec() - s_dwCheckPingTime > CServerStateChecker::MAX_RTT_REQUEST_MS)
	{
		thread t(NonBlockingServerStateChecker, &m_kServerStateChecker, &m_dwRTT, &m_fPktLossPct, &s_dwCheckPingTime);
		t.detach();
	}
#endif

/// 4.
// Search for 
bool CPythonApplication::Process()

//Add above
#if defined(ENABLE_RTT_STATISTICS)
void NonBlockingServerStateChecker(
	CServerStateChecker *m_kServerStateChecker,
	DWORD *m_dwRTT,
	float *m_fPktLossPct,
	DWORD *s_dwCheckPingTime
)
{
	CServerStateChecker::TEchoReply EchoReply;
	m_kServerStateChecker->GetEchoReply(&EchoReply);

	*m_dwRTT = EchoReply.dwRTT;
	*m_fPktLossPct = EchoReply.fPktLossPct;

	*s_dwCheckPingTime = ELTimer_GetMSec();
}
#endif

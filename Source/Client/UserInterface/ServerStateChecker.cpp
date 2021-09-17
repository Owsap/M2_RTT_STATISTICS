/// 1.
// Search
CServerStateChecker::CServerStateChecker()

// Add above
#if defined(ENABLE_RTT_STATISTICS)
#	include "AccountConnector.h"
#
#	include <iphlpapi.h>
#	include <icmpapi.h>
#
#	pragma comment(lib, "iphlpapi.lib")
#endif

/// 2.
// Search
void CServerStateChecker::Initialize()

// Add above
#if defined(ENABLE_RTT_STATISTICS)
void CServerStateChecker::GetEchoReply(TEchoReply* EchoReply)
{
	// IcmpSendEcho2 function (icmpapi.h)
	// https://docs.microsoft.com/en-us/windows/win32/api/icmpapi/nf-icmpapi-icmpsendecho2

	HANDLE hIcmpFile;
	unsigned long ipaddr = INADDR_NONE;
	DWORD dwRetVal = 0;
	char SendData[] = "p7yE6AEVE5y";
	LPVOID ReplyBuffer = NULL;
	DWORD ReplySize = 0;

	DWORD dwRTT = 0;
	if (m_byPktRequest > MAX_RTT_REQUESTS)
		ResetEchoReply();

	CAccountConnector& rkAccountConnector = CAccountConnector::Instance();
	struct hostent* remoteHost;

	if ((remoteHost = gethostbyname(rkAccountConnector.GetServerAddr())) == NULL) {
#if defined(_DEBUG_RTT)
		TraceError("Unknown Hostname.\n\n");
#endif
		return; // Unkown Hostname
	}

	char* pDmsIP = inet_ntoa(*(struct in_addr*)(remoteHost->h_addr_list[0]));
	ipaddr = inet_addr(pDmsIP);
	if (ipaddr == INADDR_NONE) {
#if defined(_DEBUG_RTT)
		TraceError("Unknown IP Address.\n\n");
#endif
		return; // Unkown IP address
	}

	hIcmpFile = IcmpCreateFile();
	if (hIcmpFile == INVALID_HANDLE_VALUE)
	{
#if defined(_DEBUG_RTT)
		TraceError("Unable to open handle.\n\n");
		TraceError("IcmpCreatefile returned error: %ld\n", GetLastError());
#endif
		return; // Unable to open handle.
	}

	// Allocate space for at a single reply
	ReplySize = sizeof(ICMP_ECHO_REPLY) + sizeof(SendData) + 8;
	ReplyBuffer = (VOID*)malloc(ReplySize);
	if (ReplyBuffer == NULL)
	{
#if defined(_DEBUG_RTT)
		TraceError("Unable to allocate memory for reply buffer.\n");
#endif
		return; // Unable to allocate memory for reply buffer.
	}

	dwRetVal = IcmpSendEcho2(hIcmpFile, NULL, NULL, NULL,
		ipaddr, SendData, sizeof(SendData), NULL,
		ReplyBuffer, ReplySize, 1000);

	m_byPktRequest += 1;
	if (dwRetVal != 0)
	{
		PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY)ReplyBuffer;
		switch (pEchoReply->Status)
		{
		case IP_DEST_HOST_UNREACHABLE:
		case IP_DEST_NET_UNREACHABLE:
		case IP_REQ_TIMED_OUT:
			dwRTT = LONG_MAX;
			break;
		default:
			dwRTT = pEchoReply->RoundTripTime;
			break;
		}

		m_dwLastRTT = dwRTT;
		m_byPktResponse += 1;
	}
	else
	{
		dwRTT = m_dwLastRTT > 0 ? m_dwLastRTT : LONG_MAX;
		m_byPktLoss += 1;
	}

	EchoReply->dwRTT = dwRTT;
	EchoReply->fPktLossPct = (m_byPktResponse > 0 ? (100 * m_byPktLoss / m_byPktResponse) : 100.0f);

#if defined(_DEBUG_RTT)
	TraceError("\nPing statistics for %s:", rkAccountConnector.GetServerAddr());
	TraceError("    Packets: Sent = %d, Received = %d, Lost = %d (%.2f%% loss),",
		m_byPktRequest, m_byPktResponse, m_byPktLoss, (100 * m_byPktLoss / m_byPktRequest));
#endif

	// Cleanup Memory
	IcmpCloseHandle(hIcmpFile);
	free(ReplyBuffer);

	return;
}

void CServerStateChecker::ResetEchoReply()
{
	m_dwLastRTT = 0;
	m_byPktRequest = 0;
	m_byPktResponse = 0;
	m_byPktLoss = 0;
}
#endif

/// 3.
// Search @ void CServerStateChecker::Initialize
	m_kStream.Disconnect();

// Add below
#if defined(ENABLE_RTT_STATISTICS)
	ResetEchoReply();
#endif
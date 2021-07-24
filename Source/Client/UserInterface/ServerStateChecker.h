/// 1.
// Search
	void Initialize();

// Add below
#if defined(ENABLE_RTT_STATISTICS)
public:
	enum ERTTMisc
	{
		MAX_RTT_REQUESTS = 4,
		MAX_RTT_REQUEST_MS = 5000,
	};

	typedef struct SEchoReply
	{
		DWORD dwRTT;
		float fPktLossPct;
	} TEchoReply;

	void GetEchoReply(TEchoReply* EchoReply);
	void ResetEchoReply();

protected:
	DWORD m_dwLastRTT;
	BYTE m_byPktRequest;
	BYTE m_byPktResponse;
	BYTE m_byPktLoss;
#endif
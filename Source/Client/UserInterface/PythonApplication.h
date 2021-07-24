/// 1.
// Search
public:
	int OnLogoOpen(char* szName);

// Add above
#if defined(ENABLE_RTT_STATISTICS)
public:
	DWORD GetRTT() { return m_dwRTT; }
	float GetPacketLossPct() { return m_fPktLossPct; }

protected:
	DWORD m_dwRTT;
	float m_fPktLossPct;
#endif
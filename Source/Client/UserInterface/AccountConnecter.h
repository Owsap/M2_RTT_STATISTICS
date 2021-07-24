/// 1.
// Search
	void Process();

// Add below
#if defined(ENABLE_RTT_STATISTICS)
public:
	const char* GetServerAddr() { return m_strAddr.c_str(); }
#endif
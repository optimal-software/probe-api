//------------------------------------------------------
#ifndef _OPTIONS_H_UID000003A649B0548E
#define _OPTIONS_H_UID000003A649B0548E

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------------------------------

class ApplicationOptions
{
public:
	void Print() const;
	void RecalculateTotalTimeout();
	int ProcessCommandLine(const int argc, const char* const argv[]);	// returns non-zero result if process exit required

public:
	enum eMode
	{
		MODE_UNKNOWN,
		MODE_GET_COUNTRIES,
		MODE_GET_ASNS,
		MODE_DO_BY_COUNTRY,
		MODE_DO_BY_ASN,
	};

public:
	bool		bVerbose		= false;
	bool		bDebug			= false;
	uint32_t	nTimeoutPingMs	= 3000;
	uint32_t	nTimeoutTotalMs	= nTimeoutPingMs;
	uint32_t	nCount			= 4;
	uint16_t	nPacketSize		= 32;
	uint32_t	nTTL			= 128;

	eMode		mode			= MODE_UNKNOWN;
	std::string	sModeArgument;
	std::string	sTarget;
};

//------------------------------------------------------
#endif //ifndef _OPTIONS_H_UID000003A649B0548E

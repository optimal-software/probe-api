//------------------------------------------------------
#ifndef _OPTIONS_H_UID000003A649B0548E
#define _OPTIONS_H_UID000003A649B0548E

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "common/Common.h"			// for CommonOptions

//------------------------------------------------------

class ApplicationOptions
{
public:
	ApplicationOptions();
	void Print() const;
	void RecalculateTotalTimeout();
	int ProcessCommandLine(const int argc, const char* const argv[]);	// returns non-zero result if process exit required

	CommonOptions GetCommonOptions() const
	{
		return CommonOptions(bDebug, bVerbose, sModeArgument, nResultsLimit, sMashapeUrl, sMashapeKey);
	}

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
	bool		bNoDelays		= false;

	bool		bResolveIp2Name = false;	// this is false in Windows by default
	bool		bUseIpv4Only	= false;
	bool		bUseIpv6Only	= false;
	bool		bDontFragment	= false;
	bool		bInfinitePing	= false;

	uint32_t	nTimeoutPingMs	= 3000;
	uint32_t	nTimeoutTotalMs	= nTimeoutPingMs;
	uint32_t	nWaitBetweenPingsMs = 100;
	uint32_t	nPingsPerProbe	= 1;
	uint32_t	nProbesLimit	= 4;
	uint32_t	nResultsLimit	= std::numeric_limits<uint32_t>::max();		// for list ASNs and list countries modes; UINT32_MAX - display ALL items from requested list
	uint16_t	nPacketSize		= 32;
	uint32_t	nTTL			= 55;

	eMode		mode			= MODE_UNKNOWN;
	std::string	sModeArgument;
	std::string	sTarget;

	std::string sMashapeUrl;
	std::string sMashapeKey;
};

//------------------------------------------------------
#endif //ifndef _OPTIONS_H_UID000003A649B0548E

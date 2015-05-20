//------------------------------------------------------
#ifndef _PARSEREPLY_H_UID0000034682CF7C13
#define _PARSEREPLY_H_UID0000034682CF7C13

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------------------------------

namespace Json
{
	class Value;
};

//------------------------------------------------------

namespace ProbeAPI
{
	enum eParseMode
	{
		ProbeList_All,
		ProbeList_All_Tracert,
		ProbeList_AsnOnly,
	};

	struct CountryInfo
	{
		std::string		sCode;
		std::string		sName;
		int				nProbes = 0;

		CountryInfo()
		{}
		CountryInfo(const Json::Value& v);
	};

	struct AsnInfo
	{
		std::string		sId;
		std::string		sName;

		AsnInfo()
		{}
		AsnInfo(const Json::Value& v);
	};

	struct NetworkInfo
	{
		std::string		sName;

		NetworkInfo()
		{}
		NetworkInfo(const Json::Value& v);
	};

	struct PingResult
	{
		bool			bTimeout = false;
		int				nTimeMs = 0;

		PingResult()
		{}
		PingResult(const Json::Value& v);
	};

	struct TracertHopResults
	{
		std::string		sReplyHost;
		std::vector<PingResult>	vectResults;

		TracertHopResults()
		{}
		TracertHopResults(const Json::Value& v);
	};

	struct TracerouteInfo
	{
		std::string		sTarget;
		std::vector<TracertHopResults>	vectHops;

		TracerouteInfo()
		{}
		TracerouteInfo(const Json::Value& v);
	};

	struct ProbeInfo
	{
		PingResult		ping;
		int64_t			nId = 0;
		std::string		sUniqueId;

		CountryInfo		country;
		AsnInfo			asn;
		NetworkInfo		network;
		TracerouteInfo	tracert;

		ProbeInfo()
		{}
		ProbeInfo(const Json::Value& v, const eParseMode mode);
	};

	std::vector<ProbeAPI::CountryInfo> ParseCountries(const std::string& sJson);

	std::vector<ProbeAPI::ProbeInfo> ParsePingTestByCountryResult(const std::string& sJson);
	std::vector<ProbeAPI::ProbeInfo> ParsePingTestByAsnResult(const std::string& sJson);

	std::vector<ProbeAPI::ProbeInfo> ParseGetProbesByCountryResult_AsnOnly(const std::string& sJson);

	std::vector<ProbeAPI::ProbeInfo> ParseTracertTestByCountryResult(const std::string& sJson);
	std::vector<ProbeAPI::ProbeInfo> ParseTracertTestByAsnResult(const std::string& sJson);
}

//------------------------------------------------------
#endif //ifndef _PARSEREPLY_H_UID0000034682CF7C13

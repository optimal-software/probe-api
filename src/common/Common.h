//------------------------------------------------------
#ifndef _COMMON_H_UID000003467CD53C58
#define _COMMON_H_UID000003467CD53C58

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HttpRequest.h"
#include "CommonOptions.h"

//------------------------------------------------------

extern volatile bool g_bTerminateProgram;

//------------------------------------------------------

class ProbeApiRequester: protected HttpRequester
{
public:
	struct Request : HttpRequester::Request
	{
		Request(const std::string& sRequestWithArgs, const CommonOptions& options);
	};

	typedef HttpRequester::Reply Reply;

public:
	Reply DoRequest(const Request& requestInfo, const bool bVerbose);

	static void HttpReplyDebugPrint(const ProbeApiRequester::Reply &reply);
};

//------------------------------------------------------
// error codes returned by the process:

namespace eRetCode
{
	enum enumRetCode: int
	{
		NoValue			= -1,
		OK				= 0,
		BadArguments	= 10,
		NotSupported	= 20,
		Cancelled		= 50,
		ApiFailure		= 100,
		ApiParsingFail	= 110,
		OtherError		= 500,
		HardFailure		= 1000,
	};
}

//------------------------------------------------------

class PException : public std::exception
{
	int					m_nRetCode = eRetCode::OtherError;
	//std::ostringstream	m_buf;
	std::string			m_str;

public:
	PException(const int retCode = eRetCode::OtherError) :
		m_nRetCode(retCode)
	{
	}

	PException(const std::string& s, const int retCode = eRetCode::OtherError) :
		//m_buf(s),
		m_str(s),
		m_nRetCode(retCode)
	{
	}

	PException(const PException& b) :
		//m_buf(b.m_buf.str()),
		m_str(b.m_str),
		m_nRetCode(b.m_nRetCode)
	{
	}

	int GetRetCode() const
	{
		return m_nRetCode;
	}

	virtual const char * what() const throw () override
	{
		//return m_buf.str().c_str();
		return m_str.c_str();
	}

	std::string str() const
	{
		//return m_buf.str();
		return m_str;
	}

	template<class T>
	PException& operator <<(const T& v)
	{
		//m_buf << v;
		m_str += OSSFMT(v);
		return *this;
	}
};

//------------------------------------------------------

void MySleep(const uint32_t nSleepMs);

//------------------------------------------------------

inline bool contains(const std::string& str, const std::string& substr)
{
	return str.find(substr) != str.npos;
}

inline bool begins(const std::string& s, const std::string& begin)
{
	const auto len = begin.length();
	if (s.length() < len)
		return false;

	return 0 == memcmp(s.c_str(), begin.c_str(), len);
}

inline bool ends(const std::string& s, const std::string& end)
{
	const auto len = end.length();
	if (s.length() < len)
		return false;

	return 0 == memcmp(s.c_str() + s.length() - len, end.c_str(), len);
}

//------------------------------------------------------

inline void explode(std::vector<std::string>& vect, const std::string& sText, const std::string& sDelim)
{
	vect.clear(); // don't free memory to allow external code memory guess size

	if (sText.empty())
		return;

	if (sDelim.empty())
	{
		vect.push_back(sText);
		return;
	}

	// Assume external code either gives vector with no reservation or makes correct reservation before call.
	// Following prediction makes explode 10% slower in comparison with external memory reservation.
	// But this prediction lowers memory usage during explode and increases its speed in 1.5 - 2.0 times
	// in comparison with no prediction and no prior reservation.
	if (vect.capacity() == 0)
	{
		size_t nPredictItems = 1; // there are always more items than delimiters by one
		for (std::size_t pos = sText.find(sDelim); pos != sText.npos;
			pos = sText.find(sDelim, pos + sDelim.length()))
		{
			nPredictItems++;
		}
		vect.reserve(nPredictItems);
	}

	const std::string::const_iterator begin = sText.cbegin();
	std::size_t pos = 0;
	while (true)
	{
		const std::size_t pos2 = sText.find(sDelim, pos);
		if (sText.npos == pos2)
		{
			vect.emplace_back(begin + pos, sText.cend());
			break;
		}

		vect.emplace_back(begin + pos, begin + pos2);
		pos = pos2 + sDelim.length();
	}
}

inline std::string implode(const std::vector<std::string>& vect, const std::string& sDelim)
{
	// speed implementation: (twice faster than string-bases implementation which is twice faster than ostringstream-based)
	const size_t n = vect.size();
	if (0 == n)
		return std::string();

	size_t nChars = sDelim.length() * (n - 1);

	for (size_t i = 0; i < n; i++)
		nChars += vect[i].length();

	if (0 == nChars)
		return std::string();

	std::unique_ptr<char[]> buffer(new char[nChars]);
	char* p = buffer.get();

	const size_t n2 = sDelim.size();
	for (size_t i = 0; i < n; i++)
	{
		if (i > 0)
		{
			memcpy(p, sDelim.data(), n2*sizeof(*p));
			p += n2;
		}
		memcpy(p, vect[i].data(), vect[i].length()*sizeof(*p));
		p += vect[i].length();
	}
	return std::string(buffer.get(), nChars);
}

//------------------------------------------------------

std::string findandreplaceConst(const std::string& source, const std::string& find, const std::string& replace);
void findandreplace(std::string& source, const std::string& find, const std::string& replace);

//------------------------------------------------------

inline uint32_t stoui32(const std::string& s)
{
	const unsigned long lresult = stoul(s, 0, 10);
	const uint32_t result = lresult;
	if (result != lresult)
	{
		throw std::out_of_range("stoui32 got bad argument: " + s);
	}
	return result;
}

//------------------------------------------------------

#ifdef __MINGW32__
// MinGW gcc does not support conversion function from STL:
// http://stackoverflow.com/questions/8542221/stdstoi-doesnt-exist-in-g-4-6-1-on-mingw

#include <stdlib.h>		// for strtoul
#include <sstream>		// for ostringstream

inline unsigned long stoul(const std::string& s)
{
	return strtoul(s.c_str(), nullptr, 10);
}

inline int stoi(const std::string& s)
{
	return atoi(s.c_str());
}

template<class T>
inline std::string to_string(const T& v)
{
	std::ostringstream oss;
	oss << v;
	return oss.str();
}

#endif

//------------------------------------------------------
#endif //ifndef _COMMON_H_UID000003467CD53C58

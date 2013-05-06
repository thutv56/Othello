
/**
 **************************************************************************************************************************************************************
 * Configuration file management class.
 * Just a tiny dirty helper class. Needs C++ clean up.
 **************************************************************************************************************************************************************
 * @file   CConfigFile.h
 * @author Antoine Villepreux
 * @date   17/06/2003 16:18:32
 **************************************************************************************************************************************************************/

#ifndef CCONFIGFILE_H
#define CCONFIGFILE_H

/**************************************************************************************************************************************************************
 * Includes
 **************************************************************************************************************************************************************/

#include <map>
#include <fstream>

/**************************************************************************************************************************************************************
 * Classes
 **************************************************************************************************************************************************************/

class CConfigFile
{
public:

	enum EMode { READ, WRITE };

	enum { LINE_LENGTH = 1024 };

	CConfigFile()
	{
		m_pFile = 0;
	}

	CConfigFile(const char* filename, EMode eMode)
	{
		Open(filename,eMode);
	}

	bool Open(const char* filename, EMode eMode)
	{
		if (m_pFile)
		{
			Close();
		}

		m_eMode = eMode;

		if (m_eMode==READ)
		{
			m_pFile = new std::fstream(filename, std::ios_base::in);

			if (!m_pFile->is_open())
			{
				return false;
			}

			while (!m_pFile->eof())
			{
				char str0[LINE_LENGTH];
				char str1[LINE_LENGTH];

				m_pFile->getline(str0, LINE_LENGTH, ' ');
				m_pFile->getline(str1, LINE_LENGTH, '\n');

				if ((m_pFile->gcount()<1) && !m_pFile->eof())
				{
					Close();
					return false;
				}

				m_map.insert(CMap::value_type(std::string(str0),std::string(str1)));
			}
		}
		else
		{
			m_pFile = new std::fstream(filename, std::ios_base::out | std::ios_base::trunc);
			
			if (!m_pFile->is_open())
			{
				return false;
			}
		}

		return true;
	}

	~CConfigFile()
	{
		Close();
	}

	void Close()
	{
		if (!m_pFile)
		{
			return;
		}

		if (m_eMode == WRITE)
		{
			if (m_pFile->is_open())
			{
				for(CMap::iterator it=m_map.begin(); it!=m_map.end(); ++it)
				{
					(*m_pFile) << it->first.c_str();
					(*m_pFile) << " ";
					(*m_pFile) << it->second.c_str();
					(*m_pFile) << std::endl;
				}
			}
		}

		m_pFile->close();
		m_map.clear();

		delete m_pFile;
		m_pFile = 0;
	}

	bool Exists(const std::string& strKey) const
	{
		CMap::const_iterator it = m_map.find(strKey);
		return (it != m_map.end());
	}

	bool Exists(const char* strKey) const
	{
		return Exists(std::string(strKey));
	}

	template<class T> T Get(const std::string& strKey) const;

	template<> std::string Get<std::string>(const std::string& strKey) const
	{
		CMap::const_iterator it = m_map.find(strKey);

		if (it != m_map.end())
		{
			return it->second;
		}

		static std::string nokey("");
		return nokey;
	}

	template<> int Get<int>(const std::string& strKey) const
	{
		return atoi(Get<std::string>(strKey).c_str());
	}

	template<> bool Get<bool>(const std::string& strKey) const
	{
		return 0 != Get<int>(strKey);
	}

	template<> float Get<float>(const std::string& strKey) const
	{
		return (float)atof(Get<std::string>(strKey).c_str());
	}

	void Set(const std::string& strKey, const std::string& x)
	{
		m_map.insert(CMap::value_type(strKey,x));
	}

	void Set(const char* strKey, const char* x)
	{
		Set(std::string(strKey),std::string(x));
	}

	void Set(const std::string& strKey, int x)
	{
		char str[LINE_LENGTH];
		sprintf(str,"%d",x);
		Set(strKey,std::string(str));
	}

	void Set(const std::string& strKey, float x)
	{
		char str[LINE_LENGTH];
		sprintf(str,"%f",x);
		Set(strKey,std::string(str));
	}

private:

	struct CLess
	{
		bool operator()(const std::string& str0, const std::string& str1) const
		{
			return strcmp(str0.c_str(), str1.c_str()) < 0;
		}
	};

	typedef std::map<std::string,std::string,CLess> CMap;

	std::fstream*	m_pFile;
	CMap			m_map;
	EMode			m_eMode;
};

/**************************************************************************************************************************************************************/

#endif


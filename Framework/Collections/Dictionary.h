#ifndef DICTIONARY
#define DICTIONARY

#include <map>

template <typename TKey, typename TVal>
class Dictionary
{
public:
	void Add(TKey key, TVal value)
	{
		m_dict.push_back(key, value);
	}
	
	bool TryGetValue(const TKey& key, TVal& value)
	{
		typename std::map<TKey, TVal>::iterator it = m_dict.find(key);
		if (it == m_dict.end())
			return false;
		
		value = it->second;
		
		return true;
	}
	
	bool HasKey(const TKey& key) const
	{
		typename std::map<TKey, TVal>::iterator it = m_dict.find(key);
		return it != m_dict.end();
	}
	
	void Clear()
	{
		m_dict.clear();
	}
	
private:
	std::map<TKey, TVal> m_dict;
};

#endif // DICTIONARY


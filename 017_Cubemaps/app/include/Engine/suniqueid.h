#pragma once

struct SUniqueId
{
public:
	SUniqueId() 
	{
		m_id = ID++;
	}

	long long GetId() const { return m_id; }

private:
	long long m_id;
	static long long ID;
};

#pragma once
#include <map>
#include <vector>
#include <iostream>
#include <sys/time.h>
#include "pbinterfacehelper.h"

#include <QMutex>

#define PROF_POINT_HELPER(FUNCTION, LINE) Profiler prof##FUNCTION##__LINE__(FUNCTION)
#define PROF_POINT PROF_POINT_HELPER(__PRETTY_FUNCTION__, __LINE__)

unsigned int gettime();

class PBINTERFACESHARED_EXPORT TimeLog
{
public:
    typedef std::pair<unsigned int, unsigned int> MSEC; //time, count
private:
    std::vector<unsigned int> m_Stack;
    std::vector<std::string> m_Prefix;
    typedef std::map<std::string, MSEC> TTimeLog;
    TTimeLog m_TimeLog;
    typedef TTimeLog::const_iterator itMap;
    static TimeLog instance;
public:
    inline static TimeLog * GetInstance()
    {
        return &instance;
    }
    
    //start timing and push to stack times
    void Start(int prefix);

    //start timing and push to stack times
    void Start(const std::string & prefix);

    // gets timedifference and push it to log
    unsigned int Stop(const std::string & name);


    //print all log
    void Print(std::ostream & oStrm = std::cerr) const;
private:
    inline TimeLog()
    {}
    QMutex mtx;
};
struct Profiler {
	Profiler(const char * path): m_path(path) {
		TimeLog::GetInstance()->Start(0);
	}
	~Profiler() {
		TimeLog::GetInstance()->Stop(m_path);
	}

private:
	const char * m_path;
};

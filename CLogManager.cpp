

#include "CLogManager.h"

// global instance
CLogManager globalLog;

// null streams stuff
nullbuf null_obj;
wnullbuf wnull_obj;
std::ostream cnull(&null_obj);
std::wostream wcnull(&wnull_obj);


CLogManager::CLogManager(int verboseLevel)
: verboseLevel(verboseLevel)
{
}
CLogManager::~CLogManager()
{
}

std::ostream &CLogManager::operator()(int logLevel)
{
    if (logLevel < verboseLevel)
        return std::cout;
    return cnull;
}

CLogManager &instance()
{
    return globalLog;
}
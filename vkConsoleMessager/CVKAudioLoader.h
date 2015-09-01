

#ifndef __C_VK_AUDIO_LOADER
#define __C_VK_AUDIO_LOADER

#include "CVKMethodCaller.h"

class CVKAudioLoader
{
protected:
	CVKMethodCaller *caller;
    CLogManager log;

    int resultCount; // the total count of entries, returned from API
    int loadedCount; // number of already downloaded entries
    std::vector<std::string> urls;
    std::string method;
    
    void loadBunchOfResults(int startCount, int loadLimit);
public:
	CVKAudioLoader(CVKMethodCaller *caller, std::string method);
	~CVKAudioLoader();
    
    void loadAllUrls();
    void loadMoreUrls(int count);
    
    std::vector<std::string> &getUrls() {return urls;}
};

#endif
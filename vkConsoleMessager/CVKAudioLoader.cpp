

#include "CVKAudioLoader.h"

#include "CVKMethodHolder.h"
using namespace std;

CVKAudioLoader::CVKAudioLoader(CVKMethodCaller *caller, std::string method)
	: caller(caller), method(method + "&")
{
}
CVKAudioLoader::~CVKAudioLoader()
{
}

void CVKAudioLoader::loadBunchOfResults(int startCount, int loadLimit)
{
	int audioCount=0;
	int totalRead=0;
	while (true)
	{
		Json::Value audio;
		caller->call(CVKMethodHolder(method)
			.addParameter("offset", startCount + totalRead)
			.addParameter("count", min(200, loadLimit - totalRead))
			.toString(), audio);

		audioCount=audio["response"][0].asInt();
        audioCount = min(audioCount, loadLimit);

		for (int i=1; i<audio["response"].size(); i++)
			urls.push_back(audio["response"][i]["url"].asString());

		totalRead+=audio["response"].size()-1; // excluding first element, which is count
        if (audio["response"].size() == 1) // no more data
            break;

		if (totalRead >= audioCount)
			break; // we read everything
	}
}

void CVKAudioLoader::loadAllUrls()
{
    urls.clear();
    loadBunchOfResults(0, INT_MAX);
}

void CVKAudioLoader::loadMoreUrls(int count)
{
    loadBunchOfResults((int)urls.size(), count);
}


#include "CVKLongPollServer.h"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Form.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <sstream>

//#in

#define SUPER_SECRET_PROXY_STRING																																																																																						("fpm.kabak:g01562430g@proxy.bsu:3128")

CVKLongPollServer::CVKLongPollServer()
{
}
CVKLongPollServer::~CVKLongPollServer()
{
}

std::string CVKLongPollServer::sendToServer(std::string url, bool useProxy) const
{
	try
	{
		curlpp::Cleanup cleaner;
		curlpp::Easy request;
        
		request.setOpt(new curlpp::options::Url(url));
		request.setOpt(new curlpp::options::HttpGet(true));
		//request.setOpt(new curlpp::options::CaInfo("cacert.pem"));
		//request.setOpt(new curlpp::options::Verbose(true));
        
		if (useProxy)
			request.setOpt(new curlpp::options::Proxy(SUPER_SECRET_PROXY_STRING));
        
		request.setOpt(new curlpp::options::Header(true));
		std::list<std::string> header;
		header.push_back("Content-Type: text/html");
		request.setOpt(new curlpp::options::HttpHeader(header));
        
		std::ostringstream out;
		request.setOpt(new curlpp::options::WriteStream(&out));
        
		request.perform();
        
		return out.str();
	}
	catch ( curlpp::LogicError & e )
	{
		std::cerr << e.what() << std::endl;
	}
	catch ( curlpp::RuntimeError & e )
	{
		std::cerr << e.what() << std::endl;
	}
	catch ( ... )
	{
		std::cerr<<"OH MY!!!!!!!!!!!!!! 000OOO__ooooo0"<<std::endl;
	}
	return "";
}

int CVKLongPollServer::call(Json::Value &params, Json::Value &responce) const
{
	std::string uri("http://");
	uri += params["server"].asString();
	uri += "?act=a_check&key=";
    uri += params["key"].asString();
    uri += "&ts=";
    uri += params["ts"].asString();
    uri += "&wait=25&mode=2";
    
	// next, get our responce and parse it
	std::string resp=sendToServer(uri);
	if (!resp.size())
		return 1;
    
	// skip headers
	size_t startPos = resp.find("\r\n\r\n");
    if (startPos != std::string::npos)
    {
        // fix our string
        resp = resp.substr(startPos + 4);
        if (false) // if useProxy, we get two headers
        {
            size_t startPos = resp.find("\r\n\r\n");
            if (startPos != std::string::npos)
                resp = resp.substr(startPos + 4);
        }
    }
    else
	{
		std::cerr<<"Header not found!"<<std::endl;
		return 1;
	}
    
	//usleep(300000);
    
	// parse our answer
	Json::Reader parser;
	if (!parser.parse(resp, responce))
	{
		std::cerr<<"Json parse error!"<<std::endl;
		std::cerr<<parser.getFormattedErrorMessages();
		return 1;
	}
    
	return 0;
}
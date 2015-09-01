

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

#include "CLogManager.h"
#include "CVKAuthorizer.h"
#include "CVKMethodCaller.h"
#include "CVKLongPollServer.h"
#include "CVKMethodHolder.h"
#include "CVKMessage.h"
#include "CVKEvents.h"

const char *apertureLogo = \
"███████████████.,-:;//;:=,████████████████\n"\
"███████████.█:H@@@MM@M#H/.,+%;,███████████\n"\
"████████,/X+█+M@@M@MM%=,-%HMMM@X/,████████\n"\
"██████-+@MM;█$M@@MH+-,;XMMMM@MMMM@+-██████\n"\
"█████;@M@@M-█XM@X;.█-+XXXXXHHH@M@M#@/.████\n"\
"███,%MM@@MH█,@%=████████████.---=-=:=,.███\n"\
"███=@#@@@MX█.,██████████████-%HX$$%%%+;███\n"\
"██=-./@M@M$██████████████████.;@MMMM@MM:██\n"\
"██X@/█-$MM/████████████████████.+MM@@@M$██\n"\
"█,@M@H:█:@:████████████████████.█=X#@@@@-█\n"\
"█,@@@MMX,█.████████████████████/H-█;@M@M=█\n"\
"█.H@@@@M@+,████████████████████%MM+..%#$.█\n"\
"██/MMMM@MMH/.██████████████████XM@MH;█=;██\n"\
"███/%+%$XHH@$=██████████████,█.H@@@@MX,███\n"\
"████.=--------.███████████-%H.,@@@@@MX,███\n"\
"████.%MM@@@HHHXX$$$%+=█.:$MMX█=M@@MM%.████\n"\
"██████=XMMM@MM@MM#H;,-+HMM@M+█/MMMX=██████\n"\
"████████=%@M@M#@$-.=$@MM@@@M;█%M%=████████\n"\
"██████████,:+$+-,/H#MMMMMMM@=█=,██████████\n"\
"████████████████=++%%%%+/:-.██████████████\n";

const int appId = 1936127;
const unsigned long selfUserId = 17209872;
const string argSend = "-s";
const string argReceive = "-r";

CLogManager log(100);
CVKAuthorizer auth(appId);
CVKMethodCaller caller(&auth);

void printHelp(const char *progName)
{
    cout << "vkConsoleMessager, util to send and receive VK.com site messages" << endl;
    cout << "Usage:" << endl;
    cout << '\t' << progName << " -s <userID> message" << endl;
    cout << '\t' << progName << " -r <nil> <nil>" << endl;
}

string escape(const string &str)
{
    ostringstream out;
    out << hex;
    
    bool needsWrapping = false;
    for (int i = 0; i < str.size(); i++)
    {
        if (!isalnum(str[i]))
        {
            needsWrapping = true;
            out << "%" << ((int)str[i] & 0xFF);
        }
        else
            out << str[i];
    }
    
    return out.str();
}

void sendMessage(string msg, string subject, unsigned long targetId)
{
    Json::Value responce;
    caller.call(CVKMethodHolder("messages.send")
                .addParameter("uid", targetId)
                .addParameter("type", 1)
                .addParameter("message", escape(msg))
                .addParameter("title", escape(subject))
                .addParameter("guid", rand())
                .toString(), responce);
    vector<string> members = responce.getMemberNames();
    if (find(members.begin(), members.end(), "error") != members.end())
        std::cout << "Error " << responce["error"]["error_code"] << endl << responce["error"]["error_msg"] << std::endl;
}

void processMessage(string msg, string subject, unsigned long senderId, time_t timestamp)
{
    cout << "Message from " << senderId << ": " << subject << endl;
    cout << msg << endl;
    
    if (senderId != selfUserId)
    {
        string searchMsg(msg);
        std::transform(searchMsg.begin(), searchMsg.end(), searchMsg.begin(), ::tolower);
        if (searchMsg.find("ascii") != string::npos &&
            searchMsg.find("#science") != string::npos)
        {
            istringstream logo(apertureLogo);
            string line;
            while (!logo.eof())
            {
                getline(logo, line);
                sendMessage(line, "...", senderId);
                usleep(300000);
            }
        }
    }
}

int main(int argc, const char **argv)
{
    srand(time(0));
    auth.setPriviledge(VK_PRIV_MESSAGES, true);
    auth.setPriviledge(VK_PRIV_OFFLINE, true);
    auth.setPriviledge(VK_PRIV_AUDIO, true);
    //std::cout << auth.getAuthString() << std::endl;
    
    {
        // latest available token (will remain valid until password is changed)
        std::string responce = "http://api.vk.com/blank.html#access_token=a4da3ef8a5dca4e8a5dca4e8b5a5c12e17aa5dea5ddb4e0f54f2976368bee8f57ec2378&expires_in=0&user_id=17209872";
        auth.parseResponce(responce);
    }
    
    // parsing command line args
    if (argc < 4)
    {
        printHelp(argv[0]);
        return 1;
    }
    
    if (argSend == argv[1])
    {
        string message;
        for (int i=3; i<argc; i++)
        {
            message += argv[i];
            message += " ";
        }
        
        unsigned long targetId = 0;
        istringstream inp(argv[2]);
        inp >> targetId;
        sendMessage(message, "...", targetId);
    }
    else if (argReceive == argv[1])
    {
        Json::Value result;
        caller.call(CVKMethodHolder("messages.getLongPollServer??")
                    .toString(), result);
        vector<string> members = result.getMemberNames();
        if (find(members.begin(), members.end(), "error") != members.end())
        {
            std::cout << "Error " << result["error"]["error_code"] << endl << result["error"]["error_msg"] << std::endl;
            return 1;
        }
        
        CVKLongPollServer longPoll;
        Json::Value pollResult;
        Json::Value params = result["response"];
        while (true)
        {
            longPoll.call(params, pollResult);
            // check for errors
            vector<string> members = result.getMemberNames();
            if (find(members.begin(), members.end(), "error") != members.end())
            {
                // requesting params again
                caller.call(CVKMethodHolder("messages.getLongPollServer??")
                            .toString(), result);
                vector<string> members = result.getMemberNames();
                if (find(members.begin(), members.end(), "error") != members.end())
                {
                    std::cout << "Error " << result["error"]["error_code"] << endl << result["error"]["error_msg"] << std::endl;
                    return 1;
                }
                Json::Value params = result["response"];
            }
            // advance events
            params["ts"] = pollResult["ts"];
            // and output them to the console
            for (int i=0; i<pollResult["updates"].size(); i++)
            {
                Json::Value &event = pollResult["updates"][i];
                // event format: 4,$message_id,$flags,$from_id,$timestamp,$subject,$text,$attachments
                if (event[0].asInt() == VK_EVENT_MESSAGE_ADDED && (event[2].asInt() & VK_MF_UNREAD) && !(event[2].asInt() & VK_MF_OUTBOX))
                    processMessage(event[6].asString(), event[5].asString(), event[3].asUInt64(), event[4].asUInt64());
            }
        }
    }
    
    
    return 0;
}
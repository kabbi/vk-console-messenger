

#ifndef __C_LOG_MANAGER
#define __C_LOG_MANAGER

#include <iostream>

template<typename Ch, typename Traits = std::char_traits<Ch> >
struct basic_nullbuf : std::basic_streambuf<Ch, Traits> {
    typedef std::basic_streambuf<Ch, Traits> base_type;
    typedef typename base_type::int_type int_type;
    typedef typename base_type::traits_type traits_type;
    
    virtual int_type overflow(int_type c) {
        return traits_type::not_eof(c);
    }
};

typedef basic_nullbuf<char> nullbuf;
typedef basic_nullbuf<wchar_t> wnullbuf;

extern std::ostream cnull;
extern std::wostream wcnull;

class CLogManager
{
protected:
    int verboseLevel;
public:
    CLogManager(int verboseLevel = 0);
    ~CLogManager();
    
    std::ostream &operator()(int logLevel=0);
    CLogManager &instance();
};

#endif

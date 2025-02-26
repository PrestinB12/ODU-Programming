#ifndef SPOOL_H
#define SPOOL_H

#include <string>

struct Spool
{
    std::string str;

    Spool(std::string s) : str(s) {}

    bool operator<(const Spool &right) const { return str < right.str; }
    bool operator==(const Spool &right) const { return str == right.str; }
};

class SpoolHasher
{
public:
    std::size_t operator()(const Spool &sp) const
    {
        std::hash<std::string> str_hash;
        return str_hash(sp.str);
    }
};

namespace std
{

    template <>
    struct hash<Spool> // denotes a specialization of hash<...>
    {
        std::size_t operator()(const Spool &spool) const
        {
            std::hash<std::string> str_hash;
			return str_hash(spool.str);
        }
    };

}

#endif
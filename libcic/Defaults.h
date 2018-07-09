#ifndef LIBCIC_DEFAULTS_H
#define LIBCIC_DEFAULTS_H

struct Defaults
{
    friend class BlockChain;
    friend class State;

public:
    Defaults();

    static Defaults* get() { if (!s_this) s_this = new Defaults; return s_this; }
    static void setDBPath(boost::filesystem::path const& _dbPath) { get()->m_dbPath = _dbPath; }
    static boost::filesystem::path const& dbPath() { return get()->m_dbPath; }

private:
    boost::filesystem::path m_dbPath;

    static Defaults* s_this;
};

#endif //LIBCIC_DEFAULTS_H

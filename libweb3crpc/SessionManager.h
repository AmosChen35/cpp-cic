#ifndef LIBWEB3CRPC_SESSIONMANAGER_H
#define LIBWEB3CRPC_SESSIONMANAGER_H

#define RPC_ADMIN if (!m_sm.hasPrivilegeLevel(_session, Privilege::Admin)) throw jsonrpc::JsonRpcException("Invalid privileges");

struct SessionPermissions
{
    std::unordered_set<Privilege> privileges;
};

class SessionManager
{
public:
    std::string newSession(SessionPermissions const& _p);
    void addSession(std::string const& _session, SessionPermissions const& _p);
    bool hasPrivilegeLevel(std::string const& _session, Privilege _l) const;

private:
    std::unordered_map<std::string, SessionPermissions> m_sessions;
};

#endif //LIBWEB3CRPC_SESSIONMANAGER_H

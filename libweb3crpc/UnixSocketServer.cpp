#include "libweb3crpc.h"

using namespace std;
using namespace jsonrpc;
using namespace CI;
using namespace CI::col;

namespace fs = boost::filesystem;

namespace CI
{
namespace col
{
size_t const c_socketPathMaxLength = sizeof(sockaddr_un::sun_path) / sizeof(sockaddr_un::sun_path[0]);

fs::path getIpcPathOrDataDir()
{
    // On Unix use datadir as default IPC path.
    fs::path path = getIpcPath();
    if (path.empty())
        return getDataDir();
    return path;
}

} //namespace col
} //namespace CI

UnixDomainSocketServer::UnixDomainSocketServer(string const& _appId):
    IpcServerBase((getIpcPathOrDataDir() / fs::path(_appId + ".ipc")).string().substr(0, c_socketPathMaxLength))
{
}

UnixDomainSocketServer::~UnixDomainSocketServer()
{
    StopListening();
}

bool UnixDomainSocketServer::StartListening()
{
    if (!m_running)
    {
        if (access(m_path.c_str(), F_OK) != -1)
            unlink(m_path.c_str());

        if (access(m_path.c_str(), F_OK) != -1)
            return false;

        m_socket = socket(PF_UNIX, SOCK_STREAM, 0);
        memset(&(m_address), 0, sizeof(sockaddr_un));
        m_address.sun_family = AF_UNIX;
#ifdef __APPLE__
        m_address.sun_len = m_path.size() + 1;
#endif
        strncpy(m_address.sun_path, m_path.c_str(), c_socketPathMaxLength);
        ::bind(m_socket, reinterpret_cast<sockaddr*>(&m_address), sizeof(sockaddr_un));
        fs::permissions(m_path, fs::owner_read | fs::owner_write);
        listen(m_socket, 128);
    }
    return IpcServerBase::StartListening();
}

bool UnixDomainSocketServer::StopListening()
{
    shutdown(m_socket, SHUT_RDWR);
    close(m_socket);
    m_socket = -1;
    if (IpcServerBase::StopListening())
    {
        unlink(m_path.c_str());
        return true;
    }
    return false;
}

void UnixDomainSocketServer::Listen()
{
    socklen_t addressLen = sizeof(m_address);
    while (m_running)
    {
        int connection = accept(m_socket, (sockaddr*) &(m_address), &addressLen);
        if (connection > 0)
        {
            DEV_GUARDED(x_sockets)
                m_sockets.insert(connection);

            // Handle the request in a new detached thread.
            std::thread{[this, connection]
            {
                GenerateResponse(connection);
                CloseConnection(connection);
            }}.detach();
        }
    }
}

void UnixDomainSocketServer::CloseConnection(int _socket)
{
    shutdown(_socket, SHUT_RDWR);
    close(_socket);
}


size_t UnixDomainSocketServer::Write(int _connection, string const& _data)
{
    ssize_t r = send(_connection, _data.data(), _data.size(), MSG_NOSIGNAL);
    if (r < 0)
        return 0;
    return static_cast<size_t>(r);
}

size_t UnixDomainSocketServer::Read(int _connection, void* _data, size_t _size)
{
    ssize_t r = read(_connection, _data, _size);
    if (r < 0)
        return 0;
    return static_cast<size_t>(r);
}

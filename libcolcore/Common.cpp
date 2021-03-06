#include "libcolcore.h"

namespace CI
{
namespace col
{
char const* Version = cic_get_buildinfo()->project_version;
std::string const EmptyString;

bytes const NullBytes;

int64_t utcTime()
{
    // TODO: Fix if possible to not use time(0) and merge only after testing in all platforms
    // time_t t = time(0);
    // return mktime(gmtime(&t));
    return time(0);
}

void InvariantChecker::checkInvariants(HasInvariants const* _this, char const* _fn, char const* _file, int _line, bool _pre)
{
    if (!_this->invariants())
    {
        cwarn << (_pre ? "Pre" : "Post") << "invariant failed in" << _fn << "at" << _file << ":" << _line;
        ::boost::exception_detail::throw_exception_(FailedInvariant(), _fn, _file, _line);
    }
}

TimerHelper::~TimerHelper()
{
    auto e = std::chrono::high_resolution_clock::now() - m_t;
    if (!m_ms || e > std::chrono::milliseconds(m_ms))
        clog(VerbosityDebug, "timer")
            << m_id << " " << std::chrono::duration_cast<std::chrono::milliseconds>(e).count() << " ms";
}

} //namespace col
} //namespace CI

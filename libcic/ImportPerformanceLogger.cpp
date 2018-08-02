#include "libcic.h"

namespace CI
{
namespace cic
{

template <class ValueType>
static std::string pairToString(std::pair<std::string const, ValueType> const& _pair)
{
    return "\"" + _pair.first + "\": " + toString(_pair.second);
}

} //namespace cic
} //namespace CI

using namespace std;
using namespace CI;
using namespace CI::col;
using namespace CI::cic;

std::string ImportPerformanceLogger::constructReport(double _totalElapsed, std::unordered_map<std::string, std::string> const& _additionalValues)
{
    static std::string const Separator = ", ";

    std::string result;
    if (!_additionalValues.empty())
    {
        auto const keyValuesAdditional = _additionalValues | boost::adaptors::transformed(pairToString<std::string>);
        result += boost::algorithm::join(keyValuesAdditional, Separator);
        result += Separator;
    }

    m_stages.emplace("total", _totalElapsed);
    auto const keyValuesStages = m_stages | boost::adaptors::transformed(pairToString<double>);
    result += boost::algorithm::join(keyValuesStages, Separator);

    return result;
}

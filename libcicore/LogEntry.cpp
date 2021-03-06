#include "libcicore.h"

using namespace CI;
using namespace CI::cic;

LogEntry::LogEntry(RLP const& _r)
{
	assert(_r.itemCount() == 3);
	address = (Address)_r[0];
	topics = _r[1].toVector<h256>();
	data = _r[2].toBytes();
}

void LogEntry::streamRLP(RLPStream& _s) const
{
	_s.appendList(3) << address << topics << data;
}

LogBloom LogEntry::bloom() const
{
	LogBloom ret;
	ret.shiftBloom<3>(sha3(address.ref()));
	for (auto t: topics)
		ret.shiftBloom<3>(sha3(t.ref()));
	return ret;
}

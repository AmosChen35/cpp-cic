#include "libcic.h"

using namespace std;
using namespace CI;
using namespace CI::col;
using namespace CI::cic;

Defaults* Defaults::s_this = nullptr;

Defaults::Defaults()
{
	m_dbPath = getDataDir();
}

#include "libcihashseal.h"

//Client configurations
#include "genesis/mainNetwork.cpp"
//#include "genesis/ropsten.cpp"

using namespace CI;
using namespace CI::col;
using namespace CI::cic;

static h256 const c_genesisDefaultStateRoot;

std::string const& CI::cic::genesisInfo(Network _n)
{
    switch (_n)
    {
    //Client genesis
    case Network::MainNetwork: return c_genesisInfoMainNetwork;
    //case Network::Ropsten: return c_genesisInfoRopsten;

    //FIXME
    /*
    //Test genesis
    case Network::MainNetworkTest: return c_genesisInfoMainNetworkTest;
    case Network::MainNetworkNoProofTest: return c_genesisInfoMainNetworkNoProofTest;
    case Network::FrontierNoProofTest: return c_genesisInfoFrontierNoProofTest;
    case Network::FrontierTest: return c_genesisInfoFrontierTest;
    case Network::HomesteadTest: return c_genesisInfoHomesteadTest;
    case Network::EIP150Test: return c_genesisInfoEIP150Test;
    case Network::EIP158Test: return c_genesisInfoEIP158Test;
    case Network::ByzantiumTest: return c_genesisInfoByzantiumTest;
    case Network::ByzantiumTransitionTest: return c_genesisInfoByzantiumTransitionTest;
    case Network::ConstantinopleTest: return c_genesisInfoConstantinopleTest;
    case Network::ConstantinopleTransitionTest: return c_genesisInfoConstantinopleTransitionTest;

    //Transition test genesis
    case Network::FrontierToHomesteadAt5: return c_genesisInfoFrontierToHomesteadAt5Test;
    case Network::HomesteadToDaoAt5: return c_genesisInfoHomesteadToDaoAt5Test;
    case Network::HomesteadToEIP150At5: return c_genesisInfoHomesteadToEIP150At5Test;
    case Network::EIP158ToByzantiumAt5: return c_genesisInfoEIP158ToByzantiumAt5Test;
    case Network::TransitionnetTest: return c_genesisInfoTest;
    */

    default:
        throw std::invalid_argument("Invalid network value");
    }
}

h256 const& CI::cic::genesisStateRoot(Network _n)
{
    switch (_n)
    {
    case Network::MainNetwork: return c_genesisStateRootMainNetwork;
    //case Network::Ropsten:

    //FIME
    /*
    case Network::Ropsten:
    case Network::MainNetworkTest:
    case Network::TransitionnetTest:
    case Network::FrontierTest:
    case Network::HomesteadTest: \
    case Network::EIP150Test:
    case Network::EIP158Test:
    case Network::ByzantiumTest:
    case Network::ConstantinopleTest:
    case Network::ConstantinopleTransitionTest:
    */
        return c_genesisDefaultStateRoot;

    default:
        throw std::invalid_argument("Invalid network value");
    }
}

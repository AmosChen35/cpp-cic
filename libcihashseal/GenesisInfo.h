#ifndef LIBCIHASHSEAL_GENESISINFO_H
#define LIBCIHASHSEAL_GENESISINFO_H

/// The network id.
enum class Network
{
    //Olympic = 0,          ///< Normal Olympic chain.
    MainNetwork = 1,        ///< Normal Frontier/Homestead/DAO/EIP150/EIP158/Byzantium/Constantinople chain.
    //Morden = 2,           ///< Normal Morden chain.
    Ropsten = 3,            ///< New Ropsten Test Network

    /*
    MainNetworkTest = 69,   ///< MainNetwork rules but without genesis accounts (for transaction tests).
    TransitionnetTest = 70, ///< Normal Frontier/Homestead/DAO/EIP150/EIP158 chain without all the premine.
    FrontierTest = 71,      ///< Just test the Frontier-era characteristics "forever" (no Homestead portion).
    HomesteadTest = 72,     ///< Just test the Homestead-era characteristics "forever" (no Frontier portion).
    EIP150Test = 73,        ///< Homestead + EIP150 Rules active from block 0 For BlockchainTests
    EIP158Test = 74,        ///< Homestead + EIP150 + EIP158 Rules active from block 0
    ByzantiumTest = 75,   ///< EIP158Test + Byzantium active from block 0
    ByzantiumTransitionTest = 76, ///< EIP158Test + Byzantium active from block 2
    FrontierNoProofTest = 77, ///< Frontier rules + NoProof seal engine
    ConstantinopleTest = 78, ///< ByzantiumTest + Constantinople active from block 0
    ConstantinopleTransitionTest = 79, ///< ByzantiumTest + Constantinople active from block 2
    MainNetworkNoProofTest = 80, ///< MainNetwork rules without genesis accounts + NoProof seal engine

    //TransitionTest networks
    FrontierToHomesteadAt5 = 100,
    HomesteadToDaoAt5 = 101,
    HomesteadToEIP150At5 = 102,
    EIP158ToByzantiumAt5 = 103,
    */

    Special = 0xff          ///< Something else.
};

std::string const& genesisInfo(Network _n);
h256 const& genesisStateRoot(Network _n);

#endif //LIBCIHASHSEAL_GENESISINFO_H

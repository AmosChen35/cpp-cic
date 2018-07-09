#ifndef LIBCOLCORE_ADDRESS_H
#define LIBCOLCORE_ADDRESS_H

/// An Ethereum address: 20 bytes.
/// @NOTE This is not endian-specific; it's just a bunch of bytes.
using Address = h160;

/// A vector of Ethereum addresses.
using Addresses = h160s;

/// A hash set of Ethereum addresses.
using AddressHash = std::unordered_set<h160>;

/// The zero address.
extern Address const ZeroAddress;

/// The last address.
extern Address const MaxAddress;

/// The SYSTEM address.
extern Address const SystemAddress;

#endif //LIBCOLCORE_ADDRESS_H

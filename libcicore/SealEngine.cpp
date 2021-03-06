#include "libcicore.h"

using namespace std;
using namespace CI;
using namespace CI::cic;

SealEngineRegistrar* SealEngineRegistrar::s_this = nullptr;

void NoProof::init()
{
    ETH_REGISTER_SEAL_ENGINE(NoProof);
}

void SealEngineFace::verify(Strictness _s, BlockHeader const& _bi, BlockHeader const& _parent, bytesConstRef _block) const
{
    _bi.verify(_s, _parent, _block);
}

void SealEngineFace::populateFromParent(BlockHeader& _bi, BlockHeader const& _parent) const
{
    _bi.populateFromParent(_parent);
}

void SealEngineFace::verifyTransaction(ImportRequirements::value _ir, TransactionBase const& _t,
    BlockHeader const& _header, u256 const& _gasUsed) const
{
    if ((_ir & ImportRequirements::TransactionSignatures) && _header.number() < chainParams().EIP158ForkBlock && _t.isReplayProtected())
        BOOST_THROW_EXCEPTION(InvalidSignature());

    if ((_ir & ImportRequirements::TransactionSignatures) && _header.number() < chainParams().constantinopleForkBlock && _t.hasZeroSignature())
        BOOST_THROW_EXCEPTION(InvalidSignature());

    if ((_ir & ImportRequirements::TransactionBasic) &&
        _header.number() >= chainParams().constantinopleForkBlock &&
        _t.hasZeroSignature() &&
        (_t.value() != 0 || _t.gasPrice() != 0 || _t.nonce() != 0))
            BOOST_THROW_EXCEPTION(InvalidZeroSignatureTransaction() << errinfo_got((bigint)_t.gasPrice()) << errinfo_got((bigint)_t.value()) << errinfo_got((bigint)_t.nonce()));

    if (_header.number() >= chainParams().homesteadForkBlock && (_ir & ImportRequirements::TransactionSignatures) && _t.hasSignature())
        _t.checkLowS();

    EVMSchedule const& schedule = evmSchedule(_header.number());

    // Pre calculate the gas needed for execution
    if ((_ir & ImportRequirements::TransactionBasic) && _t.baseGasRequired(schedule) > _t.gas())
        BOOST_THROW_EXCEPTION(OutOfGasIntrinsic() << RequirementError(
                                  (bigint)(_t.baseGasRequired(schedule)), (bigint)_t.gas()));

    // Avoid transactions that would take us beyond the block gas limit.
    if (_gasUsed + (bigint)_t.gas() > _header.gasLimit())
        BOOST_THROW_EXCEPTION(BlockGasLimitReached() << RequirementErrorComment(
                                  (bigint)(_header.gasLimit() - _gasUsed), (bigint)_t.gas(),
                                  string("_gasUsed + (bigint)_t.gas() > _header.gasLimit()")));
}

SealEngineFace* SealEngineRegistrar::create(ChainOperationParams const& _params)
{
    SealEngineFace* ret = create(_params.sealEngineName);
    assert(ret && "Seal engine not found.");
    if (ret)
        ret->setChainParams(_params);
    return ret;
}

EVMSchedule const& SealEngineBase::evmSchedule(u256 const& _blockNumber) const
{
    return chainParams().scheduleForBlockNumber(_blockNumber);
}

u256 SealEngineBase::blockReward(u256 const& _blockNumber) const
{
    EVMSchedule const& schedule{evmSchedule(_blockNumber)};
    return chainParams().blockReward(schedule);
}


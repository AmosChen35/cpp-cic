#ifndef LIBCOLCORE_EXECPTIONS_H
#define LIBCOLCORE_EXECPTIONS_H

/// Base class for all exceptions.
struct Exception : virtual std::exception, virtual boost::exception
{
    const char* what() const noexcept override { return boost::diagnostic_information_what(*this); }
};

#define DEV_SIMPLE_EXCEPTION(X)  \
    struct X : virtual Exception \
    {                            \
    }

/// Base class for all RLP exceptions.
struct RLPException : virtual Exception
{
};
#define DEV_SIMPLE_EXCEPTION_RLP(X) \
    struct X : virtual RLPException \
    {                               \
    }

DEV_SIMPLE_EXCEPTION_RLP(BadCast);
DEV_SIMPLE_EXCEPTION_RLP(BadRLP);
DEV_SIMPLE_EXCEPTION_RLP(OversizeRLP);
DEV_SIMPLE_EXCEPTION_RLP(UndersizeRLP);

DEV_SIMPLE_EXCEPTION(BadHexCharacter);
DEV_SIMPLE_EXCEPTION(NoNetworking);
DEV_SIMPLE_EXCEPTION(NoUPnPDevice);
DEV_SIMPLE_EXCEPTION(RootNotFound);
DEV_SIMPLE_EXCEPTION(BadRoot);
DEV_SIMPLE_EXCEPTION(FileError);
DEV_SIMPLE_EXCEPTION(Overflow);
DEV_SIMPLE_EXCEPTION(FailedInvariant);
DEV_SIMPLE_EXCEPTION(ValueTooLarge);
DEV_SIMPLE_EXCEPTION(UnknownField);
DEV_SIMPLE_EXCEPTION(InterfaceNotSupported);
DEV_SIMPLE_EXCEPTION(ExternalFunctionFailure);

// error information to be added to exceptions
using errinfo_invalidSymbol = boost::error_info<struct tag_invalidSymbol, char>;
using errinfo_wrongAddress = boost::error_info<struct tag_address, std::string>;
using errinfo_comment = boost::error_info<struct tag_comment, std::string>;
using errinfo_required = boost::error_info<struct tag_required, bigint>;
using errinfo_got = boost::error_info<struct tag_got, bigint>;
using errinfo_min = boost::error_info<struct tag_min, bigint>;
using errinfo_max = boost::error_info<struct tag_max, bigint>;
using RequirementError = boost::tuple<errinfo_required, errinfo_got>;
using RequirementErrorComment = boost::tuple<errinfo_required, errinfo_got, errinfo_comment>;
using errinfo_hash256 = boost::error_info<struct tag_hash, h256>;
using errinfo_required_h256 = boost::error_info<struct tag_required_h256, h256>;
using errinfo_got_h256 = boost::error_info<struct tag_get_h256, h256>;
using Hash256RequirementError = boost::tuple<errinfo_required_h256, errinfo_got_h256>;
using errinfo_extraData = boost::error_info<struct tag_extraData, bytes>;
using errinfo_externalFunction = boost::errinfo_api_function;
using errinfo_interface = boost::error_info<struct tag_interface, std::string>;
using errinfo_path = boost::error_info<struct tag_path, std::string>;

#endif //LIBCOLCORE_EXECPTIONS_H

#ifndef LIBCVM_VMFACTORY_H
#define LIBCVM_VMFACTORY_H

enum class VMKind
{
    Interpreter,
    JIT,
    Hera,
    Legacy,
    DLL
};

/// Returns the EVM-C options parsed from command line.
std::vector<std::pair<std::string, std::string>>& evmcOptions() noexcept;

/// Provide a set of program options related to VMs.
///
/// @param _lineLength  The line length for description text wrapping, the same as in
///                     boost::program_options::options_description::options_description().
boost::program_options::options_description vmProgramOptions(
    unsigned _lineLength = boost::program_options::options_description::m_default_line_length);

class VMFactory
{
public:
    VMFactory() = delete;
    ~VMFactory() = delete;

    /// Creates a VM instance of the global kind (controlled by the --vm command line option).
    static std::unique_ptr<VMFace> create();

    /// Creates a VM instance of the kind provided.
    static std::unique_ptr<VMFace> create(VMKind _kind);
};

#endif //LIBCVM_VMFACTORY_H

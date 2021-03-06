#ifndef LIBCOLCORE_FILESYSTEM_H
#define LIBCOLCORE_FILESYSTEM_H

/// Sets the data dir for the default ("ethereum") prefix.
void setDataDir(boost::filesystem::path const& _dir);
/// @returns the path for user data.
boost::filesystem::path getDataDir(std::string _prefix = "ethereum");
/// @returns the default path for user data, ignoring the one set by `setDataDir`.
boost::filesystem::path getDefaultDataDir(std::string _prefix = "ethereum");
/// Sets the ipc socket dir
void setIpcPath(boost::filesystem::path const& _ipcPath);
/// @returns the ipc path (default is DataDir)
boost::filesystem::path getIpcPath();

/// @returns a new path whose file name is suffixed with the given suffix.
boost::filesystem::path appendToFilename(boost::filesystem::path const& _orig, std::string const& _suffix);

#endif //LIBCOLCORE_FILESYSTEM_H

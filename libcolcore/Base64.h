#ifndef LIBCOLCORE_BASE64_H
#define LIBCOLCORE_BASE64_H

std::string toBase64(bytesConstRef _in);
bytes fromBase64(std::string const& _in);

#endif //LIBCOLCORE_BASE64_H

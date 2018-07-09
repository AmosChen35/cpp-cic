#ifndef LIBCOLCORE_AES_H
#define LIBCOLCORE_AES_H

bytes aesDecrypt(bytesConstRef _cipher, std::string const& _password, unsigned _rounds = 2000, bytesConstRef _salt = bytesConstRef());

#endif //LIBCOLCORE_AES_H

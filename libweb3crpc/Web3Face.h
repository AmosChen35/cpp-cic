#ifndef LIBWEB3CRPC_WEB3FACE_H
#define LIBWEB3CRPC_WEB3FACE_H

class Web3Face : public ServerInterface<Web3Face>
{
    public:
        Web3Face()
        {
            this->bindAndAddMethod(jsonrpc::Procedure("web3_sha3", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_STRING, "param1",jsonrpc::JSON_STRING, NULL), &CI::crpc::Web3Face::web3_sha3I);
            this->bindAndAddMethod(jsonrpc::Procedure("web3_clientVersion", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_STRING,  NULL), &CI::crpc::Web3Face::web3_clientVersionI);
        }

        inline virtual void web3_sha3I(const Json::Value &request, Json::Value &response)
        {
            response = this->web3_sha3(request[0u].asString());
        }
        inline virtual void web3_clientVersionI(const Json::Value &request, Json::Value &response)
        {
            (void)request;
            response = this->web3_clientVersion();
        }
        virtual std::string web3_sha3(const std::string& param1) = 0;
        virtual std::string web3_clientVersion() = 0;
};

#endif //LIBWEB3CRPC_WEB3FACE_H

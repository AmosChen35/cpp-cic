#ifndef LIBWEB3CRPC_NETFACE_H
#define LIBWEB3CRPC_NETFACE_H

class NetFace : public ServerInterface<NetFace>
{
    public:
        NetFace()
        {
            this->bindAndAddMethod(jsonrpc::Procedure("net_version", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_STRING,  NULL), &CI::crpc::NetFace::net_versionI);
            //FIXME
            /*
            this->bindAndAddMethod(jsonrpc::Procedure("net_peerCount", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_STRING,  NULL), &CI::crpc::NetFace::net_peerCountI);
            this->bindAndAddMethod(jsonrpc::Procedure("net_listening", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_BOOLEAN,  NULL), &CI::crpc::NetFace::net_listeningI);
            */
        }

        inline virtual void net_versionI(const Json::Value &request, Json::Value &response)
        {
            (void)request;
            response = this->net_version();
        }
        //FIXME
        /*
        inline virtual void net_peerCountI(const Json::Value &request, Json::Value &response)
        {
            (void)request;
            response = this->net_peerCount();
        }
        inline virtual void net_listeningI(const Json::Value &request, Json::Value &response)
        {
            (void)request;
            response = this->net_listening();
        }
        */
        virtual std::string net_version() = 0;

        //FIXME
        /*
        virtual std::string net_peerCount() = 0;
        virtual bool net_listening() = 0;
        */
};

#endif //LIBWEB3CRPC_NETFACE_H

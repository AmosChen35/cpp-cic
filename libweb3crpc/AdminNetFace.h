#ifndef LIBWEB3CRPC_ADMINNETFACE_H
#define LIBWEB3CRPC_ADMINNETFACE_H

class AdminNetFace : public ServerInterface<AdminNetFace>
{
    public:
        AdminNetFace()
        {
            this->bindAndAddMethod(jsonrpc::Procedure("admin_net_start", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_BOOLEAN, "param1",jsonrpc::JSON_STRING, NULL), &CI::crpc::AdminNetFace::admin_net_startI);
            this->bindAndAddMethod(jsonrpc::Procedure("admin_net_stop", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_BOOLEAN, "param1",jsonrpc::JSON_STRING, NULL), &CI::crpc::AdminNetFace::admin_net_stopI);
            //FIXME
            /*
            this->bindAndAddMethod(jsonrpc::Procedure("admin_net_connect", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_BOOLEAN, "param1",jsonrpc::JSON_STRING,"param2",jsonrpc::JSON_STRING, NULL), &CI::crpc::AdminNetFace::admin_net_connectI);
            this->bindAndAddMethod(jsonrpc::Procedure("admin_net_peers", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_ARRAY, "param1",jsonrpc::JSON_STRING, NULL), &CI::crpc::AdminNetFace::admin_net_peersI);
            */
            this->bindAndAddMethod(jsonrpc::Procedure("admin_net_nodeInfo", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_OBJECT, "param1",jsonrpc::JSON_STRING, NULL), &CI::crpc::AdminNetFace::admin_net_nodeInfoI);
            this->bindAndAddMethod(jsonrpc::Procedure("admin_nodeInfo", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_OBJECT,  NULL), &CI::crpc::AdminNetFace::admin_nodeInfoI);
            //FIXME
            /*
            this->bindAndAddMethod(jsonrpc::Procedure("admin_peers", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_OBJECT,  NULL), &CI::crpc::AdminNetFace::admin_peersI);
            this->bindAndAddMethod(jsonrpc::Procedure("admin_addPeer", jsonrpc::PARAMS_BY_POSITION, jsonrpc::JSON_BOOLEAN, "param1",jsonrpc::JSON_STRING, NULL), &CI::crpc::AdminNetFace::admin_addPeerI);
            */
        }

        inline virtual void admin_net_startI(const Json::Value &request, Json::Value &response)
        {
            response = this->admin_net_start(request[0u].asString());
        }
        inline virtual void admin_net_stopI(const Json::Value &request, Json::Value &response)
        {
            response = this->admin_net_stop(request[0u].asString());
        }
        //FIXME
        /*
        inline virtual void admin_net_connectI(const Json::Value &request, Json::Value &response)
        {
            response = this->admin_net_connect(request[0u].asString(), request[1u].asString());
        }
        inline virtual void admin_net_peersI(const Json::Value &request, Json::Value &response)
        {
            response = this->admin_net_peers(request[0u].asString());
        }
        */
        inline virtual void admin_net_nodeInfoI(const Json::Value &request, Json::Value &response)
        {
            response = this->admin_net_nodeInfo(request[0u].asString());
        }
        inline virtual void admin_nodeInfoI(const Json::Value &request, Json::Value &response)
        {
            (void)request;
            response = this->admin_nodeInfo();
        }
        //FIXME
        /*
        inline virtual void admin_peersI(const Json::Value &request, Json::Value &response)
        {
            (void)request;
            response = this->admin_peers();
        }
        inline virtual void admin_addPeerI(const Json::Value &request, Json::Value &response)
        {
            response = this->admin_addPeer(request[0u].asString());
        }
        */
        virtual bool admin_net_start(const std::string& param1) = 0;
        virtual bool admin_net_stop(const std::string& param1) = 0;
        /*
        virtual bool admin_net_connect(const std::string& param1, const std::string& param2) = 0;
        virtual Json::Value admin_net_peers(const std::string& param1) = 0;
        */
        virtual Json::Value admin_net_nodeInfo(const std::string& param1) = 0;
        virtual Json::Value admin_nodeInfo() = 0;
        //FIXME
        /*
        virtual Json::Value admin_peers() = 0;
        virtual bool admin_addPeer(const std::string& param1) = 0;
        */
};

#endif //LIBWEB3CRPC_ADMINNETFACE_H

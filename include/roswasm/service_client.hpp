#include <roswasm/roswasm.h>
#include <roswasm/publisher.h>
#include <roscpp_json/serialize.h>
#include <roscpp_json/deserialize.h>

namespace roswasm {

template <typename SRV>
void ServiceClientImpl<SRV>::call(const typename SRV::Request& req, const std::string& service_name)
{
    std::string json_msg = roscpp_json::serialize(req, false);
    std::string message = "\"op\":\"call_service\", \"service\":\"" + service_name + "\", \"args\":" + json_msg + ", \"id\":\"" + id + "\"";
    message = std::string("{ ") + message + " }";
    nh->send_message(message);
}

template <typename SRV>
void ServiceClientImpl<SRV>::callback(const std::string& buffer, bool result)
{
    std::cout << "Got service response: " << buffer << std::endl;
    typename SRV::Response res;
    if (result) {
        res = roscpp_json::deserialize<typename SRV::Response>(buffer);
    }
    impl_callback(res, result);
}

} // namespace roswasm
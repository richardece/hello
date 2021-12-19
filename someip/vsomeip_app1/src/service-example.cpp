/*
In this example, we show how to offer and request for a service.

A server offers a service.
Client requests for the same service.
Client registers a callback once a service becomes available/not available.
*/

#include <vsomeip/vsomeip.hpp>

#define SAMPLE_SERVICE_ID 0x1234
#define SAMPLE_INSTANCE_ID 0x5678

std::shared_ptr< vsomeip::application > app;

int main() {

    app = vsomeip::runtime::get()->create_application("World");
    app->init();
    /*
    Init performs the following:
    1. load the configuration
        - if there is no configuration specified, default config is used.
        - if there is no configuration for the routing manager, the routing manager
            will be automatically started inside this application
        - if client ID is not configured, the first client ID will be 0x0001
    2. determine routing configuration
    3. install signal handler 
    */
    app->offer_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
    app->start();   //starts message processing
                    // receieved messsages are processed via sockets and registered 
                    //      callbacks are used to pass them to application    
}
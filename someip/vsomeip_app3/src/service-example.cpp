/*
This example shows how to subscribe/notify events.
A server can send events and subscribers can subscribe if they are interested to the event.

The server offers an event (like announcing to the world about the existence of this event).
It then calls the notify method to send the event to all subscribers.
Every event belongs to an event group. It can also belong to several groups.
Events co-exist with a service. If a service is not offered, subscribers cannot subscribe to the event.

Client registers for servise availability and requests for the service.
It also registers a message handler for all types of services.
When the service becomes available, it requests for the event and subscribes to it.
When the server notifies the event, the message handler will be called.

*/

#include <iomanip>
#include <iostream>
#include <sstream>

#include <vsomeip/vsomeip.hpp>

#define SAMPLE_SERVICE_ID 0x1234
#define SAMPLE_INSTANCE_ID 0x5678
#define SAMPLE_EVENTGROUP_ID 0x4465
#define SAMPLE_EVENT_ID 0x8778

std::shared_ptr<vsomeip::application> app;


int main() {

   app = vsomeip::runtime::get()->create_application("Service-server");
   app->init();

   //Offer service
   app->offer_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);

   //Offer event
   const vsomeip::byte_t its_data[] = { 0x10 };
   std::shared_ptr<vsomeip::payload> payload;
   payload = vsomeip::runtime::get()->create_payload();
   payload->set_data(its_data, sizeof(its_data));
   std::set<vsomeip::eventgroup_t> its_groups;
   its_groups.insert(SAMPLE_EVENTGROUP_ID);
   app->offer_event(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENT_ID, its_groups, true);
   app->notify(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENT_ID, payload);

   app->start();


}
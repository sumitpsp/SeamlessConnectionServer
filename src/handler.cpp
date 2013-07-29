#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <netdb.h>

#include "handler.h"

#define PORT "11111"

using namespace std;

int SConnect::start_listener() {
	addrinfo hints;
	addrinfo* res;

	memset(&hints, 0, sizeof(struct addrinfo));

	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	if( 0 != getaddrinfo(NULL, PORT, &hints, &res)) {
		cout<<"Cant get address info for the port."<<endl;
		return 0;
	}

	UDTSOCKET udt_server = UDT::socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	if(UDT::ERROR == UDT::bind(udt_server, res->ai_addr, res->ai_addrlen)) {
		cout << "Binding error: "<< UDT::getlasterror().getErrorMessage() << endl;
		return 0;
	}

	freeaddrinfo(res);

	cout << "Server is ready at port: "<< PORT << endl;

	if(UDT::ERROR == UDT::listen(udt_server, 10)) {
		cout << "Listening error: "<<UDT::getlasterror().getErrorMessage() << endl;
	} 

	sockaddr_storage clientaddr;
	int addrlen = sizeof(clientaddr);

	UDTSOCKET incoming;

	while (true) {
		if(UDT::INVALID_SOCK == (incoming = UDT::accept(udt_server, (sockaddr*) &clientaddr, &addrlen))) {
			cout << "Accepting Connection Error: " << UDT::getlasterror(). getErrorMessage() <<endl;
			return 0;
		} 	
		
		char incominghost[NI_MAXHOST];
		char incomingport[NI_MAXSERV];

		getnameinfo((sockaddr *) &clientaddr, addrlen, incominghost, sizeof(incominghost), incomingport, sizeof(incomingport), NI_NUMERICHOST|NI_NUMERICSERV);
		cout<< "new connection " << incominghost << " : " << incomingport<<endl;

		pthread_t handler_thread;
		pthread_create(&handler_thread, NULL, handler, new UDTSOCKET(incoming));
		pthread_detach(handler_thread); 
	
	}

	UDT::close(udt_server);
}

void* SConnect::handler(void *incoming) {
	cout << "In Handler Thread"<<endl;

}


int main() {
	UDTUpDown _udt_;

	SConnect* obj = new SConnect();
	obj->start_listener();
	
} 

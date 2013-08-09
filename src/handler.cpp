#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <netdb.h>
#include <sql.h>

#include "handler.h"
#include "messages.h"

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

int recv_size(UDTSOCKET incoming, char *data, int size) {
	int rs = 0, rsize = 0;
	while(rsize < size) {
		if(UDT::ERROR ==(rs = UDT::recv(incoming, data + rsize, size - rsize, 0))) {
            cout << "Receive Error:" << UDT::getlasterror().getErrorMessage() <<endl;
            break;
        }       
        rsize+=rs;
	}

	
	return rsize;
}

int send_size(UDTSOCKET socket, char* buffer, int size) {
	
}

int SConnect::find_initiator_info(char* payload) {
	cout<<"Finding Initiator Info for" << endl;
	
	return 0;
}

int SConnect::find_peer_info(char* payload) {
	cout << "Finding ip info for" << endl;
	int ip_length = 0;
	memcpy(&ip_length, payload, sizeof(ip_length));
	cout << "Ip Length is "<< ip_length<< endl;
	payload+=sizeof(ip_length);
	char* ip = (char*) malloc(ip_length);
	memcpy(ip, payload, ip_length);
	cout <<" Ip is " << ip << endl;
	payload+=ip_length;
	int port = 0;
	memcpy(&port, payload, sizeof(port));
	cout << "Port is " << endl;
	payload+=sizeof(port);
	
	int name_length = 0;
	memcpy(&name_length, payload, sizeof(name_length));
	payload+=sizeof(name_length);
	cout << "Name Length is "<< name_length << endl;
	
	char* name = (char*) malloc(name_length);
	memcpy(name, payload, name_length);	
	
	return 0;
}
int SConnect::get_payload_type(char *payload) {
	int type = 0;
	memcpy(&type, payload, sizeof(type));
	payload+=sizeof(type);
	if(type == REPORTIP) {
		find_initiator_info(payload);
	}
	else if(type == PEERINFO) {
		find_peer_info(payload);
	}

	return 0;
}

int SConnect::handle_payload(char* payload) {
	int type = get_payload_type(payload);
}


void* SConnect::handler(void *socket) {
	cout << "In Handler Thread"<<endl;

	UDTSOCKET incoming = *(UDTSOCKET*) socket;
	
	int payload_size = 0;

	int result = recv_size(incoming, (char*) &payload_size, sizeof(int)); 
	cout << "Size received is " << payload_size<< endl;
	
	char* payload = (char*) malloc(payload_size);
	result = recv_size(incoming, payload, payload_size);

	SConnect::handle_payload(payload);

}


int main() {
	UDTUpDown _udt_;
	SDBHandler* db = new SDBHandler();
	//db->connect_to_db();
	SConnect* obj = new SConnect();
	obj->start_listener();
} 

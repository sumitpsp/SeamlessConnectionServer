#include <udt.h>
#include "cc.h"
#include "test_util.h"
#include "db_handler.h"

class SConnect {
		static int handle_payload(char* payload);
		static int get_payload_type(char* payload);
		static int find_initiator_info(char* payload);
		static int find_peer_info(char* payload);
	public:
		int start_listener();
		static void* handler(void* incoming);
};

#include <udt.h>
#include "cc.h"
#include "test_util.h"

class SConnect {
	
	public:
		int start_listener();
		static void* handler(void* incoming);
};

#include <my_streamer/message.h>

using std::make_unique;
using std::string;
using std::unique_ptr;

unique_ptr<string> Message::get_hello() const {
	return make_unique<string>("Hello World!");
}

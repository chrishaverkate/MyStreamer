#include <gtest/gtest.h>

#include <my_streamer/message.h>

TEST(MessageTests, get_hello) {
	Message m;
	ASSERT_STREQ("Hello World!", m.get_hello()->c_str());
}

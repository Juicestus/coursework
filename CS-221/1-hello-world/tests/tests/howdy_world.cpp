#include "executable.h"

TEST(howdy_world) {
    std::string msg = greeting_message();
    ASSERT_STREQ("Howdy, World!", msg.c_str());
}
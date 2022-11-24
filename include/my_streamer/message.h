#pragma once

#include <memory>
#include <string>

class Message {
public:
	[[nodiscard]] std::unique_ptr<std::string> get_hello() const;
};

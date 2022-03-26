#include "MessageReciever.h"

MessageReciever::MessageReciever()
{}


MessageReciever* MessageReciever::instance{};

MessageReciever& MessageReciever::getInstance() {

    static std::once_flag flag;

    if (!instance) {

        std::call_once(flag, []() { instance = new MessageReciever; });

    }

    return *instance;

}

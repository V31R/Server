#include "Header.h"


void Header::setType(Header::Type type) {

    type_ = type;

}

Header::Type Header::getType() const {

    return type_;

}

time_t Header::getTime() const {

    return time_;

}

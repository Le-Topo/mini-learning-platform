#include "./instructor.controller.h"


QueryResponseStatus get_instructor_by_id(long id, User *instructor)
{
    return get_user_by_id(id, instructor);
}

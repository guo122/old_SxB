
#include "sxbCommon/utils.h"

SXB_NAMESPACE_BEGIN

std::string Utils::s_runtimeDirectory = "../../../runtime/";

const std::string & Utils::getRuntimeDirectory()
{
    return s_runtimeDirectory;
}

bool Utils::getMem(double &residentMem_, double &virtualMem_)
{
    return false;
}

SXB_NAMESPACE_END

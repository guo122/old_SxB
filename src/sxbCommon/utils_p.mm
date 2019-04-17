
#import <UIKit/UIKit.h>
#import <mach/mach.h>

#include "sxbCommon/utils.h"

SXB_NAMESPACE_BEGIN

std::string Utils::s_runtimeDirectory = "";

const std::string & Utils::getRuntimeDirectory()
{
#if defined(SXB_SYSTEM_IOS)
    if (s_runtimeDirectory.empty())
    {
        NSString * bundlePath = [[ NSBundle mainBundle] pathForResource: @ "runtime" ofType :@ "bundle"];
        if (bundlePath)
        {
            s_runtimeDirectory = [bundlePath UTF8String];
            s_runtimeDirectory += "/";
        }
    }
    
#endif
    return s_runtimeDirectory;
}

bool Utils::getMem(double &residentMem_, double &virtualMem_)
{
    task_basic_info_data_t taskInfo;
    mach_msg_type_number_t infoCount = TASK_BASIC_INFO_COUNT;
    kern_return_t kernReturn = task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)&taskInfo, &infoCount);
    residentMem_ = taskInfo.resident_size / 1024.0 / 1024.0;
    virtualMem_ = taskInfo.virtual_size / 1024.0 / 1024.0;
    
    return kernReturn == KERN_SUCCESS;
}

SXB_NAMESPACE_END

#include <vlcwrapper/instance.h>

namespace vlc
{

Instance::Instance()
{
    inst_ = libvlc_new(0, nullptr);
}

Instance::~Instance()
{
    libvlc_release(inst_);
}

} // namespace vlc

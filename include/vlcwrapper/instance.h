#ifndef VLC_INSTANCE_H
#define VLC_INSTANCE_H

#include <vlc/vlc.h>

namespace vlc
{

class Instance {
public:
    static libvlc_instance_t* get()
    {
        static Instance instance;
        return instance.inst_;
    }

    Instance(const Instance&) = delete;
    void operator=(const Instance&) = delete;

private: 
    Instance();
    ~Instance();

private:
    libvlc_instance_t* inst_ = nullptr;
};

} // namespace ui

#endif
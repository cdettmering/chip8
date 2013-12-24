#include <Timers.hpp>

namespace Chip8
{
    Timers::Timers()
        : _dt(0),
          _st(0)
    {
    }

    Timers & Timers::instance()
    {
        static Timers timers;
        return timers;
    }
    
    unsigned int Timers::getDelayTimer()
    {
        return _dt;
    }

    unsigned int Timers::getSoundTimer()
    {
        return _st;
    }

    void Timers::setDelayTimer(unsigned int t)
    {
        _dt = t;
    }

    void Timers::setSoundTimer(unsigned int t)
    {
        _st = t;
    }

    void Timers::step()
    {
        if(_dt > 0) {
            _dt--;
        }
        if(_st > 0) {
            _st--;
        }
    }

}


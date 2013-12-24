/**
* @file Timers.hpp
* @brief Controls the Delay Timer and Sound Timer.
* @author Chad Dettmering
* @version 0.1
* @date 2013-12-24
*/

#ifndef CHIP8_TIMERS_HPP
#define CHIP8_TIMERS_HPP

namespace Chip8
{
    
    /**
    * @brief Emulates the Chip8 Delay Timer and Sound Timer. Both timers are
    *        decremented at a rate of 60Hz, and never go below 0. When the
    *        Sound Timer > 0 the Chip8 plays a buzz sound.
    */
    class Timers
    {
        public:

            /**
            * @brief Gets the singleton instance of the Timers module.
            *
            * @return Singleton instance of the Timers module.
            */
            static Timers & instance();

            /**
            * @brief Gets the value in DT.
            *
            * @return Value in DT.
            */
            unsigned int getDelayTimer();

            /**
            * @brief Gets the value in ST.
            *
            * @return Value in ST.
            */
            unsigned int getSoundTimer();

            /**
            * @brief Sets DT = t
            *
            * @param t The value to set to DT.
            */
            void setDelayTimer(unsigned int t);
            
            /**
            * @brief Sets ST = t
            *
            * @param t The value to set to ST.
            */
            void setSoundTimer(unsigned int t);

            /**
            * @brief Executes a single timer step. This function should be called
            *        at a rate of 60Hz.
            */
            void step();

        private:
            // For a correct singleton implementation it is necessary to make
            // the constructor, copy constructor and assignment operators private,
            // so that there isn't any accidental copying.
            Timers();
            Timers(const Timers &other);
            Timers & operator=(const Timers &other);

            unsigned int _dt;
            unsigned int _st;
    };
}

#endif

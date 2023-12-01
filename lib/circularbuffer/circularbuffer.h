// #############################################################################
// ### This file is part of the source code for the demoCloudbuilds blog     ###
// ### https://github.com/Strooom/demoCloudBuilds                            ###
// ### Author(s) : Pascal Roobrouck - @strooom                               ###
// ### License : https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode ###
// #############################################################################

#pragma once
#include <stdint.h>

// This is a circular buffer template, so it works FIFO
// push() on an already full buffer, overwrites the oldest event.
// pop() on an empty buffer, returns 0x00

template <typename itemType, uint32_t bufferLength>
class circularBuffer {
  public:
    static constexpr uint32_t length = bufferLength;

    circularBuffer(){};

    void initialize() {
        head  = 0;
        level = 0;
    };

    void push(itemType event) {
#ifndef environment_desktop
        bool interrupts_enabled = (__get_PRIMASK() == 0);
        __disable_irq();
#endif
        theBuffer[(head + level) % bufferLength] = event;
        if (level < bufferLength) {
            level++;
        } else {
            head = (head + 1) % bufferLength;
        }
#ifndef environment_desktop
        if (interrupts_enabled) {
            __enable_irq();
        }
#endif
    };

    itemType pop() {
#ifndef environment_desktop
        bool interrupts_enabled = (__get_PRIMASK() == 0);
        __disable_irq();
#endif
        itemType result;
        if (level > 0) {
            result = theBuffer[head];
            head   = (head + 1) % bufferLength;
            level--;
        } else {
            result = static_cast<itemType>(0x00);
        }
#ifndef environment_desktop
        if (interrupts_enabled) {
            __enable_irq();
        }
#endif
        return result;
    };

    bool isEmpty() const {
        return level == 0;
    };

    bool hasEvents() const {
        return level > 0;
    };

    uint32_t getLevel() const {
        return level;
    };

#ifndef unitTesting

  private:
#endif
    uint32_t head{0};
    uint32_t level{0};
    itemType theBuffer[bufferLength]{};
};

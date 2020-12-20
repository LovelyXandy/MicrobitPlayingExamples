/*
The MIT License (MIT)

Copyright (c) 2017 Lancaster University.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

/**
  * Class definition for a Event
  *
  * It represents a common event that is generated by the various components on the codal device.
  */
#include "CodalConfig.h"
#include "Event.h"
#include "Timer.h"
#include "EventModel.h"

using namespace codal;

EventModel* EventModel::defaultEventBus = NULL;

/**
  * Constructor.
  *
  * @param src The id of the Device Component that generated the event e.g. DEVICE_ID_BUTTON_A.
  *
  * @param value A component specific code indicating the cause of the event.
  *
  * @param mode Optional definition of how the event should be processed after construction (if at all):
  *                 CREATE_ONLY: Event is initialised, and no further processing takes place.
  *                 CREATE_AND_FIRE: Event is initialised, and its event handlers are immediately fired (not suitable for use in interrupts!).
  *
  * @code
  * // Create and launch an event using the default configuration
  * Event evt(id,DEVICE_BUTTON_EVT_CLICK);
  *
  * // Create an event only, do not fire onto an EventModel.
  * Event evt(id,DEVICE_BUTTON_EVT_CLICK,CREATE_AND_FIRE);
  * @endcode
  */
Event::Event(uint16_t source, uint16_t value, EventLaunchMode mode)
{
    this->source = source;
    this->value = value;

#if CONFIG_ENABLED(LIGHTWEIGHT_EVENTS)
    this->timestamp = system_timer_current_time();
#else
    this->timestamp = system_timer_current_time_us();
#endif

    if(mode != CREATE_ONLY)
        this->fire();
}

/**
  * Constructor.
  *
  * @param src The id of the Device Component that generated the event e.g. DEVICE_ID_BUTTON_A.
  *
  * @param value A component specific code indicating the cause of the event.
  *
  * @param currentTimeUs The current time in microseconds.
  *
  * @param mode Optional definition of how the event should be processed after construction (if at all):
  *                 CREATE_ONLY: Event is initialised, and no further processing takes place.
  *                 CREATE_AND_FIRE: Event is initialised, and its event handlers are immediately fired (not suitable for use in interrupts!).
  *
  * @code
  * // Create and launch an event using the default configuration
  * Event evt(id,DEVICE_BUTTON_EVT_CLICK);
  *
  * // Create an event only, do not fire onto an EventModel.
  * Event evt(id,DEVICE_BUTTON_EVT_CLICK,CREATE_AND_FIRE);
  * @endcode
  */
  Event::Event(uint16_t source, uint16_t value, CODAL_TIMESTAMP currentTimeUs, EventLaunchMode mode)
  {
      this->source = source;
      this->value = value;
      this->timestamp = currentTimeUs;

      if(mode != CREATE_ONLY)
          this->fire();
  }


/**
  * Default constructor - initialises all values, and sets timestamp to the current time.
  */
Event::Event()
{
    this->source = 0;
    this->value = 0;

#if CONFIG_ENABLED(LIGHTWEIGHT_EVENTS)
    this->timestamp = system_timer_current_time();
#else
    this->timestamp = system_timer_current_time_us();
#endif
}

/**
  * Fires this Event onto the Default EventModel, or a custom one!
  */
void Event::fire()
{
    if(EventModel::defaultEventBus)
        EventModel::defaultEventBus->send(*this);
}


/**
  * Constructor.
  * Create a new EventQueueItem.
  *
  * @param evt The event to be queued.
  */
EventQueueItem::EventQueueItem(Event evt)
{
    this->evt = evt;
    this->next = NULL;
}

/**********************************************************************

    mm58167.h - National Semiconductor MM58167 real-time clock emulation

    license: MAME, BSD-3-Clause, LGPL v2
    copyright-holders: R. Belmont

**********************************************************************/

#pragma once

#ifndef __MM58167_H__
#define __MM58167_H__

#include "emu.h"


//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_MM58167_IRQ_CALLBACK(_cb) \
	devcb = &mm58167_device::set_irq_cb(*device, DEVCB2_##_cb);


//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> mm58167_device

class mm58167_device :  public device_t,
						public device_rtc_interface
{
public:
	// construction/destruction
	mm58167_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	DECLARE_READ8_MEMBER(read);
	DECLARE_WRITE8_MEMBER(write);

	template<class _Object> static devcb2_base &set_irq_cb(device_t &device, _Object wr) { return downcast<mm58167_device &>(device).m_irq_w.set_callback(wr); }

	devcb2_write_line m_irq_w;

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	// device_rtc_interface overrides
	virtual void rtc_clock_updated(int year, int month, int day, int day_of_week, int hour, int minute, int second);
	virtual bool rtc_feature_leap_year() { return true; }

private:
	int m_regs[32];
	int m_milliseconds;

	// timers
	emu_timer *m_clock_timer;
};

// device type definition
extern const device_type MM58167;

#endif

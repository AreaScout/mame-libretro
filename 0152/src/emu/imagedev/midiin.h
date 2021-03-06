/*********************************************************************

    midiin.h

    MIDI In image device

*********************************************************************/

#ifndef __MIDIIN_H__
#define __MIDIIN_H__


/***************************************************************************
    CONSTANTS
***************************************************************************/

struct midiin_config
{
	/* callback to driver */
	devcb_write_line        m_input_callback;
};

#define MCFG_MIDIIN_ADD(_tag, _config) \
	MCFG_DEVICE_ADD(_tag, MIDIIN, 0) \
	MCFG_DEVICE_CONFIG(_config)


/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/

class midiin_device :    public device_t,
						public device_image_interface,
						public device_serial_interface,
						public midiin_config
{
public:
	// construction/destruction
	midiin_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// image-level overrides
	virtual bool call_load();
	virtual void call_unload();

	// image device
	virtual iodevice_t image_type() const { return IO_MIDIIN; }
	virtual bool is_readable()  const { return 1; }
	virtual bool is_writeable() const { return 0; }
	virtual bool is_creatable() const { return 0; }
	virtual bool must_be_loaded() const { return 0; }
	virtual bool is_reset_on_load() const { return 0; }
	virtual const char *file_extensions() const { return "mid"; }
	virtual bool core_opens_image_file() const { return FALSE; }
	virtual const option_guide *create_option_guide() const { return NULL; }

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();

	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);
	virtual void device_config_complete();

	// serial overrides
	virtual void tra_complete();    // Tx completed sending byte
	virtual void tra_callback();    // Tx send bit
	void input_callback(UINT8 state);

private:
	static const int XMIT_RING_SIZE = (8192*4*4);

	void xmit_char(UINT8 data);

	osd_midi_device *m_midi;
	emu_timer *m_timer;
	devcb_resolved_write_line m_input_func;
	UINT8 m_xmitring[XMIT_RING_SIZE];
	int m_xmit_read, m_xmit_write;
	bool m_tx_busy;
};

// device type definition
extern const device_type MIDIIN;

// device iterator
typedef device_type_iterator<&device_creator<midiin_device>, midiin_device> midiin_device_iterator;

#endif /* __MIDIIN_H__ */

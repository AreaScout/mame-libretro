/***************************************************************************

    PC-9801 Keyboard simulation

    TODO:
    - key repeat

    - Some keys to be found:
      NFER, XFER, GRPH, kana-only key next to right-shift

    - Problems with natural keyboard (ex: shift and capslock not working,
      various keys producing wrong outputs)

***************************************************************************/

#include "emu.h"
#include "machine/pc9801_kbd.h"


//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

// device type definition
const device_type PC9801_KBD = &device_creator<pc9801_kbd_device>;


//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  pc9801_kbd_device - constructor
//-------------------------------------------------

pc9801_kbd_device::pc9801_kbd_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, PC9801_KBD, "pc9801_kbd", tag, owner, clock)
{
}

//-------------------------------------------------
//  input_ports - device-specific input ports
//-------------------------------------------------

INPUT_CHANGED_MEMBER(pc9801_kbd_device::key_stroke)
{
	if(newval && !oldval)
		m_rx_buf[(UINT8)(FPTR)(param) & 0x7f] = 1;

	if(oldval && !newval)
		m_rx_buf[(UINT8)(FPTR)(param) & 0x7f] = 2;
}

static INPUT_PORTS_START( pc9801_kbd )
	PORT_START("KEY0") // 0x00 - 0x07
	PORT_BIT(0x01,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("ESC") PORT_CODE(KEYCODE_ESC)  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x00)
	PORT_BIT(0x02,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("1") PORT_CODE(KEYCODE_1) PORT_CHAR('1') PORT_CHAR('!')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x01)
	PORT_BIT(0x04,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("2") PORT_CODE(KEYCODE_2) PORT_CHAR('2') PORT_CHAR('"')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x02)
	PORT_BIT(0x08,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("3") PORT_CODE(KEYCODE_3) PORT_CHAR('3') PORT_CHAR('#')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x03)
	PORT_BIT(0x10,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("4") PORT_CODE(KEYCODE_4) PORT_CHAR('4') PORT_CHAR('$')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x04)
	PORT_BIT(0x20,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("5") PORT_CODE(KEYCODE_5) PORT_CHAR('5') PORT_CHAR('%')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x05)
	PORT_BIT(0x40,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("6") PORT_CODE(KEYCODE_6) PORT_CHAR('6') PORT_CHAR('&')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x06)
	PORT_BIT(0x80,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("7") PORT_CODE(KEYCODE_7) PORT_CHAR('7') PORT_CHAR('\'')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x07)

	// TODO: 0x0d is actually a broken bar with shift on
	PORT_START("KEY1") // 0x08 - 0x0f
	PORT_BIT(0x01,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("8") PORT_CODE(KEYCODE_8) PORT_CHAR('8') PORT_CHAR('(')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x08)
	PORT_BIT(0x02,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("9") PORT_CODE(KEYCODE_9) PORT_CHAR('9') PORT_CHAR(')')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x09)
	PORT_BIT(0x04,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("0") PORT_CODE(KEYCODE_0) PORT_CHAR('0')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x0a)
	PORT_BIT(0x08,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("- / =") PORT_CODE(KEYCODE_MINUS) PORT_CHAR('-') PORT_CHAR('=')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x0b)
	PORT_BIT(0x10,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("^") PORT_CODE(KEYCODE_EQUALS) PORT_CHAR('^')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x0c)
	PORT_BIT(0x20,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("\xC2\xA5 / |") PORT_CODE(KEYCODE_BACKSLASH)  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x0d)
	PORT_BIT(0x40,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("BACKSPACE") PORT_CODE(KEYCODE_BACKSPACE)  PORT_CHAR(8)  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x0e)
	PORT_BIT(0x80,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("TAB") PORT_CODE(KEYCODE_TAB) PORT_CHAR(9)  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x0f)

	PORT_START("KEY2") // 0x10 - 0x17
	PORT_BIT(0x01,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("Q") PORT_CODE(KEYCODE_Q) PORT_CHAR('Q') PORT_CHAR('q')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x10)
	PORT_BIT(0x02,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("W") PORT_CODE(KEYCODE_W) PORT_CHAR('W') PORT_CHAR('w')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x11)
	PORT_BIT(0x04,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("E") PORT_CODE(KEYCODE_E) PORT_CHAR('E') PORT_CHAR('e')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x12)
	PORT_BIT(0x08,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("R") PORT_CODE(KEYCODE_R) PORT_CHAR('R') PORT_CHAR('r')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x13)
	PORT_BIT(0x10,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("T") PORT_CODE(KEYCODE_T) PORT_CHAR('T') PORT_CHAR('t')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x14)
	PORT_BIT(0x20,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("Y") PORT_CODE(KEYCODE_Y) PORT_CHAR('Y') PORT_CHAR('y')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x15)
	PORT_BIT(0x40,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("U") PORT_CODE(KEYCODE_U) PORT_CHAR('U') PORT_CHAR('u')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x16)
	PORT_BIT(0x80,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("I") PORT_CODE(KEYCODE_I) PORT_CHAR('I') PORT_CHAR('i')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x17)

	PORT_START("KEY3") // 0x18 - 0x1f
	PORT_BIT(0x01,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("O") PORT_CODE(KEYCODE_O) PORT_CHAR('O') PORT_CHAR('o')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x18)
	PORT_BIT(0x02,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("P") PORT_CODE(KEYCODE_P) PORT_CHAR('P') PORT_CHAR('p')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x19)
	PORT_BIT(0x04,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("@ / ~") PORT_CODE(KEYCODE_TILDE) PORT_CHAR('@') PORT_CHAR('~')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x1a)
	PORT_BIT(0x08,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("[ / {") PORT_CODE(KEYCODE_OPENBRACE) PORT_CHAR('[') PORT_CHAR('{')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x1b)
	PORT_BIT(0x10,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("ENTER") PORT_CODE(KEYCODE_ENTER) PORT_CHAR(13)  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x1c)
	PORT_BIT(0x20,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("A") PORT_CODE(KEYCODE_A) PORT_CHAR('A') PORT_CHAR('a')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x1d)
	PORT_BIT(0x40,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("S") PORT_CODE(KEYCODE_S) PORT_CHAR('S') PORT_CHAR('s')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x1e)
	PORT_BIT(0x80,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("D") PORT_CODE(KEYCODE_D) PORT_CHAR('D') PORT_CHAR('d')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x1f)

	PORT_START("KEY4") // 0x20 - 0x27
	PORT_BIT(0x01,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("F") PORT_CODE(KEYCODE_F) PORT_CHAR('F') PORT_CHAR('f')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x20)
	PORT_BIT(0x02,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("G") PORT_CODE(KEYCODE_G) PORT_CHAR('G') PORT_CHAR('g')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x21)
	PORT_BIT(0x04,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("H") PORT_CODE(KEYCODE_H) PORT_CHAR('H') PORT_CHAR('h')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x22)
	PORT_BIT(0x08,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("J") PORT_CODE(KEYCODE_J) PORT_CHAR('J') PORT_CHAR('j')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x23)
	PORT_BIT(0x10,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("K") PORT_CODE(KEYCODE_K) PORT_CHAR('K') PORT_CHAR('k')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x24)
	PORT_BIT(0x20,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("L") PORT_CODE(KEYCODE_L) PORT_CHAR('L') PORT_CHAR('l')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x25)
	PORT_BIT(0x40,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("; / +") PORT_CODE(KEYCODE_COLON) PORT_CHAR(';') PORT_CHAR('+')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x26)
	PORT_BIT(0x80,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(": / *") PORT_CODE(KEYCODE_QUOTE) PORT_CHAR(':') PORT_CHAR('*')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x27)

	PORT_START("KEY5") // 0x28 - 0x2f
	PORT_BIT(0x01,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("] / }") PORT_CODE(KEYCODE_CLOSEBRACE) PORT_CHAR(']') PORT_CHAR('}')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x28)
	PORT_BIT(0x02,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("Z") PORT_CODE(KEYCODE_Z) PORT_CHAR('Z') PORT_CHAR('z')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x29)
	PORT_BIT(0x04,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("X") PORT_CODE(KEYCODE_X) PORT_CHAR('X') PORT_CHAR('x')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x2a)
	PORT_BIT(0x08,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("C") PORT_CODE(KEYCODE_C) PORT_CHAR('C') PORT_CHAR('c')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x2b)
	PORT_BIT(0x10,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("V") PORT_CODE(KEYCODE_V) PORT_CHAR('V') PORT_CHAR('v')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x2c)
	PORT_BIT(0x20,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("B") PORT_CODE(KEYCODE_B) PORT_CHAR('B') PORT_CHAR('b')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x2d)
	PORT_BIT(0x40,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("N") PORT_CODE(KEYCODE_N) PORT_CHAR('N') PORT_CHAR('n')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x2e)
	PORT_BIT(0x80,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("M") PORT_CODE(KEYCODE_M) PORT_CHAR('M') PORT_CHAR('m')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x2f)

	PORT_START("KEY6") // 0x30 - 0x37
	PORT_BIT(0x01,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(", / <") PORT_CODE(KEYCODE_COMMA) PORT_CHAR(',') PORT_CHAR('<')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x30)
	PORT_BIT(0x02,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(". / >") PORT_CODE(KEYCODE_STOP) PORT_CHAR('.') PORT_CHAR('>')  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x31)
	PORT_BIT(0x04,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("/ / ?") PORT_CODE(KEYCODE_SLASH) PORT_CHAR('/')  PORT_CHAR('?') PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x32)
	PORT_BIT(0x08,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("un 0-4")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x33)
	PORT_BIT(0x10,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("SPACE") PORT_CODE(KEYCODE_SPACE)  PORT_CHAR(' ') PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x34)
	PORT_BIT(0x20,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("un 0-6")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x35)
	PORT_BIT(0x40,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("ROLL DOWN") PORT_CODE(KEYCODE_PGDN)  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x36)
	PORT_BIT(0x80,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("ROLL UP") PORT_CODE(KEYCODE_PGUP)  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x37)

	PORT_START("KEY7") // 0x38 - 0x3f
	PORT_BIT(0x01,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("INS") PORT_CODE(KEYCODE_INSERT)  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x38)
	PORT_BIT(0x02,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("DEL") PORT_CODE(KEYCODE_DEL)  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x39)
	PORT_BIT(0x04,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("Up") PORT_CODE(KEYCODE_UP) PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x3a)
	PORT_BIT(0x08,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("Left") PORT_CODE(KEYCODE_LEFT) PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x3b)
	PORT_BIT(0x10,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("Right") PORT_CODE(KEYCODE_RIGHT) PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x3c)
	PORT_BIT(0x20,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("Down") PORT_CODE(KEYCODE_DOWN) PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x3d)
	PORT_BIT(0x40,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("CLS") PORT_CODE(KEYCODE_HOME)  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x3e)
	PORT_BIT(0x80,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("HELP") PORT_CODE(KEYCODE_END)  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x3f)

	PORT_START("KEY8") // 0x40 - 0x47
	PORT_BIT(0x01,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("- (PAD)") PORT_CODE(KEYCODE_MINUS_PAD)  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x40)
	PORT_BIT(0x02,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("/ (PAD)") PORT_CODE(KEYCODE_SLASH_PAD)  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x41)
	PORT_BIT(0x04,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("7 (PAD)") PORT_CODE(KEYCODE_7_PAD)  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x42)
	PORT_BIT(0x08,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("8 (PAD)") PORT_CODE(KEYCODE_8_PAD)  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x43)
	PORT_BIT(0x10,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("9 (PAD)") PORT_CODE(KEYCODE_9_PAD)  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x44)
	PORT_BIT(0x20,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("* (PAD)") PORT_CODE(KEYCODE_ASTERISK)  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x45)
	PORT_BIT(0x40,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("4 (PAD)") PORT_CODE(KEYCODE_4_PAD)  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x46)
	PORT_BIT(0x80,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("5 (PAD)") PORT_CODE(KEYCODE_5_PAD)  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x47)

	PORT_START("KEY9") // 0x48 - 0x4f
	PORT_BIT(0x01,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("6 (PAD)") PORT_CODE(KEYCODE_6_PAD)  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x48)
	PORT_BIT(0x02,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("+ (PAD)") PORT_CODE(KEYCODE_PLUS_PAD)  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x49)
	PORT_BIT(0x04,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("1 (PAD)") PORT_CODE(KEYCODE_1_PAD)  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x4a)
	PORT_BIT(0x08,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("2 (PAD)") PORT_CODE(KEYCODE_2_PAD)  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x4b)
	PORT_BIT(0x10,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("3 (PAD)") PORT_CODE(KEYCODE_3_PAD)  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x4c)
	PORT_BIT(0x20,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("EQUAL (PAD)") PORT_CODE(KEYCODE_ENTER_PAD)  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x4d)
	PORT_BIT(0x40,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("0 (PAD)") PORT_CODE(KEYCODE_0_PAD)  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x4e)
	PORT_BIT(0x80,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(", (PAD)")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x4f)

	PORT_START("KEYA") // 0x50 - 0x57
	PORT_BIT(0x01,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(". (PAD)") PORT_CODE(KEYCODE_DEL_PAD)  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x50)
	PORT_BIT(0x02,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(" un 2-2")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x51)
	PORT_BIT(0x04,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(" un 2-3")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x52)
	PORT_BIT(0x08,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(" un 2-4")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x53)
	PORT_BIT(0x10,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(" un 2-5")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x54)
	PORT_BIT(0x20,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(" un 2-6")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x55)
	PORT_BIT(0x40,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(" un 2-7")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x56)
	PORT_BIT(0x80,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(" un 2-8")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x57)

	PORT_START("KEYB") // 0x58 - 0x5f
	PORT_BIT(0x01,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(" un 3-1")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x58)
	PORT_BIT(0x02,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(" un 3-2")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x59)
	PORT_BIT(0x04,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(" un 3-3")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x5a)
	PORT_BIT(0x08,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(" un 3-4")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x5b)
	PORT_BIT(0x10,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(" un 3-5")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x5c)
	PORT_BIT(0x20,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(" un 3-6")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x5d)
	PORT_BIT(0x40,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(" un 3-7")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x5e)
	PORT_BIT(0x80,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(" un 3-8")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x5f)

	PORT_START("KEYC") // 0x60 - 0x67
	PORT_BIT(0x01,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("STOP?")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x60)
	PORT_BIT(0x02,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("COPY?")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x61)
	PORT_BIT(0x04,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("F1") PORT_CODE(KEYCODE_F1) PORT_CHAR(UCHAR_MAMEKEY(F1))  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x62)
	PORT_BIT(0x08,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("F2") PORT_CODE(KEYCODE_F2) PORT_CHAR(UCHAR_MAMEKEY(F2))  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x63)
	PORT_BIT(0x10,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("F3") PORT_CODE(KEYCODE_F3) PORT_CHAR(UCHAR_MAMEKEY(F3))  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x64)
	PORT_BIT(0x20,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("F4") PORT_CODE(KEYCODE_F4) PORT_CHAR(UCHAR_MAMEKEY(F4))  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x65)
	PORT_BIT(0x40,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("F5") PORT_CODE(KEYCODE_F5) PORT_CHAR(UCHAR_MAMEKEY(F5))  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x66)
	PORT_BIT(0x80,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("F6") PORT_CODE(KEYCODE_F6) PORT_CHAR(UCHAR_MAMEKEY(F6))  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x67)

	PORT_START("KEYD") // 0x68 - 0x6f
	PORT_BIT(0x01,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("F7") PORT_CODE(KEYCODE_F7) PORT_CHAR(UCHAR_MAMEKEY(F7))  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x68)
	PORT_BIT(0x02,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("F8") PORT_CODE(KEYCODE_F8) PORT_CHAR(UCHAR_MAMEKEY(F8))  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x69)
	PORT_BIT(0x04,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("F9") PORT_CODE(KEYCODE_F9) PORT_CHAR(UCHAR_MAMEKEY(F9))  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x6a)
	PORT_BIT(0x08,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("F10") PORT_CODE(KEYCODE_F10) PORT_CHAR(UCHAR_MAMEKEY(F10))  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x6b)
	PORT_BIT(0x10,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(" un 5-5")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x6c)
	PORT_BIT(0x20,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(" un 5-6")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x6d)
	PORT_BIT(0x40,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(" un 5-7")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x6e)
	PORT_BIT(0x80,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(" un 5-8")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x6f)

	PORT_START("KEYE") // 0x70 - 0x77
	PORT_BIT(0x01,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("SHIFT") PORT_CODE(KEYCODE_LSHIFT) PORT_CODE(KEYCODE_RSHIFT) PORT_CHAR(UCHAR_SHIFT_1) PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x70)
	PORT_BIT(0x02,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("CAPS LOCK") PORT_CODE(KEYCODE_CAPSLOCK) PORT_TOGGLE // PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x71)
	PORT_BIT(0x04,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("\xe3\x81\x8b\xe3\x81\xaa / KANA LOCK") PORT_TOGGLE  //PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x72)
	PORT_BIT(0x08,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("ALT") PORT_CODE(KEYCODE_LALT) PORT_CODE(KEYCODE_RALT) PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x73)
	PORT_BIT(0x10,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME("CTRL") PORT_CODE(KEYCODE_LCONTROL) PORT_CODE(KEYCODE_RCONTROL) PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x74)
	PORT_BIT(0x20,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(" un 6-6")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x75)
	PORT_BIT(0x40,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(" un 6-7")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x76)
	PORT_BIT(0x80,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(" un 6-8")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x77)

	PORT_START("KEYF") // 0x78 - 0x7f
	PORT_BIT(0x01,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(" un 7-1")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x78)
	PORT_BIT(0x02,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(" un 7-2")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x79)
	PORT_BIT(0x04,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(" un 7-3")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x7a)
	PORT_BIT(0x08,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(" un 7-4")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x7b)
	PORT_BIT(0x10,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(" un 7-5")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x7c)
	PORT_BIT(0x20,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(" un 7-6")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x7d)
	PORT_BIT(0x40,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(" un 7-7")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x7e)
	PORT_BIT(0x80,IP_ACTIVE_HIGH,IPT_KEYBOARD) PORT_NAME(" un 7-8")  PORT_CHANGED_MEMBER(DEVICE_SELF, pc9801_kbd_device, key_stroke, 0x7f)
INPUT_PORTS_END

ioport_constructor pc9801_kbd_device::device_input_ports() const
{
	return INPUT_PORTS_NAME( pc9801_kbd );
}

//-------------------------------------------------
//  device_validity_check - perform validity checks
//  on this device
//-------------------------------------------------

void pc9801_kbd_device::device_validity_check(validity_checker &valid) const
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void pc9801_kbd_device::device_start()
{
	m_irq_func.resolve(m_irq_cb, *this);
	m_rxtimer = timer_alloc(RX_TIMER);
	m_rxtimer->adjust(attotime::from_hz(clock()), 0, attotime::from_hz(clock()));
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void pc9801_kbd_device::device_reset()
{
	int i;

	for(i=0;i<0x80;i++)
		m_rx_buf[i] = 0;

	m_keyb_tx = 0xff;
	m_keyb_rx = 0;
	m_caps_lock_state = ioport("KEYE")->read() & (1 << 1);
	m_kana_lock_state = ioport("KEYE")->read() & (1 << 2);
}

//-------------------------------------------------
//  device_config_complete - perform any
//  operations now that the configuration is
//  complete
//-------------------------------------------------

void pc9801_kbd_device::device_config_complete()
{
	// inherit a copy of the static data
	const pc9801_kbd_interface *intf = reinterpret_cast<const pc9801_kbd_interface *>(static_config());
	if (intf != NULL)
		*static_cast<pc9801_kbd_interface *>(this) = *intf;

	// or initialize to defaults if none provided
	else
	{
		memset(&m_irq_cb, 0, sizeof(m_irq_cb));
	}
}

//-------------------------------------------------
//  device_timer - handler timer events
//-------------------------------------------------

void pc9801_kbd_device::device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr)
{
	if(id == RX_TIMER)
	{
		int i;

		/* special handling for caps lock / kana lock */
		if((ioport("KEYE")->read() & (1 << 1)) != m_caps_lock_state)
		{
			m_caps_lock_state = ioport("KEYE")->read() & (1 << 1);
			m_keyb_tx = 0x71;
			m_irq_func(ASSERT_LINE);
			return;
		}

		if((ioport("KEYE")->read() & (1 << 2)) != m_kana_lock_state)
		{
			m_kana_lock_state = ioport("KEYE")->read() & (1 << 2);
			m_keyb_tx = 0x72;
			m_irq_func(ASSERT_LINE);
			return;
		}


		/* key up */
		for(i=0;i<0x80;i++)
		{
			if(i==0x71 || i==0x72)
				continue;

			if(m_rx_buf[i] == 2)
			{
				m_keyb_tx = i | 0x80;
				m_irq_func(ASSERT_LINE);
				m_rx_buf[i] = 0;
				return;
			}
		}

		/* key down */
		for(i=0;i<0x80;i++)
		{
			if(i==0x71 || i==0x72)
				continue;

			if(m_rx_buf[i] == 1)
			{
				m_keyb_tx = i;
				m_irq_func(ASSERT_LINE);
				m_rx_buf[i] = 0;
				return;
			}
		}
	}
}

//**************************************************************************
//  READ/WRITE HANDLERS
//**************************************************************************

READ8_MEMBER( pc9801_kbd_device::rx_r )
{
	m_irq_func(CLEAR_LINE);
	return m_keyb_tx;
}

WRITE8_MEMBER( pc9801_kbd_device::tx_w )
{
	m_keyb_rx = data;
}

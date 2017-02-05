#ifndef DUMMYY8950KEYBOARDDEVICE_HH
#define DUMMYY8950KEYBOARDDEVICE_HH

#include "Y8950KeyboardDevice.hh"

namespace openmsx {

class DummyY8950KeyboardDevice final : public Y8950KeyboardDevice
{
public:
	void write(byte data, EmuTime::param time) override;
	byte read(EmuTime::param time) override;

	string_ref getDescription() const override;
	void plugHelper(Connector& connector, EmuTime::param time) override;
	void unplugHelper(EmuTime::param time) override;
};

} // namespace openmsx

#endif
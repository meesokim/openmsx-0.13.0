#ifndef AUDIOINPUTDEVICE_HH
#define AUDIOINPUTDEVICE_HH

#include "Pluggable.hh"
#include <cstdint>

namespace openmsx {

class AudioInputDevice : public Pluggable
{
public:
	/**
	 * Read wave data
	 */
	virtual int16_t readSample(EmuTime::param time) = 0;

	// Pluggable
	string_ref getClass() const final override;
};

} // namespace openmsx

#endif

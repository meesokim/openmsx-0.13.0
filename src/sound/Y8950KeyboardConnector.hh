#ifndef Y8950KEYBOARDCONNECTOR_HH
#define Y8950KEYBOARDCONNECTOR_HH

#include "Connector.hh"
#include "openmsx.hh"

namespace openmsx {

class Y8950KeyboardDevice;

class Y8950KeyboardConnector final : public Connector
{
public:
	explicit Y8950KeyboardConnector(PluggingController& pluggingController);

	void write(byte data, EmuTime::param time);
	byte read(EmuTime::param time);
	byte peek(EmuTime::param time) const;
	Y8950KeyboardDevice& getPluggedKeyb() const;

	// Connector
	const std::string getDescription() const final override;
	string_ref getClass() const final override;
	void plug(Pluggable& dev, EmuTime::param time) override;

	template<typename Archive>
	void serialize(Archive& ar, unsigned version);

private:
	byte data;
};

} // namespace openmsx

#endif

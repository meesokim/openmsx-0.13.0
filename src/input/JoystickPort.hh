#ifndef JOYSTICKPORT_HH
#define JOYSTICKPORT_HH

#include "Connector.hh"
#include "openmsx.hh"

namespace openmsx {

class JoystickDevice;
class PluggingController;

class JoystickPortIf
{
public:
	virtual ~JoystickPortIf() {}
	virtual byte read(EmuTime::param time) = 0;
	virtual void write(byte value, EmuTime::param time) = 0;
protected:
	JoystickPortIf() {}
};

class JoystickPort final : public JoystickPortIf, public Connector
{
public:
	JoystickPort(PluggingController& pluggingController,
	             string_ref name, const std::string& description);
	~JoystickPort();

	JoystickDevice& getPluggedJoyDev() const;

	// Connector
	const std::string getDescription() const override;
	string_ref getClass() const override;
	void plug(Pluggable& device, EmuTime::param time) override;

	byte read(EmuTime::param time) override;
	void write(byte value, EmuTime::param time) override;

	template<typename Archive>
	void serialize(Archive& ar, unsigned version);

private:
	void writeDirect(byte value, EmuTime::param time);

	byte lastValue;
	const std::string description;
};

class DummyJoystickPort final : public JoystickPortIf
{
public:
	byte read(EmuTime::param time) override;
	void write(byte value, EmuTime::param time) override;
};

} // namespace openmsx

#endif

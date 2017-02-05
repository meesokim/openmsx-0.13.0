#ifndef WD2793BASEDFDC_HH
#define WD2793BASEDFDC_HH

#include "MSXFDC.hh"
#include "DriveMultiplexer.hh"
#include "WD2793.hh"
#include <string>

namespace openmsx {

class WD2793BasedFDC : public MSXFDC
{
public:
	void reset(EmuTime::param time) override;

	template<typename Archive>
	void serialize(Archive& ar, unsigned version);

protected:
	explicit WD2793BasedFDC(const DeviceConfig& config, const std::string& romId = "");
	~WD2793BasedFDC() {}

	DriveMultiplexer multiplexer;
	WD2793 controller;
};

REGISTER_BASE_NAME_HELPER(WD2793BasedFDC, "WD2793BasedFDC");

} // namespace openmsx

#endif

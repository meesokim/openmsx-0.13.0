#include "RenShaTurbo.hh"
#include "XMLElement.hh"
#include "Autofire.hh"
#include "memory.hh"

namespace openmsx {

RenShaTurbo::RenShaTurbo(CommandController& commandController,
                         const XMLElement& machineConfig)
{
	if (auto* config = machineConfig.findChild("RenShaTurbo")) {
		int min_ints = config->getChildDataAsInt("min_ints", 47);
		int max_ints = config->getChildDataAsInt("max_ints", 221);
		autofire = make_unique<Autofire>(
			commandController, min_ints, max_ints, "renshaturbo");
	}
}

RenShaTurbo::~RenShaTurbo()
{
}

bool RenShaTurbo::getSignal(EmuTime::param time)
{
	return autofire ? autofire->getSignal(time) : false;
}

} // namespace openmsx

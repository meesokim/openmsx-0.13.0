#ifndef DISKCONTAINER_HH
#define DISKCONTAINER_HH

#include "serialize_meta.hh"
#include "string_ref.hh"
#include <functional>
#include <string>

namespace openmsx {

class SectorAccessibleDisk;
class MSXMotherBoard;

class DiskContainer
{
public:
	virtual ~DiskContainer();

	virtual SectorAccessibleDisk* getSectorAccessibleDisk() = 0;
	virtual const std::string& getContainerName() const = 0;
	virtual bool diskChanged() = 0;

	// for nowind
	//  - error handling with return values instead of exceptions
	virtual int insertDisk(string_ref filename) = 0;
	// for nowind
	bool isRomdisk() const;

	template<typename Archive>
	void serialize(Archive& /*ar*/, unsigned /*version*/) {}
};

// Subclass 'DiskChanger' needs (global) 'MSXMotherBoard' constructor parameter
REGISTER_BASE_CLASS_1(DiskContainer, "DiskContainer", std::reference_wrapper<MSXMotherBoard>);

} // namespace openmsx

#endif

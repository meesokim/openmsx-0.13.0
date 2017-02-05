#ifndef ROMINFO_HH
#define ROMINFO_HH

#include "RomTypes.hh"
#include "String32.hh"
#include "string_ref.hh"
#include <vector>
#include <utility>

namespace openmsx {

class RomInfo
{
public:
	RomInfo(String32 title_,   String32 year_,
                String32 company_, String32 country_,
                bool original_,    String32 origType_,
                String32 remark_,  RomType romType_,
                int genMSXid_)
		: title   (title_)
		, year    (year_)
		, company (company_)
		, country (country_)
		, origType(origType_)
		, remark  (std::move(remark_))
		, romType(romType_)
		, genMSXid(genMSXid_)
		, original(original_)
	{
	}

	const string_ref getTitle   (const char* buf) const {
		return fromString32(buf, title);
	}
	const string_ref getYear    (const char* buf) const {
		return fromString32(buf, year);
	}
	const string_ref getCompany (const char* buf) const {
		return fromString32(buf, company);
	}
	const string_ref getCountry (const char* buf) const {
		return fromString32(buf, country);
	}
	const string_ref getOrigType(const char* buf) const {
		return fromString32(buf, origType);
	}
	const string_ref getRemark  (const char* buf) const {
		return fromString32(buf, remark);
	}
	RomType          getRomType()   const { return romType; }
	bool             getOriginal()  const { return original; }
	int              getGenMSXid()  const { return genMSXid; }

	static RomType nameToRomType(string_ref name);
	static string_ref romTypeToName(RomType type);
	static std::vector<string_ref> getAllRomTypes();
	static string_ref getDescription(RomType type);
	static unsigned   getBlockSize  (RomType type);

private:
	String32 title;
	String32 year;
	String32 company;
	String32 country;
	String32 origType;
	String32 remark;
	RomType romType;
	int genMSXid;
	bool original;
};

} // namespace openmsx

#endif

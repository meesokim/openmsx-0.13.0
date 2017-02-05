#ifndef SHA1_HH
#define SHA1_HH

#include "string_ref.hh"
#include <ostream>
#include <string>
#include <cstdint>

namespace openmsx {

/** This class represents the result of a sha1 calculation (a 160-bit value).
  * Objects of this class can be constructed from/converted to 40-digit hex
  * string.
  * We treat the value '000...00' (all zeros) special. This value can be used
  * to indicate a null-sha1sum value (e.g. sha1 not yet calculated, or not
  * meaningful). In theory it's possible this special value is the result of an
  * actual sha1 calculation, but this has an _extremely_ low probability.
  */
class Sha1Sum
{
public:
	// note: default copy and assign are ok
	Sha1Sum();
	/** Construct from string, throws when string is malformed. */
	explicit Sha1Sum(string_ref hex);

	void parse40(const char* str);
	std::string toString() const;

	// Test or set 'null' value.
	bool empty() const;
	void clear();

	bool operator==(const Sha1Sum& other) const {
		for (int i = 0; i < 5; ++i) {
			if (a[i] != other.a[i]) return false;
		}
		return true;
	}
	bool operator!=(const Sha1Sum& other) const { return !(*this == other); }
	bool operator< (const Sha1Sum& other) const {
		for (int i = 0; i < 5-1; ++i) {
			if (a[i] != other.a[i]) return a[i] < other.a[i];
		}
		return a[5-1] < other.a[5-1];
	}

	bool operator<=(const Sha1Sum& other) const { return !(other <  *this); }
	bool operator> (const Sha1Sum& other) const { return  (other <  *this); }
	bool operator>=(const Sha1Sum& other) const { return !(*this <  other); }

	friend std::ostream& operator<<(std::ostream& os, const Sha1Sum& sum) {
		os << sum.toString();
		return os;
	}

private:
	uint32_t a[5];
	friend class SHA1;
};


/** Helper class to perform a sha1 calculation.
  * Basic usage:
  *  - construct a SHA1 object
  *  - repeatedly call update()
  *  - call digest() to get the result
  * Alternatively, use calc() if all data can be passed at once (IOW when there
  * would be exactly one call to update() in the recipe above).
  */
class SHA1
{
public:
	SHA1();

	/** Incrementally calculate the hash value. */
	void update(const uint8_t* data, size_t len);

	/** Get the final hash. After this method is called, calls to update()
	  * are invalid. */
	Sha1Sum digest();

	/** Easier to use interface, if you can pass all data in one go. */
	static Sha1Sum calc(const uint8_t* data, size_t len);

private:
	void transform(const uint8_t buffer[64]);
	void finalize();

	uint64_t m_count;
	Sha1Sum m_state;
	uint8_t m_buffer[64];
	bool m_finalized;
};

} // namespace openmsx

#endif

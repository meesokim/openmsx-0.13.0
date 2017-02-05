#ifndef INPUTEVENTFACTORY_HH
#define INPUTEVENTFACTORY_HH

#include "string_ref.hh"
#include <memory>

namespace openmsx {

class Event;
class TclObject;
class Interpreter;

namespace InputEventFactory
{
	using EventPtr = std::shared_ptr<const Event>;

	EventPtr createInputEvent(string_ref str,       Interpreter& interp);
	EventPtr createInputEvent(const TclObject& str, Interpreter& interp);
}

} // namespace openmsx

#endif

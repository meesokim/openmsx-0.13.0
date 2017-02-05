#include "CliExtension.hh"
#include "CommandLineParser.hh"
#include "MSXMotherBoard.hh"
#include "MSXException.hh"
#include <cassert>

using std::string;

namespace openmsx {

CliExtension::CliExtension(CommandLineParser& cmdLineParser_)
	: cmdLineParser(cmdLineParser_)
{
	cmdLineParser.registerOption("-ext", *this);
	cmdLineParser.registerOption("-exta", *this);
	cmdLineParser.registerOption("-extb", *this);
	cmdLineParser.registerOption("-extc", *this);
	cmdLineParser.registerOption("-extd", *this);
}

void CliExtension::parseOption(const string& option, array_ref<string>& cmdLine)
{
	try {
		string extensionName = getArgument(option, cmdLine);
		MSXMotherBoard* motherboard = cmdLineParser.getMotherBoard();
		assert(motherboard);
		string slotname;
		if (option.size() == 5) {
			slotname = option[4];
		} else {
			slotname = "any";
		}
		motherboard->loadExtension(extensionName, slotname);
	} catch (MSXException& e) {
		throw FatalError(e.getMessage());
	}
}

string_ref CliExtension::optionHelp() const
{
	return "Insert the extension specified in argument";
}

} // namespace openmsx

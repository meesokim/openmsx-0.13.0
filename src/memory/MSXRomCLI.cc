#include "MSXRomCLI.hh"
#include "CommandLineParser.hh"
#include "HardwareConfig.hh"
#include "MSXMotherBoard.hh"
#include "MSXException.hh"
#include <cassert>

using std::string;

namespace openmsx {

MSXRomCLI::MSXRomCLI(CommandLineParser& cmdLineParser_)
	: cmdLineParser(cmdLineParser_)
{
	cmdLineParser.registerOption("-ips", ipsOption);
	cmdLineParser.registerOption("-romtype", romTypeOption);
	cmdLineParser.registerOption("-cart", *this);
	cmdLineParser.registerOption("-carta", *this);
	cmdLineParser.registerOption("-cartb", *this);
	cmdLineParser.registerOption("-cartc", *this);
	cmdLineParser.registerOption("-cartd", *this);
	cmdLineParser.registerFileType("ri,rom", *this);
}

void MSXRomCLI::parseOption(const string& option, array_ref<string>& cmdLine)
{
	string arg = getArgument(option, cmdLine);
	string slotname;
	if (option.size() == 6) {
		slotname = option[5];
	} else {
		slotname = "any";
	}
	parse(arg, slotname, cmdLine);
}

string_ref MSXRomCLI::optionHelp() const
{
	return "Insert the ROM file (cartridge) specified in argument";
}

void MSXRomCLI::parseFileType(const string& arg, array_ref<string>& cmdLine)
{
	parse(arg, "any", cmdLine);
}

string_ref MSXRomCLI::fileTypeHelp() const
{
	static const string text("ROM image of a cartridge");
	return text;
}

void MSXRomCLI::parse(const string& arg, const string& slotname,
                      array_ref<string>& cmdLine)
{
	// parse extra options  -ips  and  -romtype
	std::vector<TclObject> options;
	while (true) {
		string option = peekArgument(cmdLine);
		if ((option == "-ips") || (option == "-romtype")) {
			options.emplace_back(option);
			cmdLine.pop_front();
			options.emplace_back(getArgument(option, cmdLine));
		} else {
			break;
		}
	}
	MSXMotherBoard* motherboard = cmdLineParser.getMotherBoard();
	assert(motherboard);
	motherboard->insertExtension("ROM",
		HardwareConfig::createRomConfig(*motherboard, arg, slotname, options));
}

void MSXRomCLI::IpsOption::parseOption(const string& /*option*/,
                                       array_ref<string>& /*cmdLine*/)
{
	throw FatalError(
		"-ips options should immediately follow a ROM or disk image.");
}

string_ref MSXRomCLI::IpsOption::optionHelp() const
{
	return "Apply the given IPS patch to the ROM or disk image specified "
	       "in the preceding option";
}

void MSXRomCLI::RomTypeOption::parseOption(const string& /*option*/,
                                           array_ref<string>& /*cmdLine*/)
{
	throw FatalError("-romtype options should immediately follow a ROM.");
}

string_ref MSXRomCLI::RomTypeOption::optionHelp() const
{
	return "Specify the rom type for the ROM image specified in the "
	       "preceding option";
}

} // namespace openmsx

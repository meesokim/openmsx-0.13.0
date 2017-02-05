#include "HDImageCLI.hh"
#include "CommandLineParser.hh"
#include "MSXException.hh"
#include <utility>
#include <vector>

using std::pair;
using std::string;

namespace openmsx {

static std::vector<pair<int, string>> images;

HDImageCLI::HDImageCLI(CommandLineParser& parser_)
	: parser(parser_)
{
	parser.registerOption("-hda", *this, CommandLineParser::PHASE_BEFORE_MACHINE);
	// TODO: offer more options in case you want to specify 2 hard disk images?
}

void HDImageCLI::parseOption(const string& option, array_ref<string>& cmdLine)
{
	// Machine has not been loaded yet. Only remember the image.
	int id = option[3] - 'a';
	images.emplace_back(id, getArgument(option, cmdLine));
}

string HDImageCLI::getImageForId(int id)
{
	// HD queries image. Return (and clear) the remembered value, or return
	// an empty string.
	auto it = std::find_if(begin(images), end(images),
		[&](pair<int, string>& p) { return p.first == id; });
	string result;
	if (it != end(images)) {
		result = std::move(it->second);
		images.erase(it);
	}
	return result;
}

void HDImageCLI::parseDone()
{
	// After parsing all remembered values should be cleared. If not there
	// was no 'hdX' hard disk.
	if (!images.empty()) {
		string hd = "hdX";
		hd[2] = 'a' + images.front().first;
		throw MSXException("No hard disk named '" + hd + "'.");
	}
}

string_ref HDImageCLI::optionHelp() const
{
	return "Use hard disk image in argument for the IDE or SCSI extensions";
}

} // namespace openmsx

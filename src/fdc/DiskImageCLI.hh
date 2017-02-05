#ifndef DISKIMAGEMANAGER_HH
#define DISKIMAGEMANAGER_HH

#include "CLIOption.hh"

namespace openmsx {

class CommandLineParser;

class DiskImageCLI final : public CLIOption, public CLIFileType
{
public:
	explicit DiskImageCLI(CommandLineParser& cmdLineParser);
	void parseOption(const std::string& option,
	                 array_ref<std::string>& cmdLine) override;
	string_ref optionHelp() const override;
	void parseFileType(const std::string& filename,
	                   array_ref<std::string>& cmdLine) override;
	string_ref fileTypeHelp() const override;

private:
	void parse(string_ref drive, string_ref image,
	           array_ref<std::string>& cmdLine);

	CommandLineParser& parser;
	char driveLetter;
};

} // namespace openmsx

#endif

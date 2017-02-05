#ifndef CLIEXTENSION_HH
#define CLIEXTENSION_HH

#include "CLIOption.hh"

namespace openmsx {

class CommandLineParser;

class CliExtension final : public CLIOption
{
public:
	explicit CliExtension(CommandLineParser& cmdLineParser);

	void parseOption(const std::string& option,
	                 array_ref<std::string>& cmdLine) override;
	string_ref optionHelp() const override;

private:
	CommandLineParser& cmdLineParser;
};

} // namespace openmsx

#endif

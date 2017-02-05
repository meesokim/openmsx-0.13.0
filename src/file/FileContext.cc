#include "FileContext.hh"
#include "FileOperations.hh"
#include "FileException.hh"
#include "StringOp.hh"
#include "serialize.hh"
#include "serialize_stl.hh"
#include "openmsx.hh"
#include "stl.hh"
#include <algorithm>
#include <cassert>

using std::string;
using std::vector;

namespace openmsx {

const string USER_DIRS    = "{{USER_DIRS}}";
const string USER_OPENMSX = "{{USER_OPENMSX}}";
const string USER_DATA    = "{{USER_DATA}}";
const string SYSTEM_DATA  = "{{SYSTEM_DATA}}";


static string subst(string_ref path, string_ref before, string_ref after)
{
	assert(path.starts_with(before));
	return after + path.substr(before.size());
}

static vector<string> getPathsHelper(const vector<string>& input)
{
	vector<string> result;
	for (auto& s : input) {
		if (StringOp::startsWith(s, USER_OPENMSX)) {
			result.push_back(subst(s, USER_OPENMSX,
			                       FileOperations::getUserOpenMSXDir()));
		} else if (StringOp::startsWith(s, USER_DATA)) {
			result.push_back(subst(s, USER_DATA,
			                       FileOperations::getUserDataDir()));
		} else if (StringOp::startsWith(s, SYSTEM_DATA)) {
			result.push_back(subst(s, SYSTEM_DATA,
			                       FileOperations::getSystemDataDir()));
		} else if (s == USER_DIRS) {
			// Nothing. Keep USER_DIRS for isUserContext()
		} else {
			result.push_back(s);
		}
	}
	return result;
}

static string resolveHelper(const vector<string>& pathList,
                            string_ref filename)
{
	string filepath = FileOperations::expandCurrentDirFromDrive(filename);
	filepath = FileOperations::expandTilde(filepath);
	if (FileOperations::isAbsolutePath(filepath)) {
		// absolute path, don't resolve
		return filepath;
	}

	for (auto& p : pathList) {
		string name = FileOperations::join(p, filename);
		name = FileOperations::expandTilde(name);
		if (FileOperations::exists(name)) {
			return name;
		}
	}
	// not found in any path
	throw FileException(filename + " not found in this context");
}

FileContext::FileContext(vector<string>&& paths_, vector<string>&& savePaths_)
	: paths(std::move(paths_)), savePaths(std::move(savePaths_))
{
}

const string FileContext::resolve(string_ref filename) const
{
	vector<string> pathList = getPathsHelper(paths);
	string result = resolveHelper(pathList, filename);
	assert(FileOperations::expandTilde(result) == result);
	return result;
}

const string FileContext::resolveCreate(string_ref filename) const
{
	string result;
	vector<string> pathList = getPathsHelper(savePaths);
	try {
		result = resolveHelper(pathList, filename);
	} catch (FileException&) {
		string path = pathList.front();
		try {
			FileOperations::mkdirp(path);
		} catch (FileException&) {
			// ignore
		}
		result = FileOperations::join(path, filename);
	}
	assert(FileOperations::expandTilde(result) == result);
	return result;
}

vector<string> FileContext::getPaths() const
{
	return getPathsHelper(paths);
}

bool FileContext::isUserContext() const
{
	return contains(paths, USER_DIRS);
}

template<typename Archive>
void FileContext::serialize(Archive& ar, unsigned /*version*/)
{
	ar.serialize("paths", paths);
	ar.serialize("savePaths", savePaths);
}
INSTANTIATE_SERIALIZE_METHODS(FileContext);

///

static string backSubstSymbols(const string& path)
{
	string systemData = FileOperations::getSystemDataDir();
	if (StringOp::startsWith(path, systemData)) {
		return subst(path, systemData, SYSTEM_DATA);
	}
	string userData = FileOperations::getSystemDataDir();
	if (StringOp::startsWith(path, userData)) {
		return subst(path, userData, SYSTEM_DATA);
	}
	string userDir = FileOperations::getUserOpenMSXDir();
	if (StringOp::startsWith(path, userDir)) {
		return subst(path, userDir, USER_OPENMSX);
	}
	// TODO USER_DIRS (not needed ATM)
	return path;
}

FileContext configFileContext(string_ref path, string_ref hwDescr, string_ref userName)
{
	return { { backSubstSymbols(FileOperations::expandTilde(path)) },
	         { FileOperations::join(
	               USER_OPENMSX, "persistent", hwDescr, userName) } };
}

FileContext systemFileContext()
{
	return { { USER_DATA, SYSTEM_DATA },
	         { USER_DATA } };
}

FileContext preferSystemFileContext()
{
	return { { SYSTEM_DATA, USER_DATA },  // first system dir
	         {} };
}

FileContext userFileContext(string_ref savePath)
{
	vector<string> savePaths;
	if (!savePath.empty()) {
		savePaths = { FileOperations::join(
		                 USER_OPENMSX, "persistent", savePath) };
	}
	return { { "", USER_DIRS }, std::move(savePaths) };
}

FileContext userDataFileContext(string_ref subDir)
{
	return { { "", USER_OPENMSX + '/' + subDir },
	         {} };
}

FileContext currentDirFileContext()
{
	return { { "" },
	         {} };
}

} // namespace openmsx

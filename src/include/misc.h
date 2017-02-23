#ifndef FILEZILLA_ENGINE_MISC_HEADER
#define FILEZILLA_ENGINE_MISC_HEADER

#include "socket.h"

enum class lib_dependency
{
	gnutls,
	count
};

std::wstring GetDependencyName(lib_dependency d);
std::wstring GetDependencyVersion(lib_dependency d);

std::string ListTlsCiphers(std::string const& priority);

// Microsoft, in its insane stupidity, has decided to make GetVersion(Ex) useless, starting with Windows 8.1,
// this function no longer returns the operating system version but instead some arbitrary and random value depending
// on the phase of the moon.
// This function instead returns the actual Windows version. On non-Windows systems, it's equivalent to
// wxGetOsVersion
bool GetRealOsVersion(int& major, int& minor);

template<typename Derived, typename Base>
std::unique_ptr<Derived>
unique_static_cast(std::unique_ptr<Base>&& p)
{
	auto d = static_cast<Derived *>(p.release());
	return std::unique_ptr<Derived>(d);
}

#if FZ_WINDOWS
DWORD GetSystemErrorCode();
fz::native_string GetSystemErrorDescription(DWORD err);
#else
int GetSystemErrorCode();
fz::native_string GetSystemErrorDescription(int err);
#endif

namespace fz {

void set_translators(
	std::wstring(*s)(char const* const t),
	std::wstring(*pf)(char const* const singular, char const* const plural, int64_t n)
);

std::wstring translate(char const* const source);
std::wstring translate(char const * const singular, char const * const plural, int64_t n);

// Poor-man's tolower. Consider to eventually use libicu or similar
std::wstring str_tolower(std::wstring const& source);
}

// Sadly xgettext cannot be used with namespaces
#define fztranslate fz::translate
#define fztranslate_mark

#endif

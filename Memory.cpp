#include <Memory.h>
#include "Memory.h"

std::string convertBytes(std::uintmax_t bytes) {
	std::string size = "";
	std::uintmax_t kb = 0, mb = 0, gb = 0, tb = 0;
	for (std::uintmax_t i = bytes; i >= 1024; i -= 1024, bytes -= 1024)
		kb++;
	for (std::uintmax_t i = kb; i >= 1024; i -= 1024, kb -= 1024)
		mb++;
	for (std::uintmax_t i = mb; i >= 1024; i -= 1024, mb -= 1024)
		gb++;
	for (std::uintmax_t i = gb; i >= 1024; i -= 1024, gb -= 1024)
		tb++;
	if (tb != 0)
		size += std::to_string(tb + float(gb / 1024.0)) + " TB";
	else if (gb != 0)
		size += std::to_string(gb + float(mb / 1024.0)) + " GB";
	else if (mb != 0)
		size += std::to_string(mb + float(kb / 1024.0)) + " MB";
	else if (kb != 0)
		size += std::to_string(kb + float(bytes / 1024.0)) + " KB";
	else
		size += std::to_string(bytes) + " Bytes";
	return size;
}

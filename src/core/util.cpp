#include "core/util.hpp"

namespace Util {
	const std::string_view pstring_view_tostring_view(PStringView *pstr) {
		return { pstr->str, pstr->len };
	}
}

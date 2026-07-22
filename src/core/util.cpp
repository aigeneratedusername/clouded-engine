#include "core/util.hpp"

namespace Util {
	const std::string_view pstring_view_tostring_view(PStringView *pstr) {
		return { pstr->str, pstr->len };
	}

	pf32 normalize(pi32 val, pi32 max) {
		return (pf32) val / (pf32) max;
	}
}

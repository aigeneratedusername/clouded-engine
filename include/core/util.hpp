#pragma once
#include "platform/types.h"

#include <string_view>

namespace Util {
	const std::string_view pstring_view_tostring_view(PStringView *pstr);

	pf32 normalize(pi32 val, pi32 max);
}

#include "engine/engine.hpp"

static PStringView gbin_path = pstring_view_init("game.bin");

static const PMemoryConfigEntry memconf_entries[] = {
	{ PMB(16), PMEMORY_REGION_DEFAULT, "MAIN" },
	{ PMB(16), PMEMORY_REGION_CONTIGUOUS, "VIDEO" },
	PMEMORYCONFIG_END
};
static const PMemoryConfig memconf = { memconf_entries };
static const PMemoryLayout *memlayout = nullptr;

int main(int argc, const char **argv) {
	PResult res = {};

	PRESULT_TRY(pinit(), res, goto out);
	PRESULT_TRY(pmemory_init(memconf), res, goto out_pinit);
	memlayout = PRESULT_PTR(PMemoryLayout, res);
	PRESULT_TRY(psystem_init(), res, goto out_pmemory);
	PRESULT_TRY(pio_init(), res, goto out_psystem);
	PRESULT_TRY(pscreen_init(), res, goto out_pio);
	PRESULT_TRY(paudio_init(), res, goto out_pscreen);

	res.status = (PStatus)eentry_point(argc, argv, memlayout, gbin_path);

out_audio:
	paudio_deinit();

out_pscreen:
	pscreen_deinit();

out_pio:
	pio_deinit();

out_psystem:
	psystem_deinit();

out_pmemory:
	pmemory_deinit(memconf);

out_pinit:
	pdeinit();

out:
	return res.status;
}

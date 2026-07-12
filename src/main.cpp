#include "engine.hpp"

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
	PRESULT_TRY(pmemory_init(memconf), res, goto cleanup_platform);
	memlayout = PRESULT_PTR(PMemoryLayout, res);
	PRESULT_TRY(psystem_init(), res, goto cleanup_pmemory);
	PRESULT_TRY(pio_init(), res, goto cleanup_psystem);
	PRESULT_TRY(pscreen_init(), res, goto cleanup_pio);
	PRESULT_TRY(paudio_init(), res, goto cleanup_pscreen);
	PRESULT_TRY(eentry_point(argc, argv, memlayout, gbin_path), res, goto cleanup_paudio);

cleanup_paudio:
	paudio_deinit();

cleanup_pscreen:
	pscreen_deinit();

cleanup_pio:
	pio_deinit();

cleanup_psystem:
	psystem_deinit();

cleanup_pmemory:
	pmemory_deinit(memconf);

cleanup_platform:
	pdeinit();

out:
	return res.status == PSTATUS_ERR ? res.err : 0;
}

#include "kernel/param.h"
#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "kernel/riscv.h"
#include "user/user.h"

void ugetpid_test();
void pgaccess_test();
void hugepage_test();
int
main(int argc, char *argv[])
{
  ugetpid_test();
  pgaccess_test();
  hugepage_test();
  printf("pgtbltest: all tests succeeded\n");
  exit(0);
}

char *testname = "???";

void
err(char *why)
{
  printf("pgtbltest: %s failed: %s, pid=%d\n", testname, why, getpid());
  exit(1);
}

void
ugetpid_test()
{
  int i;

  printf("ugetpid_test starting\n");
  testname = "ugetpid_test";

  for (i = 0; i < 64; i++) {
    int ret = fork();
    if (ret != 0) {
      wait(&ret);
      if (ret != 0)
        exit(1);
      continue;
    }
    if (getpid() != ugetpid())
      err("missmatched PID");
    exit(0);
  }
  printf("ugetpid_test: OK\n");
}

void
pgaccess_test()
{
  char *buf;
  unsigned int abits;
  printf("pgaccess_test starting\n");
  testname = "pgaccess_test";
  buf = malloc(32 * PGSIZE);
  if (pgaccess(buf, 32, &abits) < 0)
    err("pgaccess failed");
  buf[PGSIZE * 1] += 1;
  buf[PGSIZE * 2] += 1;
  buf[PGSIZE * 30] += 1;
  if (pgaccess(buf, 32, &abits) < 0)
    err("pgaccess failed");
  if (abits != ((1 << 1) | (1 << 2) | (1 << 30)))
    err("incorrect access bits set");
  free(buf);
  printf("pgaccess_test: OK\n");
}

void
hugepage_test()
{
  char *buf, *hpg;
#define SZ 32
  char stats[SZ];
  printf("hugepage_test starting\n");
  testname = "hugepage_test";

  buf = malloc(1024 * PGSIZE);
  hpg = (char *)(((unsigned long)buf + 512 * PGSIZE - 1) & ~(512 * PGSIZE - 1));
  hpg[PGSIZE * 1] += 1;
  hpg[PGSIZE * 2] += 1;
  hpg[PGSIZE * 511] += 1;
  memset(stats, 0, SZ);
  statistics(stats, SZ);
  printf("before mkhugepg: %s\n", stats);
  if (mkhugepg(hpg) < 0)
    err("mkhugepg failed");
  hpg[PGSIZE * 1] += 1;
  hpg[PGSIZE * 2] += 1;
  hpg[PGSIZE * 511] += 1;
  memset(stats, 0, SZ);
  statistics(stats, SZ);
  printf("after mkhugepg: %s\n", stats);
  printf("count = %d\n", hpg[PGSIZE * 511]);
  free(buf);
  printf("hugepage_test: OK\n");
}

#include <gtest/gtest.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include <fstream>
#include <istream>
#include <iterator>
#include <memory>
#include <unordered_map>

#include "fileops.h"
#include "inf3173/config.h"
#include "utils.h"

static const char* fname = BINARY_DIR "/testfile.bin";

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Waddress-of-packed-member"

struct hdr {
  int m;
  unsigned long v;
  struct timespec t;
} __attribute__((packed));

void load(const char* path, struct hdr* meta) {
  std::ifstream ifs(path, std::ifstream::binary);
  ASSERT_TRUE(ifs.is_open()) << "Erreur ouverture fichier";
  ifs.read((char*)meta, sizeof(struct hdr));
}

TEST(FileOps, StructureSize) { ASSERT_EQ(sizeof(struct hdr), 28); }

TEST(FileOps, Fonction) {
  struct hdr d1, d2, d3;
  struct timespec x;
  memset(&d1, 0, sizeof(struct hdr));
  memset(&d2, 0, sizeof(struct hdr));
  memset(&d3, 0, sizeof(struct hdr));
  unlink(fname);
  struct timespec t1;
  clock_gettime(CLOCK_MONOTONIC, &t1);

  ASSERT_EQ(bumpvers_fonction(fname), 0);
  load(fname, &d1);
  EXPECT_EQ(d1.m, magic);
  EXPECT_EQ(d1.v, 0);
  x = d1.t;
  delta_time(&x, &t1);
  EXPECT_GT(timespec_to_second(&x), 0);

  ASSERT_EQ(bumpvers_fonction(fname), 0);
  load(fname, &d2);
  EXPECT_EQ(d2.m, magic);
  EXPECT_EQ(d2.v, 1);
  x = d2.t;
  delta_time(&x, &d1.t);
  EXPECT_GT(timespec_to_second(&x), 0);

  ASSERT_EQ(bumpvers_fonction(fname), 0);
  load(fname, &d3);
  EXPECT_EQ(d3.m, magic);
  EXPECT_EQ(d3.v, 2);
}

TEST(FileOps, Contenu) {
  int v1 = 0xAABBCCDD;
  int v2 = 0;
  unlink(fname);
  ASSERT_EQ(bumpvers_fonction(fname), 0);
  {
    std::ofstream ofs(fname, std::ofstream::binary | std::ofstream::app);
    ofs.seekp(sizeof(struct hdr), std::ofstream::beg);
    ofs.write((char*)&v1, sizeof(v1));
  }
  ASSERT_EQ(bumpvers_fonction(fname), 0);
  {
    std::ifstream ifs(fname, std::ifstream::binary);
    ifs.seekg(sizeof(struct hdr), std::ofstream::beg);
    ifs.read((char*)&v2, sizeof(int));
  }
  ASSERT_EQ(v1, v2);
}

TEST(FileOps, Commande) {
  struct hdr d1, d2;
  struct timespec x;
  memset(&d1, 0, sizeof(struct hdr));
  memset(&d2, 0, sizeof(struct hdr));
  unlink(fname);
  struct timespec t1;
  clock_gettime(CLOCK_MONOTONIC, &t1);

  ASSERT_EQ(bumpvers_commande(fname), 0);
  load(fname, &d1);
  EXPECT_EQ(d1.m, magic);
  EXPECT_EQ(d1.v, 0);
  x = d1.t;
  delta_time(&x, &t1);
  EXPECT_GT(timespec_to_second(&x), 0);

  ASSERT_EQ(bumpvers_commande(fname), 0);
  load(fname, &d2);
  EXPECT_EQ(d2.m, magic);
  EXPECT_EQ(d2.v, 1);
  x = d2.t;
  delta_time(&x, &d1.t);
  EXPECT_GT(timespec_to_second(&x), 0);
}

int test_func(const char* fname) {
  // 10 ms
  (void)fname;
  struct timespec delay = {.tv_sec = 0, .tv_nsec = 10000000};
  nanosleep(&delay, NULL);
  return 0;
}

TEST(FileOps, Benchmark) {
  double avg = 0.0;
  do_benchmark("none", test_func, 10, &avg);
  EXPECT_NEAR(avg, 0.01, 0.005);
}

#pragma GCC diagnostic pop

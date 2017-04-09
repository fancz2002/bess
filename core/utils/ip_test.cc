#include "ip.h"

#include <arpa/inet.h>
#include <gtest/gtest.h>

namespace {

using bess::utils::Ipv4Prefix;

// Check if Ipv4Prefix can be correctly constructed from strings
TEST(IPTest, PrefixInStr) {
  Ipv4Prefix cidr_0("0.0.0.0/0");
  EXPECT_EQ(htonl(0), cidr_0.addr);
  EXPECT_EQ(htonl(0x0), cidr_0.mask);

  Ipv4Prefix cidr_1("192.168.0.0/24");
  EXPECT_EQ(htonl((192 << 24) + (168 << 16)), cidr_1.addr);
  EXPECT_EQ(htonl(0xffffff00), cidr_1.mask);

  Ipv4Prefix cidr_2("125.0.40.97/26");
  EXPECT_EQ(htonl((125 << 24) + (40 << 8) + 64), cidr_2.addr);
  EXPECT_EQ(htonl(0xffffffc0), cidr_2.mask);
}

// Check if Ipv4Prefix::Match() behaves correctly
TEST(IPTest, PrefixMatch) {
  Ipv4Prefix cidr_1("192.168.0.0/24");
  EXPECT_TRUE(cidr_1.Match(htonl((192 << 24) + (168 << 16) + 254)));
  EXPECT_FALSE(cidr_1.Match(htonl((192 << 24) + (168 << 16) + (2 << 8) + 1)));

  Ipv4Prefix cidr_2("192.168.0.1/0");
  EXPECT_TRUE(cidr_2.Match(htonl((192 << 24) + (168 << 16) + 254)));
  EXPECT_TRUE(cidr_2.Match(htonl((77 << 24) + (168 << 16) + (2 << 8) + 1)));

  Ipv4Prefix cidr_3("192.168.0.1/32");
  EXPECT_FALSE(cidr_3.Match(htonl((192 << 24) + (168 << 16) + 254)));
  EXPECT_TRUE(cidr_3.Match(htonl((192 << 24) + (168 << 16) + 1)));
}

}  // namespace (unnamed)

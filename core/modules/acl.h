#ifndef BESS_MODULES_ACL_H_
#define BESS_MODULES_ACL_H_

#include <vector>

#include "../module.h"
#include "../module_msg.pb.h"
#include "../utils/ip.h"

using bess::utils::be16_t;
using bess::utils::be32_t;
using bess::utils::CIDRNetwork;

class ACL final : public Module {
 public:
  struct ACLRule {
    bool Match(be32_t sip, be32_t dip, be16_t sport, be16_t dport) const {
      return src_ip.Match(sip) && dst_ip.Match(dip) &&
             (src_port == 0 || src_port == sport) &&
             (dst_port == 0 || dst_port == dport);
    }

    CIDRNetwork src_ip;
    CIDRNetwork dst_ip;
    be16_t src_port;
    be16_t dst_port;
    bool established;
    bool drop;
  };

  static const Commands cmds;

  pb_error_t Init(const bess::pb::ACLArg &arg);

  void ProcessBatch(bess::PacketBatch *batch) override;

  pb_cmd_response_t CommandAdd(const bess::pb::ACLArg &arg);
  pb_cmd_response_t CommandClear(const bess::pb::EmptyArg &arg);

 private:
  std::vector<ACLRule> rules_;
};

#endif  // BESS_MODULES_ACL_H_

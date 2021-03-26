#pragma once

#include <string>

#include "envoy/config/core/v3/protocol.pb.h"
#include "envoy/config/typed_config.h"
#include "envoy/network/connection.h"
#include "envoy/ssl/context_config.h"

namespace Envoy {
namespace Http {

// Store quic helpers which can be shared between connections and must live
// beyond the lifetime of individual connections.
struct PersistentQuicInfo {
  virtual ~PersistentQuicInfo() = default;
};

} // namespace Http
} // namespace Envoy

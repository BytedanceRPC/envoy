#include "common/quic/client_connection_factory_impl.h"

#include "common/quic/quic_transport_socket_factory.h"

namespace Envoy {
namespace Quic {

const Envoy::Ssl::ClientContextConfig&
getConfig(Network::TransportSocketFactory& transport_socket_factory) {
  auto* quic_socket_factory =
      dynamic_cast<QuicClientTransportSocketFactory*>(&transport_socket_factory);
  ASSERT(quic_socket_factory != nullptr);
  return quic_socket_factory->clientContextConfig();
}

PersistentQuicInfoImpl::PersistentQuicInfoImpl(
    Event::Dispatcher& dispatcher, Network::TransportSocketFactory& transport_socket_factory,
    Stats::Scope& stats_scope, TimeSource& time_source,
    Network::Address::InstanceConstSharedPtr server_addr)
    : conn_helper_(dispatcher), alarm_factory_(dispatcher, *conn_helper_.GetClock()),
      server_id_{getConfig(transport_socket_factory).serverNameIndication(),
                 static_cast<uint16_t>(server_addr->ip()->port()), false},
      crypto_config_(
          std::make_unique<quic::QuicCryptoClientConfig>(std::make_unique<EnvoyQuicProofVerifier>(
              stats_scope, getConfig(transport_socket_factory), time_source))) {}

} // namespace Quic
} // namespace Envoy

// Copyright 2021 LeoDrive, Copyright 2021 the Autoware Foundation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef UDP_DRIVER__UDP_SENDER_NODE_HPP_
#define UDP_DRIVER__UDP_SENDER_NODE_HPP_

#include "udp_driver/udp_driver.hpp"

#include <chrono>
#include <memory>
#include <string>

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_lifecycle/lifecycle_node.hpp>
#include <lifecycle_msgs/msg/state.hpp>

#include "msg_converters/converters.hpp"

namespace lc = rclcpp_lifecycle;
using LNI = rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface;

namespace drivers
{
namespace udp_driver
{

/// \brief UdpSenderNode class which can send UDP datagrams
class UdpSenderNode final
  : public lc::LifecycleNode
{
public:
  /// \brief Default constructor
  /// \param[in] options Options for the node
  explicit UdpSenderNode(const rclcpp::NodeOptions & options);

  /// \brief Constructor which accepts IoContext
  /// \param[in] options Options for the node
  /// \param[in] ctx A shared IoContext
  UdpSenderNode(
    const rclcpp::NodeOptions & options,
    const drivers::common::IoContext & ctx);

  /// \brief Destructor - required to manage owned IoContext
  ~UdpSenderNode();

  /// \brief Callback from transition to "configuring" state.
  /// \param[in] state The current state that the node is in.
  LNI::CallbackReturn on_configure(const lc::State & state) override;

  /// \brief Callback from transition to "activating" state.
  /// \param[in] state The current state that the node is in.
  LNI::CallbackReturn on_activate(const lc::State & state) override;

  /// \brief Callback from transition to "deactivating" state.
  /// \param[in] state The current state that the node is in.
  LNI::CallbackReturn on_deactivate(const lc::State & state) override;

  /// \brief Callback from transition to "unconfigured" state.
  /// \param[in] state The current state that the node is in.
  LNI::CallbackReturn on_cleanup(const lc::State & state) override;

  /// \brief Callback from transition to "shutdown" state.
  /// \param[in] state The current state that the node is in.
  LNI::CallbackReturn on_shutdown(const lc::State & state) override;

  /// \brief Callback for sending a UDP datagram
  void subscriber_callback(udp_msgs::msg::UdpPacket::SharedPtr msg);

private:
  void get_params();

  std::unique_ptr<drivers::common::IoContext> m_owned_ctx{};
  std::string m_ip{};
  uint16_t m_port{};
  std::unique_ptr<UdpDriver> m_udp_driver;
  rclcpp::Subscription<udp_msgs::msg::UdpPacket>::SharedPtr m_subscriber;
};  // class UdpSenderNode

}  // namespace udp_driver
}  // namespace drivers

#endif  // UDP_DRIVER__UDP_SENDER_NODE_HPP_

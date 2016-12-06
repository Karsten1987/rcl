// Copyright 2016 Open Source Robotics Foundation, Inc.
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

#ifndef RCL_LIFECYCLE__RCL_LIFECYCLE_H_
#define RCL_LIFECYCLE__RCL_LIFECYCLE_H_

#if __cplusplus
extern "C"
{
#endif

#ifndef __cplusplus
  #ifndef bool
    #define bool int
    #define true 1
    #define false 0
  #endif
#endif

#include <rcl_lifecycle/visibility_control.h>
#include <rcl_lifecycle/data_types.h>

RCL_LIFECYCLE_PUBLIC
rcl_lifecycle_state_machine_t
rcl_lifecycle_get_zero_initialized_state_machine();

RCL_LIFECYCLE_PUBLIC
rcl_ret_t
rcl_lifecycle_state_machine_init(rcl_lifecycle_state_machine_t * state_machine,
  rcl_node_t * node_handle,
  const rosidl_message_type_support_t * ts_pub_notify,
  const rosidl_service_type_support_t * ts_srv_get_state,
  const rosidl_service_type_support_t * ts_srv_change_state,
  bool default_states);

RCL_LIFECYCLE_PUBLIC
rcl_ret_t
rcl_lifecycle_state_machine_fini(rcl_lifecycle_state_machine_t * state_machine,
  rcl_node_t * node_handle);

/*
 * @brief enforce users to explicitely call this function
 * to resolve any error state.
 * The resolved flag indicates whether a high-level "on_error"
 * callback was successful or if the node should be finalized
 */
RCL_LIFECYCLE_PUBLIC
rcl_ret_t
rcl_lifecycle_state_machine_resolve_error(rcl_lifecycle_state_machine_t * state_machine,
  bool resolved);

RCL_LIFECYCLE_PUBLIC
rcl_ret_t
rcl_lifecycle_state_machine_is_initialized(const rcl_lifecycle_state_machine_t * state_machine);

// function definitions
/*
 * @brief traverses the transition map of the given
 * state machine to find if there is a transition from the
 * current state to the specified goal state
 * @return the transition state which is valid
 * NULL if not available
 */
RCL_LIFECYCLE_PUBLIC
const rcl_lifecycle_state_transition_t *
rcl_lifecycle_is_valid_transition(rcl_lifecycle_state_machine_t * state_machine,
  unsigned int transition_id);

RCL_LIFECYCLE_PUBLIC
const rcl_lifecycle_state_transition_t *
rcl_lifecycle_get_registered_transition(rcl_lifecycle_state_machine_t * state_machine,
  unsigned int transition_state_id);

RCL_LIFECYCLE_PUBLIC
rcl_lifecycle_state_t
rcl_lifecycle_create_state(unsigned int state, char * label);

RCL_LIFECYCLE_PUBLIC
rcl_lifecycle_state_transition_t
rcl_lifecycle_create_transition(rcl_lifecycle_state_t start, rcl_lifecycle_state_t goal);

RCL_LIFECYCLE_PUBLIC
rcl_ret_t
rcl_lifecycle_start_transition(rcl_lifecycle_state_machine_t * state_machine,
  unsigned int transition_id, bool publish_notification);

RCL_LIFECYCLE_PUBLIC
rcl_ret_t
rcl_lifecycle_finish_transition(rcl_lifecycle_state_machine_t * state_machine,
  unsigned int transition_id, bool success, bool publish_notification);

#if __cplusplus
}
#endif  // extern "C"

#endif  // RCL_LIFECYCLE__RCL_LIFECYCLE_H_

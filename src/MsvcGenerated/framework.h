// framework.h : include file for standard system include files,
// or project specific include files
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <Windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>

// stl stuff
#include <iostream>
#include <string>

//*
// gRPC
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

// helloworld.grpc.pb.cc
#include <functional>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/impl/channel_interface.h>
#include <grpcpp/impl/client_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/sync_stream.h>

// helloworld.pb.cc
#include <algorithm>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/extension_set.h"
#include "google/protobuf/wire_format_lite.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/reflection_ops.h"
#include "google/protobuf/wire_format.h"

#include "resource/protos/helloworld.grpc.pb.h"

// Reflection
#include "test/cpp/util/proto_reflection_descriptor_database.h"
#include "google/protobuf/dynamic_message.h"


// Client call emulation
#pragma warning( disable: 4996 )
#pragma warning( disable: 4244 )
#pragma warning( disable: 4200 )
#pragma warning( disable: 4146 )
#pragma warning( disable: 4312 )
#pragma warning( disable: 4267 )
#include "src/core/lib/surface/server.h"
#include "src/core/lib/surface/call.h"
#include "src/core/lib/channel/channel_stack_builder_impl.h"
#include "src/core/ext/transport/chttp2/transport/chttp2_transport.h"
#include "src/core/ext/transport/chttp2/transport/internal.h"

// Hung in pluck
#include "src/cpp/thread_manager/thread_manager.h"


// Leaks
#include "src\core\lib\config\config_vars.h"

//*/

#ifdef _DEBUG
//#	include 
#endif

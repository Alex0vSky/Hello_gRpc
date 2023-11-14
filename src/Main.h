// src\Main.h - code main class, for unittests code coverage
#pragma once // Copyright 2023 Alex0vSky (https://github.com/Alex0vSky)
#include "Version.h"
//#include "resource\protos\helloworld.grpc.pb.h"

using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;

ABSL_FLAG(uint16_t, port, 50051, "Server port for the service");
// Logic and data behind the server's behavior.
class GreeterServiceImpl final : public Greeter::Service {
	Status SayHello(ServerContext* context, const HelloRequest* request, HelloReply* reply) override {
		std::string prefix( "Hello " );
		reply ->set_message( prefix + request ->name( ) );
		std::cout << "answer (" << request ->name( ) << ")" << std::endl; // logging mark
		return Status::OK;
	}
};

// Unprivate @insp https://stackoverflow.com/questions/424104/can-i-access-private-members-from-outside-the-class-without-using-friends
struct B_member { 
  typedef std::vector<std::unique_ptr<grpc_core::Server::RegisteredMethod>> grpc_core::Server::*type;
  friend type get(B_member);
};
template<typename Tag, typename Tag::type M> struct Rob { 
  friend typename Tag::type get(Tag) {
    return M;
  }
};
template struct Rob<B_member, &grpc_core::Server::registered_methods_>;

struct grpc_core_Server_AllocatingRequestMatcherBase {
	grpc_core::Server* const server_;
	grpc_completion_queue* const cq_;
	size_t cq_idx_;
};
struct grpc_core_Server_AllocatingRequestMatcherRegistered 
	: public grpc_core_Server_AllocatingRequestMatcherBase 
{
	grpc_core::Server::RegisteredMethod* const registered_method_;
	std::function<grpc_core::Server::RegisteredCallAllocation()> allocator_;
};
struct grpc_core_Server_RequestMatcherInterface
	: public grpc_core_Server_AllocatingRequestMatcherRegistered 
{
	typedef int RequestedCall;
	typedef int MatchResult;
	virtual ~grpc_core_Server_RequestMatcherInterface() {}
	virtual void ZombifyPending() = 0;
	virtual void KillRequests(grpc_error_handle error) = 0;
	virtual size_t request_queue_count() const = 0;
	virtual void RequestCallWithPossiblePublish(size_t request_queue_index,
												RequestedCall* call) = 0;
	virtual grpc_core::ArenaPromise<absl::StatusOr<MatchResult>> MatchRequest(
		size_t start_request_queue_index) = 0;
	virtual void MatchOrQueue(size_t start_request_queue_index,
							grpc_core::Server::CallData* calld) = 0;
	// Returns the server associated with this request matcher
	virtual Server* server() const = 0;
};
// struct Server::RegisteredMethod @from src\core\lib\surface\server.cc
struct grpc_core_Server_RegisteredMethod {
  const std::string method;
  const std::string host;
  const grpc_server_register_method_payload_handling payload_handling;
  const uint32_t flags;
  std::unique_ptr< grpc_core_Server_RequestMatcherInterface > matcher;
};

//grpc_tcp* tcp = (grpc_tcp*)ep; return tcp->peer_string;
static absl::string_view win_get_peer(grpc_endpoint* ep) {
	return "ipv6:%5B::1%5D:52403";
}
static absl::string_view win_get0(grpc_endpoint* ep) {
	return "ipv6:%5B::1%5D:50051";
}
void write_dummy(grpc_endpoint* ep, grpc_slice_buffer* slices, grpc_closure* cb,
	void* arg, int max_frame_size) {
}
void add_to_pollset_dummy(grpc_endpoint* ep, grpc_pollset* pollset) {
}

// Unprivate inher
struct grpc_ServerBuilder : public grpc::ServerBuilder {
  using grpc::ServerBuilder::BuildChannelArgs;
};

void RunServer(uint16_t port) {
#pragma region original
	std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
	GreeterServiceImpl service;

	grpc::EnableDefaultHealthCheckService(true);
	grpc::reflection::InitProtoReflectionServerBuilderPlugin();
	ServerBuilder serverBuilder;
	// Listen on the given address without any authentication mechanism.
	serverBuilder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	// Register "service" as the instance through which we'll communicate with
	// clients. In this case it corresponds to an *synchronous* service.
	serverBuilder.RegisterService(&service);

	// Finally assemble the server.
	std::unique_ptr<Server> server(serverBuilder.BuildAndStart());
	std::cout << "Server listening on " << server_address << std::endl;
#pragma endregion // original

//if ( false )

	{
	// Input client data
	size_t id = 2; // doesnt matter value, not zero
	std::vector< unsigned char > fromUdp = { 0x0a, 0x05, 0x77, 0x6f, 0x72, 0x6c, 0x64 };

	//// For reflection
	//std::shared_ptr<grpc::Channel> channelInProc = server ->InProcessChannel( grpc::ChannelArguments{ } );
	//::grpc::ProtoReflectionDescriptorDatabase reflection_db( channelInProc );
	//google::protobuf::DescriptorPool desc_pool( &reflection_db );
	//const google::protobuf::ServiceDescriptor* service_desc = desc_pool.FindServiceByName( "helloworld.Greeter" );
	//const google::protobuf::MethodDescriptor* method_desc = desc_pool.FindMethodByName( "helloworld.Greeter.SayHello" );
	//auto symbol2 = desc_pool.FindFileContainingSymbol( "helloworld" );
	//auto message_type0 = symbol2 ->message_type( 0 );
	//auto message_type1 = symbol2 ->message_type( 1 );
	//std::string DebugString;
	//DebugString = method_desc ->file( ) ->package( );
	//DebugString = method_desc ->DebugString( );
	//auto input_type = method_desc ->input_type( );
	//DebugString = input_type ->DebugString( );
	//auto field0 = input_type ->field( 0 );
	//DebugString = field0 ->DebugString( );

	::grpc_core::Server *servC = ::grpc_core::Server::FromC( server ->c_server( ) );
	typedef std::vector<std::unique_ptr<grpc_core::Server::RegisteredMethod>> &rm_t;
	rm_t vecRm2 = (servC) ->*get(B_member());

	grpc_core_Server_RegisteredMethod *srm0 = 
		(grpc_core_Server_RegisteredMethod *)vecRm2[ 0 ].get( );
	auto matcher = srm0 ->matcher.get( );

	// private C++, grpc_core::Server::ChannelData::AcceptStream
	grpc_call_create_args args_call_create;

	grpc_endpoint_vtable grpc_endpoint_vtable_;
	grpc_endpoint_vtable_.get_peer = &win_get_peer;
	grpc_endpoint_vtable_.get_local_address = &win_get0;
	grpc_endpoint_vtable_.write = &write_dummy;
	grpc_endpoint_vtable_.add_to_pollset = &add_to_pollset_dummy;
	grpc_endpoint ep0 = { &grpc_endpoint_vtable_ };
    grpc_endpoint *ep = &ep0;

	grpc::ChannelArguments channelArguments = ( (grpc_ServerBuilder &)serverBuilder ).BuildChannelArgs( );
	grpc_channel_args channel_args0;
	channelArguments.SetChannelArgs( &channel_args0 );
	grpc_core::ChannelArgs channel_args3 = 
	grpc_core::CoreConfiguration::Get( )
                                .channel_args_preconditioning( )
                                .PreconditionChannelArgs( &channel_args0 );
	// @from Chttp2ServerListener::ActiveConnection::HandshakingState::OnHandshakeDone src\core\ext\transport\chttp2\server\chttp2_server.cc
	bool is_client = false;
    grpc_transport* optional_transport = grpc_create_chttp2_transport( channel_args3, ep, is_client );
	// In TLS, for grpc_core::ExecCtx::Get( ), GRPC_EXEC_CTX_FLAG_IS_INTERNAL_THREAD
	grpc_core::ExecCtx exec_ctx;
    // tmp
    grpc_pollset* accepting_pollset = nullptr;
    grpc_error_handle channel_init_err =
        servC ->SetupTransport(
            optional_transport, accepting_pollset, channel_args3,
            grpc_chttp2_transport_get_socket_node( optional_transport ));
	bool b_channel_init_err = channel_init_err.ok( );
	if ( !b_channel_init_err )
		return;

	grpc_channel_stack_type channel_stack_type = grpc_channel_stack_type::GRPC_SERVER_CHANNEL; // GRPC_CLIENT_DIRECT_CHANNEL
	grpc_core::ChannelStackBuilderImpl builder(
			grpc_channel_stack_type_string(channel_stack_type), channel_stack_type,
			channel_args3
		);
	grpc_closure* on_close = nullptr;
	grpc_slice_buffer* read_buffer = nullptr;
	grpc_closure on_receive_settings_;
    //grpc_chttp2_transport_start_reading( optional_transport, read_buffer, &on_receive_settings_, on_close); // ???

	const char* target = nullptr;
	builder.SetTarget( target );
	builder.SetTransport( optional_transport );
	bool bStack = grpc_core::CoreConfiguration::Get( ).channel_init( ).CreateStack(&builder);
	if ( !bStack )
		return;
	absl::StatusOr<grpc_core::RefCountedPtr<grpc_core::Channel>> channel0 = 
		grpc_core::Channel::CreateWithBuilder( &builder );
	grpc_core::RefCountedPtr<grpc_core::Channel> channelX = channel0.value( );
	grpc_channel_stack* channel_stack = channelX.get( ) ->channel_stack( );
#define CHANNEL_ELEMS_FROM_STACK(stk)										\
	((grpc_channel_element*)((char*)(stk) + GPR_ROUND_UP_TO_ALIGNMENT_SIZE(	\
												sizeof(grpc_channel_stack))))
	grpc_channel_element* channel_elems = CHANNEL_ELEMS_FROM_STACK( channel_stack );
	auto pChannelData = (grpc_core::Server::ChannelData*)channel_elems[ 0 ].channel_data;
	// S, private
	pChannelData ->server_ = grpc_core::RefCountedPtr<grpc_core::Server>( servC );
	// @from grpc_chttp2_parsing_accept_stream
	grpc_chttp2_stream* accepting = nullptr;
	grpc_chttp2_transport *t = (grpc_chttp2_transport *)optional_transport;
	GPR_ASSERT(t->accepting_stream == nullptr);
	t->accepting_stream = &accepting;

	args_call_create.channel = channelX;
	args_call_create.server = servC;
	args_call_create.parent = nullptr;
	args_call_create.propagation_mask = 0;
	args_call_create.cq = nullptr;
	args_call_create.pollset_set_alternative = nullptr;
	args_call_create.server_transport_data = 
		reinterpret_cast<void* >( id ); // for !is_client;
	args_call_create.send_deadline = grpc_core::Timestamp::InfFuture( );
	grpc_call* call;
	grpc_error_handle error = grpc_call_create( &args_call_create, &call );
	grpc_call_stack* call_stack = grpc_call_get_call_stack( call );
	if ( !call_stack )
		return;
	grpc_call_element* elem = grpc_call_stack_element(call_stack, 0);
	auto* calld = static_cast<grpc_core::Server::CallData*>(elem->call_data);
	if ( !error.ok( ) ) {
		calld->FailCallCreation();
		return;
	}
	calld ->Start( elem );
	// S, filling data
	calld ->payload_ = grpc_raw_byte_buffer_create( nullptr, 0 );
	grpc_core::SliceBuffer buf;
	grpc_core::Slice single = 
		grpc_core::Slice::FromCopiedBuffer( fromUdp.data( ), fromUdp.size( ) );
	buf.Append( std::move( single ) );
	grpc_slice_buffer_move_into(
			buf.c_slice_buffer( )
			, &calld ->payload_ ->data.raw.slice_buffer
		);

	// affect add_to_pollset
	matcher ->MatchOrQueue( 0, calld );

	std::this_thread::sleep_for( std::chrono::seconds( 3 ) );
	}

	// Wait for the server to shutdown. Note that some other thread must be
	// responsible for shutting down the server for this call to ever return.
	server ->Wait( );
	// TODO(alex): check memleak server ->Shutdown( );
}
namespace prj_syscross { namespace HelloGRpc {
struct Main { // Server
	static UINT run(int argc, char** argv) {
		absl::ParseCommandLine( argc, argv );
		RunServer( absl::GetFlag( FLAGS_port ) );
		return 0;
	}
};
}} // namespace prj_syscross::HelloGRpc

// src\HelloGRpc.cpp - entry point
// Copyright 2023 Alex0vSky (https://github.com/Alex0vSky)
#include "MsvcGenerated\stdafx.h"
#include "Main.h"
//// To avoid bug in incremental-link
//#include "src\resource\protos\helloworld.grpc.pb.cc"
//#include "src\resource\protos\helloworld.pb.cc"

int main(int argc, char** argv) {
#ifdef _DEBUG
	//HeapSetInformation( NULL, HeapEnableTerminationOnCorruption, NULL, NULL );
	//_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif
	ABSL_LTS_RELEASE_VERSION;
	grpc::Version( );
	//_CrtSetBreakAlloc( 11579 );

	{
		//auto init0 = grpc::InsecureChannelCredentials( );
		//GreeterClient init1(
		//		grpc::CreateChannel( "localhost:50051", grpc::InsecureChannelCredentials( ) )
		//	);
	}

	_CrtMemState cmsBefore;
	_CrtMemCheckpoint( &cmsBefore ); (void)cmsBefore;
	UINT uExitCode = prj_syscross::HelloGRpc::Main::run( argc, argv );

	google::protobuf::ShutdownProtobufLibrary( );
	grpc_shutdown( );
	// openssl
	//EVP_cleanup( );
	//CRYPTO_cleanup_all_ex_data( );
	//ERR_remove_thread_state( 0 );
	//ERR_remove_state( 0 );
	//ERR_free_strings( );
	auto &clean0 = grpc_core::ConfigVars::Get( );
	clean0.Reset( );

	_CrtMemState cmsAfter;
	_CrtMemCheckpoint( &cmsAfter ); (void)cmsAfter;

	_CrtMemState cmsDiff;
	_CrtMemDifference( &cmsDiff, &cmsBefore, &cmsAfter ); (void)cmsDiff;
	_CrtMemDumpStatistics( &cmsDiff );
	_CrtMemDumpAllObjectsSince( &cmsBefore );

	return static_cast< int >( uExitCode );
}

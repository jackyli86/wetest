#include "stdafx.h"

#include "echo_service.pb.h"
using namespace pb;

TEST(TEST_GOOGLE, TEST_GOOGLE_PROTOBUF) {
	EchoRequest request;
	request.set_message("hello,world!");

	cout << "size_long = " << request.ByteSizeLong() << endl;

	char* pBuf = new char(100);

	char* pszBuf = (char*)malloc(request.ByteSizeLong() + 1);
	memset(pszBuf, 0, request.ByteSizeLong() + 1);
	EXPECT_TRUE(request.SerializeToArray(pszBuf, request.ByteSizeLong() + 1));

	EchoRequest request1;
	request1.ParseFromArray(pszBuf, (int)request.ByteSizeLong());


	cout <<"[" << request1.SerializeAsString() << "]" << endl;
	EXPECT_EQ(request.message(), request1.message());

	free(pszBuf);
}
#include "pch.h"
#include "CppUnitTest.h"
#include "../PTW_5_1/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UTPTW51
{
	TEST_CLASS(UTPTW51)
	{
	public:
		
		TEST_METHOD(RewriteToFileIf_ValidBinaryFile_ValuesWhichSatisfyIf)
		{
			// Arrange
			const string source = "1_test";
			const string destination = "2_test";

			char expected = '³';
			char invalid_character = 'ç';

			fstream write(source, ios::out | ios::binary | ios::trunc);

			write.write(reinterpret_cast<char *>(&invalid_character), sizeof(invalid_character));
			write.write(reinterpret_cast<char *>(&expected), sizeof(expected));

			write.close();
			// Act
			RewriteToFileIf(source, destination);
			
			fstream read(destination, ios::in | ios::binary | ios::_Nocreate);

			char actual;

			read.read(reinterpret_cast<char *>(&actual), sizeof(actual));

			read.close();
			// Assert

			Assert::AreEqual(expected, actual);
		}
	};
}

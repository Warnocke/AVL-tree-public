// #include <catch2/catch_test_macros.hpp>
// #include <iostream>
// #include <vector>
// #include <sstream>
//
// // uncomment and replace the following with your own headers
// //Evan Warnock 98804113
//  #include "AVL.h"
//
// using namespace std;
// //Required test cases
// TEST_CASE("5 incorrect commands","[insert]") {
// 	AVL tree;
// 	tree.insert("St3v3n@Malkmu5","12345678");
// 	tree.insert("","12345678");
//
// 	tree.insert("Johnny Greenwood","!2345678");
// 	tree.insert("Johnny Marr","1234567");
// 	tree.insert("Jeff Tweedy","123456789");
//
// 	REQUIRE(!tree.findNAMEbool("St3v3n@Malkmu5"));
// 	REQUIRE(!tree.findNAMEbool(""));
//
// 	REQUIRE(!tree.findIDbool("!2345678"));
// 	REQUIRE(!tree.findIDbool("1234567"));
// 	REQUIRE(!tree.findIDbool("123456789"));
// }
//
// TEST_CASE("3 Edge cases","[search][remove][removeInOrder]") {
// 	AVL tree;
// 	tree.insert("Thom Yorke","00000001");
// 	tree.insert("Nels Cline","00000002");
// 	tree.insert("Ezra Koenig","00000003");
//
// 	ostringstream outstream;
// 	streambuf* oldCout = cout.rdbuf(outstream.rdbuf());
//
// 	tree.remove("Tommy yorkle");
// 	tree.searchUFID("12345678");
// 	tree.removeInOrder(4);
//
// 	cout.rdbuf(oldCout);
//
// 	REQUIRE(outstream.str() == "unsuccessful\nunsuccessful\nunsuccessful\n");
//
// }
//
// TEST_CASE("Test all 4 rotation cases","[insert][printInOrder]") {
// 	//left rotation
// 	AVL tree1;
// 	tree1.insert("James Murphy","00000005");
// 	tree1.insert("Nancy Whang","00000006");
// 	tree1.insert("Pat Mahoney","00000007");
// 	REQUIRE(tree1.getRoot()->ufid == 6);
// 	REQUIRE(tree1.getRoot()->left->ufid == 5);
// 	REQUIRE(tree1.getRoot()->right->ufid == 7);
//
// 	//right rotation
// 	AVL tree2;
// 	tree2.insert("David Byrne","00000005");
// 	tree2.insert("Tina Weymouth","00000004");
// 	tree2.insert("Jerry Harrison","00000003");
// 	REQUIRE(tree2.getRoot()->ufid == 4);
// 	REQUIRE(tree2.getRoot()->left->ufid == 3);
// 	REQUIRE(tree2.getRoot()->right->ufid == 5);
// 	//left right rotation
// 	AVL tree3;
// 	tree3.insert("Isaac Brock","00000005");
// 	tree3.insert("Jeremiah Green","00000003");
// 	tree3.insert("Lisa Molinaro","00000004");
// 	REQUIRE(tree3.getRoot()->ufid == 4);
// 	REQUIRE(tree3.getRoot()->left->ufid == 3);
// 	REQUIRE(tree3.getRoot()->right->ufid == 5);
// 	//right left rotation
// 	AVL tree4;
// 	tree4.insert("Ringo Starr","00000005");
// 	tree4.insert("George Harrison","00000007");
// 	tree4.insert("John Lennon","00000006");
// 	REQUIRE(tree4.getRoot()->ufid == 6);
// 	REQUIRE(tree4.getRoot()->left->ufid == 5);
// 	REQUIRE(tree4.getRoot()->right->ufid == 7);
//
// }
//
//
// TEST_CASE("All 3 deletion cases","[remove]") {
// 	//No child
// 	AVL tree1;
// 	//I'm out of band member names
// 	tree1.insert("Name","000000010");
// 	tree1.insert("John John","000000015");
// 	tree1.insert("John John","00000005");
// 	tree1.insert("John John","00000007");
// 	tree1.insert("John John","00000003");
// 	tree1.remove("00000007");
// 	REQUIRE(!tree1.findIDbool("00000007"));
//
// 	//one child
// 	AVL tree2;
// 	tree2.insert("Name","000000010");
// 	tree2.insert("John John","000000015");
// 	tree2.insert("John John","00000005");
// 	tree2.insert("John John","00000003");
// 	tree2.remove("00000005");
// 	REQUIRE(!tree2.findIDbool("00000005"));
//
// 	//
// 	AVL tree3;
// 	tree3.insert("Name","000000010");
// 	tree3.insert("John John","000000015");
// 	tree3.insert("John John","00000005");
// 	tree3.insert("John John","00000007");
// 	tree3.insert("John John","00000003");
// 	tree3.remove("00000005");
// 	REQUIRE(!tree3.findIDbool("00000005"));
// }
//
//
// TEST_CASE("100 Node test", "[insert][remove]") {
// 	AVL tree;
// 	string name = "John Doe";
// 	vector<string> expectedListStr;
//
// 	while (expectedListStr.size() < 100) {
// 		int randomInput = 10000000 + rand() % 90000000;
// 		string ufid = to_string(randomInput);
//
// 		if (std::count(expectedListStr.begin(), expectedListStr.end(), ufid) == 0) {
// 			tree.insert(name, ufid);
// 			expectedListStr.push_back(ufid);
// 		}
// 	}
//
// 	sort(expectedListStr.begin(), expectedListStr.end());
//
// 	vector<string> actualList = tree.getIdInOrder();
// 	REQUIRE(expectedListStr == actualList);
// }
//
//
// //The following test cases are AI generated. I got permission to do so
// TEST_CASE("AVL Insert and Search by ID", "[insert][search]") {
// 	AVL tree;
// 	tree.insert("Alice Smith", "12345678");
// 	tree.insert("Bob Jones", "23456789");
//
// 	REQUIRE(tree.findIDbool("12345678"));
// 	REQUIRE(tree.findIDbool("23456789"));
// 	REQUIRE_FALSE(tree.findIDbool("11111111"));
// }
//
// TEST_CASE("AVL Insert and Search by Name", "[insert][search]") {
// 	AVL tree;
// 	tree.insert("Charlie Brown", "34567890");
// 	tree.insert("Dana White", "45678901");
//
// 	REQUIRE(tree.findNAMEbool("Charlie Brown"));
// 	REQUIRE(tree.findNAMEbool("Dana White"));
// 	REQUIRE_FALSE(tree.findNAMEbool("Nonexistent Name"));
// }
//
// TEST_CASE("AVL Inorder Traversal", "[traversal]") {
// 	AVL tree;
// 	tree.insert("Eve", "33334444");
// 	tree.insert("Frank", "11112222");
// 	tree.insert("Grace", "55556666");
//
// 	auto names = tree.getNamesInOrder();
// 	auto ids = tree.getIdInOrder();
//
// 	REQUIRE(names.size() == 3);
// 	REQUIRE(ids[0] == "11112222");
// 	REQUIRE(ids[1] == "33334444");
// 	REQUIRE(ids[2] == "55556666");
// }
//
// TEST_CASE("AVL Remove Node", "[remove]") {
// 	AVL tree;
// 	tree.insert("Henry", "10000000");
// 	tree.insert("Ivy", "20000000");
// 	tree.insert("Jack", "30000000");
//
// 	REQUIRE(tree.findIDbool("20000000"));
// 	tree.remove("20000000");
// 	REQUIRE_FALSE(tree.findIDbool("20000000"));
// }
//
//

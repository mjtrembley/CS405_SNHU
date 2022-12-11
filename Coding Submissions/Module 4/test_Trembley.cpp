// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}
*/

// TODO: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    // if empty, the size must be 0
    ASSERT_TRUE(collection->size() == 0);

    add_entries(1);

    // is the collection still empty?
    // if not empty, what must the size be?
    ASSERT_TRUE(collection->size() == 1);
}

// TODO: Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    add_entries(5);

    ASSERT_TRUE(collection->size() == 5);
}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, MaxGreaterThanOrEqualToSize){
    //add 11 entries
    add_entries(11);

    //Verify that the max size is greater than or equal to 0,1,5,10 entires
    ASSERT_TRUE(collection->max_size() >= 0);
    ASSERT_TRUE(collection->max_size() >= 1);
    ASSERT_TRUE(collection->max_size() >= 5);
    ASSERT_TRUE(collection->max_size() >= 10);

}

// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CapGreaterThanOrEqualToSize) {
    //add 11 entries
    add_entries(11);

    //Verify that the capacity is greater than or euql to 0,1,5,10
    ASSERT_TRUE(collection->capacity() >= 0);
    ASSERT_TRUE(collection->capacity() >= 0);
    ASSERT_TRUE(collection->capacity() >= 0);
    ASSERT_TRUE(collection->capacity() >= 0);

}

// TODO: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, ResizeIncreaseCollection) {
    //starting entries
    add_entries(16);

    //declare preious value to collection size
    int startingSize = collection->size();

    //resize the container to hold more elements
    collection->resize(20);

    //Assert if current collection size is greater than startingSize
    ASSERT_TRUE(collection->size() > startingSize);
}

// TODO: Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, ResizeDecreaseCollection) {
    //starting entries
    add_entries(16);

    //declare previous value to collection size
    int startingSize = collection->size();

    //resize container to hold only 1 element
    collection->resize(1);

    //Assert if current collection is smaller than startingSize
    ASSERT_TRUE(collection->size() < startingSize);
}

// TODO: Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, ResizeCollectionToZero) {
    //starting entries
    add_entries(16);

    //declare previous value to collection size
    int startingSize = collection->size();

    //resize container to zero
    collection->resize(0);

    //Assert if current collection is smaller than startingSize
    ASSERT_TRUE(collection->size() == 0);
}

// TODO: Create a test to verify clear erases the collection
TEST_F(CollectionTest, ClearErasesCollection) {
    //starting entries
    add_entries(14);

    //clear collection
    collection->clear();

    //Assert if collection has been cleared to zero
    ASSERT_TRUE(collection->size() == 0);
}

// TODO: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, EraseCollection) {
    //starting entries
    add_entries(10);

    //Erase the collection
    collection->erase(collection->begin(), collection->end());

    //Assert if collection has been erased back to zero
    ASSERT_TRUE(collection->size() == 0);
}

// TODO: Create a test to verify reserve increases the capacity but not the size of the collection

TEST_F(CollectionTest, ReserveIncreaseCapNotSize) {
    //starting entries
    add_entries(10);

    //initialized local variables
    int initialCap = collection->capacity();
    int initialSize = collection->size();

    //Reserve to at least 50
    collection->reserve(50);

    //Assert if size is equal to start but the capacity is larger
    ASSERT_TRUE(collection->size() == initialSize);
    ASSERT_TRUE(collection->capacity() > initialCap);
}

// TODO: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test

TEST_F(CollectionTest, OutOfRangeException) {
    //starting entries
    add_entries(20);

    //EXPECT out off range to exception to be thrown when calling vector with out of bounds access
    EXPECT_THROW(collection->at(25), std::out_of_range);
}

// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative
TEST_F(CollectionTest, SizeReducedAfterPopBack_Trembley) {
    //starting entries
    add_entries(5);

    collection->pop_back(); // Remove last element in the vector

    //Assert FALSE that collection size is NOT 5
    //Assert TRUE that collection size has changed to 4
    ASSERT_FALSE(collection->size() == 5);
    ASSERT_TRUE(collection->size() == 4);
}

TEST_F(CollectionTest, CustomAssignValues_Trembley) {
    //starting entries
    add_entries(20);

    //modify container to only hold 8 elements, all value of 1
    collection->assign(8, 1); // Add 8 elements with value of 1

    //Assert FALSE that collection size is NOT empty/zero
    //Assert TRUE that collection size has changed to 8 elements
    //Assert TRUE that element at index 2 holds the value of 1
    ASSERT_FALSE(collection->size() == 0);
    ASSERT_TRUE(collection->size() == 8);
    ASSERT_TRUE(collection->at(2) == 1);
}
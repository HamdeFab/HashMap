// HashMapTests.cpp

#include <gtest/gtest.h>
#include "HashMap.hpp"


TEST(HashMapTests, sizeOfNewlyCreatedHashMapIsZero)
{
    HashMap empty;
    ASSERT_EQ(0, empty.size());
}


TEST(HashMapTests, emptyMapContainsNoKeys)
{
    HashMap empty;
    ASSERT_FALSE(empty.contains("first"));
    ASSERT_FALSE(empty.contains("second"));
}


TEST(HashMapTests, containKeyAfterAddingIt)
{
    HashMap hm;
    hm.add("Boo", "perfect");
    ASSERT_TRUE(hm.contains("Boo"));
}

TEST(TestHashMap, testAdd)
{
   HashMap hm1;
   std::string key{"Boo"};
   std::string value{"perfect"};
   hm1.add(key, value);
   ASSERT_EQ("perfect", hm1.value("Boo"));

   hm1.remove("Boo");
   ASSERT_EQ(false, hm1.contains("Boo"));
   hm1.add(key, value);
   ASSERT_EQ(true, hm1.contains("Boo"));

}

TEST(TestHashMap, testRemove)
{
   HashMap hm1;
   std::string key{"Boo"};
   std::string value{"perfect"};
   hm1.add(key, value);
   ASSERT_EQ(true, hm1.contains("Boo"));
   ASSERT_EQ("perfect", hm1.value("Boo"));

   hm1.remove("Boo");
   ASSERT_EQ(false, hm1.contains("Boo"));

}

TEST(TestHashMap, testSize)
{
   HashMap hm1;
   std::string key{"Boo"};
   std::string value{"perfect"};
   hm1.add(key, value);
   ASSERT_EQ("perfect", hm1.value("Boo"));

   hm1.remove("Boo");
   ASSERT_EQ(false, hm1.contains("Boo"));
   hm1.add(key, value);
   ASSERT_EQ(true, hm1.contains("Boo"));


   ASSERT_EQ(1, hm1.size());
   ASSERT_EQ(10, hm1.bucketCount());
   hm1.add("Hamza0", "Khalique0");
   ASSERT_EQ(2, hm1.size());

   hm1.add("Hamza1", "Khalique1");
   hm1.add("Hamza2", "Khalique2");
   hm1.add("Hamza3", "Khalique3");
   hm1.add("Hamza4", "Khalique4");
   hm1.add("Hamza5", "Khalique5");
   hm1.add("Hamza6", "Khalique6");
   ASSERT_EQ(8, hm1.size());
   ASSERT_EQ(0.8, hm1.loadFactor());
   ASSERT_EQ(10, hm1.bucketCount());
   hm1.add("Hamza7", "Khalique7");
   ASSERT_EQ(9, hm1.size());

}

TEST(TestHashMap, testBucketCount)
{
   HashMap hm1;
   std::string key{"Boo"};
   std::string value{"perfect"};
   hm1.add(key, value);
   ASSERT_EQ("perfect", hm1.value("Boo"));

   hm1.remove("Boo");
   ASSERT_EQ(false, hm1.contains("Boo"));
   hm1.add(key, value);
   ASSERT_EQ(true, hm1.contains("Boo"));


   ASSERT_EQ(1, hm1.size());
   ASSERT_EQ(10, hm1.bucketCount());
   hm1.add("Hamza0", "Khalique0");
   ASSERT_EQ(2, hm1.size());

   hm1.add("Hamza1", "Khalique1");
   hm1.add("Hamza2", "Khalique2");
   hm1.add("Hamza3", "Khalique3");
   hm1.add("Hamza4", "Khalique4");
   hm1.add("Hamza5", "Khalique5");
   hm1.add("Hamza6", "Khalique6");
   ASSERT_EQ(8, hm1.size());
   ASSERT_EQ(0.8, hm1.loadFactor());
   ASSERT_EQ(10, hm1.bucketCount());
   hm1.add("Hamza7", "Khalique7");
   ASSERT_EQ(9, hm1.size());
   ASSERT_NEAR(0.428, hm1.loadFactor(), 0.001);
   ASSERT_EQ(21, hm1.bucketCount());

}

TEST(TestHashMap, testCopy)
{
   HashMap hm1;
   std::string key{"Boo"};
   std::string value{"perfect"};
   hm1.add(key, value);
   ASSERT_EQ("perfect", hm1.value("Boo"));

   hm1.remove("Boo");
   ASSERT_EQ(false, hm1.contains("Boo"));
   hm1.add(key, value);
   ASSERT_EQ(true, hm1.contains("Boo"));


   ASSERT_EQ(1, hm1.size());
   ASSERT_EQ(10, hm1.bucketCount());
   hm1.add("Hamza0", "Khalique0");
   ASSERT_EQ(true, hm1.contains("Hamza0"));
   ASSERT_EQ(2, hm1.size());

   hm1.add("Hamza1", "Khalique1");
   ASSERT_EQ(3, hm1.size());
   hm1.add("Hamza2", "Khalique2");
   ASSERT_EQ(4, hm1.size());
   hm1.add("Hamza3", "Khalique3");
   ASSERT_EQ(5, hm1.size());
   hm1.add("Hamza4", "Khalique4");
   ASSERT_EQ(6, hm1.size());
   hm1.add("Hamza5", "Khalique5");
   ASSERT_EQ(7, hm1.size());
   hm1.add("Hamza6", "Khalique6");
   ASSERT_EQ(8, hm1.size());
   ASSERT_EQ(0.8, hm1.loadFactor());
   ASSERT_EQ(10, hm1.bucketCount());
   hm1.add("Hamza7", "Khalique7");
   ASSERT_EQ(9, hm1.size());
   ASSERT_NEAR(0.428, hm1.loadFactor(), 0.001);
   ASSERT_EQ(21, hm1.bucketCount());


   EXPECT_EQ(true, hm1.contains("Boo"));
   hm1.remove("Hamza7");
   ASSERT_EQ(false, hm1.contains("Hamza7"));

   hm1.remove("Hamza7");
   hm1.remove("Hamza6");
   hm1.remove("Hamza5");
   hm1.remove("Hamza4");
   EXPECT_EQ(5, hm1.size());
   ASSERT_EQ(21, hm1.bucketCount());

   HashMap hm2{hm1};
   ASSERT_EQ(5, hm2.size());
   ASSERT_EQ(true, hm2.contains("Hamza3"));
   ASSERT_EQ(false, hm2.contains("Hamza4"));

}

TEST(TestHashMap, testLoadFactor)
{
   HashMap hm1;
   std::string key{"Boo"};
   std::string value{"perfect"};
   hm1.add(key, value);
   ASSERT_EQ("perfect", hm1.value("Boo"));

   hm1.remove("Boo");
   ASSERT_EQ(false, hm1.contains("Boo"));
   hm1.add(key, value);
   ASSERT_EQ(true, hm1.contains("Boo"));


   ASSERT_EQ(1, hm1.size());
   ASSERT_EQ(10, hm1.bucketCount());
   hm1.add("Hamza0", "Khalique0");
   ASSERT_EQ(2, hm1.size());

   hm1.add("Hamza1", "Khalique1");
   hm1.add("Hamza2", "Khalique2");
   hm1.add("Hamza3", "Khalique3");
   hm1.add("Hamza4", "Khalique4");
   hm1.add("Hamza5", "Khalique5");
   hm1.add("Hamza6", "Khalique6");
   ASSERT_EQ(8, hm1.size());
   ASSERT_EQ(0.8, hm1.loadFactor());
   ASSERT_EQ(10, hm1.bucketCount());
   hm1.add("Hamza7", "Khalique7");
   ASSERT_EQ(9, hm1.size());
   ASSERT_NEAR(0.428, hm1.loadFactor(), 0.001);
}

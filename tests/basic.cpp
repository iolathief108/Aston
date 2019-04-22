
#include "gtest/gtest.h"
#include "Aston/ObjectBuffer.h"

struct Prototype {
    int         level;
    float       power;
    std::string name;
};

template<typename S>
void serialize(S &s, Prototype &o)
{
    s.value4b(o.level);
    s.value4b(o.power);
    s.text1b(o.name, 20);
}

TEST(main, share)
{
    //writing
    Prototype heller{432, 23.5f, "Heller"};

    ObjectBuffer buffer("Aston", 256);
    buffer.writeObject(heller);

    //reading
    Prototype mercer;

    ObjectBuffer object("Aston", 256);
    object.getObject(mercer);

    //testing
    EXPECT_EQ(mercer.level, 432);
    EXPECT_EQ(mercer.power, 23.5f);
    EXPECT_EQ(mercer.name, "Heller");

}
#include "gtest/gtest.h"
#include "Converters.h"

const int second = 44100 * 2;

TEST(ConvertersTest, Muter) {
    Muter muter;
    char* stream = new char[second];
    for (int i = 0; i < second; ++i) {
        stream[i] = i % 128;
    }
    stream = muter.convert(stream);
    for (int i = 0; i < second; ++i) {
        EXPECT_EQ(stream[i], 0);
    }
    delete[](stream);
}

TEST(ConvertersTest, Mixer) {
    Mixer mixer;
    char* stream1 = new char[second];
    char* stream2 = new char[second];
    int value1 = 60;
    int value2 = 30;
    for (int i = 0; i < second; ++i) {
        stream1[i] = value1;
        stream2[i] = value2;
    }
    stream1 = mixer.convert(stream1, stream2);
    for (int i = 0; i < second; ++i) {
        EXPECT_EQ(stream1[i], (value1 + value2) / 2);
    }
    delete[](stream1);
    delete[](stream2);
}

TEST(ConvertersTest, Booster) {
    Booster booster;
    char* stream = new char[second];
    int value = 60;
    for (int i = 0; i < second; ++i) {
        stream[i] = value;
    }
    int coefficient = 2;
    stream = booster.convert(stream, nullptr, coefficient);
    for (int i = 0; i < second; ++i) {
        EXPECT_EQ(stream[i], value * coefficient);
    }
    delete[](stream);
}
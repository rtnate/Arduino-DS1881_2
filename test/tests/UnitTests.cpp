#include <gtest/gtest.h>
#include <DS1881_2.h>
#include <iostream>

TEST(TestVerification, AssertGTestWorks)
{
    EXPECT_EQ(2*3, 6);
    std::cout << "Does std::out work here?";
}

TEST(DS1881_2_UnitTests, TestInstantiation) {
    DS1882 basicConstruction(0x0); 
    EXPECT_EQ(DS1882::SlaveAddressBase, 0x28);
    EXPECT_EQ(basicConstruction.getI2CBusAddress(), 0x28);
    DS1882 alternateAddress(0x2);
    EXPECT_EQ(alternateAddress.getI2CBusAddress(), 0x2A);
    DS1882 byPins1(LOW, LOW, HIGH);
    EXPECT_EQ(byPins1.getI2CBusAddress(), 0x2C);
    DS1882 byPins2(HIGH, LOW, LOW);
    EXPECT_EQ(byPins2.getI2CBusAddress(), 0x29);
    DS1882 byPins3(LOW, HIGH, LOW);
    EXPECT_EQ(byPins3.getI2CBusAddress(), 0x2A);
    DS1882 byPins4(HIGH, HIGH, HIGH);
    EXPECT_EQ(byPins4.getI2CBusAddress(), 0x2F);
}


TEST(DS1881_2_UnitTests, TestMockI2C) {
    TwoWire mockI2c;
    EXPECT_FALSE(mockI2c.hasBegun());
    mockI2c.begin(0x10);
    EXPECT_TRUE(mockI2c.hasBegun());
    EXPECT_EQ(mockI2c.lastTxAddress(), 0x10);
    mockI2c.beginTransmission(0x28);
    mockI2c.write(0xA);
    mockI2c.write(0x1);
    uint8_t result = mockI2c.endTransmission();
    EXPECT_EQ(result, 0);
    EXPECT_EQ(mockI2c.lastTxAddress(), 0x28);
    EXPECT_EQ(mockI2c.TransmittedData().available(), 2);
    int c = mockI2c.TransmittedData().read();
    EXPECT_EQ(c, 0xA);
    EXPECT_EQ(mockI2c.TransmittedData().available(), 1);
    int c2 = mockI2c.TransmittedData().read();
    EXPECT_EQ(c2, 0x1);
}

TEST(DS1881_2_UnitTests, TestDefaultConfiguration) {
    TwoWire mockI2c;
    EXPECT_FALSE(mockI2c.hasBegun());

    DS1882 device(0x0, mockI2c);
    device.begin();
    EXPECT_TRUE(mockI2c.hasBegun());
    EXPECT_EQ(mockI2c.TransmittedData().available(), 0);
}

TEST(DS1881_2_UnitTests, TestAlternateConfiguration) {
    TwoWire mockI2c;
    EXPECT_FALSE(mockI2c.hasBegun());

    DS1882 device(0x1, mockI2c);
    device.begin();
    EXPECT_TRUE(mockI2c.hasBegun());
    device.configure(DS1882::PotentiometerMode::PotentiometerPositions63, 
        true, true);

    EXPECT_EQ(mockI2c.lastTxAddress(), 0x29);
    EXPECT_EQ(mockI2c.TransmittedData().available(), 1);
    int c = mockI2c.TransmittedData().read();
    EXPECT_EQ(c, 0x82);
}

TEST(DS1881_2_UnitTests, TestPot0Writing) {
    TwoWire mockI2c;
    EXPECT_FALSE(mockI2c.hasBegun());

    DS1882 device(0x2, mockI2c);
    device.begin(DS1882::PotentiometerMode::PotentiometerPositions63);
    EXPECT_TRUE(mockI2c.hasBegun());
    EXPECT_EQ(mockI2c.lastTxAddress(), 0x2A);
    EXPECT_EQ(mockI2c.TransmittedData().available(), 1);
    int c = mockI2c.TransmittedData().read();
    EXPECT_EQ(c, 0x86);
    //Write Pot 0 to 24
    EXPECT_EQ(mockI2c.TransmittedData().available(), 0);
    device.writePot0(24);
    EXPECT_EQ(mockI2c.TransmittedData().available(), 1);
    c = mockI2c.TransmittedData().read();
    EXPECT_EQ(c, 0x0 | 24);
    //Write Pot 0 to Mute
    EXPECT_EQ(mockI2c.TransmittedData().available(), 0);
    device.writePot0(63);
    EXPECT_EQ(mockI2c.TransmittedData().available(), 1);
    c = mockI2c.TransmittedData().read();
    EXPECT_EQ(c, 0x0 | 63);
    //Write Pot 0 to Full
    EXPECT_EQ(mockI2c.TransmittedData().available(), 0);
    device.writePot0(0);
    EXPECT_EQ(mockI2c.TransmittedData().available(), 1);
    c = mockI2c.TransmittedData().read();
    EXPECT_EQ(c, 0x0);
    //Write Pot 0 to Error Value
    EXPECT_EQ(mockI2c.TransmittedData().available(), 0);
    device.writePot0(197);
    EXPECT_EQ(mockI2c.TransmittedData().available(), 1);
    c = mockI2c.TransmittedData().read();
    EXPECT_LE(c, 63);
}

TEST(DS1881_2_UnitTests, TestPot1Writing) {
    TwoWire mockI2c;
    EXPECT_FALSE(mockI2c.hasBegun());

    DS1882 device(0x2, mockI2c);
    device.begin(DS1882::PotentiometerMode::PotentiometerPositions63);
    EXPECT_TRUE(mockI2c.hasBegun());
    EXPECT_EQ(mockI2c.lastTxAddress(), 0x2A);
    EXPECT_EQ(mockI2c.TransmittedData().available(), 1);
    int c = mockI2c.TransmittedData().read();
    EXPECT_EQ(c, 0x86);
    //Write Pot 0 to 24
    EXPECT_EQ(mockI2c.TransmittedData().available(), 0);
    device.writePot1(24);
    EXPECT_EQ(mockI2c.TransmittedData().available(), 1);
    c = mockI2c.TransmittedData().read();
    EXPECT_EQ(c, 0x40 | 24);
    //Write Pot 0 to Mute
    EXPECT_EQ(mockI2c.TransmittedData().available(), 0);
    device.writePot1(63);
    EXPECT_EQ(mockI2c.TransmittedData().available(), 1);
    c = mockI2c.TransmittedData().read();
    EXPECT_EQ(c, 0x40 | 63);
    //Write Pot 0 to Full
    EXPECT_EQ(mockI2c.TransmittedData().available(), 0);
    device.writePot1(0);
    EXPECT_EQ(mockI2c.TransmittedData().available(), 1);
    c = mockI2c.TransmittedData().read();
    EXPECT_EQ(c, 0x40);
    //Write Pot 0 to Error Value
    EXPECT_EQ(mockI2c.TransmittedData().available(), 0);
    device.writePot1(197);
    EXPECT_EQ(mockI2c.TransmittedData().available(), 1);
    c = mockI2c.TransmittedData().read();
    EXPECT_LE(c, 127);
    EXPECT_GE(c, 0x40);
}

TEST(DS1881_2_UnitTests, TestBothPotWriting) {
    TwoWire mockI2c;
    EXPECT_FALSE(mockI2c.hasBegun());

    DS1882 device(0x2, mockI2c);
    device.begin(DS1882::PotentiometerMode::PotentiometerPositions63);
    EXPECT_TRUE(mockI2c.hasBegun());
    EXPECT_EQ(mockI2c.lastTxAddress(), 0x2A);
    EXPECT_EQ(mockI2c.TransmittedData().available(), 1);
    int c = mockI2c.TransmittedData().read();
    EXPECT_EQ(c, 0x86);
    //Write Two Random Values
    EXPECT_EQ(mockI2c.TransmittedData().available(), 0);
    device.writePots(22, 37);
    EXPECT_EQ(mockI2c.TransmittedData().available(), 2);
    c = mockI2c.TransmittedData().read();
    EXPECT_EQ(c, 0x00 | 22);
    c = mockI2c.TransmittedData().read();
    EXPECT_EQ(c, 0x40 | 37);
    //Write Two Random Values
    EXPECT_EQ(mockI2c.TransmittedData().available(), 0);
    device.writePots(42, 16);
    EXPECT_EQ(mockI2c.TransmittedData().available(), 2);
    c = mockI2c.TransmittedData().read();
    EXPECT_EQ(c, 0x00 | 42);
    c = mockI2c.TransmittedData().read();
    EXPECT_EQ(c, 0x40 | 16);

    //Write Both To Mute
    EXPECT_EQ(mockI2c.TransmittedData().available(), 0);
    device.writePots(63, 63);
    EXPECT_EQ(mockI2c.TransmittedData().available(), 2);
    c = mockI2c.TransmittedData().read();
    EXPECT_EQ(c, 63);
    c = mockI2c.TransmittedData().read();
    EXPECT_EQ(c, 127);

    //Write Both To Full
    EXPECT_EQ(mockI2c.TransmittedData().available(), 0);
    device.writePots(0, 0);
    EXPECT_EQ(mockI2c.TransmittedData().available(), 2);
    c = mockI2c.TransmittedData().read();
    EXPECT_EQ(c, 0);
    c = mockI2c.TransmittedData().read();
    EXPECT_EQ(c, 0x40);
}
#include "../src/RoutingTable.h"
#include <iostream>
#include <vector>
#include <string>

// Utility function to convert an IP string to a uint32_t
uint32_t ipStringToUint(const std::string& ip) {
    uint32_t result;
    if (inet_pton(AF_INET, ip.c_str(), &result) != 1) {
        throw std::runtime_error("Invalid IP address format");
    }
    return result;
}

// Function to perform a single test case
int runTestCase(const std::string& ip, const std::string& expectedInterface, RoutingTable& routingTable) {
    uint32_t testIp = ipStringToUint(ip);
    auto result = routingTable.getRoutingEntry(testIp);

    std::cout << "Testing IP: " << ip << "\n";
    if (result) {
        std::cout << "Matched Interface: " << result->iface << "\n";
        if (result->iface == expectedInterface) {
            std::cout << "Test passed.\n";
            std::cout << "-------------------------\n";
            return 1;
        } else {
            std::cout << "Test failed. Expected interface: " << expectedInterface << "\n";
            std::cout << "-------------------------\n";
            return 0;
        }
    } else {
        if (expectedInterface == "none") {
            std::cout << "Test passed. No match as expected.\n";
            std::cout << "-------------------------\n";
            return 1;
        } else {
            std::cout << "Test failed. Expected interface: " << expectedInterface << "\n";
            std::cout << "-------------------------\n";
            return 0;
        }
    }
}

// Function to run all test cases
void runAllTests() {
    // Instantiate a RoutingTable (update the file path as needed)
    RoutingTable routingTable("tests/rtable.txt");

    // Define test cases
    std::vector<std::pair<std::string, std::string>> testCases = {
        // IP, Expected Interface
        {"192.168.1.15", "eth0"},
        {"10.123.45.67", "eth1"},
        {"172.20.5.1", "eth2"},
        {"8.8.8.8", "none"},
        {"192.168.2.100", "eth3"},
        {"172.16.0.1", "eth4"},
        {"10.0.0.5", "eth5"},
        {"192.168.1.0", "eth0"},
        {"192.168.1.255", "eth0"},
        {"169.254.1.1", "none"},
        {"0.0.0.0", "none"},
        {"255.255.255.255", "none"},
        {"11.11.11.11", "none"},
        {"8.8.4.4", "none"}
    };

    // Run each test case
    int passedTests = 0;
    for (const auto& [ip, expectedInterface] : testCases) {
        int temp = runTestCase(ip, expectedInterface, routingTable);
        passedTests += temp;
    }

    if (passedTests == testCases.size()) {
        std::cout << "\033[1;32mPassed " << passedTests << "/" << testCases.size() << " tests.\033[0m\n"; // Green text
    } else {
        std::cout << "\033[1;31mPassed " << passedTests << "/" << testCases.size() << " tests.\033[0m\n"; // Red text
    }

}

int main() {
    runAllTests();
    return 0;
}

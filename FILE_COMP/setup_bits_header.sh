#!/bin/bash

# Create directory in system include path
sudo mkdir -p /usr/local/include/bits

# Create the stdc++.h file
sudo tee /usr/local/include/bits/stdc++.h > /dev/null << 'EOF'
// Custom bits/stdc++.h for macOS
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

// STL Containers
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <iterator>

// STL Algorithms & Functions
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <bitset>

// C++ Language Support
#include <typeinfo>
#include <exception>
#include <memory>
#include <locale>
#include <array>
#include <tuple>
#include <random>
#include <chrono>
#include <valarray>

// C Standard Library headers
#include <cmath>
#include <complex>
#include <cassert>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <cwctype>
#include <climits>
#include <cstdint>
#include <cinttypes>
#include <regex>
#include <thread>
#include <mutex>
EOF

# Set appropriate permissions
sudo chmod 644 /usr/local/include/bits/stdc++.h

echo "Installation complete! You can now use #include <bits/stdc++.h> in your C++ programs."

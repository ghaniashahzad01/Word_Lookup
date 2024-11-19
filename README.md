# Word Lookup App using Trie and Bloom Filter

## Table of Contents
1. [Overview](#overview)
2. [Features](#features)
3. [Technologies Used](#technologies-used)
4. [Getting Started](#getting-started)
   - [Prerequisites](#prerequisites)
   - [Installation](#installation)
5. [How It Works](#how-it-works)
   - [Data Structures](#data-structures)
   - [Main Workflow](#main-workflow)
6. [UI Overview](#ui-overview)
7. [Example Usage](#example-usage)
8. [Code Structure](#code-structure)
9. [Contributing](#contributing)
10. [License](#license)

## Overview
This project implements a **Word Lookup App** that provides real-time word suggestions based on user input. It utilizes two powerful data structures:

- **Trie**: A tree-like data structure used for efficient prefix-based search.
- **Bloom Filter**: A probabilistic data structure to check whether an element is a member of a set with a small probability of false positives.

The app combines these two structures to provide fast word lookups and suggestions.

## Features
- **Word Suggestion**: As the user types, the app provides suggestions based on stored words.
- **Efficient Searching**: Utilizes Trie and Bloom Filter for fast lookups and minimal false positives.
- **Real-Time Feedback**: Word suggestions appear as the user types, ensuring a responsive experience.

## Technologies Used
- **C++**: Main programming language for backend logic.
- **Qt (Qt Widgets)**: For building the user interface (UI).
  
### Data Structures
- **Trie**: For efficient prefix matching.
- **Bloom Filter**: To check if a word exists with a chance of false positives.

## Getting Started

### Prerequisites
Ensure you have the following installed before getting started:
- **Qt 5.x or later**: Required to build and run the application.
- **C++ Compiler**: For compiling the project.
- **CMake** (optional): If you're managing the build process with CMake.

### Installation
1. Clone the repository:
    ```bash
    git clone https://github.com/your-username/word-lookup-app.git
    cd word-lookup-app
    ```

2. Open the project in **Qt Creator**:
    - Launch Qt Creator.
    - Open the `.pro` or `CMakeLists.txt` file from the project directory.

3. Build the project:
    - Click on the **Build** button in Qt Creator.
    - Ensure no compilation errors.

4. Run the application:
    - Click the **Run** button to launch the app.

## How It Works

### Data Structures
- **Trie**: The Trie is used to store and retrieve words efficiently based on prefixes. The app stores words by their first letter, making prefix searches fast.
- **Bloom Filter**: A probabilistic structure used for quick membership tests. It helps check if a word exists in the app's word set before performing a full Trie search.

### Main Workflow
- The user starts typing in the input field.
- The app performs a Trie-based search for words matching the current prefix.
- Simultaneously, the Bloom Filter is checked to verify if the word exists before adding it to the list of suggestions.
- Suggested words are updated in real-time as the user types.

## UI Overview
The main window includes:
- **Title Label**: Displays "Word Lookup App".
- **Input Field**: The user types in this field to get suggestions.
- **Suggestions List**: Displays word suggestions based on the user’s input.
- **Search Button**: Allows the user to trigger the search manually.

## Example Usage
1. Open the application.
2. Type a few letters in the input field (e.g., "app").
3. The app will show suggestions like "apple", "appreciate", etc.
4. As you continue typing, the suggestions will dynamically update.

## Code Structure
- **MainWindow.cpp**: Contains logic for handling UI interactions.
- **BloomFilter.cpp**: Defines the Bloom Filter class for efficient membership testing.
- **Trie.cpp**: Implements the Trie class for prefix-based word search.

## Contributing
Feel free to fork this repository and submit pull requests if you want to contribute. Please ensure your changes do not introduce bugs and pass existing tests.

## License
This project is licensed under the MIT License - see the LICENSE file for details.



#include "MainWindow.h"
#include <QApplication>


using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Initialize Trie and BloomFilter
    trie = new Trie();
    bloomFilter = new BloomFilter();

    // Setup UI and populate data
    setupUI();
    populateBloomFilterAndTrie();
    configureStyles();
}

void MainWindow::setupUI() {
    // Create main layout
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    // Title Label
    QLabel* titleLabel = new QLabel("Word Suggestion App", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet(
        "font-size: 24px; "
        "color: #2c3e50; "
        "font-weight: bold; "
        "margin: 15px;"
        );


    // Input Line Edit
    inputLineEdit = new QLineEdit(this);
    inputLineEdit->setPlaceholderText("Start typing to get suggestions...");

    // Suggestions List Widget
    suggestionListWidget = new QListWidget(this);

    // Search Button
    QPushButton* searchButton = new QPushButton("Search", this);
    searchButton->setObjectName("searchButton");

    // Add widgets to layout
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(inputLineEdit);
    mainLayout->addWidget(suggestionListWidget);
    mainLayout->addWidget(searchButton);

    // Set central widget
    setCentralWidget(centralWidget);

    // Connect signals
    connect(searchButton, &QPushButton::clicked, this, &MainWindow::onSearchButtonClicked);
    connect(inputLineEdit, &QLineEdit::textChanged, this, &MainWindow::onTextChanged);

    // Set window properties
    setWindowTitle("Word Suggestion App");
    resize(500, 600);
}

void MainWindow::configureStyles() {
    // Custom color gradient background
    setStyleSheet(

"QMainWindow {"
        "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, "
        "        stop:0 rgba(216, 241, 254, 255), "  // Light blue
        "        stop:1 rgba(255, 229, 204, 255));"   // Light peach
        "} "
        "QLineEdit {"
        "    padding: 10px; "
        "    font-size: 16px; "
        "    border: 2px solid #3498db; "
        "    border-radius: 10px; "
        "    background-color: white; "
        "} "
        "QListWidget {"
        "    background-color: rgba(255, 255, 255, 180); "
        "    border: 1px solid #95a5a6; "
        "    border-radius: 10px; "
        "} "
        "#searchButton {"
        "    background-color: #3498db; " // Blue background
        "    color: white; "              // White text
        "    padding: 10px; "
        "    border-radius: 10px; "
        "} "
        "#searchButton:hover {"
        "    background-color: #2980b9; " // Darker blue on hover
        "} "
);


}

void MainWindow::populateBloomFilterAndTrie() {
    // Words grouped by first letter
    vector<string> words = {
        // A words
        "apple", "amazing", "awesome", "angel", "adventure",
        "ant", "airport", "activity", "account", "art",
        "ask", "awake", "accept", "alphabet", "architect",

        // B words
        "banana", "beautiful", "bright", "brave", "butterfly",
        "ball", "book", "bottle", "branch", "boat",
        "butter", "bag", "breeze", "brother", "bake",

        // C words
        "cat", "computer", "coffee", "camera", "chocolate",
        "clock", "candy", "create", "courage", "climate",
        "clean", "crystal", "car", "calm", "cousin",

        // D words
        "dog", "dance", "dark", "dream", "delight",
        "diamond", "dragon", "drive", "dove", "dinner",
        "divine", "danger", "desire", "drum", "dawn",

        // E words
        "elephant", "earth", "energy", "example", "education",
        "enjoy", "environment", "early", "elegant", "explore",
        "engine", "emergency", "egg", "event", "elite",

        // F words
        "fish", "flower", "friend", "fun", "future",
        "forest", "faith", "fashion", "fame", "fool",
        "family", "focus", "fire", "fence", "feather",

        // G words
        "guitar", "grape", "great", "gather", "glow",
        "garden", "goose", "golf", "guilty", "grand",
        "glory", "goal", "gift", "gold", "giraffe",

        // H words
        "hello", "help", "happy", "house", "honey",
        "holiday", "horizon", "heaven", "hunger", "human",
        "hero", "history", "hospital", "harvest", "harmony",

        // I words
        "ice", "incredible", "imagine", "increase", "inspire",
        "idea", "influence", "identity", "invention", "integrity",
        "improve", "individual", "invite", "icecream", "instrument",

        // J words
        "juice", "journey", "jump", "joke", "jewel",
        "jungle", "justice", "join", "jazz", "jacket",
        "jogging", "jumpy", "jolly", "jogger", "jumpy",

        // K words
        "kite", "king", "kangaroo", "kitchen", "knowledge",
        "kind", "key", "kiss", "kitten", "keyboard",
        "knight", "knock", "knee", "kingdom", "kick",

        // L words
        "lion", "love", "light", "life", "language",
        "lemon", "luck", "laugh", "learning", "leader",
        "laptop", "lake", "loud", "look", "local",

        // M words
        "moon", "music", "mountain", "miracle", "moment",
        "mango", "magic", "make", "meal", "master",
        "moonlight", "motive", "mystery", "memory", "mouse",

        // N words
        "night", "nature", "news", "noise", "never",
        "nation", "nerd", "neat", "noble", "nurse",
        "new", "name", "neighbor", "navy", "network",

        // O words
        "orange", "ocean", "open", "opportunity", "owl",
        "out", "overcome", "order", "outcome", "observe",
        "organize", "object", "outfit", "oil", "oxygen",

        // P words
        "peace", "piano", "play", "power", "person",
        "pencil", "peaceful", "picture", "plenty", "project",
        "plan", "plant", "pride", "prayer", "product",

        // Q words
        "queen", "question", "quick", "quiet", "quality",
        "quiz", "quake", "quilt", "quarter", "quaint",
        "quarantine", "quote", "quantity", "quaint", "quiver",

        // R words
        "rose", "rain", "river", "right", "road",
        "run", "rely", "revolution", "reach", "relax",
        "read", "reflex", "rising", "respect", "routine",

        // S words
        "sun", "sea", "smile", "school", "soul",
        "star", "success", "salt", "snow", "study",
        "sound", "summer", "sister", "strength", "stop",

        // T words
        "tree", "time", "thought", "trust", "train",
        "toy", "thank", "temperature", "tiger", "tornado",
        "travel", "taste", "team", "treat", "text",

        // U words
        "under", "umbrella", "universe", "unique", "understand",
        "union", "unite", "urgent", "ultimate", "urban",
        "user", "use", "up", "utensil", "unreal",

        // V words
        "village", "voice", "value", "view", "vacation",
        "vocal", "vowel", "victory", "video", "vibe",
        "vivid", "venture", "volunteer", "vocal", "veteran",

        // W words
        "water", "wonder", "world", "work", "wish",
        "wave", "whisper", "wait", "worry", "weather",
        "wonderful", "week", "warm", "welcome", "walk",

        // X words
        "xenon", "x-ray", "xylophone", "xenophobic", "xenial",
        "xerox", "xander", "xenolith", "xenogenesis", "xmas",
        "x-stand", "xclusive", "x-factor", "xpress", "xact",

        // Y words
        "yellow", "yarn", "yoga", "yesterday", "young",
        "yell", "youth", "yield", "year", "yogurt",
        "yes", "yacht", "yellowish", "yawn", "yogic",

        // Z words
        "zebra", "zero", "zoo", "zodiac", "zenith",
        "zip", "zoom", "zeal", "zigzag", "zen",
        "zinc", "zest", "zombie", "zone", "zinger"
    };


    for (const string& word : words) {
        // Add to Trie
        trie->insert(word);

        // Add to Bloom Filter
        bloomFilter->add(word);

        // Categorize words by first letter
        char firstLetter = word[0];
        alphabetWords[firstLetter].push_back(word);
    }
}

void MainWindow::onTextChanged(const QString& text) {
    // Clear previous suggestions
    suggestionListWidget->clear();

    // Get input text
    string prefix = text.toLower().toStdString();

    if (prefix.empty()) return;

    // Get suggestions from Trie
    vector<string> suggestions = trie->getSuggestionsForPrefix(prefix);

    if (suggestions.empty()) {
        // If no suggestions, try to find words with similar first letter
        if (!prefix.empty()) {
            char firstLetter = prefix[0];
            if (alphabetWords.find(firstLetter) != alphabetWords.end()) {
                suggestionListWidget->addItem("No exact match. Similar words:");
                for (const string& word : alphabetWords[firstLetter]) {
                    suggestionListWidget->addItem(QString::fromStdString(word));
                }
            } else {
                suggestionListWidget->addItem("No suggestions available.");
            }
        }
    } else {
        // Add suggestions to list
        for (const string& suggestion : suggestions) {
            suggestionListWidget->addItem(QString::fromStdString(suggestion));
        }
    }
}

void MainWindow::onSearchButtonClicked() {
    string word = inputLineEdit->text().toLower().toStdString();

    if (word.empty()) {
        QMessageBox::warning(this, "Error", "Please enter a word.");
        return;
    }

    // Check if word exists in Trie
    vector<string> suggestions = trie->getSuggestionsForPrefix(word);

    if (suggestions.empty()) {
        // If no exact match, find similar words
        vector<string> similarWords = findSimilarWords(word);

        if (!similarWords.empty()) {
            QString message = "Word not found. Did you mean:\n";
            for (const string& similar : similarWords) {
                message += QString::fromStdString(similar) + "\n";
            }
            QMessageBox::information(this, "Suggestions", message);
        } else {
            // Show "No results found" message box if no results or similar words are found
            QMessageBox::information(this, "No Results Found", "No results found for the search.");
        }
    } else {
        // Display suggestions if found
        suggestionListWidget->clear();
        for (const string& suggestion : suggestions) {
            suggestionListWidget->addItem(QString::fromStdString(suggestion));
        }
    }
}

// Simple Levenshtein distance for finding similar words
vector<string> MainWindow::findSimilarWords(const string& word) {
    vector<string> similarWords;
    char firstLetter = word[0];

    // Check words with the same first letter
    if (alphabetWords.find(firstLetter) != alphabetWords.end()) {
        for (const string& dictWord : alphabetWords[firstLetter]) {
            int distance = 0;
            int minLen = min(word.length(), dictWord.length());

            // Calculate difference
            for (int i = 0; i < minLen; i++) {
                if (word[i] != dictWord[i]) {
                    distance++;
                }
            }

            // Add if distance is small (indicating similarity)
            if (distance <= 2) {
                similarWords.push_back(dictWord);
            }
        }
    }

    return similarWords;
}

MainWindow::~MainWindow() {
    delete trie;
    delete bloomFilter;
}
